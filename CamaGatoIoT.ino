#include <Arduino.h>
#include <WiFi.h>
#include <esp_sleep.h>
#include "HX711.h"
#include <HTTPClient.h>
#include <Preferences.h>
#include <senhas.h> /*este arquivo não sobe para o github, 
                      trata-se de senhas pessoais. siga os 
                      comentários abaixo para colocar suas 
                      senhas como se pede*/

#define debug  //descomente esta linha para debugar o código

// *******  WIFI  *******
const char* ssid = yourSSID ;  //substitua yourSSID por seu wifi entre aspas, exemplo:  "MINHACASA"
const char* pass =  yourPASS;  //substitua yourPASS por sua senha entre aspas, exemplo  "SU@53h@" 

// *******  Google sheet  *******
const char* scriptURL = yourScriptURL; // Substitua yourScriptURL pelo endereço de app  criado no google sheet
void connectWiFi(void);
void enviaParaGoogle(float peso, float temperatura, float bateria);

// *******  Automato  *******
int automato = 0;         
int automatoDebug = 0;
unsigned long contaPiscadaAnterior = 0;  // will store last time LED was updated
const long intervaloPiscada = 250;       // intervaloPiscada at which to blink (milliseconds)
unsigned long hiberna5min = 0;
const long interval5min = 5 * 60 * 1000;  // 5 minuto * segundo * milesegundos  total= 5 minuto.
int interval24h = 24 * 6;  // 24horas * 6 * (10)min, pois usa o numero de hibernações, a cada 10min para contar o tempo.
//int interval24h = 6;  // 24horas * 6 * (10)min, pois usa o numero de hibernações, a cada 10min para contar o tempo.
bool status_LED = false;
int contaPiscada = 0;

// ****** Hibernação  *****
const gpio_num_t TOUCH_WAKE_PIN = GPIO_NUM_2;  // ligar ao módulo touch
//const uint64_t SLEEP_TIME_US = 10ULL * 60 * 1000000ULL;  // minuto * segundo * microssengundos  total= 10 minutos
const uint64_t SLEEP_TIME_US = 1ULL * 10 * 1000000ULL;  // minuto * segundo * microssengundos  total= 10 segundos
esp_sleep_wakeup_cause_t wakeup_cause;
void goToSleep(void);

// *******  HX711  *******
#define HX711_DT 3   // terminal de dados
#define HX711_SCK 4  // terminal de clock
HX711 scale;
#define pesoMinimo 300            // g
#define pesoAlteracaoMinima 100   // 100g
RTC_DATA_ATTR float pesoAnterior = 0.0;  // RTC_DATA_ATTR -> não se perde na hibernação
RTC_DATA_ATTR uint32_t contadorSleep = 0;

Preferences prefs;  //  para gravar calibração.
float massaAtual;
float massaModulo;
float scalaPref;
float offsetPref;
float valorMassa(void);


// *******  Bateria  *******
#define PINO_BATERIA 1      // pino ADC usado para o divisor
const float R1 = 100000.0;  // ohms
const float R2 = 100000.0;  // ohms
float bateriaAtual;
float valorBateria(void);


// *******  BLYNK  *******
//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID YOUR_BLYNK_TEMPLATE_ID
#define BLYNK_TEMPLATE_NAME YOUR_BLYNK_TEMPLATE_NAME
#define BLYNK_AUTH_TOKEN YOUR_BLYNK_TEMPLATE_NAME
#include <BlynkMultiClient.h>
static WiFiClient blynkWiFiClient;
unsigned long startBlynkEnvio;
BLYNK_CONNECTED();
BLYNK_WRITE(V0);
BLYNK_WRITE(V1);


#ifdef debug
#define MySPrint(x) Serial.print(x)
#define MySPrintln(x) Serial.println(x)
#else
#define MySPrint(x)
#define MySPrintln(x)
#endif

void setup() {
  pinMode(2, INPUT_PULLDOWN);
  pinMode(TOUCH_WAKE_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  wakeup_cause = esp_sleep_get_wakeup_cause();

  Serial.begin(115200);
  delay(500);

  //Que atitude tomar de acordo de como acordou
  switch (wakeup_cause) {
    case ESP_SLEEP_WAKEUP_TIMER:  // Acordou por estouro de timer

      MySPrintln("Acordou por estouro de timer");
      massaAtual = valorMassa();
      if (massaAtual < pesoMinimo) {  // Se balança vazia.
        MySPrintln("Balanca vazia");
        delay(100);
        goToSleep();    // volta a hibernar
        break;
      };

      massaModulo = massaAtual - pesoAnterior;          // calcula a variação de massa.
      if (massaModulo < 0) massaModulo = -massaModulo;  // calcula o módulo variação de massa.
      if (massaModulo <= pesoAlteracaoMinima) {         // sem alteração significativa
        MySPrint("Peso anterior:");
        MySPrintln(pesoAnterior);
        MySPrintln("Sem alteração de massa significativa, não enviar");
        if (contadorSleep > interval24h) {
          MySPrintln("Estouro de 24 horas");
          pesoAnterior = 0;  //permite reentrada apos 24h
          contadorSleep = 0; // reinicia contagem de 24h +/-
        }
        delay(100);
        goToSleep();
        break;
      };

      bateriaAtual = valorBateria();   // obtem tensão da bateria
      MySPrintln("Conectando Wifi");
      connectWiFi();                    // conecta wifi  
      MySPrintln("Enviando para a GOOGLE");
      enviaParaGoogle(massaAtual / 1000, 0, bateriaAtual); // envia para o google 
      MySPrintln("Conectando BLYNK");
      Blynk.addClient("WiFi", blynkWiFiClient, 80);
      Blynk.config(BLYNK_AUTH_TOKEN);
      while (!Blynk.connect()) delay(250);
      MySPrintln("Enviando BLYNK");
      Blynk.virtualWrite(V8, massaAtual / 1000);
      Blynk.virtualWrite(V9, massaAtual / 1000);
      Blynk.virtualWrite(V4, bateriaAtual);
      startBlynkEnvio = millis();                  // Dá tempo para a pilha TCP enviar tudo
      while (millis() - startBlynkEnvio < 1000) {  // aguarda ~1 segundo
        Blynk.run();
        delay(10);
      }
      MySPrintln("Hiberna");
      pesoAnterior = massaAtual;  //evita reentrada se massa for semelhante
      delay(100);
      goToSleep();
      break;

    case ESP_SLEEP_WAKEUP_GPIO:
      MySPrintln("Acordou por gpio");
      hiberna5min = millis();
      if (WiFi.status() != WL_CONNECTED) connectWiFi();
      automato = 1;
      break;

    case ESP_SLEEP_WAKEUP_UNDEFINED:
      MySPrintln("Acordou por causa indefinida");
      delay(100);
      goToSleep();
      break;

    default:
      Serial.printf("Wakeup reason: %d\n", wakeup_cause);
      delay(100);
      goToSleep();
      break;
  }
}





void loop() {
  unsigned long currentMillis = millis();
  // timer para piscar led
  if (currentMillis - contaPiscadaAnterior >= intervaloPiscada && contaPiscada > 0) {
    contaPiscadaAnterior = currentMillis;
    if (status_LED) {
      status_LED = false;
      digitalWrite(LED_BUILTIN, status_LED);
      contaPiscada--;
    } else {
      status_LED = true;
      digitalWrite(LED_BUILTIN, status_LED);
    }
  }

  //Timer para hiberna depois de 5 minutos sem interação com usuário
  if ((wakeup_cause == ESP_SLEEP_WAKEUP_GPIO) && (currentMillis - hiberna5min >= interval5min)) { 
    MySPrintln("Hiberna 5 min");
    delay(100);
    goToSleep();
  }


  switch (automato) {
    case 1:
      if (WiFi.status() == WL_CONNECTED) {
        Blynk.addClient("WiFi", blynkWiFiClient, 80);
        Blynk.config(BLYNK_AUTH_TOKEN);
        automato = 2;
      }
      break;

    case 2:
    //terminar aqui
      //apenas aguarda conecção
      //sai desta parte do automato atravez da função BLYNK_CONNECTED
      if (WiFi.status() != WL_CONNECTED) connectWiFi();
      
      Blynk.run();
      break;

    case 3:
      // futura expansão do código
      Blynk.run();
      break;
  }

  if (automato != automatoDebug) {  // debug para programador acompanhar o automato
    automatoDebug = automato;
    MySPrint("automato = ");
    MySPrintln(automato);
  }
}


void enviaParaGoogle(float peso, float temperatura, float bateria) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(scriptURL);
    http.addHeader("Content-Type", "application/json");
    String jsonData = "{\"peso\": " + String(peso) + ", \"temperatura\": " + String(0) + ", \"bateria\": " + String(bateria) + "}";
    int httpResponseCode = http.POST(jsonData);
    MySPrint("Código HTTP: ");
    MySPrintln(httpResponseCode);
    http.end();
  }
}


float valorMassa(void) {
  do {
    scale.begin(HX711_DT, HX711_SCK);
    MySPrintln("inicializando  HX711");
    delay(100);
  } while (!scale.is_ready());

  MySPrintln("Calibrando...");
  prefs.begin("config", false);

  do {
    scalaPref = prefs.getFloat("scalaPref_", -1);  // verifica se ja tem valor gravado na memória
    offsetPref = prefs.getFloat("offsetPref_", -1);
    MySPrint("scalaPref: ");
    MySPrintln(scalaPref);
    MySPrint("offsetPref: ");
    MySPrintln(offsetPref);
    if (scalaPref < 0) {
      prefs.putFloat("scalaPref_", 173.870163);  // Se não tem, grava valor definido em tempo de produção
      MySPrintln("Ajustando escala pela primeira vez");
    }
    if (offsetPref < 0) {
      prefs.putFloat("offsetPref_", 172004);  // Se não tem, grava valor definido em tempo de produção
      MySPrintln("Ajustando offset pela primeira vez");
    }
  } while (scalaPref < 0 || offsetPref < 0);

  scale.set_scale(scalaPref);
  scale.set_offset(offsetPref);  //calibrando
  MySPrintln("Pesando...");
  scale.power_up();
  delay(100);
  float leitura = scale.get_units(10);  // média de 10 leituras
  MySPrint("Peso: ");
  MySPrint(leitura);
  MySPrintln("g");
  return leitura;
}


float valorBateria(void) {
  analogReadResolution(12);  // 12 bits (0-4095)
  int leitura = analogRead(PINO_BATERIA);
  float tensao_adc = (leitura / 4095.0) * 3.3;  // tensão no pino
  float tensao_bateria = tensao_adc * ((R1 + R2) / R2);
  MySPrint("ADC: ");
  MySPrint(leitura);
  MySPrint("  |  Tensão da bateria: ");
  MySPrint(tensao_bateria);
  MySPrintln(" V");
  return tensao_bateria;
}


void connectWiFi(void) {
  MySPrint("Connecting to ");
  MySPrintln(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    MySPrint(".");
  }
}

void goToSleep(void) {
  Blynk.disconnect();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  esp_deep_sleep_enable_gpio_wakeup((1ULL << TOUCH_WAKE_PIN), ESP_GPIO_WAKEUP_GPIO_HIGH);  //
  esp_sleep_enable_timer_wakeup(SLEEP_TIME_US);
  contadorSleep = contadorSleep + 1;  // opcional: timer backup
  MySPrint("Entrando em deep sleep n");
  MySPrintln(contadorSleep);
  MySPrintln("\n");
  digitalWrite(HX711_SCK, HIGH);  // Coloca HX711 em Power Down
  digitalWrite(LED_BUILTIN, LOW);
  delay(10);
  esp_deep_sleep_start();
}


BLYNK_CONNECTED() {
  MySPrintln("blink conectado");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  contaPiscada = 5;
  hiberna5min = millis();
  automato = 3;
}


BLYNK_WRITE(V0) {  //PESA
  int value = param.asInt();
  MySPrint("V0 acionado: ");
  MySPrintln(value);
  MySPrintln("Enviando dados para BLYNK");//RTC_DATA_ATTR float taraVolatil = 0;
  bateriaAtual = valorBateria();
  massaAtual = valorMassa();
  if (massaAtual > pesoMinimo) {
    MySPrintln("Enviando dados para BLYNK");
    Blynk.virtualWrite(V8, massaAtual / 1000);
  } else {
    MySPrintln("Não atingio valor minimo para envio");
  }
  Blynk.virtualWrite(V9, massaAtual / 1000);
  Blynk.virtualWrite(V4, bateriaAtual);
  Blynk.virtualWrite(V0, 0);

  if (massaAtual > pesoMinimo) {
    MySPrintln("Enviando dados para google");
    enviaParaGoogle(massaAtual / 1000, 0, bateriaAtual);
  } else {
    MySPrintln("Não atingio valor minimo para envio");
  }
  hiberna5min = millis();
  contaPiscada = 2;
}

BLYNK_WRITE(V1) {  // TARA A BALANÇA
  int value = param.asInt();
  MySPrint("V1 acionado: ");
  MySPrintln(value);
  scale.tare();
  prefs.begin("config", false);
  float taraTemp = scale.get_offset();
  prefs.putFloat("offsetPref_", taraTemp);  // grava a nova tara no
  MySPrintln("Ajustando offset por comando do Blynk");
  bateriaAtual = valorBateria();
  Blynk.virtualWrite(V9, 0);
  Blynk.virtualWrite(V4, bateriaAtual);
  Blynk.virtualWrite(V1, 0);
  hiberna5min = millis();
  contaPiscada = 2;
}
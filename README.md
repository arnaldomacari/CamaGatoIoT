![Banner do Projeto](images/banner_cama_gato_iot.png)

<p align="center">
  <span style="font-size:18px; color:blue; font-style:italic;">
    <b>Monitoramento automático de peso e comportamento de felinos com ESP32-C3 Super Mini, HX711 e integração com Google Sheets e Blynk.</b>
  </span>
</p>

---

<p align="center">
  <a href="https://github.com/arnaldomacari/CamaGatoIoT/stargazers"><img src="https://img.shields.io/github/stars/arnaldomacari/CamaGatoIoT?style=for-the-badge" alt="Stars"></a>
  <a href="https://github.com/arnaldomacari/CamaGatoIoT/issues"><img src="https://img.shields.io/github/issues/arnaldomacari/CamaGatoIoT?style=for-the-badge" alt="Issues"></a>
  <a href="https://github.com/arnaldomacari/CamaGatoIoT"><img src="https://img.shields.io/github/last-commit/arnaldomacari/CamaGatoIoT?style=for-the-badge" alt="Last Commit"></a>
  <img src="https://img.shields.io/badge/ESP32--C3-Firmware-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow?style=for-the-badge">
  <a href="LICENSE"><img src="https://img.shields.io/badge/Licença-MIT-green?style=for-the-badge"></a>
</p>

---

## 📘 Resumo

O projeto **Cama de Gato com Balança IoT** propõe o monitoramento automatizado do peso de felinos domésticos, permitindo detectar variações corporais associadas a condições fisiológicas ou patológicas. O sistema usa uma base com **células de carga e módulo HX711**, controlados por um **ESP32-C3** que opera em deep sleep para economizar energia e desperta periodicamente para coletar e enviar dados.

As medições são transmitidas automaticamente para:
- uma **planilha no Google Sheets**, que mantém o histórico e facilita análises;
- o **aplicativo Blynk**, onde o tutor acompanha leituras em tempo real e dispara medições manuais.

---

## 🧠 Objetivos

- Detectar variações sutis de peso corporal em gatos, indicando possíveis doenças metabólicas ou alterações alimentares.
- Desenvolver um sistema de monitoramento contínuo, não invasivo, de baixo custo e com conectividade em nuvem.
- Contribuir para estudos e práticas de bem-estar animal e telemetria veterinária.

---

## 📝 Justificativa

De acordo com dados do Instituto Pet Brasil, em matéria de LUCCA (2025) publicado no  Correio Braziliense, estima-se que os lares brasileiros já abrigam mais de 30 milhões de gatos. Já a ABINPET (2025) aponta um crescimento previsto de cerca de 3,5% para o setor pet em 2025, com um faturamento que pode chegar a R$ 78 bilhões. Apesar desse cenário de expansão, estudo com 19 milhões de gatos nos Estados Unidos mostraram que 52% deles tiveram a saúde acompanhada apenas uma vez durante a vida, sendo o peso corporal um dos indicadores mais simples e importantes (CAMPIGOTTO et al., 2019), o mesmo estudo também elaborou uma curva de peso em função da idade, que pode servir de base em consultas veterinárias. O controle do peso corporal também tem relação direta com a longevidade dos pets. Segundo Pennell et al. (2019), em labradores com mais de dez anos de idade, um desvio de apenas 1 kg no peso aumentava em 19% a probabilidade de morte do animal. E finalizando, segundo matéria da University of Guelph (2019), pequenas variações no peso corporal de gatos podem indicar problemas de saúde subjacentes, reforçando a importância do monitoramento contínuo do peso ao longo da vida do animal, recomendando a aquisição de balanças. Alterações discretas no peso corporal são, muitas vezes, os primeiros sinais de enfermidades em felinos e tendem a passar despercebidas em rotinas domésticas convencionais. Ao unir sensores de baixo custo, computação embarcada eficiente e integração com plataformas de visualização de dados, o projeto possibilita acompanhamento longitudinal, embasando decisões veterinárias mais rápidas e assertivas. A solução também serve como prova de conceito para tutorizar práticas de bem-estar animal apoiadas por IoT, incentivando a comunidade a adaptar e expandir o sistema conforme necessidades específicas.

---

## ⚙️ Arquitetura do Sistema

![Circuito_principal](images/mermaid.png)

---

## 🧰 Escolha de Materiais



## 🧩 Componentes Utilizados

| Componente                   | Função                         | Observações                              |
| ---------------------------- | ------------------------------ | ---------------------------------------- |
| **ESP32-C3**                 | Microcontrolador principal     | Comunicação Wi-Fi e deep sleep           |
| **HX711**                    | Conversor ADC 24 bits          | Leitura das células de carga             |
| **Células de carga**         | Sensor de peso                 | Montadas em ponte de Wheatstone          |
| **Sensor capacitivo**        | Interação do usuário           | Acorda o sistema do modo de hibernação   |
| **Divisor resistivo (R1=R2)**| Monitoramento da bateria       | Lido pelo ADC do ESP32-C3                |
| **Fonte/Bateria 5V ou LiPo** | Alimentação                    | Requer estabilidade para leituras precisas |
| **Google Apps Script**       | Integração com planilha        | Recebe POST JSON do ESP32-C3             |
| **Blynk App (Free Tier)**    | Interface do usuário           | Widgets V0, V1, V4, V8 e V9 configurados |
| **Placa perfurada 7cm x 3cm**| Aletrnativa a placa CI         | Suporte aos modulos no 1° teste          |

---

## ⚡ Circuitos
### Visão geral da conexão entre ESP32-C3, HX711, células de carga e alimentação.

![Circuito_principal](images/circuito_principal.png)

---

## 🖼️ Imagens do Protótipo
### Partes mecânicas
#### Célula de carga

![Acessorios_Celula_de_Carga](images/acessorios_celula_de_carga01.png)
![Acessorios_Celula_de_Carga](images/acessorios_celula_de_carga02.png)

![Acessorios_Celula_de_Carga](images/acessorios_celula_de_carga03.png)
![Acessorios_Celula_de_Carga](images/acessorios_celula_de_carga04.png)

#### Caixa de circuitos
![Acessorios_Celula_de_Carga](images/caixa01.png)
![Acessorios_Celula_de_Carga](images/caixa02.png)

![Acessorios_Celula_de_Carga](images/caixa03.png)
![Acessorios_Celula_de_Carga](images/caixa04.png)

![Acessorios_Celula_de_Carga](images/caixa05.png)


### Partes eletrônica
#### Teste em protoboard.
![Protoboard](images/protoboard.png)


#### Circuito para teste final.
![Placa](images/prototipo_final.png)


#### Base pequena para teste de bancada.
![Protoboard](images/base_por_cima.png)
![Protoboard](images/base_por_baixo.png)


#### Finalizando
![Protoboard](images/caixa06.png)
![Protoboard](images/caixa07.png)


---

## 🔄 Funcionamento

- A cada ~10 minutos o ESP32-C3 acorda do deep sleep.
- Verifica se há peso ≥ 300 g acima da tara; caso contrário volta a dormir.
- Se detectar massa relevante, compara com a última leitura enviada:
  - se passaram ≥ 24 h ou houve variação ≥ 100 g, registra o novo valor;
  - envia peso e nível de bateria para o Google Sheets e para o Blynk.
- O usuário pode acordar o sistema com o botão capacitivo para:
  - solicitar uma nova pesagem manual (widget `V0`);
  - tarar a balança (widget `V1`).
- Sem interação manual, o dispositivo volta a dormir após ~5 minutos acordado.

---

## 🛠️ Requisitos de Software

- Arduino IDE ≥ 2.0 ou PlatformIO com suporte a ESP32-C3.
- Bibliotecas:
  - [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32) (inclui `WiFi`, `Preferences`, `esp_sleep`).
  - [HX711](https://github.com/bogde/HX711).
  - [Blynk](https://github.com/blynkkk/blynk-library) (com `BlynkMultiClient`).
- Conta Google com acesso ao Apps Script e Google Sheets.
- Conta Blynk (Free Tier compatível).


### Bibliotecas instaladas na Arduino IDE
![Protoboard](images/biblioteca01.png)
![Protoboard](images/biblioteca02.png)
---

## 🚀 Como Começar

1. **Monte o prototipo seguindo as imagens acima**

2. **Clonar o repositório**
   ```bash
   git clone https://github.com/arnaldomacari/CamaGatoIoT.git
   cd CamaGatoIoT
   ```

3. **Criar `senhas.h`** (não versionado) na raiz do projeto:
   ```cpp
   #define yourSSID "NOME_DA_REDE"
   #define yourPASS "SENHA_DA_REDE"
   #define yourScriptURL "https://script.google.com/macros/s/SEU_APP/exec"

   #define YOUR_BLYNK_TEMPLATE_ID "TMPLxxxx"
   #define YOUR_BLYNK_TEMPLATE_NAME "Nome do Template"
   #define YOUR_BLYNK_AUTH_TOKEN "token_do_dispositivo"
   ```

---

4. **Selecionar a placa e compilar**
   - Na IDE, escolha a placa; para este projeto optou-se pela **NoLogo ESP32-C3 Super Mini** 
   - Ajuste a porta serial e compile.
   - Faça upload e monitore a serial a 115200 bps (ativando `#define debug` para logs detalhados).

![Protoboard](images/NoLogo_ESP32-C3_super_mini.png)


5. **Calibração e Operação**

A própria biblioteca do **RobTillaart** para HX711 fornece um exemplo para calibrar sua balança. 

![Calibracao](images/calibracao.png)

- Abra o exemplo,  
- ajuste as linhas **13 e 14** como mostrado abaixo 
```cpp
  - uint8_t dataPin = 3;  
  - uint8_t clockPin = 4;
```
- Grave a sketch no esp32. 
- Com o auxilio de um **peso conhecido**, sigas as intruções mostradas no Monito Serial da IDE arduino.  
  - Se o monitor serial não estiver aparecendo, use **Ctrl + Shift + M** para abrir o monitor.
  - Se estiver usando um ESP com conexão direta com a USB, como o **ESP32-c3 Super Mini** coloque um **delay** apos iniciar a porta serial

```cpp
void setup()
{
  Serial.begin(115200);
  delay(1000);  //  espera Serial Monito se conectar na USB Serial 
```

- Ao final, será mostrado os **valores de calibração** similar a :

```cpp
WEIGHT: 3000
SCALE:  135.926117

use **scale.set_offset(253466)**; and **scale.set_scale(135.926117)**;
in the setup of your project 
```

- Substitua os valores no código **CamaGatoIoT.ino** como mostrado abaixo:

```cpp
// Calibração em tempo de projeto
#define scalaPrefIni 135.926117
#define offsetPrefIni 253466
```
Na primeira vez que usar ou toda vez que mudar algo sobre a base, como uma cama nova, tare a balança usando o app blynk

---


6. **Configurar o Blynk**
   - Crie um template com widgets:
     - `V0` botão momentâneo (Pesagem manual).
     - `V1` botão momentâneo (Tara).
     - `V4` display numérico (Tensão da bateria).
     - `V5` botão momentâneo (Desligar circuito eletrônico).
     - `V8` display numérico (Peso atual em kg).
     - `V9` gráfico ou histórico (Últimos envios em kg).
   - Copie `Template ID`, `Template Name` e `Auth Token` para `senhas.h`.

![Protoboard](images/appBlynk.jpeg)

7. **Publicar o Google Apps Script**
   - Crie uma planilha e um Apps Script para receber POST com JSON (`peso`, `temperatura`, `bateria`). 


```javascript
function doPost(e) {
  var sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Página1");
  var data = JSON.parse(e.postData.contents);

  sheet.appendRow([
    new Date(),
    data.peso,
    data.temperatura, //reservado para futuros testes
    data.bateria
  ]);

  // --- Atualiza sempre a célula fixa com o último valor ---
  // --- Utilizado para mostrar o último valor no gráfico de medidor e no geral
  sheet.getRange("G1").setValue(new Date());
  sheet.getRange("H1").setValue(data.peso);
  sheet.getRange("I1").setValue(data.temperatura); //reservado para futuros testes
  sheet.getRange("J1").setValue(data.bateria);

  return ContentService
           .createTextOutput("OK")
           .setMimeType(ContentService.MimeType.TEXT);
}
```


   - Publique como aplicação web acessível a qualquer pessoa com o link.
   - Cole a URL gerada em `yourScriptURL` em  **senhas.h**.
  


## 🔋 Ajuste da Curva da Tensão da Bateria

O monitoramento da bateria utiliza o ADC do ESP32-C3 lendo um divisor resistivo. Para que a tensão exibida no Blynk e no Google Sheets corresponda ao valor real, foi feito um ajuste de curva:

| Blynk (V) | Multímetro (V) | Equação Ajustada (V) | Erro (V) |
| --------: | -------------: | -------------------: | -------: |
| 4,42      | 4,14           | 4,15                 | -0,02    |
| 4,30      | 3,94           | 3,96                 | -0,02    |
| 3,94      | 3,52           | 3,53                 | -0,01    |
| 3,19      | 2,95           | 2,94                 | 0,01     |
| 3,04      | 2,81           | 2,80                 | 0,01     |

![Calibracao](images/calibracao_bateria.png)

```cpp
float valorBateria(void) {
  analogReadResolution(12);  // 12 bits (0-4095)
  int leitura = analogRead(PINO_BATERIA);
  float tensao_adc = (leitura / 4095.0) * 3.3;  // AD de 12bits para 3.3V
  float x = tensao_adc * ((R1 + R2) / R2);      // Compensa o divisor de tensão
  float tensao_bateria = -19.2 + 17.6*x + -4.78*x*x + 0.451*x*x*x;  // Corrige valores lidos usando 
                                                                    // uma curva cúbica e tendo como  
                                                                    // referência as leituras de 
                                                                    // um multímetro
```                                                                    

Esse procedimento garante que alertas de bateria baixa e gráficos históricos representem fielmente a autonomia do sistema.


## 💾 Estrutura do Repositório

- `CamaGatoIoT.ino` – firmware principal com máquina de estados, leituras e integrações.
- `senhas.h` – credenciais locais (exemplo acima, mantenha fora do versionamento).
- `images/` – diagramas e fotos do protótipo (adicione `banner_cama_gato_iot.png` e demais imagens).
- `LICENSE` – licença MIT.

---



## 📊 Exemplo de Planilha Google

- Campos sugeridos: `timestamp`, `peso_kg`, `bateria_v`, a temperatura será usada em uma expansão futura.

![Protoboard](images/grafico.png)

---

## 🧪 Testes e Métricas Atuais

**Ainda em execução**

---

## 📚 Referências

- ABINPET. **Setor pet projeta crescer apenas 3,5% em 2025, com faturamento de R$ 78 bilhões.** 2025. Disponível em: https://www.gov.br/agricultura/pt-br/assuntos/camaras-setoriais-tematicas/documentos/camaras-setoriais/animais-e-estimacao/2025/43a-ro-15-07-2025/release-projecao1tri25-setor-pet.pdf.  Acesso em: 26 out. 2025.

- CAMPIGOTTO, Adam J. et al. Investigation of relationships between body weight and age among domestic cats stratified by breed and sex. **Journal Of The American Veterinary Medical Association**, [S.L.], v. 255, n. 2, p. 205-212, 15 jul. 2019. American Veterinary Medical Association (AVMA). http://dx.doi.org/10.2460/javma.255.2.205.  Disponível em: https://avmajournals.avma.org/view/journals/javma/255/2/javma.255.2.205.xml. Acesso em: 03 nov. 2025.. Acesso em: 03 nov. 2025.

- LUCCA,B. **Adoção de gatos aumenta no Brasil e 30 milhões de felinos têm um lar.** 2025. Correio Braziliense. Disponível em: Adoção de gatos aumenta no Brasil e 30 milhões de felinos têm um lar. Acesso em: 26 out. 2025.

- PENELL, Johanna Christina; MORGAN, David Mark; WATSON, Penny; CARMICHAEL, Stuart; ADAMS, Vicki Jean. Body weight at 10 years of age and change in body composition between 8 and 10 years of age were related to survival in a longitudinal study of 39 Labrador retriever dogs. **Acta Veterinaria Scandinavica**, [S.L.], v. 61, n. 1, p. 42-48, 9 set. 2019. Springer Science and Business Media LLC. http://dx.doi.org/10.1186/s13028-019-0477-x . Disponível em: https://actavetscand.biomedcentral.com/articles/10.1186/s13028-019-0477-x . Acesso em: 26 out. 2025.

- **UNIVERSITY OF GUELPH**. U of G researchers first to track how cats’ weight changes over time. Guelph: University of Guelph News, 24 jul. 2019. Disponível em: https://news.uoguelph.ca/2019/07/u-of-g-researchers-first-to-track-how-cats-weight-changes-over-time/. Acesso em: 3 nov. 2025.


---

## 👨‍🔬 Autor

**Arnaldo José Macari**  
Engenheiro de Alimentos e Desenvolvedor de Sistemas Embarcados  
São José do Rio Preto – SP, Brasil

---

## 🪪 Licença

Distribuído sob a licença MIT. Consulte o arquivo [`LICENSE`](LICENSE) para mais informações.

---

## 🤝 Contribuição

Contribuições são bem-vindas! Abra uma issue ou envie um pull request com melhorias no firmware, documentação ou design mecânico.

<p align="center">
  <sub>Desenvolvido com ❤️ e curiosidade científica – integrando IoT, automação e bem-estar animal.</sub>
</p>

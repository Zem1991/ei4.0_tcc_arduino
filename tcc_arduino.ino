// Definir o pino analógico onde o sensor está conectado
const int lm35Pin = A0;

void setup() {
  // Iniciar a comunicação serial para exibir os dados
  Serial.begin(9600);
}

void loop() {
  // Ler o valor analógico do pino A0 (de 0 a 1023)
  int sensorValue = analogRead(lm35Pin);

  // Converter o valor analógico (0-1023) para milivolts (0-5000mV)
  // A fórmula é (sensorValue / 1023) * 5000 (mV)
  // Também pode ser escrito como sensorValue * 5000 / 1023
  float voltage = sensorValue * (5000.0 / 1023.0);

  // Converter a tensão em graus Celsius
  // O LM35 fornece 10 mV por grau Celsius, então dividimos a tensão por 10
  float temperatureC = voltage / 10.0;

  // Exibir os resultados no Monitor Serial
  Serial.print("Valor Lido: ");
  Serial.print(sensorValue);
  Serial.print(" | Tensao: ");
  Serial.print(voltage);
  Serial.print(" mV | Temperatura: ");
  Serial.print(temperatureC);
  Serial.println(" C");

  // Esperar um segundo antes da próxima leitura
  delay(1000);
}

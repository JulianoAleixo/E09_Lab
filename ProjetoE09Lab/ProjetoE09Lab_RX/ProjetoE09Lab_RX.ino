void setup() {
  Serial.begin(9600);
  Serial.println("Receptor iniciado. Aguardando dados...");
}

void loop() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    Serial.print(c);
  }
}

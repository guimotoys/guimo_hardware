// Função para identificar obstáculos (Guimo Autônomo)

void guimo_Autonomo() {
  int distance, duration;
  digitalWrite(trigPin, HIGH);
  delay(200);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2)/29.1;
  Serial.println("");
  Serial.println(distance);
  auto_Frente();
  if (distance < 22) {
    auto_Esquerda();
  }
}

void auto_Frente() {
  iniciar_Motor();
  motorDireita.write(0);
  motorEsquerda.write(180);
  delay(150);
  Serial.println("Frente");
}

void auto_Esquerda() {
  rotacao_Parado();
  iniciar_Motor();
  motorDireita.write(0);
  motorEsquerda.write(0);
  delay(150);
  Serial.println("Esquerda");
}
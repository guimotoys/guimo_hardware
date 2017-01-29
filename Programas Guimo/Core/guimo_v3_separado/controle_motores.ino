// Função para iniciar os motores

void iniciar_Motor() {
  motorDireita.attach(10);
  motorEsquerda.attach(11);
}

// Função para parar os motores
void rotacao_Parado() {
  motorDireita.detach();
  motorEsquerda.detach();
}

// Função que para ir para frente
void rotacao_Frente() {
  iniciar_Motor();
  motorDireita.write(0);
  motorEsquerda.write(180);
  delay(500);
  Serial.println("Frente");
  MinhaSerial.println("Frente");
  rotacao_Parado();
}

// Função que faz ir para trás
void rotacao_Re() {
  iniciar_Motor();
  motorDireita.write(180);
  motorEsquerda.write(0);
  delay(500);
  rotacao_Parado();
  }

// Função que faz virar para direita
void rotacao_Direita() {
  iniciar_Motor();
  motorDireita.write(180);
  motorEsquerda.write(180);
  delay(500);
  rotacao_Parado();
}

// Função que faz virar para esquerda
void rotacao_Esquerda() {
  iniciar_Motor();
  motorDireita.write(0);
  motorEsquerda.write(0);
  delay(500);
  Serial.println("Esquerda");
  rotacao_Parado();
}

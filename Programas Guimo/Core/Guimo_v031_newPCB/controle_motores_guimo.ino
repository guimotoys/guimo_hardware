// Fun��o para iniciar os motores

void iniciar_Motor() {
  motorDireita.attach(5);
  motorEsquerda.attach(6);
}

// Fun��o para parar os motores
void rotacao_Parado() {
  motorDireita.detach();
  motorEsquerda.detach();
}

// Fun��o que para ir para frente
void rotacao_Frente() {
  iniciar_Motor();
  motorDireita.write(0);
  motorEsquerda.write(180);
  delay(500);
  Bluetooth.println("Frente");
  rotacao_Parado();
}

// Fun��o que faz ir para tr�s
void rotacao_Re() {
  iniciar_Motor();
  motorDireita.write(180);
  motorEsquerda.write(0);
  delay(500);
  rotacao_Parado();
  }

// Fun��o que faz virar para direita
void rotacao_Direita() {
  iniciar_Motor();
  motorDireita.write(180);
  motorEsquerda.write(180);
  delay(500);
  rotacao_Parado();
}

// Fun��o que faz virar para esquerda
void rotacao_Esquerda() {
  iniciar_Motor();
  motorDireita.write(0);
  motorEsquerda.write(0);
  delay(500);
  rotacao_Parado();
}

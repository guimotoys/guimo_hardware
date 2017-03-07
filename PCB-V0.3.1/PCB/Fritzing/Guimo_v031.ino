#include <Arduino.h>

// Descri��o das Portas Utilizadas
// Digitais: 2,3,5,6,7
// Anal�gicas: 
// Por Perif�rico: Ultrassom(D2,D3); Bluetooh(D5,D6); ResistorCorpo(D7); Motores(D10,D11);   

#include <SoftwareSerial.h>
#include<Wire.h>
#include<Servo.h>

#define echoPin 2
#define trigPin 3

char bufB;  //Buffer de comunica��o do Bluetooh
char buf;  //Buffer de comunica��o com a Cabe�a (arduino com arduino)
const int MPU=0x68;  
int AcX,AcY,AcZ; 
int corpo = 7;
int val = 0;
int pinoSensor = A6;
int valorSensor = 0;
long randNumber;

Servo motorDireita, motorEsquerda;

// Define os pinos para a serial  (RX, TX)
SoftwareSerial MinhaSerial(6,5);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(corpo, INPUT);

  //Inicia a serial 
  Serial.begin(9600); 
  Serial.println("Dados recebidos :"); 
  
  MinhaSerial.begin(9600);
 
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);

} 
    
void loop() 
{     
  val = digitalRead(corpo);
  if (val > 0)
  {
    MinhaSerial.println("carrinho");
  }

  buf = Serial.read();

  if (buf == '1')
  {
    MinhaSerial.println("guimo");
  }

  if (buf == '2')
  {
    MinhaSerial.println("robo");
  }
  
// A��es Bluetooh
//------------------------------------------------------------------  
  while(MinhaSerial.available() > 0)
  {
    bufB = MinhaSerial.read();
    
// Troca de tela
    if (bufB == 'g')
    {
      MinhaSerial.println("g");
      Serial.println("g");
    }
    
    if (bufB == 'a')
    {
      acelerometro();
    }
    
// Programa��o para controlar os movimentos do Guimo   
    if (bufB == 'f')
    {
      MinhaSerial.println("Avante GUIMO");
      Serial.println("Avante GUIMO");
      rotacao_Frente();
      while(MinhaSerial.available() > 0)
      bufB = MinhaSerial.read();
    }
    
    if (bufB == 'l')
    {
      MinhaSerial.println("Esquerda");
      Serial.println("Esquerda");
      rotacao_Esquerda();
      while(MinhaSerial.available() > 0)
      bufB = MinhaSerial.read();
    }
    
    if (bufB == 'r')
    {
      MinhaSerial.println("Direita");
      Serial.println("Direita");
      rotacao_Direita();
      while(MinhaSerial.available() > 0)
      bufB = MinhaSerial.read();
    }
    
    if (bufB == 'b')
    {
      MinhaSerial.println("Tras");
      Serial.println("Tras");
      rotacao_Re();
      while(MinhaSerial.available() > 0)
      bufB = MinhaSerial.read();
    }

// A fun��o Aut�nomo s� come�ar� quando o Guimo receber "u"
    if (bufB == 'u')
    {
      guimo_Autonomo();
    }

// A fun��o Segue-linha s� come�ar� quando o Guimo receber "s"
//    if (bufB == 's')
//    {
//      valorSensor = analogRead(pinoSensor);
//      if (valorSensor > 50)
//      {
//        segue_Linha();
//        Serial.println("Linha Detectada");
//        delay(1000);
//      }
//    }
  }
}
//------------------------------------------------------------------


// Reinicia o programa do in�cio, mas n�o reseta os perif�ricos e os registros
void software_Reset() 
{
  asm volatile ("jmp 0");
}  

// Fun��o para o Guimo seguir uma linha
//void segue_Linha() {
//  if (valorSensor > 50){
//    rotacao_Frente();
//  }
//  
//}
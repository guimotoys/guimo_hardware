#include <Arduino.h>
#include <Narcoleptic.h>

// Descrição das Portas Utilizadas
// Digitais: 2,3,5,6,7
// Analógicas: 
// Por Periférico: Ultrassom(D2,D3); Bluetooh(D5,D6); ResistorCorpo(D7); Motores(D10,D11);   

#include <SoftwareSerial.h>
#include<Wire.h>
#include<Servo.h>

#define echoPin 2
#define trigPin 3

char bufB;  //Buffer de comunicação do Bluetooh
char buf;  //Buffer de comunicação com a Cabeça (arduino com arduino)
const int MPU=0x68;  
int AcX,AcY,AcZ; 
int corpo = 7;
int val = 0;
int pinoSensor = A6;
int valorSensor = 0;

Servo motorDireita, motorEsquerda;

// Define os pinos para a serial  (RX, TX)
SoftwareSerial SerialHC06(6,5);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(corpo, INPUT);

  //Inicia a serial 
  Serial.begin(9600); 
  Serial.println("Dados recebidos :"); 
  
  SerialHC06.begin(9600);
 
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
    SerialHC06.println("carrinho");
  }

  buf = Serial.read();

  if (buf == '1')
  {
    SerialHC06.println("guimo");
  }

  if (buf == '2')
  {
    SerialHC06.println("robo");
  }
  
// Ações Bluetooh
//------------------------------------------------------------------  
  while(SerialHC06.available() > 0)
  {
    bufB = SerialHC06.read();
    
// Troca de tela
    if (bufB == 'g')
    {
      SerialHC06.println("g");
      Serial.println("g");
    }
    
    if (bufB == 'a')
    {
      acelerometro();
    }
    
// Programação para controlar os movimentos do Guimo   
    if (bufB == 'f')
    {
      SerialHC06.println("Avante GUIMO");
      Serial.println("Avante GUIMO");
      rotacao_Frente();
//      while(SerialHC06.available() > 0)
//      bufB = SerialHC06.read();
    }
    
    if (bufB == 'l')
    {
      SerialHC06.println("Esquerda");
      Serial.println("Esquerda");
      rotacao_Esquerda();
//      while(SerialHC06.available() > 0)
//      bufB = SerialHC06.read();
    }
    
    if (bufB == 'r')
    {
      SerialHC06.println("Direita");
      Serial.println("Direita");
      rotacao_Direita();
//      while(SerialHC06.available() > 0)
//      bufB = SerialHC06.read();
    }
    
    if (bufB == 'b')
    {
      SerialHC06.println("Tras");
      Serial.println("Tras");
      rotacao_Re();
//      while(SerialHC06.available() > 0)
//      bufB = SerialHC06.read();
    }

// A função Autônomo só começará quando o Guimo receber "u"
    if (bufB == 'u')
    {
      guimo_Autonomo();
    }

// A função Segue-linha só começará quando o Guimo receber "s"
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


// Reinicia o programa do início, mas não reseta os periféricos e os registros
void software_Reset() 
{
  asm volatile ("jmp 0");
}  

// Função para o Guimo seguir uma linha
//void segue_Linha() {
//  if (valorSensor > 50){
//    rotacao_Frente();
//  }
//  
//}

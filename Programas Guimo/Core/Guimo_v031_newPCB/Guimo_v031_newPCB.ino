#include <Arduino.h>
#include <SoftwareSerial.h>
#include<Wire.h>
#include<Servo.h>

//#define echoPin 2
//#define trigPin 3

char bufBlue[20]; //vetor de char
int num = 0;  //variavel para setar a primeira posição do vetor de char
String dados; 

//char bufB;  //Buffer de comunica��o do Bluetooh
//char buf;  //Buffer de comunica��o com a Cabe�a (arduino com arduino)
const int MPU=0x68;  
int AcX,AcY,AcZ; 
//int corpo = 7;
int val = 0;
//int pinoSensor = A6;
int valorSensor = 0;
long randNumber;

Servo motorDireita, motorEsquerda;

// Define os pinos para a serial  (TX, RX)
SoftwareSerial Bluetooth(3,4);

void setup() {
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
//  pinMode(corpo, INPUT);

  //Inicia a serial 
  Serial.begin(9600); 
//  Serial.println("Dados recebidos :"); 
  
  Bluetooth.begin(9600);
 
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);

} 
    
//void loop() 
//{     
////  val = digitalRead(corpo);
////  if (val > 0)
////  {
////    Bluetooth.println("carrinho");
////  }
//
//  buf = Serial.read();
//
//  if (buf == '1')
//  {
//    Bluetooth.println("guimo");
//  }
//
//  if (buf == '2')
//  {
//    Bluetooth.println("robo");
//  }
//  
// A��es Bluetooh
//------------------------------------------------------------------  
void loop() 
{
  // put your main code here, to run repeatedly:
   while(Bluetooth.available() > 0)
   {
//      comandosBluetooth();
      bufBlue[num] = Bluetooth.read();
      if(bufBlue[num]=='\n')
      {
//        Serial.println(bufBlue);
//        Bluetooth.println(bufBlue);
        String dados = bufBlue;
        dados.trim();
 //       Serial.println(dados);
        Bluetooth.println(dados);
        
  if (dados == "f")
    {
      Bluetooth.println("Avante GUIMO");
      rotacao_Frente();
//      while(Bluetooth.available() > 0)
//     bufBlue = Bluetooth.read()
    }
      
    if (dados == "b")
    {
      Bluetooth.println("Tras");
      rotacao_Re();
//      while(Bluetooth.available() > 0)
//      bufBlue = Bluetooth.read();
    }
      
    if (dados == "r")
    {
      Bluetooth.println("Direita");
      rotacao_Direita();
//      while(Bluetooth.available() > 0)
//      bufBlue = Bluetooth.read();
    }
     
    if (dados == "l")
    {
      Bluetooth.println("Esquerda");
      rotacao_Esquerda();
//      while(Bluetooth.available() > 0)
//      bufBlue = Bluetooth.read();
    }
   
    if (dados == "0")
    {
      Serial.print("0");
    }

    if (dados == "1")
    {
      Serial.println("1");
    }

    if (dados == "2")
    {
      Serial.println("2\n");
    }

    if (dados == "3")
    {
      Serial.print("3\n");
    }
 
    if (dados == "4")
    {
      Serial.print("4\n");
    }

    if (dados == "5")
    {
      Serial.println("5");
    }

    if (dados == "6")
    {
      Serial.println("6");
    }

    if (dados == "7")
    {
      Serial.println("7");
    }

    if (dados == "8")
    {
      Serial.println("8");
    }

    if (dados == "9")
    {
      Serial.println("9");
    }

    if (dados == "10")
    {
      Serial.println("10");
    }

    if (dados == "11")
    {
      Serial.println("11");
    }

    if (dados == "12")
    {
      Serial.println("12");
    }

    if (dados == "13")
    {
      Serial.println("13");
    }
    
    if (dados == "14")
    {
      Serial.println("14");
    }

    if (dados == "lanche")
    {
      Serial.print("lanche.bmp\n"); 
    }

    if (dados == "maca")
    {
      Serial.println("maca.bmp\n"); 
    }

    if (dados == "refri")
    {
      Serial.println("refri.bmp\n"); 
    }

    if (dados == "suco")
    {
      Serial.println("suco.bmp\n"); 
    }

    if (dados == "pedra")
    {
      Serial.println("pedra.bmp\n"); 
    }

    if (dados == "tesoura")
    {
      Serial.println("tesoura.bmp\n"); 
    }

    if (dados == "papel")
    {
      Serial.println("papel.bmp\n"); 
    }

    if (dados == "menina")
    {
      Serial.println("menina.bmp\n"); 
    }

    if (dados == "bigode")
    {
      Serial.println("bigode.bmp\n"); 
    }

    if (dados == "fome")
    {
      Serial.println("fome.bmp\n"); 
    }

    if (dados == "oculos")
    {
      Serial.println("oculos.bmp\n"); 
    }

    if (dados == "inverso")
    {
      Serial.println("inverso.bmp\n"); 
    }

    if (dados == "lingua")
    {
      Serial.println("lingua.bmp\n"); 
    }

    if (dados == "doente")
    {
      Serial.println("doente.bmp\n"); 
    }

    if (dados == "remedio")
    {
      Serial.println("remedio.bmp\n"); 
    }

    if (dados == "carinho")
    {
      Serial.println("carinho.bmp\n"); 
    }

    if (dados == "padrao")
    {
      Serial.println("padrao.bmp\n");
    }

    if (dados == "robo")
    {
      Serial.println("robo.bmp\n");
    }    
    
        //Limpar o vetor de char
        for (int ca =0; ca<20; ca++)
        {
           bufBlue[ca]=0;
        }
        num=0;
        break;
       }
      num++;
    } 
}
  
//------------------------------------------------------------------


// Reinicia o programa do in�cio, mas n�o reseta os perif�ricos e os registros
void software_Reset() 
{
  asm volatile ("jmp 0");
}  

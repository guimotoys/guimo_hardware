//char bufBlue[20]; //vetor de char
//int num = 0;  //variavel para setar a primeira posição do vetor de char
//String dados; 

void comandosBluetooth()
{
   bufBlue[num] = Bluetooth.read();
      if(bufBlue[num]=='\n')
      {
        Serial.println(bufBlue);
        Bluetooth.println(bufBlue);
        String dados = bufBlue;
        dados.trim();
        Bluetooth.println(dados);
        if(dados=="acel")
        {
          acelerometro();
          Serial.println("acelerometro");
          Bluetooth.println("acelerometroBluetooth");
        }
        if(dados=="fui")
        {
          Bluetooth.println("DeuBOOOOM");
        }
        //Limpar o vetor de char
        for (int ca =0; ca<20; ca++)
        {
           bufBlue[ca]=0;
        }
        num=0;
//        break;
       }
      num++;
//  String dados = bufBlue;
//  Serial.println("entrou");
//  Bluetooth.println(dados);
//  Serial.println(dados);
//  Serial.println(dados);
//  Serial.println(dados);
//  Serial.println(dados);
//  Serial.println(dados);
//  
//  
//        if(dados=="fui ")
//        {
//          Serial.println("acelerometro");
//          Bluetooth.println("DeuBom");
//        }
//      
//  if (bufBlue == "forward            ")
//    {
//      Bluetooth.println("Avante GUIMO");
//      rotacao_Frente();
//      while(Bluetooth.available() > 0)
//     bufBlue = Bluetooth.read()
//    }
      
//    if (dados = "back")
//    {
//      Bluetooth.println("Tras");
//      rotacao_Re();
////      while(Bluetooth.available() > 0)
////      bufBlue = Bluetooth.read();
//    }
//      
//    if (dados = "right")
//    {
//      Bluetooth.println("Direita");
//      rotacao_Direita();
////      while(Bluetooth.available() > 0)
////      bufBlue = Bluetooth.read();
//    }
//     
//    if (dados = "left")
//    {
//      Bluetooth.println("Esquerda");
//      rotacao_Esquerda();
////      while(Bluetooth.available() > 0)
////      bufBlue = Bluetooth.read();
//    }
//   
////    if (dados = "0")
////    {
////      Serial.println("0");
////    }
////
////    if (dados = "1")
////    {
////      Serial.println("1");
////    }
////
////    if (dados = "2")
////    {
////      Serial.println("2");
////    }
////
////    if (dados = "3")
////    {
////      Serial.println("3");
////    }
//// 
////    if (dados = "4")
////    {
////      Serial.println("4");
////    }
////
////    if (dados = "5")
////    {
////      Serial.println("5");
////    }
////
////    if (dados = "6")
////    {
////      Serial.println("6");
////    }
////
////    if (dados = "7")
////    {
////      Serial.println("7");
////    }
////
////    if (dados = "8")
////    {
////      Serial.println("8");
////    }
////
////    if (dados = "9")
////    {
////      Serial.println("9");
////    }
////
////    if (dados = "10")
////    {
////      Serial.println("10");
////    }
////
////    if (dados = "11")
////    {
////      Serial.println("11");
////    }
////
////    if (dados = "12")
////    {
////      Serial.println("12");
////    }
////
////    if (dados = "13")
////    {
////      Serial.println("13");
////    }
////    
////    if (dados = "14")
////    {
////      Serial.println("14");
////    }
//
//    if (dados = "guimoHamburguer")
//    {
//      Serial.println("guimoHamburguer"); 
//    }
//
//    if (dados = "guimoMaca")
//    {
//      Serial.println("guimoMaca"); 
//    }
//
//    if (dados = "guimoRefrigerante")
//    {
//      Serial.println("guimoRefrigerante"); 
//    }
//
//    if (dados = "guimoSuco")
//    {
//      Serial.println("guimoSuco"); 
//    }
//
//    if (dados = "guimoPedra")
//    {
//      Serial.println("guimoPedra"); 
//    }
//
//    if (dados = "guimoTesoura")
//    {
//      Serial.println("guimoTesoura"); 
//    }
//
//    if (dados = "guimoPapel")
//    {
//      Serial.println("guimoPapel"); 
//    }
//
//    if (dados = "guimoMenina")
//    {
//      Serial.println("guimoMenina"); 
//    }
//
//    if (dados = "guimoBigode")
//    {
//      Serial.println("guimoBigode"); 
//    }
//
//    if (dados = "guimoFome")
//    {
//      Serial.println("guimoFome"); 
//    }
//
//    if (dados = "guimoOculos")
//    {
//      Serial.println("guimoOculos"); 
//    }
//
//    if (dados = "guimoPontaCabeca")
//    {
//      Serial.println("guimoPontaCabeca"); 
//    }
//
//    if (dados = "guimoLinguaDeFora")
//    {
//      Serial.println("guimoLinguaDeFora"); 
//    }
//
//    if (dados = "guimoDoente")
//    {
//      Serial.println("guimoDoente"); 
//    }
//
//    if (dados = "guimoPotion")
//    {
//      Serial.println("guimoPotion"); 
//    }
//
//    if (dados = "guimoCarinho")
//    {
//      Serial.println("guimoCarinho"); 
//    }
    
}


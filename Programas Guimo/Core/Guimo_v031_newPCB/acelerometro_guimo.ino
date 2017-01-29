void acelerometro() 
{
  
          Wire.beginTransmission(MPU);
          Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
          Wire.endTransmission(false);
      
          //Solicita os dados do sensor
          Wire.requestFrom(MPU,14,true);  
      
          //Armazena o valor dos sensores nas variaveis correspondentes
          AcX=Wire.read()<<8|Wire.read(); //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
          AcY=Wire.read()<<8|Wire.read(); //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
          //AcZ=Wire.read()<<8|Wire.read(); //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
      
          //Mostra os valores na serial
          Bluetooth.print(AcX);  Bluetooth.println(";"); 
          Bluetooth.print(AcY);  Bluetooth.println(";"); 
          //Bluetooth.print(AcZ);  Bluetooth.println(";"); 
          Serial.print(AcX);  Serial.println(";"); 
          Serial.print(AcY);  Serial.print(";"); 
          //Serial.print(AcZ);  Serial.println(";"); 
     
          //Aguarda 300 ms e reinicia o processo
          delay(33);
          
          //Reset Arduino
          if(AcX == 0)
          {
            software_Reset();
          }

          //Identifica se o Guimo está de ponta cabeça
          if(AcY < -10000)
          {
            Serial.println("inverso.bmp/n");
          }
}
}

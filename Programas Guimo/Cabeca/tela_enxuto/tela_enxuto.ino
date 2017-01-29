#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Narcoleptic.h>

#define LCD_RST A4
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define SD_CS 10  // Set the chip select line to whatever you use (10 doesnt conflict with the library)

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RST);

char buf;
char bufCore[20]; //vetor de char
int num = 0;  //variavel para setar a primeira posição do vetor de char
String dados; 

void setup()
{
  Serial.begin(9600);
  tft.reset();
  tft.begin(0x7575);

  Serial.print(F("Initializing SD card..."));
  if (!SD.begin(SD_CS)) {
    Serial.println(F("failed!"));
    return;
  }
  
  Serial.println(F("OK!"));
  
  tft.setRotation(1);
  tft.fillScreen(0);

  bmpDraw("padrao.bmp", 0, 0);

}

void loop()
{
  
  while(Serial.available() > 0)
  {

     bufCore[num] = Serial.read();
      if(bufCore[num]=='\n')
      {
        tft.setRotation(1);
//        Serial.println(bufCore);
        bufCore[num]=0;           // Zera o \n para não imprimir
        bmpDraw(bufCore, 0, 0);
        delay(500);
        String dados = bufCore;
        dados.trim();
        if (dados == "1"||dados == "2"||dados == "3"||dados == "4"||dados == "5")
        //Após a entrevista da globo adicionei os dados de 5 a 14
        {
        Text(dados);
        }
        //Limpar o vetor de char
        for (int ca =0; ca<20; ca++)
        {
           bufCore[ca]=0;
        }
        num=0;
        break;
       }
    num++;
  }
}

#define BUFFPIXEL 20

void bmpDraw(char *filename, int x, int y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = false;        // BMP is stored bottom-to-top
  uint16_t w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');
  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.println(F("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.println(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = true;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...
          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each column...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              // Push LCD buffer to the display first
              if(lcdidx > 0) {
                tft.pushColors(lcdbuffer, lcdidx, first);
                lcdidx = 0;
                first  = false;
              }
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = tft.color565(r,g,b);
          } // end pixel
        } // end scanline
        // Write any remaining data to LCD
        if(lcdidx > 0) {
          tft.pushColors(lcdbuffer, lcdidx, first);
        } 
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}

unsigned long Text(String dados){
  tft.fillScreen(BLACK);
  tft.setRotation(3);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE);  
  tft.setTextSize(5);
  if (dados == "0")
  {
    tft.setTextSize(5);
    tft.println("MUITO bem e voce?");
  }
  if (dados == "1")
  {
    tft.setTextSize(5);
    tft.println("Melhor ");
    tft.println("agora, ");
    tft.println("vamos ");
    tft.println("brincar?");
  }  
//  if (dados == "2")
//  {
//    tft.setTextSize(4);
//    tft.println("Poderia estar");
//    tft.println("melhor, estou");
//    tft.println("muito sozinho");
//    tft.setCursor(140,150);
//    tft.setRotation(2);
//    tft.setTextSize(6);
//    tft.println(":(");
//  }
//  if (dados == "3")
//  {
//    tft.setTextSize(4);
//    tft.println("Estou de pe.");
//    tft.println("Nao esta me");
//    tft.println("vendo nao?");
//  }  
//  if (dados == "4")
//  {
//    tft.setTextSize(4);
//    tft.println("Mim estar bem ");
//    tft.setTextSize(3);
//    tft.println("Desculpa, ");
//    tft.println("estou me ");
//    tft.println("acostumando ");
//    tft.println("com o ");
//    tft.println("Portugues.");
//  }  
    if (dados == "2")
  {
    tft.setTextSize(4);
    tft.println("Eu sabia, ");
    tft.println("mas agora ");
    tft.println("eu esqueci.");
    tft.setCursor(140,150);
    tft.setRotation(2);
    tft.setTextSize(6);
    tft.println(":(");
  }
  if (dados == "3")
  {
    tft.setTextSize(5);
    tft.println("Um ");
    tft.println("planeta");
    tft.println("muito ");
    tft.println("distante.");
  }  
//  if (dados == "7")
//  {
//    tft.setTextSize(4);
//    tft.println("Da loja de ");
//    tft.println("brinquedos, ");
//    tft.println("oras bolas.");
//  }
//  if (dados == "8")
//  {
//    tft.setTextSize(4);
//    tft.println("Eu vim da");
//    tft.println("Guimolandia,");
//    tft.println("tenho saudade");
//    tft.println("de la.");
//    tft.setCursor(140,80);
//    tft.setRotation(2);
//    tft.setTextSize(6);
//    tft.println(":(");
//  }  
//  if (dados == "9")
//  {
//    tft.setTextSize(4);
//    tft.println("Tambem ");
//    tft.println("queria saber. ");
//    tft.println("Me ajuda ");
//    tft.println("a descobrir?");
//  }  
    if (dados == "4")
  {
    tft.setTextSize(5);
    tft.println("Sim, vamos");
    tft.println("jogar um");
    tft.println("jogo?");
    tft.setCursor(140,80);
    tft.setRotation(2);
    tft.setTextSize(6);
    tft.println(":)");
  }
//  if (dados == "")
//  {
//    tft.setTextSize(4);
//    tft.println("Eu sempre ");
//    tft.println("quero fazer");
//    tft.println("alguma coisa.");
//    tft.setCursor(140,150);
//    tft.setRotation(2);
//    tft.setTextSize(6);
//    tft.println("|)");
//  }  
  if (dados == "5")
  {
    tft.setTextSize(5);
    tft.println("So se ");
    tft.println("for agora.");
    tft.setCursor(120,150);
    tft.setRotation(2);
    tft.setTextSize(6);
    tft.println(":P");
  }
//  if (dados == "13")
//  {
//    tft.setTextSize(4);
//    tft.println("So depois ");
//    tft.println("que eu comer.");
//    tft.println("Estou com ");
//    tft.println("muita fome.");
//  }  
//  if (dados == "14")
//  {
//    tft.setTextSize(4);
//    tft.println("Que tal");
//    tft.println("depois de ");
//    tft.println("tirarmos um");
//    tft.println("cochilo?");
//    tft.setCursor(150,150);
//    tft.setRotation(2);
//    tft.setTextSize(6);
//    tft.println(":P");
//  }  
  return micros() - start;
  dados = "";
}

//||dados == "5"||dados == "6"||dados == "7"||dados == "8"||dados == "9"||dados == "10"||dados == "11"||dados == "12"||dados == "13"||dados == "14"

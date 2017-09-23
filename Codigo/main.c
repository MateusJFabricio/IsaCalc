// Programa: IsaCalc
// by Mateus Fabricio - 2017
 
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>    
#include <SD.h>
#include <SPI.h>
 
#define SD_CS 10

#define YP A1 // Y+ is on Analog1 (use A3 para o 9341)
#define XM A2 // X- is on Analog2 (use A2 para o 9341)
#define YM 7 // Y- is on Digital7 (use 9 para o 9341)
#define XP 6 // X+ is on Digital6 (use 8 para o 9341)

#define SOMA          1
#define SUBTRACAO     2
#define MULTIPLICACAO 3
#define DIVISAO       4

Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 100);

int CliqueX = 0;
int CliqueY = 0;

void EscreveTFT(String frase, int x, int y, int t, String cor, int tempo)
{
  if      (cor == "PRETO")    {tft.setTextColor(0x0000);}
  else if (cor == "AZUL")     {tft.setTextColor(0x001F);}
  else if (cor == "VERMELHO") {tft.setTextColor(0xF800);}
  else if (cor == "VERDE")    {tft.setTextColor(0x07E0);}
  else if (cor == "CIANO")    {tft.setTextColor(0x07FF);}
  else if (cor == "MAGENTA")  {tft.setTextColor(0xF81F);}
  else if (cor == "AMARELO")  {tft.setTextColor(0xFFE0);}
  else if (cor == "BRANCO")   {tft.setTextColor(0xFFFF);};
  tft.setTextSize(t);
  tft.setCursor(x, y);
  tft.println(frase);
  delay(tempo);
}

void setup()
{
  Serial.begin(9600);
  //Inicializa o display
    tft.reset();
    delay(500);
    uint16_t identifier = tft.readID();
    identifier == 0x9325;
    tft.begin(identifier);
    tft.fillScreen(0x0000);
    tft.setRotation(3);
  //Inicializa cartão de memória
  EscreveTFT("Carregando cartao SD...", 10, 100, 2,"BRANCO", 1000); 
  EscreveTFT("Carregando cartao SD...", 10, 100,2, "PRETO", 0); 
    while (!SD.begin(SD_CS)) { 
      EscreveTFT("Falha ao carregar cartao.", 10, 100,2, "BRANCO", 2000);
      EscreveTFT("Falha ao carregar cartao.", 10, 100,2, "PRETO", 100);
    }
    EscreveTFT("Cartao carregado", 10, 100,2, "BRANCO", 1000);
  
  //Tela de inicialização
  bmpDraw("imagem1.bmp", 0, 0);
  delay(5000);
  bmpDraw("imagem6.bmp", 0, 0);
  delay(500);
}
void ConfiguraImpressao(){
  
}
void ImprimeNumeroCalc(String *Dig, String val, bool direita)
{
  //Apaga caso o valor seja um operador
  if (*Dig == "+" || *Dig == "-" || *Dig == "x" || *Dig == "/"){
    ApagaDigitadoCalc(Dig);  }
  tft.setRotation(0);
  EscreveTFT(*Dig, 15, 20, 3, "PRETO", 0);
  if (direita == 1){
    *Dig = *Dig + val;}
  else{
    *Dig = val + *Dig;}
  EscreveTFT(*Dig, 15, 20, 3, "BRANCO", 0);
  tft.setRotation(3);
}
void ApagaDigitadoCalc(String *Digitado)
{
  tft.setRotation(0);
  tft.fillRect(0, 0,240, 320-277, 0x0000);
  *Digitado = "";
  tft.setRotation(3);
}
 float fRetornaValor(String *Valor){
  String Digitado = *Valor;
  //BackSpace
  if (GetClique(181, 63, 222, 118, 500)==1 && Digitado.length() > 0)
  {
    int i;
    String Memoria = "";
    tft.setRotation(0);
    EscreveTFT(Digitado, 15, 20, 3, "PRETO", 0);
    for(i=0; i < Digitado.length() - 1; i++)
    {
      Memoria = Memoria + Digitado.charAt(i);
    }
    EscreveTFT(Memoria, 15, 20, 3, "BRANCO", 0);
    tft.setRotation(3);
    Digitado = Memoria;
  };
  //Limita a quantidade digitada para 9 digitos
  if (Digitado.length() <= 9){
    //Clicou btn 1
    if (GetClique(45, 8, 86, 61, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "1", 1);
    };
    //Clicou btn 2
    if (GetClique(45, 64, 85, 116, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "2", 1);
    };
    //Clicou btn 3
    if (GetClique(43, 120, 84, 172, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "3", 1);
    };
    //Clicou btn 4
    if (GetClique(91, 10, 131, 61, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "4", 1);
    };
    //Clicou btn 5
    if (GetClique(89, 64, 131, 117, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "5", 1);
    };
    //Clicou btn 6
    if (GetClique(90, 119, 130, 173, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "6", 1);
    };
    //Clicou btn 7
    if (GetClique(137, 9, 175, 61, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "7", 1);
    };
    //Clicou btn 8
    if (GetClique(135, 65, 176, 116, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "8", 1);
    };
    //Clicou btn 9
    if (GetClique(136, 120, 174, 170, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "9", 1);
    };
    //Clicou btn 0
    if (GetClique(0, 10, 39, 117, 500)==1)
    {
      ImprimeNumeroCalc(&Digitado, "0", 1);
    };
  };
  //Clicou btn +-
  if (GetClique(181, 119, 220, 173, 500)==1)
    {
      Serial.print(Digitado);
      //inicia com menos
      if (Digitado.indexOf("-") >= 0 ){
        tft.setRotation(0);
        EscreveTFT(Digitado, 15, 20, 3, "PRETO", 0);
        Digitado.remove(0, 1);
        EscreveTFT(Digitado, 15, 20, 3, "BRANCO", 0);
        tft.setRotation(3); 
      }else{
        ImprimeNumeroCalc(&Digitado, "-", 0);
      };
    };
    
  *Valor = Digitado;
  return Digitado.toFloat();
}
float RetornaCalculo(float Valor1, float Valor2, int iOperacao){
  switch (iOperacao){
    case SOMA:
      return Valor1 + Valor2;
      break;
    
    case SUBTRACAO:
      return Valor1 - Valor2;
      break;
      
    case DIVISAO:
      return Valor1 / Valor2;
      break;
      
    case MULTIPLICACAO:
      return Valor1 * Valor2;
      break;
  }
}
void imprimeResultado(float R)
{
  tft.setRotation(0);
  tft.setTextSize(3);
  tft.setTextColor(0x001F);
  tft.setCursor(15, 20);
  tft.println(R);
  tft.setRotation(3);
}
        
void TelaCalculadora()
{
  String Digitado = "";
  int iRodada = 1;
  int iOperacao = 0; // Soma  = 1; Subtração = 2; Multiplicação = 3; Divisao = 4 ; Default = 0;
  float Valor1, Valor2, Resultado, ValorMemoria = 0;
  bmpDraw("imagem3.bmp", 0, 0);
  while(1==1){
    //------------------Retorna para o menu
    if (GetClique(181, 8, 220, 61, 500)==1)
    {
      return;
    };
    //------------Finaliza Retorna para o menu
    //-----------Retorna os valores digitados
    Valor2 = fRetornaValor(&Digitado);
    if (iRodada == 1){
      Valor1 = fRetornaValor(&Digitado);}
      
    //Clicou em =
    if (GetClique(2, 172, 40, 230, 500)==1)
    {
      if (iRodada == 2){
        Resultado = RetornaCalculo(Valor1, Valor2, iOperacao);
        Valor1 = Resultado;
        ApagaDigitadoCalc(&Digitado);
        imprimeResultado(Resultado);
      }
    }  
    //-----------Botão de Reset de operação
    //Clicou btn C
    if (GetClique(227, 10, 265, 62, 500)==1)
      {
        ApagaDigitadoCalc(&Digitado);
        Valor1 = 0.0;
        Valor2 = 0.0;
        Digitado = "";
        iRodada = 1;
      };
    //-----------Finaliza Botão de Reset de operação
    //-----------Pega operador de operação
    //Clicou btn +
    if (GetClique(44, 173, 85, 229, 500)==1)
      {
        ApagaDigitadoCalc(&Digitado);
        ImprimeNumeroCalc(&Digitado, "+",1);
        //Soma
        iOperacao = SOMA;
        iRodada = 2;
      };
    //Clicou btn -
    if (GetClique(91, 175, 130, 229, 500)==1)
      {
        ApagaDigitadoCalc(&Digitado);
        ImprimeNumeroCalc(&Digitado, "-", 1);
        //Subtrai
        iOperacao = SUBTRACAO;
        iRodada = 2;
      };
    //Clicou btn x
    if (GetClique(137, 175, 177, 230, 500)==1)
      {
        ApagaDigitadoCalc(&Digitado);
        ImprimeNumeroCalc(&Digitado, "x", 1);
        //Multiplica
        iOperacao = MULTIPLICACAO;
        iRodada = 2;
      };
    //Clicou btn /
    if (GetClique(182, 175, 220, 230, 500)==1)
      {
        ApagaDigitadoCalc(&Digitado);
        ImprimeNumeroCalc(&Digitado, "/", 1);
        iOperacao = DIVISAO;
        iRodada = 2;
      };
    //-----------Finaliza a Pega do operador de operação  
    //------------Botões de controle de Memória  
    //Clicou btn MC
    if (GetClique(224, 64, 265, 115, 500)==1)
      {
        ValorMemoria = 0;
      };
    //Clicou btn MR
    if (GetClique(226, 119, 266, 172, 500)==1)
      {
        Valor2 = ValorMemoria;
        ApagaDigitadoCalc(&Digitado);
        imprimeResultado(ValorMemoria);
      };
    //Clicou btn M+
    if (GetClique(225, 176, 263, 227, 500)==1)
      {
        ValorMemoria = Resultado;
      };
    //------------Finaliza Botões de controle de Memória  
   }
}
void TelaJogo()
{
  //-----------------------------------------------
  bmpDraw("imagem5.bmp", 0, 0);
  int i = 0;
  EscreveTFT(String(i), 50, 100, 12,"BRANCO", 0);
  while (1==1){
    //Incrementa
    if (GetClique(1, 55, 320, 240, 100)){
      EscreveTFT(String(i), 50, 100, 12,"PRETO", 0);
      i++;
      EscreveTFT(String(i), 50, 100, 12,"BRANCO", 0);
    }
    //Decrementa
    if (GetClique(50, 2, 96, 31, 300)){
      EscreveTFT(String(i), 50, 100, 12,"PRETO", 0);
      i--;
      EscreveTFT(String(i), 50, 100, 12,"BRANCO", 0);
    }
    //Zera
    if (GetClique(4, 11, 45, 31, 300)){
      EscreveTFT(String(i), 50, 100, 12,"PRETO", 0);
      i=0;
      EscreveTFT(String(i), 50, 100, 12,"BRANCO", 0);
    }
    //Sai
    if (GetClique(282, 4, 317, 32, 300)){
      EscreveTFT(String(i), 50, 100, 12,"PRETO", 0);
      EscreveTFT("Tchau! =)", 50, 100, 5,"BRANCO", 0);
      return;
    }
  }
  //-----------------------------------------------
  /*
  bmpDraw("imagem4.bmp", 0, 0);
  int i,m, pox1,pox2, poy1, poy2, tempo=500, rodada = 0, acelerador = 0;
  int Score = 0;
  while(1==1)
  {
    pox1 = random(0, 290);
    poy1 = random(23, 210);
    pox2 = pox1 + 40;
    poy2 = poy1 + 40;
    tft.fillRect(pox1, poy1, 30, 30, 0x0000);
    if(acelerador>30) {acelerador=0; tempo = 500;};
    if (tempo > 100){
      tempo = 500 - (acelerador * 25);
    }else if ((tempo >10)& (tempo <=100)){
      tempo = tempo - 10;
      }
    else{tempo = 10;};

    for(i=tempo;i > 0; i--)
    {
      EscreveTFT(String(m), 150, 10, 2,"PRETO", 0);
      m = i;
      EscreveTFT(String(i), 150, 10, 2,"BRANCO", 0);
      if ((GetClique(pox1, poy1, pox2, poy2, 0)==1))
      {
        EscreveTFT(String(Score), 65, 7, 2,"PRETO", 0);
        Score++;
        acelerador++;
        EscreveTFT(String(Score), 65, 7, 2,"BRANCO", 0);
        break;
      };
        //Clique em sair
      if ((GetClique(271, 7, 316, 20, 0)==1))
      {
        bmpDraw("imagem2.bmp", 0, 0);
        return;
      }
      rodada++;
    }
    tft.fillRect(pox1, poy1 , 30, 30, 0x001F); 
  }
  */
}
void TelaMenu()
{
  bmpDraw("imagem2.bmp", 0, 0);
  while(1==1)
  {
    //Menu calculadora
    if ((GetClique(16, 33, 70, 88, 0)==1))
    {
      TelaCalculadora();
      bmpDraw("imagem2.bmp", 0, 0);
    };
    //Menu contador
    if ((GetClique(107, 35, 173, 91, 0)==1))
    {
      TelaJogo();
      bmpDraw("imagem2.bmp", 0, 0);
    };
  }
}
void loop()
{
  TelaMenu(); 
}

bool GetClique(int xmenos,int ymenos, int xmais, int ymais, int espera)
{
  TSPoint p;
  p = ts.getPoint();
  pinMode(XM, OUTPUT);
  digitalWrite(XM, LOW);
  pinMode(YP, OUTPUT);
  digitalWrite(YP, HIGH);
  pinMode(YM, OUTPUT);
  digitalWrite(YM, LOW);
  pinMode(XP, OUTPUT);
  digitalWrite(XP, HIGH);
  CliqueX = (float) (320.0 * (p.x - 250.0)/(950.0 - 250.0));
  CliqueY = (float) (240.0 * ((830.0 - 260.0) - (p.y-260.0)) / (830.0 - 260.0));
  if (CliqueX > xmenos & CliqueX < xmais & CliqueY > ymenos & CliqueY < ymais )
  {
    delay(espera);
    return true;
  }
  return false;
} 
#define BUFFPIXEL 20
 
void bmpDraw(char *filename, int x, int y) 
{
  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3 * BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;
 
  if ((x >= tft.width()) || (y >= tft.height())) return;
 
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
  if (read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.println(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if (read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed
        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);
        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;
        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if (bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }
        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if ((x + w - 1) >= tft.width())  w = tft.width()  - x;
        if ((y + h - 1) >= tft.height()) h = tft.height() - y;
        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x + w - 1, y + h - 1);
 
        for (row = 0; row < h; row++) {
          if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if (bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }
 
          for (col = 0; col < w; col++) { // For each column...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              // Push LCD buffer to the display first
              if (lcdidx > 0) {
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
            lcdbuffer[lcdidx++] = tft.color565(r, g, b);
          } // end pixel
        } // end scanline
        // Write any remaining data to LCD
        if (lcdidx > 0) {
          tft.pushColors(lcdbuffer, lcdidx, first);
        }
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }
 
  bmpFile.close();
  if (!goodBmp) Serial.println(F("BMP format not recognized."));
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

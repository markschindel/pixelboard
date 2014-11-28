#include <MemoryFree.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 11
#define LAT A3

#define OE  9
#define A   A0
#define B   A1
#define C   A2

#define CMD_SIZE 512
#define MAX_ELEMENTS 30

#define DEBUG 0

//ESI
uint16_t logo1 [] = {
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x4385,0x6D47,0x75A7,0x7E08,0x7E08,0x7E08,0x7E08,0x7E08,0x7E08,0x7E08,0x7E08,0x75A7,0x5CA6,0x75E8,0x0000,
0x0000,0x13D0,0x6527,0x7DE8,0x7E08,0x7E08,0x7E08,0x7E08,0x7E08,0x7E08,0x7DE8,0x64C6,0x3AE4,0x5C66,0x7E08,0x0000,
0x0000,0x0332,0x0A2A,0x53E5,0x7DE8,0x7E08,0x7E08,0x7E08,0x7E08,0x7E08,0x5C45,0x21C2,0x4384,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x02F0,0x0125,0x3283,0x7E08,0x7E08,0x7E08,0x7E08,0x5405,0x1101,0x32A3,0x75E8,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x0352,0x02AE,0x0082,0x1982,0x7567,0x7E08,0x4B84,0x0040,0x2A23,0x7587,0x7E08,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x0352,0x0352,0x020C,0x0020,0x1982,0x29E2,0x0860,0x1982,0x6D27,0x7E08,0x7E08,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x0352,0x0352,0x0332,0x0149,0x0040,0x0000,0x10C1,0x5425,0x7E08,0x7E08,0x7E08,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x0352,0x0352,0x0352,0x0188,0x0000,0x0000,0x08A1,0x64C5,0x7E08,0x7E08,0x7E08,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x0352,0x0352,0x028E,0x0041,0x0083,0x00C5,0x0000,0x21C3,0x7DA6,0x7E08,0x7E08,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x0352,0x02D0,0x00A3,0x00C4,0x024C,0x02CF,0x0149,0x0041,0x3284,0x8606,0x7E08,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x0310,0x0188,0x00C4,0x02D0,0x0352,0x0352,0x0352,0x016A,0x0082,0x3B45,0x8627,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x024D,0x0126,0x0352,0x0352,0x0352,0x0352,0x0352,0x0352,0x018A,0x00C3,0x5C86,0x7E08,0x7E08,0x0000,
0x0000,0x0352,0x020B,0x0352,0x0352,0x0352,0x0352,0x0352,0x0352,0x0352,0x0352,0x026D,0x1165,0x75A7,0x7E08,0x0000,
0x0000,0x02F0,0x0352,0x0352,0x0352,0x0352,0x0352,0x0352,0x0352,0x0352,0x0352,0x0332,0x02CE,0x22A7,0x7E08,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000  
};

//Arduino
uint16_t logo2 [] = {
0x0000,0x0000,0x0000,0x0000,0x03CF,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x03CF,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x0000,0x0000,0x0000,
0x0000,0x0000,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x0000,0x0000,
0x0000,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x0000,
0x03CF,0x04B3,0x04B3,0x3555,0x4596,0x3555,0x04B3,0x04B3,0x04B3,0x04B3,0x3555,0x4596,0x3555,0x04B3,0x04B3,0x03CF,
0x04B3,0x04B3,0x9EDB,0xFFFF,0xFFFF,0xFFFF,0xBF3C,0x14F4,0x14F4,0xBF3C,0xFFFF,0xFFFF,0xFFFF,0xAEFC,0x04B3,0x04B3,
0x04B3,0x8659,0xFFFF,0x04B3,0x04B3,0x04B3,0xFFFF,0xBF3C,0xBF3C,0xFFFF,0x04B3,0x04B3,0x04B3,0xFFFF,0x8659,0x04B3,
0x04B3,0xEFDF,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0xFFFF,0xFFFF,0x04B3,0x04B3,0xFFFF,0x04B3,0x04B3,0xEFDF,0x04B3,
0x04B3,0xFFFF,0x04B3,0xFFFF,0xFFFF,0xFFFF,0x04B3,0xFFFF,0xFFFF,0x04B3,0xFFFF,0xFFFF,0xFFFF,0x04B3,0xFFFF,0x04B3,
0x04B3,0xDF9E,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0xFFFF,0xFFFF,0x04B3,0x04B3,0xFFFF,0x04B3,0x04B3,0xEFDF,0x04B3,
0x04B3,0x8659,0xFFFF,0x04B3,0x04B3,0x04B3,0xFFFF,0xBF3C,0xBF3C,0xFFFF,0x04B3,0x04B3,0x04B3,0xFFFF,0x8659,0x04B3,
0x03CF,0x04B3,0x9EDB,0xFFFF,0xFFFF,0xFFFF,0xBF3C,0x14F4,0x14F4,0xBF3C,0xFFFF,0xFFFF,0xFFFF,0xAEFC,0x04B3,0x03CF,
0x0000,0x04B3,0x04B3,0x3555,0x4596,0x3555,0x04B3,0x04B3,0x04B3,0x04B3,0x3555,0x4596,0x3555,0x04B3,0x04B3,0x0000,
0x0000,0x0000,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x0000,0x0000,
0x0000,0x0000,0x0000,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x03CF,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x04B3,0x03CF,0x0000,0x0000,0x0000,0x0000
};

//Pi
uint16_t logo3 [] = {
0x0000,0x0000,0x0000,0x0000,0x0000,0x0080,0x0020,0x0000,0x0000,0x0000,0x0020,0x0080,0x0020,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0920,0x4D00,0x5540,0x5560,0x33A0,0x0000,0x2AE0,0x5560,0x5540,0x4D20,0x1A00,0x0000,0x0000,
0x0000,0x0000,0x0000,0x08E0,0x5E00,0x5540,0x4480,0x55C0,0x11A0,0x5580,0x44A0,0x4D00,0x5E40,0x1A00,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x3380,0x5E40,0x55C0,0x1A80,0x0020,0x09E0,0x4D60,0x5E40,0x4460,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x3280,0x4B20,0x1820,0x4801,0x1800,0x42C0,0x32E0,0x0020,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x3000,0xC806,0x4001,0xB005,0xF829,0xD007,0x5802,0xC806,0x2800,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x9804,0x7003,0x4802,0x7003,0x7003,0x8004,0x6002,0x8004,0x9804,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x1000,0x2800,0x8804,0xF828,0xE027,0x1800,0xC826,0xF828,0xA005,0x3801,0x1800,0x0000,0x0000,
0x0000,0x0000,0x0000,0xB806,0x7803,0xE027,0xF028,0xF828,0x3801,0xD827,0xF028,0xE828,0x8804,0xC026,0x0000,0x0000,
0x0000,0x0000,0x0000,0xE027,0x3801,0xA005,0xF028,0x9804,0x2800,0x7003,0xE027,0xA805,0x3001,0xD827,0x0000,0x0000,
0x0000,0x0000,0x0000,0x4801,0x4801,0x1000,0x2000,0xA005,0xF028,0xC006,0x2000,0x2800,0x8003,0x4001,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0xE827,0xC826,0x2000,0xF028,0xF028,0xF828,0x5802,0xC826,0xF828,0x1000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0xA805,0xF829,0x7803,0x7803,0xD827,0x9004,0x7803,0xF829,0xC826,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0800,0x8004,0x4801,0x4001,0x8003,0x5802,0x4001,0x8804,0x1000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xB826,0xF828,0xC826,0x0800,0x0000,0x0000,0x0000,0x0000,0x0000,
0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
};

typedef struct {
  int x;
  int y;  
  uint16_t color;
  uint8_t textSize;
  boolean isPixmap;
  char *data;
  uint16_t *pixmap;
} screenElement ;

screenElement screen[MAX_ELEMENTS];
uint8_t screenElements=0;
int screenWidth=0;

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true, 2 );

int   scrollX   = matrix.width();
int32_t   prevDebug, prevScroll = 0;

uint16_t  hue     = 0;
       
uint8_t   scrollSpeed = 8;

boolean doneScroll=true, repeat=false;

char  input[CMD_SIZE+1],
      command[CMD_SIZE+1],
      line[CMD_SIZE+1];  
;

int ipos=0;
  
void setup() {
  input[0], command[0] ='\0';
  Serial.begin(38400);
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
}

void loop() {

  printDebug(false,"loop");
  
  readCommand();
  
  if(doneScroll) {
    parseCommand();
    if(!repeat) command[0]='\0';
  }

  if(screenElements>0) {
    updateScreen();
  } else {
    matrix.fillScreen(0);
    matrix.swapBuffers(false);  
  }
  
}

void readCommand() {

  while (Serial.available() > 0) {
    char c = Serial.read();
    if (ipos < CMD_SIZE) {
      if ((c=='\n')||(c=='\r')) {
        input[ipos]='\0';
        ipos=0;
        if(doneScroll) {
          strcpy(command,input);
          sendResponse("Ok");
        } else {
          sendResponse("Busy");
        }
      } else {
        input[ipos++]=c;
      }
    } else {
      strcpy(command,"input buffer error");
      ipos=0;
    }
  }
}

void sendResponse( char * message) {
  Serial.println(message);        
}

void uploadLogo(char logoIndex) {
  int bytesReceived=0;
  uint16_t *logoPtr;
  int32_t start = millis();
  int timeout=3000;

  if (charTologo(logoIndex, &logoPtr)) {
    while ( ( bytesReceived < 512 ) && ( (start + timeout) > millis() ) ) {
      while (Serial.available() > 0) {
        char c = Serial.read();
        input[bytesReceived++]=c;
      }
    }
    if ( bytesReceived == 512 ) {
      memcpy(logoPtr,input,512);
    } else {
      setScreen("Upload failed");
    }
  } else {
    setScreen("Bad logo index");
  }
  ipos=0;
  input[0]='/0';
}

boolean charTologo(char logoIndex, uint16_t **logo) {
  
  boolean rc=true;
  
  switch (logoIndex) {
    case '1':
      *logo=logo1;
      break;
    case '2':
      *logo=logo2;
      break;
    case '3':
      *logo=logo3;
      break;
    default:
      rc=false;
      break;
  }

  return(rc);
}

void parseCommand() {
  
  char cc = '\0';
  char *dataStart;
  boolean parseComplete=false;
  char color[] = "FFFFFF";  

  strcpy(line,command);

  uint8_t screenPos=0, linePos=0, lineMax=0, dataLen=0;
  
  screenElements=0;
  screenWidth=0;  
  lineMax=strlen(line);
  
  while ((line[linePos] != '\0')&&(!parseComplete)) {
    if ( (line[linePos] =='/') && (line[linePos+1] !='/') ){
      line[linePos]='\0';
      linePos++;
      cc=line[linePos];
      if (dataLen > 0) {
        screen[screenElements-1].data=dataStart;
        if (screen[screenElements-1].isPixmap) {
          if (!charTologo(screen[screenElements-1].data[0], &screen[screenElements-1].pixmap)) { 
              parseComplete = true;
              setScreen("bad logo index");
          }
          screenWidth=screenWidth+16;
        } else {
          if ( (screenElements > 1) && (screen[screenElements-1].x == screen[screenElements-2].x) ) {
            if ( strlen(screen[screenElements-1].data) > strlen(screen[screenElements-2].data) ) {
              screenWidth=screenWidth+( strlen(screen[screenElements-1].data) - strlen(screen[screenElements-2].data) )*(screen[screenElements-1].textSize*6);
            } 
          } else {
            screenWidth=screenWidth+strlen(screen[screenElements-1].data)*(screen[screenElements-1].textSize*6);
          }
        }
      }
      switch (cc) {
        case '0':
          dataLen = 0;
          screenElements++;
          screen[screenElements-1].color=hexStringtoColor("444444");
          screen[screenElements-1].x=screenWidth;
          screen[screenElements-1].y=0;
          screen[screenElements-1].textSize=2;
          screen[screenElements-1].isPixmap=false;  
          break;
        case '1':
          dataLen = 0;
          screenElements++;
          screen[screenElements-1].color=hexStringtoColor("444444");          
          if ( (screenElements > 1) && (screen[screenElements-2].textSize == 1) ) {
            screen[screenElements-1].x=screen[screenElements-2].x;
          } else {
            screen[screenElements-1].x=screenWidth;
          }
          screen[screenElements-1].y=0;
          screen[screenElements-1].textSize=1;
          screen[screenElements-1].isPixmap=false;  
          break;
        case '2':
          dataLen = 0;
          screenElements++;
          screen[screenElements-1].color=hexStringtoColor("444444");          
          if ( (screenElements > 1) && (screen[screenElements-2].textSize == 1) ) {
            screen[screenElements-1].x=screen[screenElements-2].x;
          } else {
            screen[screenElements-1].x=screenWidth;
          }
          screen[screenElements-1].y=8;
          screen[screenElements-1].textSize=1;
          screen[screenElements-1].isPixmap=false;  
          break;
        case '#':
          if ( linePos + 7 > lineMax ) {
            parseComplete = true;
            setScreen("bad color");
          } else {
            strncpy(color,&line[linePos+1],6);
            if (dataLen == 0) {
              screen[screenElements-1].color=hexStringtoColor(color);
            } else {
              dataLen = 0;
              screenElements++;
              screen[screenElements-1].color=hexStringtoColor(color);
              screen[screenElements-1].x=screenWidth;
              screen[screenElements-1].y=screen[screenElements-2].y;
              screen[screenElements-1].textSize=screen[screenElements-2].textSize;
              screen[screenElements-1].isPixmap=false;  
            }
            linePos=linePos+6;
          }
          break;
        case 'L':
        case 'l':        
          if ( linePos + 1 > lineMax ) {
            parseComplete = true;
            setScreen("no logo index");
          } else {
            dataLen = 1;
            screenElements++;
            screen[screenElements-1].color=0;
            screen[screenElements-1].x=screenWidth;
            screen[screenElements-1].y=0;
            screen[screenElements-1].textSize=2;
            screen[screenElements-1].isPixmap=true;
          }
          break;
        case 'r':
        case 'R':        
          if ( linePos + 1 > lineMax ) {
            parseComplete = true;
            setScreen("no repeat value");
          } else {
            if (line[linePos+1]=='0') {
              repeat=false;
            } else {
              repeat=true;
            }
            linePos=linePos+1;
          }
          break;
        case 'u':
        case 'U':        
          if ( linePos + 1 > lineMax ) {
            parseComplete = true;
            setScreen("no upload value");
          } else {
            uploadLogo(line[linePos+1]);
            linePos=lineMax;
            parseComplete = true;
          }
          break;
        default:
          parseComplete = true;
          setScreen("bad command");
          break;
      }
      dataStart=&line[linePos+1];
    } else if ( (line[linePos] =='/') && (line[linePos+1] =='/') ){
      memmove(&line[linePos],&line[linePos+1],lineMax-linePos);
      dataLen++;
    } else {
      dataLen++;
    }
    linePos++;
  }
  
  if ((! parseComplete)&&(screenElements)) {
    screen[screenElements-1].data=dataStart;
    if (screen[screenElements-1].isPixmap) {
      if (!charTologo(screen[screenElements-1].data[0], &screen[screenElements-1].pixmap)) { 
          parseComplete = true;
          setScreen("bad logo index");
      }
      screenWidth=screenWidth+16;
    } else {
      if ( (screenElements > 1) && (screen[screenElements-1].x == screen[screenElements-2].x) ) {
        if ( strlen(screen[screenElements-1].data) > strlen(screen[screenElements-2].data) ) {
          screenWidth=screenWidth+( strlen(screen[screenElements-1].data) - strlen(screen[screenElements-2].data) )*(screen[screenElements-1].textSize*6);
        } 
      } else {
        screenWidth=screenWidth+strlen(screen[screenElements-1].data)*(screen[screenElements-1].textSize*6);
      }
    }
  }

  if (DEBUG >=2) printDebug(true,"parsed");

}

void setScreen(char *message) {

  if ( message == "" ) {
    screenElements=0;
  } else {
    screenElements=1;
    screen[screenElements-1].x=0;
    screen[screenElements-1].y=0;
    screen[screenElements-1].textSize=1;
    screen[screenElements-1].color=hexStringtoColor("444444");
    screen[screenElements-1].isPixmap=false;  
    screen[screenElements-1].data=message;
    screenWidth=strlen(screen[screenElements-1].data)*(screen[screenElements-1].textSize*6);
  }
}

void updateScreen() {
  scrollMessage();
}

void drawLogo(uint16_t *pixmap, int8_t x, int8_t y) {
  drawPixmap(pixmap, 16, 16, x, y);
}

void drawPixmap(uint16_t *pixmap, uint8_t width, uint8_t height, int8_t x, int8_t y) {

  uint8_t px, py;

  for(px=0;px<width;px++) {
    for(py=0;py<height;py++) {
      matrix.drawPixel(px+x,py+y,pixmap[px+py*width]);
    }  
  }  

}

uint16_t hexStringtoColor(char *instring) {

  uint8_t red = 0, grn = 0, blu = 0;
  char hexchar[]="FF";

  strncpy(hexchar, instring, 2);
  red=strtoul(hexchar,0,16);

  strncpy(hexchar, instring+2, 2);
  grn=strtoul(hexchar,0,16);
  
  strncpy(hexchar, instring+4, 2);
  blu=strtoul(hexchar,0,16);
  
  return(matrix.Color888(red,grn,blu));

}

void scrollMessage() {

  if ( millis() > prevScroll + scrollSpeed ) {
    doneScroll=false;
  
    // Clear background
    matrix.fillScreen(0);
  
    if (DEBUG>=3) Serial.println(scrollX);
    
    if ( ( screenElements == 2 ) && ( screen[0].textSize==1 ) && ( screen[1].textSize==1 ) && (strlen(screen[0].data) <= 10) ) {
      screen[0].x=scrollX*-1;
    }
    displayMessage(scrollX);
  
    // Move text left (w/wrap)
    if((--scrollX) < screenWidth * -1) {
      scrollX = matrix.width();
      doneScroll = true;
    }
    matrix.swapBuffers(false);
    prevScroll = millis();
  }   

}

void displayMessage(int x) {

  // Rotate hue
  hue += 7;
  if(hue >= 1536) hue -= 1536;

  for (uint8_t i=0; i<screenElements; i++) {
    if (screen[i].isPixmap) {
      drawLogo(screen[i].pixmap, screen[i].x+x, screen[i].y);
    } else {
      matrix.setTextSize(screen[i].textSize);
      if (screen[i].color == 0) {
        matrix.setTextColor(matrix.ColorHSV(hue, 255, 255, true));
      } else {  
        matrix.setTextColor(screen[i].color);
      }
      matrix.setCursor(screen[i].x+x, screen[i].y);
      matrix.print(screen[i].data);
    }
  }

}

void printScreen() {

  if (screenElements || screenWidth) {
  
    Serial.print("screenElements: ");
    Serial.print(screenElements);
    Serial.print(" screenWidth:");
    Serial.println(screenWidth);  
    Serial.print("command:");
    Serial.println(command);
    
    for (uint8_t i=0; i<screenElements; i++) {
      Serial.print("screenElement:");
      Serial.println(i);
      Serial.print("screen[screenElement].x:");
      Serial.println(screen[i].x);
      Serial.print("screen[screenElement].y:"); 
      Serial.println(screen[i].y); 
      Serial.print("screen[screenElement].color:");
      Serial.println(screen[i].color);
      Serial.print("screen[screenElement].textSize:");
      Serial.println(screen[i].textSize);
      Serial.print("screen[screenElement].isPixmap:");
      Serial.println(screen[i].isPixmap);
      Serial.print("screen[screenElement].data:");
      Serial.println(screen[i].data);
    }
  }
}

void printStatus() {

  Serial.print("scrollX=");
  Serial.print(scrollX);
  Serial.print(" doneScroll=");
  Serial.println(doneScroll);

}

void printDebug(uint8_t force, char * message) {

  if ( ( millis() > prevDebug + 2000 ) || (force) ) {

    if (DEBUG) {

      Serial.print("# ");  
      Serial.print(message);        
      Serial.println(" #");  

      Serial.print("now=");
      Serial.print(millis());
      Serial.print(" freeMemory()=");
      Serial.println(freeMemory());
      printScreen();
      printStatus();
      Serial.println("# - #");      
    }
    prevDebug = millis();
  }
}


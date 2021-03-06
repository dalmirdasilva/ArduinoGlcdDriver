#include <Wire.h>
#include <Closeable.h>
#include <Seekable.h>
#include <InputStream.h>
#include <SeekableInputStream.h>
#include <ExternalEepromInputStream.h> 
#include <ExternalEepromSeekableInputStream.h>
#include <ExternalEeprom.h>
#include <External24cl256Eeprom.h>
#include <Glcd.h>
#include <GlcdPoint.h>
#include <GlcdRectangle.h>
#include <GlcdStraight.h>
#include <GlcdGraphicState.h>
#include <GlcdDrawer.h>
#include <GlcdShapes.h>
#include <GlcdText.h>
#include <GlcdBitmapFont.h>

void setup() {
  Serial.begin(9600);
  uint16_t i, j;

  Serial.println("Are you sure to continue? (y/n)");
  while (!Serial.available());
  while (Serial.read() != 'y');

  External24cl256Eeprom ee(0x50);
  ExternalEepromSeekableInputStream eeis(&ee);
    
  GlcdGraphicState graphicState;
  GlcdStraight glcdDriver;
  GlcdDrawer glcdDrawer(&glcdDriver, &graphicState);
    
  glcdDriver.init(Glcd::MODE_ON);
  glcdDriver.screen(0x00);
  graphicState.setColor(Glcd::COLOR_WHITE);

  GlcdBitmapFont font(&eeis);
  GlcdText glcdText(&glcdDriver, &font, &graphicState);
    
  glcdDrawer.line(10, 10, 20, 10);
  glcdDrawer.line(20, 10, 30, 20);
  glcdDrawer.line(30, 20, 20, 20);
  glcdDrawer.line(20, 20, 10, 10);

  GlcdRectangle rec(30, 30, 100, 60);
  glcdText.printString(&rec, (unsigned char*)"#{Testing...} @OK!", 100, 1);
  
  eeis.close();
  Serial.print("Finished at: ");
  Serial.println(millis());
}

void loop() {
}

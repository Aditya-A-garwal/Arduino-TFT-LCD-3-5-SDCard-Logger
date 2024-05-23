#include "Arduino.h"

#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"

#include "TouchScreen.h"

#include "SPI.h"
#include "SD.h"

#include "constants.h"

MCUFRIEND_kbv tft;

TouchScreen ts(XP, YP, XM, YM, 300);

void to_display_mode() {

  pinMode(XM, OUTPUT);
  pinMode(XP, OUTPUT);
  pinMode(YM, OUTPUT);
  pinMode(YP, OUTPUT);
}

bool valid_touch() {

  TSPoint p = ts.getPoint();
  to_display_mode();

  return (PRESSURE_LO <= p.z) && (p.z <= PRESSURE_HI);
}

void get_touch(uint16_t *xptr, uint16_t *yptr) {

  TSPoint p;

  while (1) {
    p = ts.getPoint();
    if ((PRESSURE_LO <= p.z) && (p.z <= PRESSURE_HI)) {
      break;
    }
  }

  *xptr = p.x;
  *yptr = p.y;

  to_display_mode();
}

void convert(uint16_t *x, uint16_t *y) {

	*x = constrain(*x, XBEGIN, XEND);
	*y = constrain(*y, YBEGIN, YEND);

	*x = map(*x, XBEGIN, XEND, 0, 319);
	*y = map(*y, YBEGIN, YEND, 0, 479);
}

void setup() {

  Serial.begin(9600);

  tft.begin(0x9486);
  tft.fillScreen(BLACK);

  if (!SD.begin(10)) {
    Serial.println("SD Card initialization failed");
    while (1);
  }

  if (SD.exists("LOGS.TXT")) {
    Serial.println("Clearing previous logs");
    SD.remove("LOGS.TXT");
  }

  tft.fillRect(0, 0, 16, 16, GREEN);
}

void loop() {

  uint16_t tx, ty;

  if (valid_touch()) { // keep checking for a valid touch

	  // read the coordinates and convert them to pixel-coordinates
    get_touch(&tx, &ty);
    convert(&tx, &ty);

		// open the file (report the error if it could not be opened)
		// and paint the square red
    File logs = SD.open("LOGS.TXT", FILE_WRITE);
    if (!logs) {
      Serial.println("Error opening/creating logs file");
      while (1);
    }

    tft.fillRect(0, 0, 16, 16, RED);

    logs.print(millis()); // timestamp
    logs.print(',');
    logs.print(tx);       // x-coordinate
    logs.print(',');
    logs.println(ty);     // y-coordinate

		// close the file, paint the square green and
		// wait for a second before reading the screen again
    logs.close();
    tft.fillRect(0, 0, 16, 16, GREEN);
    delay(1000);
  }
}

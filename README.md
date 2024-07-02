# Log Data to SD Card with a 3.5" TFT LCD Touchscreen With Arduino UNO R3/R4

![GitHub License](https://img.shields.io/github/license/Aditya-A-garwal/Arduino-TFT-LCD-3-5-SDCard-Logger)
![GitHub forks](https://img.shields.io/github/forks/Aditya-A-garwal/Arduino-TFT-LCD-3-5-SDCard-Logger?style=flat-square&color=blue)
![GitHub Repo stars](https://img.shields.io/github/stars/Aditya-A-garwal/Arduino-TFT-LCD-3-5-SDCard-Logger?style=flat-square&color=blue)
![GitHub issues](https://img.shields.io/github/issues-raw/Aditya-A-garwal/Arduino-TFT-LCD-3-5-SDCard-Logger?style=flat-square&color=indianred)
![GitHub closed issues](https://img.shields.io/github/issues-closed-raw/Aditya-A-garwal/Arduino-TFT-LCD-3-5-SDCard-Logger?style=flat-square)
![GitHub pull requests](https://img.shields.io/github/issues-pr/Aditya-A-garwal/Arduino-TFT-LCD-3-5-SDCard-Logger?style=flat-square&color=indianred)
![GitHub closed pull requests](https://img.shields.io/github/issues-pr-closed/Aditya-A-garwal/Arduino-TFT-LCD-3-5-SDCard-Logger?style=flat-square)
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Aditya-A-garwal/Arduino-TFT-LCD-3-5-SDCard-Logger/build.yml?style=flat-square)

## Overview

This repository contains a program to log data to an SD Card on a 3.5" TFT LCD Shield along with an Arduino UNO R3/R4/Mega, as shown below -

|![Image of LCD Touch Shield from Top](images/LCD_top.png)|![Image of LCD Touch Shield from Bottom](images/LCD_bottom.png)|
|-|-|

Most 3.5" TFT LCD Touch displays use the ILI9486 Display Driver and include a resistive touchscreen. **The PCB Layout & silkscreen text may vary slightly between displays. This does not change their behaviour and functionality.** This repository depends on the following libraries -

- [Adafruit Touch Screen Library](https://github.com/adafruit/Adafruit_TouchScreen) to manage touch input
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library/tree/master) for graphics primitives
- [This fork of the MCUFriend KBV library](https://github.com/slviajero/MCUFRIEND_kbv) to drive the display (this makes it compatible with the UNO R4)

The program has been written using PlatformIO, and has been tested on the [Arduino UNO R3](https://docs.arduino.cc/hardware/uno-rev3/), [Arduino UNO R4 Minima](https://docs.arduino.cc/hardware/uno-r4-minima/) & [Arduino UNO R4 WiFi](https://docs.arduino.cc/hardware/uno-r4-wifi/).

> [!TIP]
> A detailed tutorial on how to use this repository is available at https://dumblebots.com/2024/07/02/using-3-5-tft-lcd-display-with-ili9486-arduino-part-3-text-files-sd-card/. The tutorial includes a comprehensive explanation of the code and how to use it.

## Building/Uploading With PlatformIO

Since this project has been written using PlatformIO by default, simply run the following commands to fetch the libraries, build the project and upload the program -

```shell
pio pkg install
pio run
pio run --target upload
```

## Building/Uploading With Arduino IDE

Create a new sketch and copy the contents of [```src/main.cpp```](/src/main.cpp) from this repository into the default ```.ino``` file. Create a new tab/file in the IDE named ```constants.h``` and copy the contents of [```src/constants.h```](/src/constants.h) from this repository into this file.

Install the Adafruit Touch Screen Library and Adafruit GFX Library from the Library Manager (under *Sketch>Include Library>Manage Libraries...*)

Download [this](https://github.com/slviajero/MCUFRIEND_kbv) repository as a ZIP file and install it by navigating to *Sketch>Include Library>Add .ZIP Library*, and selecting the downloaded file from the file explorer.

After this, you can Build and Upload the program as usual.


## Using the Example
> [!TIP]
> Before using this example, make sure to calibrate the touchscreen and enter the calibration values in the `constants.h` file, as shown in [this guide](https://dumblebots.com/2024/05/17/using-3-5-tft-lcd-display-with-ili9486-arduino-part-2-touch-calibration/).

As soon as the program is uploaded, the display should turn black and the message "SD Card initialization failed" should get printed on the Serial Monitor. Insert a *FAT formatted SD Card* into the SD Card slot of the TFT LCD Shield and reset the program.

A small green square should be drawn on the top-left of the display, indicating that the program is running, and that it is safe to remove the SD Card/Power-off the board. When the screen is touched, the coordinates of the point are logged onto the SD Card on a new line in the `LOGS.TXT` file (this file is created automatically if it does not exist). Along with the coordinates, the timestamp of the touch is also stored.

The logs are not updated constantly, but at a rate of 1 Hz (only once per second). When IO is being performed with the SD Card, the square on the top-left of the display turns red, indicating that it is not safe to remove the SD Card/Power-off the board.

## Troubleshooting

Some common problems and their solutions -

|Problem|Solution|
|-|-|
|Display stays white after uploading program|Non-Standard Driver (not ILI9486)|
|Display not responding after touch|Try changing the order of the touch pins in [```src/constants.h```](/src/constants.h) file, i.e. swap the values of ```XP```, ```YP```, ```XM``` and ```YM```|
|Compilation issues related to SPI|Update the Arduino IDE version and/or install the SPI library|
|Display Flickering/Arduino is reset automatically|Faulty Power Supply/Cable|

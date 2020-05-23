///
/// \file  TestTEA5767.ino
/// \brief An Arduino sketch to operate a TEA5767 chip based radio using the Radio library.
///
/// \author Matthias Hertel, http://www.mathertel.de
/// \copyright Copyright (c) 2014 by Matthias Hertel.\n
/// This work is licensed under a BSD style license.\n
/// See http://www.mathertel.de/License.aspx
///
/// \details
/// This sketch implements a "as simple as possible" radio without any possibility to modify the settings after initializing the chip.\n
/// The radio chip is initialized and setup to a fixed band and frequency. These settings can be changed by modifying the
/// FIX_BAND and FIX_STATION definitions.
///
/// Open the Serial console with 57600 baud to see the current radio information.
///
/// Wiring
/// ------
/// Arduino port | TEA5767 signal
/// ------------ | ---------------
///         3.3V | VCC
///          GND | GND
///           A5 | SCLK
///           A4 | SDIO
///           D2 | RST
///
/// More documentation and source code is available at http://www.mathertel.de/Arduino
///
/// History:
/// --------
/// * 15.09.2014 created.
/// * 15.11.2015 wiring corrected.

#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <TEA5767.h>
#include <EEPROM.h>

/// The band that will be tuned by this sketch is FM.
#define FIX_BAND RADIO_BAND_FM

/// The station that will be tuned by this sketch is 103.10 MHz.
//#define FIX_STATION 10310
int freq = 10310;
uint8_t volume = 3;

/// Rotary Encoder
#define CLK 2
#define DATA 3
#define BUTTON 4
static uint8_t prevNextCode = 0;
static uint16_t store = 0;

TEA5767 radio;    // Create an instance of Class for TEA5767

/// Setup a FM only radio configuration
/// with some debugging on the Serial port
void setup() {

  // Rotary Encoder
  pinMode(CLK, INPUT);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DATA, INPUT);
  pinMode(DATA, INPUT_PULLUP);
  pinMode(BUTTON, INPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  // open the Serial port
  Serial.begin(57600);
  Serial.println("Radio...");
  delay(200);

  // Initialize the Radio
  radio.init();
  

  // Enable information to the Serial port
  radio.debugEnable();

  

  // HERE: adjust the frequency to a local sender
  radio.setBandFrequency(FIX_BAND, 10310); // RMC
  radio.setVolume(volume);
  radio.setMono(true);
} // setup


/// show the current chip data every 3 seconds.
void loop() {
  
  // Rotary Encoder
  static int8_t c, val;
  if ( val = read_rotary() ) {
    freq += val*10;
    radio.setBandFrequency(FIX_BAND, freq); // RMC
  }

if (digitalRead(BUTTON)==0) {

      delay(10);
      if (digitalRead(BUTTON)==0) {
          Serial.println("Calibration Reset");
          while(digitalRead(BUTTON)==0);
      }
   }
  
//
//  char s[12];
//  radio.formatFrequency(s, sizeof(s));
//  Serial.print("Station:");
//  Serial.println(s);
//
//  Serial.print("Radio:");
//  radio.debugRadioInfo();
//
//  Serial.print("Audio:");
//  radio.debugAudioInfo();

  //delay(1000);
} // loop

// A vald CW or  CCW move returns 1, invalid returns 0.
int8_t read_rotary() {
  static int8_t rot_enc_table[] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0};

  prevNextCode <<= 2;
  if (digitalRead(DATA)) prevNextCode |= 0x02;
  if (digitalRead(CLK)) prevNextCode |= 0x01;
  prevNextCode &= 0x0f;

  // If valid then store as 16 bit data.
  if  (rot_enc_table[prevNextCode] ) {
    store <<= 4;
    store |= prevNextCode;
    //if (store==0xd42b) return 1;
    //if (store==0xe817) return -1;
    if ((store & 0xff) == 0x2b) return -1;
    if ((store & 0xff) == 0x17) return 1;
  }
  return 0;
}

// End.

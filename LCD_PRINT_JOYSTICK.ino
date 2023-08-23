
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

const int JOY_X_PIN = A0;        // Analog pin for X-axis
const int JOY_Y_PIN = A1;        // Analog pin for Y-axis
const int JOY_THRESHOLD = 100;   // Threshold
String curr_song = "";
String curr_artist = "";

void setup() {
  lcd.begin(16, 2);   
  Serial.begin(9600);
}

void loop() {
  //READING SONG AND ARTIST AND DISPLAYING THEM ON SCREEN
  //Python sends song first
  curr_song = Serial.readStringUntil('\n');

  //Set to first line of LCD
  lcd.setCursor(0, 0);
  lcd.print(readSong);
  //DELAY to let it show on screen
  delay(200);
  
  //Read artist, Python sends this second
  curr_artist = Serial.readStringUntil('\n');
  //Set to second line of LCD
  lcd.setCursor(0, 1);
  lcd.print(readArtist);
  delay(200);

  //READING JOYSTICK INPUT AND SENDING TO PYTHON FOR PROCESSING

  int joyXValue = analogRead(JOY_X_PIN);
  int joyYValue = analogRead(JOY_Y_PIN);

  //Finding direction
  //Delay to process input
  if (joyXValue < (512 - JOY_THRESHOLD)) {
    Serial.println("Left");
    delay(50);
  } else if (joyXValue > (512 + JOY_THRESHOLD)) {
    Serial.println("Right");
     delay(50);
  } else if (joyYValue < (512 - JOY_THRESHOLD)) {
    Serial.println("Up");
     delay(50);
  } else if (joyYValue > (512 + JOY_THRESHOLD)) {
    Serial.println("Down");
     delay(50);
  } else {
    Serial.println("Center");
     delay(50);
  }
  delay(50);
  /*
  if(readSong.length() > 15 || readArtist.length() > 15)
  {
  for (int counter = 0; counter < 16; counter++) {
    
    // scrolling one position to the right.
    lcd.scrollDisplayRight();
    delay(150);
  }
  }
  */
  //Clear LCD for next iteration
  lcd.clear();
  
}
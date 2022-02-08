#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

byte D[] = {
  B11110,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11110
};
byte startPos[] = {
  B11111,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B11111
  };
byte middlePos[] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111 
  };
byte endPos[] = {
  B11111,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B11111
  };
byte filledIn[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};


bool isBooted = false;
bool desktopRendered = false;
void setup() {
  pinMode(11, OUTPUT);
  lcd.begin();
  lcd.setCursor(0, 0);
  Serial.begin(9600);
}
void loop() {

  if (isBooted == false) {
    boot();
  } else {
    if (desktopRendered == true) {
      Serial.println("Desktop rendered");
      //Serial.println(analogRead(A3) * (5.0 / 1023.0));
      if (analogRead(A3) * (5.0 / 1023.0) > 4) {
        Serial.println("Opening");
        systemInfo();
      }
      else if (analogRead(A0) * (5.0 / 1023.0) > 4) {
        settings();
      }
      else if (analogRead(A2) * (5.0 / 1023.0) > 4) {
        digitalWrite(11, HIGH);
        delay(50);
        digitalWrite(11, LOW);
      }
      else if (analogRead(A1) * (5.0 / 1023.0) > 4) {
        openPrograms();  
      }



    } else {
      renderDesktop();
      desktopRendered = true;
    }
  }
}
void boot() {
  lcd.clear();
  lcd.createChar(0, D);
  lcd.setCursor(4, 1);
  lcd.print("Ar");
  lcd.setCursor(7, 1);
  lcd.print("uinOS-BETA");
  lcd.setCursor(6, 1);
  lcd.write(0);

  //progress bar code
   lcd.createChar(1, startPos);
   lcd.createChar(2, middlePos);
   lcd.createChar(3, endPos);
   lcd.createChar(4, filledIn);
   lcd.setCursor(4,2);
   lcd.write(1);
   lcd.setCursor(16,2);
   lcd.write(3);
   //lcd.setCursor(4,2);
   //lcd.write(2);

    for(int i=5; i < 16; i++){
      lcd.setCursor(i,2);
      lcd.write(2);  
    }
    delay(1000);
   for(int i=4; i < 17; i++){
    lcd.setCursor(i,2);
    lcd.write(4); 
    delay(500);
   }
  isBooted = true;
}
void renderDesktop() {
  lcd.clear();
  lcd.noDisplay();
  delay(500);
  lcd.display();
  lcd.home();
  lcd.print("B1: Settings");
  lcd.setCursor(0, 1);
  lcd.print("B2: Programs");
  lcd.setCursor(0, 2);
  lcd.print("B3: Restart Arduino");
  lcd.setCursor(0, 3);
  lcd.print("B4: System info");
}
void systemInfo() {
  lcd.clear();
  while (true) {
    lcd.setCursor(0, 0);
    lcd.print("ArDuinOS-BETA");
    lcd.setCursor(0, 1);
    lcd.print("v1.0-1.1");
    lcd.setCursor(0,2);
    lcd.print("GeekCreit Uno");
    lcd.setCursor(0,3);
    lcd.print("2022 RubyDevelopment");
    if (analogRead(A3) * (5.0 / 1023.0) > 4) {
      break;
    }
  }
  renderDesktop();
}
void settings() {
  lcd.clear();
  lcd.noDisplay();
  delay(200);
  lcd.display();
  while (true) {
    lcd.home();
    lcd.print("B1: backlight");
    if (analogRead(A3) * (5.0 / 1023.0) > 4) {
      break;
    }
    else if (analogRead(A0) * (5.0 / 1023.0) > 4) {
      backlightSettings();
    }
  }
  renderDesktop();
}
void backlightSettings() {
  lcd.clear();
  while (true) {
    lcd.home();
    lcd.print("B1: on");
    lcd.setCursor(0, 1);
    lcd.print("B2: off");
    if (analogRead(A3) * (5.0 / 1023.0) > 4) {
      break;
    }
    if (analogRead(A0) * (5.0 / 1023.0) > 4) {
      lcd.noBacklight();
    }
    if (analogRead(A1) * (5.0 / 1023.0) > 4) {
      lcd.backlight();
    }
  }
  settings();
}
void openPrograms(){
  lcd.clear();
  lcd.noDisplay();
  delay(100);
  lcd.display();
  while(true){
    lcd.home();  
    lcd.print("No programs loaded");

    Serial.println(analogRead(A1) * (5.0 / 1023.0));
    if (analogRead(A3) * (5.0 / 1023.0) > 4) {break;}  
  }
  renderDesktop();
}

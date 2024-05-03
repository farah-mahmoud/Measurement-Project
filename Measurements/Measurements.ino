#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key = 0;
int adc_key_in = 0;
//Related to potentiometer
const int AnalogPin = A1;
int AnalogValue;
float Voltage;
float Temp, Current, Mass;
//Defining Buttons
#define btnRight 0
#define btnUp 1
#define btnDown 2
#define btnLeft 3
#define btnSelect 4
#define btnNone 5

//Create a function to define keys
int read_LCD_buttons() {
  // read the buttons
  adc_key_in = analogRead(0);
  if (adc_key_in > 1000) return btnNone;
  if (adc_key_in < 50) return btnRight;
  if (adc_key_in < 195) return btnUp;
  if (adc_key_in < 380) return btnDown;
  if (adc_key_in < 555) return btnLeft;
  if (adc_key_in < 790) return btnSelect;
  return btnNone;
}
void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);  //position at the top left
  lcd.print("Turn the knob");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd_key = read_LCD_buttons();
  //potentiometer
  AnalogValue = analogRead(AnalogPin);
  byte leftButtonState = digitalRead(leftBP);
  //latching
  static byte lastLeftState = 0;  // make this either static [u]or[/u] global.

  /* debounce here if needed */

  if (leftButtonState != lastLeftState) {
    // do something

    lastLeftState = leftButtonState;  // update the last state.
  } else {                            /* do nothing */
  }
  if (lcd_key == btnRight) {
    //Voltage = (5.0 / 1023.0) * AnalogValue;
    //at 0 voltage --> read 0.3 v (offset error)
    Voltage = map(AnalogValue, 0, 1023, 3, 50) / 10.0;
    lcd.setCursor(0, 1);
    lcd.print("Voltage = ");
    lcd.print(Voltage);
    lcd.print(" V");
    delay(250);
    lcd.clear();
    lcd.setCursor(0, 0);  //position at the top left
    lcd.print("Turn the knob");
  }
  if (lcd_key == btnLeft) {
    //Temp = (50.0 / 1023.0) * AnalogValue;
    //at 0 Temp --> read 20 C (offset error)
    Temp = map(AnalogValue, 0, 1023, 200, 500) / 10.0;
    lcd.setCursor(0, 1);
    lcd.print("Temp = ");
    lcd.print(Temp);
    lcd.print(" C");
    delay(250);
    lcd.clear();
    lcd.setCursor(0, 0);  //position at the top left
    lcd.print("Turn the knob");
  }
  if (lcd_key == btnUp) {
    //Current = (20.0 / 1023.0) * AnalogValue;
    //at 0 Current --> read 0.3 mA (offset error)
    Current = map(AnalogValue, 0, 1023, 3, 200) / 10.0;
    lcd.setCursor(0, 1);
    lcd.print("Current =");
    lcd.print(Current);
    lcd.print("mA");
    delay(250);
    lcd.clear();
    lcd.setCursor(0, 0);  //position at the top left
    lcd.print("Turn the knob");
  }
  if (lcd_key == btnDown) {
    //Mass = (10.0 / 1023.0) * AnalogValue;
    //at 0 Mass --> read 0.5 Kg (offset error)
    Mass = map(AnalogValue, 0, 1023, 5, 100) / 10.0;
    lcd.setCursor(0, 1);
    lcd.print("Mass = ");
    lcd.print(Mass);
    lcd.print(" Kg");
    delay(250);
    lcd.clear();
    lcd.setCursor(0, 0);  //position at the top left
    lcd.print("Turn the knob");
  }
}
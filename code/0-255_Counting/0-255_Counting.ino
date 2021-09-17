 int latchPin = 4;  // D2 Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 5; // D1 Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 16;  // D0 Data pin of 74HC595 is connected to Digital pin 4

byte leds = 0;    // Variable to hold the pattern of which LEDs are currently turned on or off

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);

}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{
  leds = 0; // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
  updateShiftRegister();
  delay(500);
  for (int i = 0; i < 255; i++) // Turn all the LEDs ON one by one.
  {
//    bitSet(leds, i); 
// Set the bit that controls that LED in the variable 'leds'
    leds++;
    updateShiftRegister();  
    delay(2000);
  }
}
// 00, 01, 10, 11
/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, leds);
   Serial.print((int)leds);
   Serial.print("\n");
   digitalWrite(latchPin, HIGH);
   
}

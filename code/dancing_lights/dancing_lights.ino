// Data pin of 74HC595 is connected to Digital pin 4

int getBit(int p) {
  switch (p) {
  case 60:
    return 0; //note C3 (middle C)
  case 62:
    return 1; //D3
  case 64:
    return 2; //E3
  case 65:
    return 3; //F3
  case 67:
    return 4; //G3
  case 69:
    return 5; //A3
  case 71:
    return 6; //B3
  case 72:
    return 7; //C4
  case 74:
    return 0; //D4
  case 76:
    return 1; //E4
  case 77:
    return 2; //F4
  case 79:
    return 3; //G4
  case 81:  
    return 4; //A4
  case 83:
    return 5; //B4
  case 84:
    return 6; //C5
  case 86:
    return 7; //D5
  case 88:
    return 0; //E5
  case 89:
    return 1; //F5
  case 91:
    return 2; //G5
  case 93:
    return 3; //A5
  case 95:
    return 4; //B5
  case 96:
    return 5; //C6
  case 98:
    return 6; //D6
  case 100:
    return 7; //E6
  default:
    return 69;
  }
}

//Pin connected to latch pin (ST_CP) of 74HC595
const int latchPin = 4;
//Pin connected to clock pin (SH_CP) of 74HC595
const int clockPin = 5;
//Pin connected to Data in (DS) of 74HC595
const int dataPin = 16;

int pitch, cmd, velocity;
int light;
boolean state;

byte lightData1 = 0, lightData2 = 0, lightData3 = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(38400);
}

void loop() {

  //read the midi signal
  if (Serial.available() > 2) {
    
    cmd = Serial.read();
    pitch = Serial.read();
    velocity = Serial.read();

    //the lights are set according to the data on MIDI ch.1
    
    if (cmd == 144) state = 0; //144 ch1 noteON ; 0=relayON
    else if (cmd == 128) state = 1; //128 ch1 noteOFF ; 1=relayOFF
//    state = 1;
    // so that lights don't change while the new data is being shifted
    digitalWrite(latchPin, LOW);

    light = getBit(pitch);
    // set the corresponding bit in lightData

    Serial.print("\ncmd : ");
    Serial.print(cmd);
    Serial.print("\nlight : ");
    Serial.print(light);

    if (light < 8) {
      bitWrite(lightData1, light, state);
    }
      
    shiftOut(dataPin, clockPin, MSBFIRST, lightData1);
    Serial.print("\nLightData : ");
    Serial.print((int) lightData1);
   
    digitalWrite(latchPin, HIGH);    
  }
}

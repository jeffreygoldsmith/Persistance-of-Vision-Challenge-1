/*
 * Name   : Jeffrey Goldsmith
 * Teacher: Mr. D'Arcy
 * Date   : 30 January 2016
 * Course : TEI3M
 * 
 * Description: Using one shift register to count from 0 to 99 through multiplexing(persistance of vision).
 */

byte latchPin = 8; //Pin connected to ST_CP of 74HC595
byte clockPin = 12;  //Pin connected to SH_CP of 74HC595
byte dataPin = 11; //Pin connected to DS of 74HC595
byte switchPin = 13;  // Square wave pin to switch sides of dual 7 segment 


boolean flg;  // Flag boolean to indicate wrap around
int index = -1;  // index of tens digit

static const byte delaySec = 50;   // Delay before next count

byte charMap[] = {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};    // Bitmap of number 0-9

byte numElements = sizeof(charMap);  // Size of charMap


void setup() 
{
  pinMode(latchPin, OUTPUT);  // Set pins to output
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(switchPin, OUTPUT);
}

void loop() 
{
  //
  // Count from 0-9.
  //
  
  for (byte j = 0; j < numElements; j++)
  {
    if (j == 0) // Check for when wrap around occurs
      flg = 1;
    for (byte i = 0; i < delaySec; i++)
    {
      digitalWrite(switchPin, LOW);   // Display tens digit
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, charMap[index]);
      digitalWrite(latchPin, HIGH);

      digitalWrite(switchPin, HIGH);  // Display units digit
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, MSBFIRST, charMap[j]);
      digitalWrite(latchPin, HIGH);

      if (flg == 1)
      {
        index++;
        flg = 0;
      }
    }
  }
}

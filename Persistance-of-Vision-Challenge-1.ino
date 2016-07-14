/*
 * Name   : Jeffrey Goldsmith
 * Teacher: Mr. D'Arcy
 * Date   : 30 January 2016
 * Course : TEI3M
 * 
 * Description: Using one shift register to count from 0 to 99 through multiplexing(persistance of vision).
 */

static const byte LATCH_PIN = 8;   // Pin connected to ST_CP of 74HC595
static const byte CLOCK_PIN = 12;  // Pin connected to SH_CP of 74HC595
static const byte DATA_PIN = 11;   // Pin connected to DS of 74HC595
static const byte NUM_LED = 8;     // Amount of rows/columns in LED matrix

byte rowMap[] = {B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000};  // Bitmap for rows of LED matrix
byte columnMap[] = {B11101111, B11100111, B11100111, B11100011, B11000011, B11000001, B10000000, B00000000};  // Bitmap for columns of LED matrix


void setup() 
{
  pinMode(LATCH_PIN, OUTPUT);  // Set pins to output
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
}

void loop() 
{
  //
  // Display pattern on LED matrix.
  //
  
  for (int i = 0; i < NUM_LED; i++)
  {
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, rowMap[i]);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, columnMap[i]);
    digitalWrite(LATCH_PIN, HIGH);
    delay(150);
  }
}

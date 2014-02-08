/*
 * Include necessary XBee library if necesary
 */
#include <> 

/*
 * DEFINE variables
 */
BYTE = 1024

/*
 * Setup the necessary I/O pins and other stuff
 */
int xIn = ;
int xOut = ;
int baudRate = 57600;
// Initialize SerialPort
Serial xSerial(xIn, xOut);

void setup()
{
  xSerial.begin(baudRate);
}

void printXDebug(char msg)
{
  xSerial.println(msg, BYTE); 
}

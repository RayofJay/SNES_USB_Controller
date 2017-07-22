//*******
//GLOBALS
//*******
//Pins used to communicate with the SNES controller via SPI (Serial Peripheral Interface)
const int pinCS = 10;     //Slave Select

//These aren't used, but nice to know
const int pinMOSI = 11;   //Master Out Slave In
const int pinMISO = 12;   //Master In Slave Out
const int pinSCLK = 13;   //Clock

//Clock Speed
const int ClockSpeed = 1000000; //Specs said this could be 12MHz, but 1MHz seems to work fine

#include <SPI.h>



//*****
//SETUP
//*****
void setup()
{
  pinMode(pinCS, OUTPUT); //internet said to configure the Slave Select pin manually
  SPI.begin();            //sets up the SCLK, MOSI, and MISO pins
}



//****
//LOOP
//****
void loop()
{
  int intbtnIndex = 0;        //Tracks how many buttons are currently being pressed on the SNES controller.  
  int aintKeysToSend[5];      //Holds the keys to send out via USB (Keyboard emulation).  The arduino keyboard emulation can only output 6 keys at once it seems.
  int intSNESButtonData = 0;  //The bit data received serially from the SNES controller
  
  //Buttons in the order they come from the SNES controller
  //(B, Y, Select, Start, Up, Down, Left, Right),(A, X, L, R, HIGH, HIGH, HIGH, HIGH)
  int aintSNESKeys[] = {KEY_B,KEY_Y,KEY_C,KEY_S,KEY_P,KEY_N,KEY_F,KEY_T,KEY_A,KEY_X,KEY_L,KEY_R};

  //Keyboard can only send 6 keys at once (which is fine for the SNES controller)
  //Initialize them all to zero.  I believe the keyboard emulator doesn't actually send anything for zeroes.
  aintKeysToSend[0]=0;
  aintKeysToSend[1]=0;
  aintKeysToSend[2]=0;
  aintKeysToSend[3]=0;
  aintKeysToSend[4]=0;
  aintKeysToSend[5]=0;

  SPI.beginTransaction(SPISettings(ClockSpeed, LSBFIRST, SPI_MODE0)); //Setup the SPI
  digitalWrite(pinCS, LOW); //Set the slave select bit                //Tell the V520B chip in the SNES controller that it has been selected for communication
  intSNESButtonData = SPI.transfer16(0);                              //SPI RX/TX simultaneously.  Send nothing (0) and receive 16 bits
  digitalWrite(pinCS, HIGH); //Set the slave select bit               //Deselect the V520B chip.  Necessary for the next iteration
  SPI.endTransaction();                                               //Terminate the SPI communication

  //Loop through all 12 possible button presses
  //Build an array of at most 6 buttons to send out via USB
  for(int i=0;i<12;i++)
  {
    if ((intSNESButtonData & PowerOf2(i)) == 0) //Tests a single bit (button press) at bit index PowerOf2(i)
    {
      if (intbtnIndex < 6)  //Make sure we only have 6 keys maximum
      {
        aintKeysToSend[intbtnIndex] = aintSNESKeys[i];
        intbtnIndex++;                                  //A key was pressed.  Increment the button press count
      }
    }
  }

  //********************
  //Send all of the keys
  //********************
  //Set the keyboard emulator key values
  Keyboard.set_key1(aintKeysToSend[0]);
  Keyboard.set_key2(aintKeysToSend[1]);
  Keyboard.set_key3(aintKeysToSend[2]);
  Keyboard.set_key4(aintKeysToSend[3]);
  Keyboard.set_key5(aintKeysToSend[4]);
  Keyboard.set_key6(aintKeysToSend[5]);

  Keyboard.send_now();
}



//Calculate powers of 2
//This function is needed because of the integer return data type
//This is used in bitwise AND operations that requires an integer
//The pow function returns a float which is unsuitable
int PowerOf2(int exponent)
{
  int intTotal = 1;
  
  if ((exponent >0) and (exponent <=16))
  {
    for(int i=1;i<=exponent;i++)
    {
      intTotal = intTotal * 2;
    }
  }
  
  return intTotal;
}


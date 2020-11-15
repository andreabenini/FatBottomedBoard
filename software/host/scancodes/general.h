// Function Defines

#define LowB(x) (*((unsigned char*)  &(##x)+1)) 
#define HighB(x) (*((unsigned char*) &(##x)+0)) 

#define ByteLow(v)   ((unsigned char) (v))
#define ByteHigh(v)  ((unsigned char) (((unsigned int) (v)) >> 8))

void DelayMSec(unsigned short int iMilliSeconds);

void LedOn();
void LedOff();
void LedBlink();

void HardwareInit();
void SetError(uint8_t iError);
void SerialInit();

/**/

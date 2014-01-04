/*** PCL4C.H ***/

#ifdef __cplusplus

/* External Library Function Prototypes for C++ */

extern "C" int SioBaud(int, int);
extern "C" int SioBrkKey();
extern "C" int SioBrkSig(int, char);
extern "C" int SioCrtWrite(char);
extern "C" int SioCTS(int);
extern "C" int SioDCD(int);
extern "C" int SioDSR(int);
extern "C" int SioDTR(int, char);
extern "C" int SioDelay(int);
extern "C" int SioDone(int);
extern "C" int SioError(int);
extern "C" int SioFIFO(int, int);
extern "C" int SioFlow(int, int);
extern "C" int SioGetDiv(int);
extern "C" int SioGetc(int, int);
extern "C" int SioInfo(char);
extern "C" int SioIRQ(int, int);
extern "C" int SioKeyPress();
extern "C" int SioKeyRead();
extern "C" int SioLine(int);
extern "C" int SioLoopBack(int);
extern "C" int SioModem(int, char);
extern "C" int SioParms(int, int, int, int);
extern "C" int SioPorts(int,int,int,int);
extern "C" int SioPutc(int, char);
extern "C" int SioRead(int, int);
extern "C" int SioReset(int, int);
extern "C" int SioRI(int);
extern "C" int SioRTS(int, char);
extern "C" int SioRxBuf(int, int, int);
extern "C" int SioRxFlush(int);
extern "C" int SioRxQue(int);
extern "C" long SioTimer();
extern "C" int SioTxBuf(int, int, int);
extern "C" int SioTxFlush(int);
extern "C" int SioTxQue(int);
extern "C" int SioUART(int, int);
extern "C" int SioUnGetc(int, char);

#else

/* External Library Function Prototypes for C */

extern int SioBaud(int, int);
extern int SioBrkKey();
extern int SioBrkSig(int, char);
extern int SioCrtWrite(char);
extern int SioCTS(int);
extern int SioDCD(int);
extern int SioDSR(int);
extern int SioDTR(int, char);
extern int SioDelay(int);
extern int SioDone(int);
extern int SioError(int);
extern int SioFIFO(int, int);
extern int SioFlow(int, int);
extern int SioGetDiv(int);
extern int SioGetc(int, int);
extern int SioInfo(char);
extern int SioIRQ(int, int);
extern int SioKeyPress();
extern int SioKeyRead();
extern int SioLine(int);
extern int SioLoopBack(int);
extern int SioModem(int, char);
extern int SioParms(int, int, int, int);
extern int SioPorts(int,int,int,int);
extern int SioPutc(int, char);
extern int SioRead(int, int);
extern int SioReset(int, int);
extern int SioRI(int);
extern int SioRTS(int, char);
extern int SioRxBuf(int, int, int);
extern int SioRxFlush(int);
extern int SioRxQue(int);
extern long SioTimer();
extern int SioTxBuf(int, int, int);
extern int SioTxFlush(int);
extern int SioTxQue(int);
extern int SioUART(int, int);
extern int SioUnGetc(int, char);

#endif

/* Port Codes */

#define COM1   0
#define COM2   1
#define COM3   2
#define COM4   3
#define COM5   4
#define COM6   5
#define COM7   6
#define COM8   7
#define COM9   8
#define COM10  9
#define COM11 10
#define COM12 11
#define COM13 12
#define COM14 13
#define COM15 14
#define COM16 15
#define COM17 16
#define COM18 17
#define COM19 18
#define COM20 19

/* Baud Rate Cods */

#define Baud300 0
#define Baud600 1
#define Baud1200 2
#define Baud2400 3
#define Baud4800 4
#define Baud9600 5
#define Baud19200 6
#define Baud38400 7
#define Baud57600 8
#define Baud115200 9

#define NORESET -1

/* Parity Codes */

#define NoParity 0
#define OddParity  1
#define EvenParity 3
#define MarkParity 5
#define SpaceParity 7

/* Stop Bit Codes */

#define OneStopBit  0
#define TwoStopBits 1

/* Word Length Codes */

#define WordLength5  0
#define WordLength6  1
#define WordLength7  2
#define WordLength8  3

/* Buffer Size Codes */

#define Size8    0
#define Size16   1
#define Size32   2
#define Size64   3
#define Size128  4
#define Size256  5
#define Size512  6
#define Size1024 7
#define Size2048 8
#define Size4096 9
#define Size8192  10
#define Size16384 11
#define Size32768 12
#define Size1K   7
#define Size2K   8
#define Size4K   9
#define Size8K  10
#define Size16K 11
#define Size32K 12

/* Line Status Masks */

#define TransBufferEmpty 0x20
#define BreakDetect  0x10
#define FramingError 0x08
#define ParityError  0x04
#define OverrunError 0x02
#define DataReady    0x01

/* Modem Status Masks */

#define DCD 0x80
#define RI  0x40
#define DSR 0x20
#define CTS 0x10
#define DeltaDCD 0x08
#define DeltaRI  0x04
#define DeltaDSR 0x02
#define DeltaCTS 0x01

/* Break Signal Commands */

#define ASSERT_BREAK 'A'
#define CANCEL_BREAK 'C'
#define DETECT_BREAK 'D'

/* SioDTR & SioRTS Commands */

#define SET_LINE   'S'
#define CLEAR_LINE 'C'
#define READ_LINE  'R'

/* FIFO level codes */

#define FIFO_OFF -1
#define LEVEL_1   0
#define LEVEL_4   1
#define LEVEL_8   2
#define LEVEL_14  3

/* IRQ codes */

#define IRQ2  2
#define IRQ3  3
#define IRQ4  4
#define IRQ5  5
#define IRQ6  6
#define IRQ7  7
#define IRQ8  8
#define IRQ9  9
#define IRQ10 10
#define IRQ11 11
#define IRQ12 12
#define IRQ13 13
#define IRQ14 14
#define IRQ15 15

/* SioInfo Commands */

#define VERSION 'V'
#define M_MODEL 'M'

/* SioPort dumbcard types */

#define PC_PORTS  0
#define DIGIBOARD 1
#define BOCABOARD 2
#define FASTCOM   2
#define GTEK      2

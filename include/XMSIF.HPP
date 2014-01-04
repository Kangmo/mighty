/***************************************************************************
*   XMSIF.HPP                                                              *
*   HEADER FOR XMSIF                                                       *
*   OS:        DOS                                                         *
*   VERSION:   1.5                                                         *
*   DATE:      04/22/93                                                    *
*                                                                          *
*   Copyright (c) 1993 James W. Birdsall. All Rights Reserved.             *
*   Thanks to Bob Parsons of Parsons Technology for the original           *
*    version of this file.                                                 *
*                                                                          *
***************************************************************************/

#ifndef XMSIF_H
#define XMSIF_H

/*
** system includes <>
*/

/*
** custom includes ""
*/

/*
** local #defines
*/

/* error returns */

#define XMMOOPS     -1
#define NOXMM       -2


/* XMM library errors */

#define XMM_NOINIT          0x40
#define XMM_UMBHUGE         0x41
#define XMM_BADPTR          0x42
#define XMM_ELTOOBIG        0x43
#define XMM_SKTOOBIG        0x44
#define XMM_BADVERS         0x45


/* XMS driver errors */

#define XMM_UNIMP           0x80
#define XMM_VDISK           0x81
#define XMM_A20ERROR        0x82
#define XMM_GENERROR        0x8E
#define XMM_UNRECERROR      0x8F

#define XMM_NOHMA           0x90
#define XMM_HMAUSED         0x91
#define XMM_HMATOOBIG       0x92
#define XMM_HMANOALLOC      0x93
#define XMM_A20STILLEN      0x94

#define XMM_NOFREEX         0xA0
#define XMM_NOFREEXHAN      0xA1
#define XMM_BADXHAN         0xA2
#define XMM_BADSRCHAN       0xA3
#define XMM_BADSRCOFF       0xA4
#define XMM_BADDESTHAN      0xA5
#define XMM_BADDESTOFF      0xA6
#define XMM_BADLENGTH       0xA7
#define XMM_COPYOVERLAP     0xA8
#define XMM_PARITY          0xA9
#define XMM_NOLOCK          0xAA
#define XMM_LOCKED          0xAB
#define XMM_TOOMANYLOCKS    0xAC
#define XMM_LOCKFAIL        0xAD

#define XMM_UMBSMALLER      0xB0
#define XMM_NOFREEUMB       0xB1
#define XMM_BADUMBHAN       0xB2


/* function macros */

#define XMMcopyto(clen,src,dhan,doff)    _XMMcopy((clen),0, \
                                            (unsigned long)(src),(dhan),(doff))
#define XMMcopyfrom(clen,shan,soff,dest) _XMMcopy((clen),(shan),(soff),0, \
                                                         (unsigned long)(dest))

#define XMMicopyto(n,e,b,s,h,f)          _XMMicopy((n),(e),(b),0, \
                                                (unsigned long)(s),(h),(f),(b))
#define XMMicopyfrom(n,e,b,h,f,d)        _XMMicopy((n),(e),(b),(h),(f),0, \
                                                            (unsigned long)(d))


/*
** misc: copyright strings, version macros, etc.
*/

/*
** typedefs
*/

struct XMMregs {
    unsigned int regAX;
    unsigned int regBX;
    unsigned int regDX;
    unsigned int regSI;
    unsigned int regDS;
};

struct XMMbigregs {
    unsigned long regEAX;
    unsigned long regEBX;
    unsigned long regECX;
    unsigned long regEDX;
};


/*
** global variables
*/

extern unsigned char const _XMMerror;         /* XMS error variable */
extern unsigned int  const _XMMversion;       /* XMS version, BCD */

extern char const xmsif_vers_vers[];
extern char const xmsif_vers_date[];
extern char const xmsif_vers_time[];


/*
** function prototypes
*/

extern "C" int XMMlibinit(void);
extern "C" unsigned int XMMgetversion(void);

extern "C" unsigned long XMMcoreleft(void);
extern "C" unsigned long XMMallcoreleft(void);

extern "C" int XMMalloc(unsigned long bytes);
extern "C" int XMMrealloc(int handle, unsigned long bytes);
extern "C" int XMMfree(int handle);

extern "C" int _XMMcopy(unsigned long clen,
                        int shan, unsigned long soff,
                        int dhan, unsigned long doff);
extern "C" int _XMMicopy(unsigned long nelem, int elsize,
                         unsigned int sskip, int shan, unsigned long soff,
                         int dhan, unsigned long doff, unsigned int dskip);

extern "C" int XMMrawcall(struct XMMregs *regs);
extern "C" void XMMraw3(struct XMMbigregs *regs);

extern "C" unsigned long UMBcoreleft(void);
extern "C" unsigned long UMBallcoreleft(void);

extern "C" void far *UMBalloc(unsigned long bytes, unsigned long *finalsize);
extern "C" int UMBfree(void far *handle);

#endif

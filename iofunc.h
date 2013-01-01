/*******************************************************************************
* @Title: iofunc.h 
*
* @Author: Phil Smith 
*
* @Date: 02-Nov-2011	10:20 AM
*
* @Project: Controller
*
* @Purpose: 
*
* @Modification History: 
*
*******************************************************************************/
#ifndef __IOFUNC_H__
#define __IOFUNC_H__

/* TRANSDELAY - delay time between write/read transitions */
/* unit: usec */
#define TRANSDELAY 10000

/* Define individual relays */
#define ALLOUTS '0'
#define OUTPUT1 '1'
#define OUTPUT2 '2'
#define OUTPUT3 '3'
#define OUTPUT4 '4'
#define OUTPUT5 '5'
#define OUTPUT6 '6'
#define OUTPUT7 '7'
#define OUTPUT8 '8'

/* Define relay masks */
#define OP1   0x01
#define OP2   0x02
#define OP3   0x04
#define OP4   0x08
#define OP5   0x10
#define OP6   0x20
#define OP7   0x40
#define OP8   0x80
#define NO_OP 0x00
#define AL_OP 0xFF

/* Define individual inputs */
#define ALLINS '0'
#define INPUT1 '1'
#define INPUT2 '2'
#define INPUT3 '3'
#define INPUT4 '4'

enum modes { ON, OFF, TOGGLE };

void getOutputStatus( int fildes, char relay);
void setOutput( int fildes, char relay, int mode);
void setOutputDirect( int fildes, char mask);

void getInputStatus( int fildes, char relay);

#endif/* __IOFUNC_H__ */

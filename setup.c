/*******************************************************************************
* @Title: setup.c 
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
#include "setup.h"
/* headers needed for open() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* headers needed for terminal functions */
#include <termios.h>

/* header needed for perror() */
#include <errno.h>
/* standard headers */
#include <stdio.h>
#include <stdlib.h>

extern char* devName;
extern int fPtr;

struct termios term;

/* This function must setup the character device terminal so that
 * the main body can communicate */
int initialize(){

   /* file descriptor is needed for terminal functions */
   fPtr = open( devName, O_RDWR);  
   if( fPtr <= 0 ){
   /* The open did not work */
      printf( "Failed to open device: %s\n", devName);
      printf( "fPtr = %d\n", fPtr);
      exit(-2);
   }

   int lmask = 0;
   int imask = 0;
   int omask = 0;

   imask &= 0;
   imask |= IGNBRK;

   /* Setup 9600-8-N-1 comm */
   setParam(fPtr, ispeed, B9600);
   setParam(fPtr, ospeed, B9600);
   /* Setup cflags */
   setParam(fPtr, c_cflag, CS8); 
   /* Setup lflags */
   setParam(fPtr, c_lflag, lmask); 
   /* Setup iflags */
   setParam(fPtr, c_iflag, imask); 
   /* Setup oflags */
   setParam(fPtr, c_oflag, omask); 
}
void setParam(int fildes, int param, int val){
   /* scheme: 3 tries to set each attribute. If any attribute cannot be set, exit */
   int triesRemaining = MAXTRIES;
   int code;
   char *fault[4];
   *fault = "GOOD";
   while( triesRemaining-- > 0 ){
      /* set output speed */
      tcgetattr( fPtr, &term);
      switch( param ){

      case ispeed:
#ifdef __DEBUG__
      printf( "%02d: Setting ispeed:\ntries: %d\n", ispeed, triesRemaining);
#endif /*__DEBUG__*/
         if( term.c_ispeed != val ){
            cfsetispeed( &term, val);
            tcsetattr( fPtr, TCSANOW, &term);
         }else{
            return;
         }

      case ospeed:
#ifdef __DEBUG__
      printf( "%02d: Setting ospeed:\ntries: %d\n", ospeed, triesRemaining);
#endif /*__DEBUG__*/
         if( term.c_ospeed != val ){
            cfsetospeed( &term, val);
            tcsetattr( fPtr, TCSANOW, &term);
         }else{
            return;
         }

      case c_cflag:
#ifdef __DEBUG__
      printf( "%02d: Setting c_cflag:\ntries: %d\n", c_cflag, triesRemaining);
#endif /*__DEBUG__*/
         if( (term.c_cflag & CSIZE) != val ){
            term.c_cflag &= ~CSIZE; /* zero the bitset */
            term.c_cflag |= val;    /* set CS8 */
            tcsetattr( fPtr, TCSANOW, &term);
         }else{
            return;
         }
      case c_lflag:
#ifdef __DEBUG__
      printf( "%02d: Setting c_lflag:\ntries: %d\n", c_lflag, triesRemaining);
#endif /*__DEBUG__*/
         if( (term.c_lflag) != val ){
            term.c_lflag = val; 
            tcsetattr( fPtr, TCSANOW, &term);
         }else{
            return;
         }
      case c_iflag:
#ifdef __DEBUG__
      printf( "%02d: Setting c_iflag:\ntries: %d\n", c_iflag, triesRemaining);
#endif /*__DEBUG__*/
         if( (term.c_iflag) != val ){
            term.c_iflag = val;  
            tcsetattr( fPtr, TCSANOW, &term);
         }else{
            return;
         }
      case c_oflag:
#ifdef __DEBUG__
      printf( "%02d: Setting c_oflag:\ntries: %d\n", c_oflag, triesRemaining);
#endif /*__DEBUG__*/
         if( (term.c_oflag) != val ){
            term.c_oflag = val;   
            tcsetattr( fPtr, TCSANOW, &term);
         }else{
            return;
         }
      default:
         /* Do nothing */
         break;
      } /* switch */
   }/* while(tries) */
   
   switch( code = param ){
   case ispeed:
      *fault = "ISPD";
      break;
   case ospeed:
      *fault = "OSPD";
      break;
   case c_cflag:
      *fault = "CCFL";
      break;
   case c_lflag:
      *fault = "CLFL";
      break;
   case c_iflag:
      *fault = "CIFL";
      break;
   case c_oflag:
      *fault = "COFL";
      break;
   default:
     /* Do nothing */
      break;
   }
   printf( "EE: %s ran out of tries during init.\n", *fault);
   exit(-1);

}

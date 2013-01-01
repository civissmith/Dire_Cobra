/*******************************************************************************
* @Title: iofunc.c 
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
#include "iofunc.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

extern int fPtr;

/* getOutputStatus:
 *
 */
#define BUFF 4
void getOutputStatus( int fildes, char relay){

   char wBuff[3];
   char rBuff[BUFF];
   char re_read_required = 1;
   int i;

   /* Set the status command */
   wBuff[0] = 'S';
   wBuff[1] = relay;
   wBuff[2] = '\r';

   write( fildes, (const void*) wBuff, (sizeof(wBuff)));
   usleep(TRANSDELAY);  /* slow the transition between writing and reading */
   read( fildes, (void*) rBuff, sizeof(rBuff));

   if( relay == '0' ){
      read( fildes, (void*) rBuff, sizeof(rBuff));

      printf("\nOutput Status:\n");
      printf("5 through 8: %c\n", rBuff[0]);
      printf("1 through 4: %c\n", rBuff[1]);

   }else{
      read( fPtr, (void*) rBuff, sizeof(rBuff)-1);
      printf("Output Status:\n");
      printf("Relay #%c: %c\n", relay, rBuff[0]);

   }

   /* Attempt to read the trailing '#' out of the buffer */
   read( fildes, (void*) rBuff, sizeof(rBuff)-(BUFF-1));

/* NOTE: Sometimes the <cr><lf> will be mis-read, the final character should
 *       always be '#', but this may not be what was captured. This check
 *       (as kludgy as it may be) will scan to make sure that a '#' was the
 *       last thing in the controller's write buffer - signaling that it is
 *       ready for more input */
   /* search for a trailing '#' */
   for( i = 0; i < BUFF; i++){
      if( rBuff[i] == '#' ){
         re_read_required = 0;
      }
   }
   if( re_read_required ){
     read( fildes, (void*) rBuff, sizeof(rBuff)-(BUFF-1));
   }
}

/* getInputStatus
 *
 */

#define BUFF2 5
void getInputStatus( int fildes, char relay){
   char wBuff[3];
   char rBuff[BUFF2];
   short re_read_required = 1;

   int i = 0;
   /* Set the status command */
   wBuff[0] = 'I';
   wBuff[1] = relay;
   wBuff[2] = '\r';

   write( fildes, (const void*) wBuff, (sizeof(wBuff)));
   usleep(TRANSDELAY);  /* slow the transition between writing and reading */

// for( i = 0; i < BUFF2; i++){
//    rBuff[i] = '%';
// }
// printf("\nClearing echo from buffer\n");
   read( fildes, (void*) rBuff, sizeof(rBuff)-1);
// for( i = 0; i < BUFF2; i++){
//    if( rBuff[i] == '\n')
//       printf("rBuff[%d]: <lf>\t%02x\n",i,rBuff[i],rBuff[i]);
//    else if( rBuff[i] == '\r')
//       printf("rBuff[%d]: <cr>\t%02x\n",i,rBuff[i],rBuff[i]);
//    else
//       printf("rBuff[%d]: %c\t%02x\n",i,rBuff[i],rBuff[i]);
// }


   /* Inputs only occupy rBuff[1] */
   if( relay == '0' ){
//    for( i = 0; i < BUFF2; i++){
//       rBuff[i] = '*';
//    }

//    printf("\nReading inputs\n");
      read( fildes, (void*) rBuff, sizeof(rBuff));
//    for( i = 0; i < BUFF2; i++){
//       if( rBuff[i] == '\n')
//          printf("rBuff[%d]: <lf>\t%02x\n",i,rBuff[i],rBuff[i]);
//       else if( rBuff[i] == '\r')
//          printf("rBuff[%d]: <cr>\t%02x\n",i,rBuff[i],rBuff[i]);
//       else
//          printf("rBuff[%d]: %c\t%02x\n",i,rBuff[i],rBuff[i]);
//    }
      for( i = 0; i < BUFF2; i++){
         if( rBuff[i] != 0x0a  )
            re_read_required = 1;
         else
            re_read_required = 0;
      }
      if( re_read_required ){
        read( fildes, (void*) rBuff, sizeof(rBuff)-(BUFF2-1));
      }

        printf("\nInput Status:\n");
        printf("1 through 4: %c\n", rBuff[1]);
   }else{
//    for( i = 0; i < BUFF2; i++){
//       rBuff[i] = '^';
//    }
      read( fPtr, (void*) rBuff, sizeof(rBuff)-1);
//    for( i = 0; i < BUFF2; i++){
//       if( rBuff[i] == '\n')
//          printf("rBuff[%d]: <lf>\t%02x\n",i,rBuff[i],rBuff[i]);
//       else if( rBuff[i] == '\r')
//          printf("rBuff[%d]: <cr>\t%02x\n",i,rBuff[i],rBuff[i]);
//       else
//          printf("rBuff[%d]: %c\t%02x\n",i,rBuff[i],rBuff[i]);
//    }
        printf("\nInput Status:\n");
        printf("Input #%c: %c\n", relay, rBuff[0]);
   }

   /* Attempt to read the trailing '#' out of the buffer */

/* NOTE: Sometimes the <cr><lf> will be mis-read, the final character should
 *       always be '#', but this may not be what was captured. This check
 *       (as kludgy as it may be) will scan to make sure that a '#' was the
 *       last thing in the controller's write buffer - signaling that it is
 *       ready for more input */
   /* search for a trailing '#' */
   for( i = 0; i < BUFF2; i++){
      if( rBuff[i] == '#' ){
         re_read_required = 0;
      }
   }
   if( re_read_required ){
     read( fildes, (void*) rBuff, sizeof(rBuff)-(BUFF2-1));
   }


}

/* setOutput:
 *
 */
void setOutput( int fildes, char relay, int mode){

   char wBuff[3];
   char rBuff[5];

   /* Set the status command */
   switch( mode ){
   case ON:
      wBuff[0] = 'N';
      break;
   case OFF:
      wBuff[0] = 'F';
      break;
   case TOGGLE:
      wBuff[0] = 'T';
      break;
   default:
      break;
      /* DO NOTHING */
   }
   wBuff[1] = relay;
   wBuff[2] = '\r';

   write( fildes, (const void*) wBuff, (sizeof(wBuff)));
   usleep(TRANSDELAY);  /* slow the transition between writing and reading */

   /* This read is to discard the echo, it must be done so succesive reads
    * don't grab bad data */
   read( fildes, (void*) rBuff, sizeof(rBuff));
}
/* setOutputDirect:
 *
 */

void setOutputDirect( int fildes, char mask){

   char wBuff[4];
   char rBuff[6];

   /* Set the status command */
   wBuff[0] = 'R';
   wBuff[1] = (((mask & 0xF0) >> 4) + 0x30);
   wBuff[2] = ((mask & 0x0F) + 0x30);
   wBuff[3] = '\r';

   write( fildes, (const void*) wBuff, (sizeof(wBuff)));
   usleep(TRANSDELAY);  /* slow the transition between writing and reading */

   /* This read is to discard the echo, it must be done so succesive reads
    * don't grab bad data */
   read( fildes, (void*) rBuff, sizeof(rBuff));


}

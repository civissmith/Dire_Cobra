/*******************************************************************************
* @Title: controller.c 
*
* @Author: Phil Smith 
*
* @Date: 29-Oct-2011	01:10 PM
*
* @Project: Controller
*
* @Purpose: The main entry point for the controller daemon.
*
* @Modification History: 
*
*******************************************************************************/
//#define __DEBUG__
#include "iofunc.h"
#include "setup.h"
#include <fcntl.h>

/* vars to be paramaterized later */
char* devName = "/dev/ttyUSB0";
int  fPtr;


int main(){

   initialize();
   

   getOutputStatus(fPtr, ALLOUTS);
   getOutputStatus(fPtr, ALLOUTS);
   getInputStatus(fPtr, ALLINS);
   getInputStatus(fPtr, INPUT1);
   getInputStatus(fPtr, INPUT2);
   getInputStatus(fPtr, INPUT3);
   getInputStatus(fPtr, INPUT4);
   setOutput(fPtr, OUTPUT5, ON);
   getOutputStatus(fPtr, OUTPUT5);
   sleep(1);
   setOutput(fPtr, OUTPUT6, ON);
   getOutputStatus(fPtr, OUTPUT6);
   sleep(1);
   setOutput(fPtr, OUTPUT7, ON);
   getOutputStatus(fPtr, OUTPUT7);
   sleep(1);
   setOutput(fPtr, OUTPUT8, ON);
   getOutputStatus(fPtr, OUTPUT8);
   sleep(1);

   getOutputStatus(fPtr, ALLOUTS);
   setOutputDirect(fPtr, NO_OP);
   getOutputStatus(fPtr, ALLOUTS);


   close(fPtr);
}

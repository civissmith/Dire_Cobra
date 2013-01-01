/*******************************************************************************
* @Title: setup.h 
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
#ifndef __SETUP_H__
#define __SETUP_H__


/* ISPEED - input serial speed */
/* unit: bits per second (baud) */
#define ISPEED B9600

/* OSPEED - output serial speed */
/* unit: bits per second (baud) */
#define OSPEED B9600

#define MAXTRIES 10

enum params { ispeed, ospeed, c_cflag, c_iflag, c_oflag, c_lflag};

int initialize();
void setParam(int fildes, int param, int val);

#endif /* __SETUP_H__ */

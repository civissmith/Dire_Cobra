#!/usr/bin/tcsh
################################################################################
# @Title: connectTocontroller.sh 
#
# @Author: Phil Smith 
#
# @Date: 30-Oct-2011	02:17 PM
#
# @Project: 
#
# @Purpose: connects to the device at USB0 at 9600. Should work for Arduino
#           or serial I/O box.
#
# @Modification History: 
#
###############################################################################
stty -F /dev/ttyUSB0 cs8 9600 ignbrk -brkint -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts

screen /dev/ttyUSB0 9600

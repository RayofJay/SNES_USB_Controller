# SNES_USB_Controller
Convert an Original SNES Controller to USB primarily to be used with PC emulators.

version 1.03 by JayRay

I bought a teensy 3.2 to convert a SNES controller I had, but all the information I found either was for the old teensy 2.0, didn't provide the arduino code, didn't use the V520B chip in the SNES controller, or left out too much detail.  The arduino code attached works with the teensy 3.2 board and wired as shown to the SNES controller board.

I'm omitting a lot of detail here because this detail is easily found elsewhere via google.  This posting is to demonstrate the procedure specifically on the teensy 3.2 and to provide the actual arduino code.

Note that the assembled image attached shows the teensy outside the controller.  This will be the finally step to my project - to house the teensy inside the controller.  Since this will not change the arduino code, I am creating this posting now.



UPDATE (22-Jul-2017 10:00) version 1.04

I've investigated other devices looking for something smaller to fit in the controller better, but nothing found thus far.  The Adafruit Trinket looked promising, but it doesn't have the onboard USB-serial converter.  

I've just about decided to totall remove the white connector base on the SNES controller.  It's no longer required as I can wired the Teensy directly to the SNES board.  I can also replace the stiff SNES cable with something lighter/smaller, or, at least, trim it down significantly and remove the sheathing.  Johnburkets method of removee the collar from around the mini USB connector seems to be in order as well.  So far, I have removed the center post from the back of the controller that supports the pressing of the start and select button.  This removal does not seem to flex the board in any adverse manner, as well the Start and Select buttons are rarely pressed compared to the DPad and XYAB button.

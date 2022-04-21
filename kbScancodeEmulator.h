#ifndef ___KBSCANCODEEMULATOR
#define ___KBSCANCODEEMULATOR
#include <stdio.h>
#include <string.h>
#include "usb_hid_keys.h"

class KbScancodeEmulator

{
	public:
	KbScancodeEmulator();
~	KbScancodeEmulator();
	void MakeScancodeString(unsigned char charToSend, unsigned char specialKey, unsigned char * bString, int * bStringDim, bool encode);
	void SendKbScancode();
	void SendKbSpecialScancode(unsigned char key, unsigned char specialKey, bool encode);
	bool CheckSpecialKey();

	FILE* kbFile;
	unsigned char keyboardBuffer[256];

	unsigned char specialCodes[30] [10] = {
		27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 				// 00-Escape
		27, 91, 65, 10, 0, 0, 0, 0, 0, 0, 			// 01-ArrowUp
		27, 91, 66, 10, 0, 0, 0, 0, 0, 0, 			// 02-ArrowDown
		27, 91, 67, 10, 0, 0, 0, 0, 0, 0, 			// 03-ArrowRight
		27, 91, 68, 10, 0, 0, 0, 0, 0, 0, 			// 04-ArrowLeft
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 05-F1
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0,		// 06-F2
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0,		// 07-F3
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 08-F4
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 09-F5
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 10-F6
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 11-F7
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 12-F8
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 13-F9
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 14-F10
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 15-F11
		27, 91, 49, 49, 126, 10, 0, 0, 0, 0, 		// 16-F12
		27, 91, 53, 126, 10, 0, 0, 0, 0, 0, 		// 17-PgUp
		27, 91, 54, 126, 10, 0, 0, 0, 0, 0, 		// 18-PgDn
		27, 91, 50, 126, 10, 0, 0, 0, 0, 0, 		// 19-Insert
		27, 91, 51, 126, 10, 0, 0, 0, 0, 0, 		// 20-Delete
		27, 91, 49, 126, 10, 0, 0, 0, 0, 0, 		// 21-Home
		27, 91, 52, 126, 10, 0, 0, 0, 0, 0, 		// 22-End
		27, 91, 49, 59, 53, 65, 10, 0, 0, 0,	 	// 23-PgUp NBK
		27, 91, 49, 59, 53, 66, 10, 0, 0, 0, 		// 24-PgDn NBK
		27, 91, 49, 59, 53, 68, 10, 0, 0, 0, 		// 25-Home NBK
		27, 91, 49, 59, 53, 67, 10, 0, 0, 0,		// 26-End NBK
		9, 10, 0, 0, 0, 0, 0, 0, 0, 0, 				// 27-Return
		9, 10, 0, 0, 0, 0, 0, 0, 0, 0 				// 28-TAB
		};

	protected:
	unsigned char EncodeCharForKB(unsigned char charToEncode, int * charShift);

	unsigned char releaseKeys[9];
	unsigned char commandText[14];
	int commandDim;


};
	
#endif

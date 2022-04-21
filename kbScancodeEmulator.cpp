#include "kbScancodeEmulator.h"

KbScancodeEmulator::KbScancodeEmulator()
{
	commandDim=0;
	for(int i=0; i<8; i++)
	releaseKeys[i]=0;
}

KbScancodeEmulator::~KbScancodeEmulator()
{
}

unsigned char KbScancodeEmulator::EncodeCharForKB(unsigned char charToEncode, int * charShift)
{
	if( (charToEncode > '0') && (charToEncode <= '9'))
	{
		*charShift=0;
		return charToEncode-19;
	}

	if( (charToEncode <= 'z') && (charToEncode >= 'a'))
	{
		*charShift=0;
		return charToEncode-93;
	}

	if( (charToEncode <= 'Z') && (charToEncode >= 'A'))
	{
		*charShift=1;
		return charToEncode-61;
	}
	*charShift=1;
	switch(charToEncode)
	{
		case 126: // ~
			return 53;
		case 33: // !
			return 30;
		case 64: // @
			return 31;
		case 35: // #
			return 32;
		case 36: // $
			return 33;
		case 37: // %
			return 34;
		case 94: // ^
			return 35;
		case 38: // &
			return 36;
		case 42: // *
			return 37;
		case 40: // (
			return 38;
		case 41: // )
			return 39;
		case 95: // _
			return 45;
		case 43: // +
			return 46;
		case 123: // {
			return 47;
		case 125: // }
			return 48;
		case 124: // |
			return 49;
		case 58: // :
			return 51;
		case 34: // "
			return 52;
		case 60: // <
			return 54;
		case 62: // >
			return 55;
		case 63: // ?
			return 56;
	}
	*charShift=0;
	switch(charToEncode)
	{
		case 96: // `
			return 53;
		case 48: // 0
			return 39;
		case 45: // -
			return 45;
		case 61: // =
			return 46;
		case 91: // [
			return 47;
		case 93: // ]
			return 48;
		case 92: // "\"
			return 49;
		case 59: // ;
			return 51;
		case 39: // '
			return 52;
		case 44: // ,
			return 54;
		case 46: // .
			return 55;
		case 47: // /
			return 56;
		case 32: // space
			return 44;
		case 10: // line feed
			return 40;
	}
	return 0;
}

void KbScancodeEmulator::MakeScancodeString(unsigned char charToSend,  unsigned char specialKey, unsigned char * bString, int * bStringDim, bool encode=true)
{
	int option;
	unsigned char kbChar;
	if(encode)
	{
		kbChar=EncodeCharForKB(charToSend, &option);
		if(specialKey==0)
		{
			switch(option)
			{
				case 0: // regular
					bString[0]=0;
					bString[1]=0;
				break;
		
				case 1: // shifted
					bString[0]=32;
					bString[1]=0;
				break;
			}
		}
		else
		{
			bString[0]=specialKey;
			bString[1]=0;
		}
		bString[2]=kbChar;
	}
	else
	{
		bString[0]=0;
		bString[1]=0;
		bString[2]=charToSend;
	}
	for( int i=0; i<5; i++)
		bString[i+3]=0;
	*bStringDim=8;
}

void KbScancodeEmulator::SendKbScancode()
{
	if(CheckSpecialKey())
		return;
	if( !(kbFile=fopen("/dev/hidg0", "wb")))
	{
		printf("Unable to open keyboard device file: /dev/hidg0\n");
		return;
	}	

	for(int i=0; i<sizeof(keyboardBuffer); i++)
	{
		if(keyboardBuffer[i]==10)
			break;
		MakeScancodeString(keyboardBuffer[i], 0, commandText, &commandDim);
		fwrite(commandText, commandDim, 1, kbFile);
		fwrite(releaseKeys, 8, 1, kbFile);
	}
	MakeScancodeString(10, 0, commandText, &commandDim); // line feed
	
	fwrite(commandText, commandDim, 1, kbFile);	
	fwrite(releaseKeys, 8, 1, kbFile);	
	fclose(kbFile);
}

void KbScancodeEmulator::SendKbSpecialScancode(unsigned char key, unsigned char specialKey, bool encode=true)
{
	if( !(kbFile=fopen("/dev/hidg0", "wb")))
	{
		printf("Unable to open keyboard device file: /dev/hidg0\n");
		return;
	}	
	MakeScancodeString(key, specialKey, commandText, &commandDim, encode);
	fwrite(commandText, commandDim, 1, kbFile);	
	fwrite(releaseKeys, 8, 1, kbFile);	
	fclose(kbFile);
}

	bool KbScancodeEmulator::CheckSpecialKey()
{
//*
	for(int i=0; i<30; i++)
	{

		if( !strcmp((char*)specialCodes[i] , (char*)keyboardBuffer))
		{
			unsigned char spKey=0;
			switch(i)
			{
				case 0: // Escape
					spKey=KEY_ESC;
				break;
				case 1: // ArrowUp
					spKey=KEY_UP;
				break;
				case 2: // ArrowDown
					spKey=KEY_DOWN;
				break;
				case 3: // ArrowRight
					spKey=KEY_RIGHT;
				break;

				case 4: // ArrowLeft
					spKey=KEY_LEFT;
				break;
				case 5: // F1
					spKey=KEY_F1;
				break;
				case 6: // F2
					spKey=KEY_F2;
				break;
				case 7: // F3
					spKey=KEY_F3;
				break;
				case 8: // F4
					spKey=KEY_F4;
				break;
				case 9: // F5
					spKey=KEY_F5;
				break;
				case 10: // F6
					spKey=KEY_F6;
				break;
				case 11: // F7
					spKey=KEY_F7;
				break;
				case 12: // F8
					spKey=KEY_F8;
				break;
				case 13: // F9
					spKey=KEY_F9;
				break;
				case 14: // F10
					spKey=KEY_F10;
				break;
				case 15: // F11
					spKey=KEY_F11;
				break;
				case 16: // F12
					spKey=KEY_F12;
				break;
				case 17: // PgUp
					spKey=KEY_PAGEUP;
				break;
				case 18: // PgDn
					spKey=KEY_PAGEDOWN;
				break;
				case 19: // Insert
					spKey=KEY_INSERT;
				break;
				case 20: // Delete
					spKey=KEY_DELETE;
				break;
				case 21: // Home
					spKey=KEY_HOME;
				break;
				case 22: // End
					spKey=KEY_END;
				break;
				case 23: // PgUp NBK
					spKey=KEY_PAGEUP;
				break;
				case 24: // PgDn NBK
					spKey=KEY_PAGEDOWN;
				break;
				case 25: // Home NBK
					spKey=KEY_HOME;
				break;
				case 26: // End NBK
					spKey=KEY_END;
				break;
				case 27: // Return
					spKey=KEY_ENTER;
				break;
				case 28: // TAB
					spKey=KEY_TAB;
				break;




			}
			SendKbSpecialScancode(spKey, 0, false);
			return true;
		}
	}
//*/

	if(!strcmp("helpme\n", (char*)keyboardBuffer))
	{
		printf("\nSpecial commands: ctrlc=ctrl+c, ctrlo=ctrl+o, ctrlz=ctrl+z\n");
		printf("keyback=Backspace, keydel=Delete\n");
		printf("keyup, keydown, keyleft, keyright - arrow keys\n");
		printf("\n");
		return true;
	}
	if(!strcmp("ctrlc\n", (char*)keyboardBuffer))
	{
		SendKbSpecialScancode('c', KEY_MOD_LCTRL);
		return true;
	}
	if(!strcmp("ctrlo\n", (char*)keyboardBuffer))
	{
		SendKbSpecialScancode('o', KEY_MOD_LCTRL);
		return true;
	}
	if(!strcmp("ctrlz\n", (char*)keyboardBuffer))
	{
		SendKbSpecialScancode('z', KEY_MOD_LCTRL);
		return true;
	}
	if(!strcmp("keyup\n", (char*)keyboardBuffer))
	{
		SendKbSpecialScancode(KEY_UP, 0, false);
		return true;
	}
	if(!strcmp("keydown\n", (char*)keyboardBuffer))
	{
		SendKbSpecialScancode(KEY_DOWN, 0, false);
		return true;
	}
	if(!strcmp("keyleft\n", (char*)keyboardBuffer))
	{
		SendKbSpecialScancode(KEY_LEFT, 0, false);
		return true;
	}
	if(!strcmp("keyright\n", (char*)keyboardBuffer))
	{
		SendKbSpecialScancode(KEY_RIGHT, 0, false);
		return true;
	}
	if(!strcmp("keyback\n", (char*)keyboardBuffer))
	{
		SendKbSpecialScancode(KEY_BACKSPACE, 0, false);
		return true;
	}
	if(!strcmp("keydel\n", (char*)keyboardBuffer))
	{
		SendKbSpecialScancode(KEY_DELETE, 0, false);
		return true;
	}
	return false;
}

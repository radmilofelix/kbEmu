#include <stdio.h>
#include "kbScancodeEmulator.h"

#define DEBUG

KbScancodeEmulator kbscem;

int main(int argc, char **argv)
{
	printf("kbEmu start.\nHit Enter to send the string to USB.\nUse ctrl/c to exit.\n\n");
	
	while(1)
	{
		printf(" > ");
		fgets((char*)kbscem.keyboardBuffer, sizeof(kbscem.keyboardBuffer), stdin);
#ifdef DEBUG
	for(int i=0; i<256; i++)
	{
		if(kbscem.keyboardBuffer[i]==0)
			break;
	}
#endif		
		kbscem.SendKbScancode();
	}
	printf("Program end.\n\n");
}

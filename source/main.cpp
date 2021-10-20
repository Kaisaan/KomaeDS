#include <nds.h>
#include <maxmod9.h>
#include <stdio.h>

// grit adds a nice header we can include to access the data
// this has the same name as the image
#include "nagito.h"

#include "soundbank.h"
#include "soundbank_bin.h"

int main(void)
{
    // set the mode for 2 text layers and two extended background layers
	videoSetMode(MODE_5_2D);
    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);

	consoleDemoInit();

	mmInitDefaultMem((mm_addr)soundbank_bin);
	
	mmLoadEffect ( SFX_NAGITO );
	mm_sound_effect nagito = {
		{ SFX_NAGITO } ,			// id
		(int)(1.0f * (1<<10)),	// rate
		0,		// handle
		255,	// volume
		127,	// panning
	};

	iprintf("\n\tHello there, everyone!\n");
	iprintf("\tIt's me, Nagito Komaeda\n");
	iprintf("\tOn the Nintendo DS!\n");
	iprintf("\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	iprintf("\n\n\tMade by Kaisaan Siddiqui");

	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);

	dmaCopy(nagitoBitmap, bgGetGfxPtr(bg3), 256*256);
	dmaCopy(nagitoPal, BG_PALETTE, 256*2);
	
	mmEffectEx(&nagito);
	
	while(1) {
		swiWaitForVBlank();
		scanKeys();
		if (keysDown()&KEY_START) break;
	}

	return 0;
}

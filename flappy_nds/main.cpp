#include <nds.h>
#include <nds/arm9/input.h>
#include <gl2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "pipe.h"
#include "player.h"

int score = 0;
std::vector<Pipe> pipes;

void renderPlayer(Player* player) {
	glBoxFilled(
		250,
		player->getY() - 10,
		256,
		player->getY() + 10,
		RGB15(0, 255, 0)
	);
}

bool processInput(Player* player) {
	scanKeys();
	int keys = keysDown();
	if (keys & KEY_START) return true;
	return false;
}

void drawPipe(Player* player) {
	
}

void vblank() {}

int main(void) {
	videoSetMode(MODE_5_3D);
	irqSet(IRQ_VBLANK, vblank);
	glScreen2D();
	Player player;

	for (int i = 0; i < 4; i++) {
		Pipe pipe(
			96,
			0,
			//TODO: Pipe generation
		);
	}

	while(1) {
		if (processInput(&player)) break;
		glBegin2D();
		renderPlayer(&player);
		drawPipe(&player);
		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}
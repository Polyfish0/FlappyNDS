#include <nds.h>
#include <nds/arm9/input.h>
#include <gl2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include "pipe.h"
#include "player.h"

int score = 0;
float speed = 0.05;
std::vector<Pipe> pipes;

void processPhysics(Player* player, std::vector<Pipe>* pipes) {
	for(unsigned int i = 0; i < pipes->size(); i++) {
		Pipe pipe = pipes->at(i);
		pipe.setPosX(pipe.getPosX() - speed);
		std::replace(pipes->begin(), pipes->end(), pipes->at(i), pipe);
	}
}

void renderPlayer(Player* player) {
	glBoxFilled(250, player->getY() - 10, 256, player->getY() + 10, RGB15(0, 255, 0));
}

bool processInput(Player* player) {
	scanKeys();
	int keys = keysDown();
	if(keys & KEY_START) return true;
	return false;
}

void drawPipes(std::vector<Pipe>* pipes) {
	for(unsigned int i = 0; i < pipes->size(); i++) {
		Pipe pipe = pipes->at(i);
		glBoxFilled(pipe.getPosX(), 0, pipe.getPosX() + 10, 21 + pipe.getShift(), RGB15(0, 255, 0));
		glBoxFilled(pipe.getPosX(), 192, pipe.getPosX() + 10, 71 + pipe.getShift(), RGB15(0, 255, 0));
	}
}

void vblank() {}

int main(void) {
	videoSetMode(MODE_5_3D);
	irqSet(IRQ_VBLANK, vblank);
	srand(time(NULL));
	glScreen2D();
	Player player;

	for(int i = 0; i < 3; i++) {
		Pipe pipe(96 + (55 * i), rand() % 101);
		pipes.push_back(pipe);
	}

	while(1) {
		if(processInput(&player)) break;
		glBegin2D();
		renderPlayer(&player);
		drawPipes(&pipes);
		processPhysics(&player, &pipes);
		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}
	return 0;
}
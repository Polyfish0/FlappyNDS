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
float speed = 0.3;
float velocity = 0;
const float gravityFactor = 0.05;
const float gravity = 1.5;
int color = RGB15(0, 255, 0);
std::vector<Pipe> pipes;

void processPhysics(Player* player, std::vector<Pipe>* pipes) {
	for(unsigned int i = 0; i < pipes->size(); i++) {
		Pipe pipe = pipes->at(i);
		if(pipe.getPosX() <= -10) {
			pipes->at(i) = Pipe(256, rand() % 101, 10, 1);
		}else {
			pipe.setPosX(pipe.getPosX() - speed);
			pipes->at(i) = pipe;
		}
	}

	float newY = player->getY() + (gravity + velocity);

#ifdef DEBUG
	printf("\x1b[6;0HnewY = %f", newY);
#endif
	
	if(newY <= 14.9) {
		player->setY(15);
		velocity = -1.5;
	}else if(newY >= 192) {
		player->setAlive(false);
	}else {
		player->setY(newY);
	}

	if(velocity != 0) {
		if(velocity + gravityFactor <= 0) {
			velocity += gravityFactor;
		}else {
			velocity = 0;
		}
	}
}

void renderPlayer(Player* player) {
	glBoxFilled(80, player->getY() - 15, 86, player->getY(), color);
}

bool processInput(Player* player) {
	scanKeys();
	int keys = keysDown();
	if(keys & KEY_START) return true;
	if(player->isAlive()) {
		if(keys & KEY_A) velocity = -2.5;
	}else {
	}
	return false;
}

void renderPipes(std::vector<Pipe>* pipes) {
	for(unsigned int i = 0; i < pipes->size(); i++) {
		Pipe pipe = pipes->at(i);
		glBoxFilled(pipe.getPosX(), 0, pipe.getPosX() + pipe.getThickness(), 21 + pipe.getShift(), color);
		glBoxFilled(pipe.getPosX(), 192, pipe.getPosX() + pipe.getThickness(), 71 + pipe.getShift(), color);
	}
}

void checkHitbox(Player* player, std::vector<Pipe>* pipes) {
	for(unsigned int i = 0; i < pipes->size(); i++) {
		Pipe pipe = pipes->at(i);
		if(pipe.getPosX() <= 80) {
			score += pipe.getPoints();
			pipe.setPoints(0);
			pipes->at(i) = pipe;
		}
		if(pipe.getPosX() < 80) {
			if(80 < pipe.getPosX() + pipe.getThickness()) {
				if(player->getY() <= 21 + pipe.getShift() || player->getY() >= 71 + pipe.getShift()) {
					player->setAlive(false);
				}
			}
		}
	}
}

void vblank() {}

int main(void) {
#ifdef DEBUG
	defaultExceptionHandler();
	consoleDemoInit();
#endif
	videoSetMode(MODE_5_3D);
	irqSet(IRQ_VBLANK, vblank);
	srand(time(NULL));
	glScreen2D();
	Player player;

	for(int i = 0; i < 4; i++) {
		Pipe pipe(162 + (70 * i), rand() % 101, 10, 1);
		pipes.push_back(pipe);
	}

	while(1) {
#ifdef DEBUG
		printf("\x1b[0;0HVelocity = %f", velocity);
		printf("\x1b[2;0HAlive = %d", player.isAlive());
		printf("\x1b[4;0HPlayer Y = %f", player.getY());
		printf("\x1b[8;0HScore = %d", score);
#endif
		if(processInput(&player)) break;
		glBegin2D();
		renderPlayer(&player);
		checkHitbox(&player, &pipes);
		renderPipes(&pipes);
		if(player.isAlive()) {
			processPhysics(&player, &pipes);
		}
		glEnd2D();
		glFlush(0);
		swiWaitForVBlank();
	}
	return 0;
}
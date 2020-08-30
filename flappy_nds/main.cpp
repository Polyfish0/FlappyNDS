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
		if(pipes->at(i).getPosX() <= -10) {
			pipes->at(i).setShift(rand() % 101);
			pipes->at(i).setPoints(1);
			pipes->at(i).setPosX(256);
		}else {
			pipes->at(i).setPosX(pipes->at(i).getPosX() - speed);
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
		glBoxFilled(pipes->at(i).getPosX(), 0, pipes->at(i).getPosX() + pipes->at(i).getThickness(), 21 + pipes->at(i).getShift(), color);
		glBoxFilled(pipes->at(i).getPosX(), 192, pipes->at(i).getPosX() + pipes->at(i).getThickness(), 71 + pipes->at(i).getShift(), color);
	}
}

void checkHitbox(Player* player, std::vector<Pipe>* pipes) {
	for(unsigned int i = 0; i < pipes->size(); i++) {
		if(pipes->at(i).getPosX() <= 80) {
			score += pipes->at(i).getPoints();
			pipes->at(i).setPoints(0);
		}
		if(pipes->at(i).getPosX() < 86) {
			if(86 < pipes->at(i).getPosX() + pipes->at(i).getThickness()) {
				if(player->getY() <= 21 + pipes->at(i).getShift() || player->getY() >= 71 + pipes->at(i).getShift()) {
					player->setAlive(false);
				}
			}
		}
	}
}

void vblank() {}

int main(void) {
	defaultExceptionHandler();
	consoleDemoInit();
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
#ifndef DEBUG
		printf("\x1b[0;0HScore = %d", score);
#endif
#ifdef DEBUG
		printf("\x1b[0;0HVelocity = %f", velocity);
		printf("\x1b[2;0HAlive = %d", player.isAlive());
		printf("\x1b[4;0HPlayer Y = %f", player.getY());
		printf("\x1b[8;0HScore = %d", score);
		printf("\x1b[10;0HPipes vector size = %d", pipes.size());
#endif
		if(processInput(&player)) {
			glEnd2D();
			glFlush(0);
			break;
		}
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
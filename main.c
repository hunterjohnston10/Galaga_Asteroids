/*
# This is the main game logic for a galaga game
#Author: Hunter Johnston (hunterjohnston10@gmail.com)
#Version: 1.1
*/

#include "mylib.h"
#include "game.h"

int main() {

	REG_DISPCNT = MODE3 | BG2_ENABLE;
	
 	
 	while(1) {
 		
 		//title sequence
 		//extern u16* videoBuffer;
		extern Fighter fighter;
		extern Missile missile;
 		int titleScreen;
 		int titleScreenDrawn;
 		int x;
 		int playAgain;
 		int gameOverScreenDrawn;
 		int score;
 		int arrayOffset;
 		int returnToTitle;
 		int speed;
 		extern Enemy enemyArray[ENEMY_ARRAY_SIZE];

 		titleScreen = 1;
 		titleScreenDrawn = 0;
 		while(titleScreen) {
 			if (!KEY_DOWN_NOW(BUTTON_START) && !titleScreenDrawn) {
 				clearScreenBlack();
 				drawTitleScreen();
 				titleScreenDrawn = 1;
 			}
 			if (KEY_DOWN_NOW(BUTTON_START)) {
 				titleScreen = 0;
 				clearScreenBlack();
 			}
 		}

 		wait(100000);

 		//game sequence
 		x = 1;
 		loopCounter = 0;
 		score = 0;
 		arrayOffset = 0;
 		returnToTitle = 0;
 		speed = ENEMY_SPEED_1;
 		while(x != 0) {
 			waitForVblank();
 			clearScreenBlack();
 			drawFighter(&fighter);
 			moveFighter(&fighter);
 			spawnEnemy(&loopCounter, enemyArray, arrayOffset);
 			if (loopCounter % FRAMES_ELAPSED) {
 				arrayOffset++;
 			}
 			if (arrayOffset % ENEMY_ARRAY_SIZE == 0) {
 				arrayOffset = 0;
 			}
 			moveEnemy(enemyArray, speed);
 			shootMissile(&fighter);
 			drawMissile(&missile);
 			moveMissile(&missile);
 			enemyMissileCollision(enemyArray, &missile, &fighter, &score);
 			enemyFighterCollision(enemyArray, &fighter);
 			drawLives(&fighter);
 			drawBoost(&fighter);
 			scoreCounter(&loopCounter, &score);
 			drawScore(&score);
 			if(KEY_DOWN_NOW(BUTTON_SELECT)) {
 				returnToTitle = 1;
 				x = 0;
 				clearScreenBlack();
 			}
 			loopCounter++;
 			if (loopCounter < 0) {
 				loopCounter = 0;
 			}
 			if (fighter.lives == 0) {
 				x = 0;
 				returnToTitle = 0;
 			}
 			if (score >= 1000) {
 				speed = ENEMY_SPEED_2;
 			} else if (score >= 2000) {
 				speed = ENEMY_SPEED_3;
 			} else if (score >= 3000) {
 				speed = ENEMY_SPEED_4;
 			}
 		}

 		resetGame();

 		volatile int y = 0;
 		while (y < 1000 && !KEY_DOWN_NOW(BUTTON_SELECT)) {
 			drawGameOverScreen();
 			y++;
 		}

 		if (KEY_DOWN_NOW(BUTTON_SELECT)) {
 			returnToTitle = 1;
 		}

 		//game over sequence
 		if (returnToTitle) {
 			playAgain = 1;
 			gameOverScreenDrawn = 0;
 		} else {
 			playAgain = 0;
 			gameOverScreenDrawn = 0;
 		}
 		while (!playAgain) {
 			if (!KEY_DOWN_NOW(BUTTON_START) && !gameOverScreenDrawn) {
 				//drawGameOverScreen();
 				drawClosingScreen();
 				gameOverScreenDrawn = 1;
 			}
 			if (KEY_DOWN_NOW(BUTTON_START) || KEY_DOWN_NOW(BUTTON_SELECT)) {
 				playAgain = 1;
 				clearScreenBlack();
 			}
 			
 		}
 		wait(100000);

 	}

	return 0;
}
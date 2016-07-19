#include "mylib.h"
#include "game.h"
#include "galagaplane.h"
#include "galagaplane45.h"
#include "galagaplane90.h"
#include "galagaplane135.h"
#include "galagaplane180.h"
#include "galagaplanen45.h"
#include "galagaplanen90.h"
#include "galagaplanen135.h"
#include "bug.h"
#include "moth.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Fighter fighter = {.x = 110, .y = 70, .lives = 3 , .orientation = 0, .boost = 100};
Missile missile = {.isOnScreen = 0};

void spawnEnemy(int *loopCounter, Enemy *enemyArray, int arrayOffset) {
	int enemyType = rand() % 2;
	int width;
	int height;
	if (enemyType == 1) {
		width = BUG_WIDTH;
		height = BUG_HEIGHT;
	} else {
		width = MOTH_WIDTH;
		height = MOTH_HEIGHT;
	}
	if (!(*loopCounter % FRAMES_ELAPSED) && !((enemyArray+arrayOffset)->isOnScreen)) {
		int x = rand() % 240;
		int y = rand() % 160;
		if (x < 0) {
			x = 5;
		} else if (x > 240 - width) {
			x = 240 - width - 5;
		}
		if (y < 0) {
			y = 5;
		} else if (y > 160 - height) {
			y = 160 - height - 1;
		}
		if (enemyType == 1) {
			Enemy enemy = createEnemy(x, 0, 1);
			*(enemyArray + arrayOffset) = enemy;
		} else {
			Enemy enemy = createEnemy(0, y, 2);
			*(enemyArray + arrayOffset) = enemy;
		}
	}
}

//type = 1 --> bug
//type = 2 --> moth
Enemy createEnemy(int x, int y, int type) {
	Enemy enemy;
	if (type == 1) {	
		enemy.x = x;
		enemy.y = y;
		enemy.isOnScreen = 1;
		enemy.width = BUG_WIDTH;
		enemy.height = BUG_HEIGHT;
		enemy.data = bug_data;
		enemy.type = 1;
		int x = rand() % 2;
		if (x) {
			enemy.orientation = 135;
		} else {
			enemy.orientation = -135;
		}
	} else {
		enemy.x = x;
		enemy.y = y;
		enemy.isOnScreen = 1;
		enemy.width = MOTH_WIDTH;
		enemy.height = MOTH_HEIGHT;
		enemy.data = moth_data;
		enemy.type = 2;
		int x = rand() % 2;
		if (x) {
			enemy.orientation = 45;
		} else {
			enemy.orientation = 135;
		}
	}
	return enemy;
}

void drawEnemy(Enemy *bug) {
	if (bug->isOnScreen) {
		drawImage3(bug->x, bug->y, bug->width, bug->height, bug->data);
	}
}

void moveEnemy(Enemy *enemyArray, int enemySpeed) {
	for (int i = 0; i < ENEMY_ARRAY_SIZE; i++) {
		if ((enemyArray + i)->orientation == -135) {
			if ((enemyArray + i)->x <= 0 && ((enemyArray + i)->y + (enemyArray + i)->height) >= 160) {
				(enemyArray + i)->orientation = 45;
				((enemyArray + i)->x) += enemySpeed;
				((enemyArray + i)->y) -= enemySpeed;
			} else if ((enemyArray + i)->x <= 0) {
				((enemyArray + i)->orientation) = 135;
				((enemyArray + i)->x) += enemySpeed;
				((enemyArray + i)->y) += enemySpeed;
			} else if (((enemyArray + i)->y + (enemyArray + i)->height) >= 160) {
				((enemyArray + i)->orientation) = -45;
				((enemyArray + i)->x) -= enemySpeed;
				((enemyArray + i)->y) -= enemySpeed;
			} else {
				((enemyArray + i)->x) -= enemySpeed;
				((enemyArray + i)->y) += enemySpeed;
			}
		} else if ((enemyArray + i)->orientation == -45) {
			if ((enemyArray + i)->x <= 0 && ((enemyArray + i)->y <= 0)) {
				(enemyArray + i)->orientation = 135;
				((enemyArray + i)->x) += enemySpeed;
				((enemyArray + i)->y) += enemySpeed;
			} else if ((enemyArray + i)->x <= 0) {
				(enemyArray + i)->orientation = 45;
				((enemyArray + i)->x) += enemySpeed;
				((enemyArray + i)->y) -= enemySpeed;
			} else if ((enemyArray + i)->y <= 0) {
				(enemyArray + i)->orientation = -135;
				((enemyArray + i)->x) -= enemySpeed;
				((enemyArray + i)->y) += enemySpeed;
			} else {
				((enemyArray + i)->x) -= enemySpeed;
				((enemyArray + i)->y) -= enemySpeed;
			}
		} else if ((enemyArray + i)->orientation == 45) {
			if (((enemyArray + i)->x) + ((enemyArray + i)->width) >= 240 && ((enemyArray + i)->y <= 0)) {
				(enemyArray + i)->orientation = -135;
				((enemyArray + i)->x) -= enemySpeed;
				((enemyArray + i)->y) += enemySpeed;
			} else if (((enemyArray + i)->x) + ((enemyArray + i)->width) >= 240) {
				((enemyArray + i)->orientation) = -45;
				((enemyArray + i)->x) -= enemySpeed;
				((enemyArray + i)->y) -= enemySpeed;
			} else if ((enemyArray + i)->y <= 1) {
				(enemyArray + i)->orientation = 135;
				((enemyArray + i)->x) += enemySpeed;
				((enemyArray + i)->y) += enemySpeed;
			} else {
				((enemyArray + i)->x) += enemySpeed;
				((enemyArray + i)->y) -= enemySpeed;
			}
		} else if ((enemyArray + i)->orientation == 135) {
			if (((enemyArray + i)->x) + ((enemyArray + i)->width) >= 240 && ((enemyArray + i)->y + (enemyArray + i)->height) >= 160) {
				((enemyArray + i)->orientation) = -45;
				((enemyArray + i)->x) -= enemySpeed;
				((enemyArray + i)->y) -= enemySpeed;
			} else if (((enemyArray + i)->x) + ((enemyArray + i)->width) >= 240) {
				(enemyArray + i)->orientation = -135;
				((enemyArray + i)->x) -= enemySpeed;
				((enemyArray + i)->y) += enemySpeed;
			} else if (((enemyArray + i)->y + (enemyArray + i)->height) >= 160) {
				(enemyArray + i)->orientation = 45;
				((enemyArray + i)->x) += enemySpeed;
				((enemyArray + i)->y) -= enemySpeed;
			} else {
				((enemyArray + i)->x) += enemySpeed;
				((enemyArray + i)->y) += enemySpeed;
			}
		}
		drawEnemy(enemyArray + i);
	}
}

void drawFighter(Fighter *fighter) {
	if (fighter->orientation == 0) {
		drawImage3(fighter->x, fighter->y, GALAGAPLANE_WIDTH, GALAGAPLANE_HEIGHT, galagaplane_data);
	} else if (fighter->orientation == 45) {
		drawImage3(fighter->x, fighter->y, GALAGAPLANE45_WIDTH, GALAGAPLANE45_HEIGHT, galagaplane45_data);
	} else if (fighter->orientation == 90) {
		drawImage3(fighter->x, fighter->y, GALAGAPLANE90_WIDTH, GALAGAPLANE90_HEIGHT, galagaplane90_data);
	} else if (fighter->orientation == 135) {
		drawImage3(fighter->x, fighter->y, GALAGAPLANE135_WIDTH, GALAGAPLANE135_HEIGHT, galagaplane135_data);
	} else if (fighter->orientation == 180) {
		drawImage3(fighter->x, fighter->y, GALAGAPLANE180_WIDTH, GALAGAPLANE180_HEIGHT, galagaplane180_data);
	} else if (fighter->orientation == -45) {
		drawImage3(fighter->x, fighter->y, GALAGAPLANEN45_WIDTH, GALAGAPLANEN45_HEIGHT, galagaplanen45_data);
	} else if (fighter->orientation == -90) {
		drawImage3(fighter->x, fighter->y, GALAGAPLANEN90_WIDTH, GALAGAPLANEN90_HEIGHT, galagaplanen90_data);
	} else if (fighter->orientation == -135) {
		drawImage3(fighter->x, fighter->y, GALAGAPLANEN135_WIDTH, GALAGAPLANEN135_HEIGHT, galagaplanen135_data);
	}
}

void moveFighter(Fighter *fighter) {
	int fighterSpeed;
	if (KEY_DOWN_NOW(BUTTON_B) && fighter->boost > 0) {
		fighterSpeed = 4;
		(fighter->boost)--;
	} else {
		fighterSpeed = 2;
	}
	if (KEY_DOWN_NOW(BUTTON_LEFT) && KEY_DOWN_NOW(BUTTON_UP)) {
		if (fighter->x <= 0) { //button left
			fighter->x = fighter->x + 0;
		} else {
			fighter->x = fighter->x - fighterSpeed;
		}
		if (fighter->y <= 0) { //button up
			fighter->y = fighter->y + 0;
		} else {
			fighter->y = fighter->y - fighterSpeed;
		}
		fighter->orientation = -45;
	}
	else if (KEY_DOWN_NOW(BUTTON_RIGHT) && KEY_DOWN_NOW(BUTTON_UP)) {
		if ((fighter->x + GALAGAPLANE_WIDTH) >= 239) { //button right
			fighter->x = fighter->x + 0;
		} else {
			fighter->x = fighter->x + fighterSpeed;
		}
		if (fighter->y <= 0) { //button up
			fighter->y = fighter->y + 0;
		} else {
			fighter->y = fighter->y - fighterSpeed;
		}
		fighter->orientation = 45;
	}
	else if (KEY_DOWN_NOW(BUTTON_DOWN) && KEY_DOWN_NOW(BUTTON_LEFT)) {
		if (fighter->x <= 0) { //button left
			fighter->x = fighter->x + 0;
		} else {
			fighter->x = fighter->x - fighterSpeed;
		}
		if ((fighter->y + GALAGAPLANE_HEIGHT) >= 160) { //button down
			fighter->y = fighter->y + 0;
		} else {
			fighter->y = fighter->y + fighterSpeed;
		}
		fighter->orientation = -135;
	}
	else if (KEY_DOWN_NOW(BUTTON_DOWN) && KEY_DOWN_NOW(BUTTON_RIGHT)) {
		if ((fighter->y + GALAGAPLANE_HEIGHT) >= 160) { //button down
			fighter->y = fighter->y + 0;
		} else {
			fighter->y = fighter->y + fighterSpeed;
		}
		if ((fighter->x + GALAGAPLANE_WIDTH) >= 239) { //button right
			fighter->x = fighter->x + 0;
		} else {
			fighter->x = fighter->x + fighterSpeed;
		}
		fighter->orientation = 135;
	}
	else if (KEY_DOWN_NOW(BUTTON_UP)) {
		if (fighter->y <= 0) { //button up
			fighter->y = fighter->y + 0;
		} else {
			fighter->y = fighter->y - fighterSpeed;
		}
		fighter->orientation = 0;
	}
	else if (KEY_DOWN_NOW(BUTTON_DOWN)) {
		if ((fighter->y + GALAGAPLANE_HEIGHT) >= 160) { //button down
			fighter->y = fighter->y + 0;
		} else {
			fighter->y = fighter->y + fighterSpeed;
		}
		fighter->orientation = 180;
	}
	else if (KEY_DOWN_NOW(BUTTON_LEFT)) {
		if (fighter->x <= 0) { //button left
			fighter->x = fighter->x + 0;
		} else {
			fighter->x = fighter->x - fighterSpeed;
		}
		fighter->orientation = -90;
	}
	else if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
		if ((fighter->x + GALAGAPLANE_WIDTH) >= 239) { //button right
			fighter->x = fighter->x + 0;
		} else {
			fighter->x = fighter->x + fighterSpeed;
		}
		fighter->orientation = 90;
	}
}

void moveMissile(Missile *missile) {
	if (missile->isOnScreen) {
		if (missile->orientation == 0) {
			if (missile->y <= -(missile->height)) {
				missile->isOnScreen = 0;
			} else {
				(missile->y) = (missile->y) - 3;
			}
		} else if (missile->orientation == 45) {
			if (missile->y <= -(missile->height) || missile->x >= (239 - missile->width)) {
				missile->isOnScreen = 0;
			} else {
				missile->y = missile->y - 2;
				missile->x = missile->x + 2;
			}
		} else if (missile->orientation == 90) {
			if (missile->x >= (237 - missile->width)) {
				missile->isOnScreen = 0;
			} else {
				missile->x = missile->x + 3;
			}
		} else if (missile->orientation == 135){
			if (missile->x >= (239 - missile->width) || missile->y >= (160 - missile->height)) {
				missile->isOnScreen = 0;
			} else {
				missile->y = missile->y + 2;
				missile->x = missile->x + 2;
			}
		} else if (missile->orientation == 180) {
			if (missile->y >= (160 - missile->height)) {
				missile->isOnScreen = 0;
			} else {
				missile->y = missile->y + 3;
			}
		} else if (missile->orientation == -45) {
			if (missile->y <= -(missile->height) || missile->x <= 0) {
				missile->isOnScreen = 0;
			} else {
				missile->x = missile->x - 2;
				missile->y = missile->y - 2;
			}
		} else if (missile->orientation == -90) {
			if (missile->x <= 3) {
				missile->isOnScreen = 0;
			} else {
				missile->x = missile->x - 3;
			}
		} else if (missile->orientation == -135) {
			if (missile->x <= 0 || missile->y >= (160 - missile->height)) {
				missile->isOnScreen = 0;
			} else {
				missile->x = missile->x - 2;
				missile->y = missile->y + 2;
			}
		}
	}
}

void shootMissile(Fighter *fighter) {
	if (KEY_DOWN_NOW(BUTTON_A) && !(missile.isOnScreen)) {
		missile.isOnScreen = 1;
		missile.orientation = fighter->orientation;
		if (fighter->orientation == 0) {
			missile.x = (fighter->x + (GALAGAPLANE_WIDTH/2) - 1);
			missile.y = (fighter->y - missile.height);
			missile.height = MISSILE_HEIGHT;
			missile.width = MISSILE_WIDTH;
		} else if (fighter->orientation == 45) {
			missile.x = (fighter->x + GALAGAPLANE_WIDTH);
			missile.y = fighter->y - missile.height;
			missile.height = MISSILE_HEIGHT;
			missile.width = MISSILE_WIDTH;
		} else if (fighter->orientation == 90) {
			missile.x = (fighter->x + GALAGAPLANE_WIDTH + missile.width);
			missile.y = (fighter->y + (GALAGAPLANE_HEIGHT/2) - 1);
			missile.height = MISSILE_WIDTH;
			missile.width = MISSILE_HEIGHT;
		} else if (fighter->orientation == 135) {
			missile.x = (fighter->x + GALAGAPLANE_WIDTH + missile.width);
			missile.y = (fighter->y + GALAGAPLANE_HEIGHT);
			missile.height = MISSILE_HEIGHT;
			missile.width = MISSILE_WIDTH;
		} else if (fighter->orientation == 180) {
			missile.x = (fighter->x + (GALAGAPLANE_WIDTH/2) - 1);
			missile.y = (fighter->y + GALAGAPLANE_HEIGHT + missile.height);
			missile.height = MISSILE_HEIGHT;
			missile.width = MISSILE_WIDTH;
		} else if (fighter->orientation == -45) {
			missile.x = fighter->x;
			missile.y = fighter->y - missile.height;
			missile.height = MISSILE_HEIGHT;
			missile.width = MISSILE_WIDTH;
		} else if (fighter->orientation == -90) {
			missile.x = (fighter->x - missile.width);
			missile.y = (fighter->y + (GALAGAPLANE_HEIGHT/2) - 1);
			missile.height = MISSILE_WIDTH;
			missile.width = MISSILE_HEIGHT;
		} else if (fighter->orientation == -135) {
			missile.x = (fighter->x - missile.width);
			missile.y = (fighter->y + GALAGAPLANE_HEIGHT);
			missile.height = MISSILE_HEIGHT;
			missile.width = MISSILE_WIDTH;
		}

		if (missile.x > (240 - missile.width) || missile.x < missile.width) {
			missile.isOnScreen = 0;
		}
	}
}

void enemyMissileCollision(Enemy *bug, Missile *missile, Fighter *fighter, int *score) {
	for (int i = 0; i < ENEMY_ARRAY_SIZE; i++) {
		Enemy *enemy = bug + i;
		if (enemy->isOnScreen && missile->isOnScreen) {
			int missileX = missile->x;
			int missileXplusW = missile->x + missile->width;
			int missileY = missile->y;
			int missileYplusH = missile->y + missile->height;

			int enemyX = enemy->x;
			int enemyXplusW = enemy->x + enemy->width;
			int enemyY = enemy->y;
			int enemyYplusH = enemy->y + enemy->height;

			if (((missileX >= enemyX) && (missileX <= enemyXplusW) && (missileY <= enemyYplusH) && (missileY >= enemyY)) || ((missileXplusW >= enemyX) && (missileXplusW <= enemyXplusW) && (missileYplusH <= enemyYplusH) && (missileYplusH >= enemyY))) {
				missile->isOnScreen = 0;
				(bug+i)->isOnScreen = 0;
				*score+=100;
				if (fighter->boost < 100) {
					fighter->boost += 20;
				}
				if (fighter->boost > 100) {
					fighter->boost = 100;
				}
			}
		}
	}	
}

void enemyFighterCollision(Enemy *bug, Fighter *fighter) {
	for (int i = 0; i < ENEMY_ARRAY_SIZE; i++) {
		Enemy *enemy = bug + i;
		if (enemy->isOnScreen) {
			int fighterX = fighter->x;
			int fighterXplusW = fighter->x + GALAGAPLANE_WIDTH;
			int fighterY = fighter->y;
			int fighterYplusH = fighter->y + GALAGAPLANE_HEIGHT;

			int enemyX = enemy->x;
			int enemyXplusW = enemy->x + enemy->width;
			int enemyY = enemy->y;
			int enemyYplusH = enemy->y + enemy->height;
			int statement1 = (fighterX >= enemyX) && (fighterY >= enemyY) && (fighterX <= enemyXplusW) && (fighterY <= enemyYplusH); //top left corner of fighter
			int statement2 = (fighterXplusW >= enemyX) && (fighterY >= enemyY) && (fighterXplusW <= enemyXplusW) && (fighterY <= enemyYplusH); //top right corner of fighter
			int statement3 = (fighterX >= enemyX) && (fighterYplusH >= enemyY) && (fighterX <= enemyXplusW) && (fighterYplusH <= enemyYplusH); //bottom left corner
			int statement4 = (fighterXplusW >= enemyX) && (fighterYplusH >= enemyY) && (fighterXplusW <= enemyXplusW) && (fighterYplusH <= enemyYplusH); //bottom right corner

			if (statement1 || statement2 || statement3 || statement4) {
				fighter->lives = fighter->lives - 1;
				enemy->isOnScreen = 0;
				
			}
		}
	}
}

void drawMissile(Missile *missile) {
	if (missile->isOnScreen) {
		drawRectangle(missile->x, missile->y, missile->width, missile->height, WHITE);
	}
}

void resetGame() {
	fighter.x = 110;
	fighter.y = 70;
	fighter.lives = 3;
	fighter.orientation = 0;
	fighter.boost = 100;
	missile.isOnScreen = 0;
	for (int i = 0; i < ENEMY_ARRAY_SIZE; i++) {
		(enemyArray + i)->isOnScreen = 0;
	}
}

void scoreCounter(int *loopCounter, int *score) {
	if ((*loopCounter % 60) == 0) {
		(*score) += 10;
	}
}

void drawLives(Fighter *fighter) {
	int lives = fighter->lives;
	char str[2];
	char str1[8];
	sprintf(str, "%d", lives);
	strcpy(str1, "Lives: ");
	strcat(str1, str);
	drawString(145, 0, str1, WHITE);
}

void drawBoost(Fighter *fighter) {
	int boost = fighter->boost;
	char str[4];
	char str1[11];
	sprintf(str, "%d", boost);
	strcpy(str1, "Boost: ");
	strcat(str1, str);
	drawString(145, 80, str1, WHITE);
}

void drawScore(int *score) {
	char str[93];
	char str1[100];
	sprintf(str, "%d", *score);
	strcpy(str1, "Score: ");
	strcat(str1, str);
	drawString(145, 160, str1, WHITE);
}
typedef struct 
{
	int x;
	int y;
	int lives;
	int orientation; //degrees [-135 -> +180 by 45's]
	int boost;
} Fighter;

typedef struct
{
	int x;
	int y;
	int width;
	int height;
	int isOnScreen;
	int orientation; //same constraints as Fighter struct
} Missile;

typedef struct
{
	int x;
	int y;
	int width;
	int height;
	int type;
	const unsigned short *data;
	int isOnScreen;
	int orientation; // degrees [-135, -45, 45, 135]
} Enemy;

#define ENEMY_ARRAY_SIZE 3

Enemy enemyArray[ENEMY_ARRAY_SIZE];

#define MISSILE_WIDTH 5
#define MISSILE_HEIGHT 10

#define ENEMY_SPEED_1 1
#define ENEMY_SPEED_2 2
#define ENEMY_SPEED_3 3
#define ENEMY_SPEED_4 4

void spawnEnemy(int *loopCounter, Enemy* enemyArray, int arrayOffset);
Enemy createEnemy(int x, int y, int type);
void drawEnemy(Enemy *bug);
void moveEnemy(Enemy *enemyArray, int speed);
void drawFighter(Fighter * fighter);
void moveFighter(Fighter *fighter);
void enemyMissileCollision(Enemy *bug, Missile *missile, Fighter *fighter, int *score);
void enemyFighterCollision(Enemy *bug, Fighter *fighter);
void moveMissile(Missile *missile);
void shootMissile(Fighter *fighter);
void drawMissile(Missile *missile);
void resetGame();
void scoreCounter(int *loopCounter, int *score);
void drawLives(Fighter *fighter);
void drawBoost(Fighter *fighter);
void drawScore(int *score);
Fighter fighter_initializer();
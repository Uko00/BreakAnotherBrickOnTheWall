#include "raylib.h"
#define SCREEN_WIDTH 450
#define SCREEN_HEIGHT 600
#define TARGET_FPS 60
#define BRICK_COLS 6
#define BRICK_ROWS 4

/*Definições*/
extern Rectangle player; // Retângulo do player
extern int velocityXPlayer; // Velocidade horizontal do player
extern int brickBreakingBallRadius; 
extern Vector2 brickBreakingBallVelocity; //Velocide da bolinha
extern Vector2 brickBreakingBallCenter; // Centro da bolinha quebra tijolos 
extern   Rectangle brickWall[BRICK_ROWS][BRICK_COLS];
extern bool brickWallCanDraw[BRICK_ROWS][BRICK_COLS];

typedef enum ballSideCollided { // que lado a bolinha colidiu
	UP,
	DOWN,
	LEFT, 
	RIGHT
} ballSideCollided;

typedef struct BrickID { // colidiu, indice i e indice j
	bool coll;
	int i;
	int j;
} BrickID;

extern BrickID * ballBrickCollisionStru;

/*Funções*/
void gameScene(); // Responsável pela cena do jogoo
void initBrickWall(); // Inicia a parede de tijolos
BrickID *checkCollisionBallBrick(); // Checa a colisão entre a bola e qualquer tijolo
bool checkCollisionSideBallRec(Vector2 ballCenter, float ballRadius, Rectangle Rectangle);

/*Atualizações*/
void updatePlayer(); 
void updateBrickBreakingBall();

/*Renderizações*/
void drawPlayer();
void drawBrickBreakingBall();
void drawBrickWall();

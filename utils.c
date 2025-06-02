#include "raylib.h"
#include "utils.h"
#include <stdio.h>

int velocityXPlayer = 3;
int brickBreakingBallRadius = 15;

Rectangle player = { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT-40, 130, 20 };
Rectangle   brickWall[BRICK_ROWS][BRICK_COLS];
bool brickWallCanDraw[BRICK_ROWS][BRICK_COLS];

Vector2 brickBreakingBallCenter = {SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f}; // Centro da bolinha que vai quebrar os tijolos
Vector2 brickBreakingBallVelocity = {3, -3};

Color playerColor = BLACK; // Cor do player - caso precise ser atualizado eventualmente int velocityXPlayer = 3; void updatePlayer() {
Color brickBreakingBallColor = BLACK;
Color brickColor = BLACK;

BrickID * ballBrickCollisionStru;

bool checkCollisionSideBallRec(Vector2 ballCenter, float ballRadius, Rectangle rec) {
	if (ballCenter.y > rec.y && ballCenter.y < rec.y+rec.height) return true;
	return false;
};

BrickID * checkCollisionBallBrick() {
	for (int i=0; i<BRICK_ROWS; i++) {
		for (int j=0; j<BRICK_COLS; j++) {

			/*Reconhece corretamente a colisão no topo e na base*/
			if(CheckCollisionCircleRec(brickBreakingBallCenter, brickBreakingBallRadius, brickWall[i][j]) && brickWallCanDraw[i][j]) {

				brickWallCanDraw[i][j] = false;
				return &(BrickID) {true, i, j};
			};
		};
	};
	return &(BrickID) { 0, 0, 0 }; // Remover caso não funcione
}; 

void initBrickWall() {
	int x = 2;
	int y = 2;
	float brickWidth = SCREEN_WIDTH/BRICK_COLS;

	for (int i=0; i<BRICK_ROWS; i++) {
		for (int j=0; j<BRICK_COLS; j++) {

			brickWall[i][j].width = brickWidth;
			brickWall[i][j].height= 30;
			brickWall[i][j].x = x;
			brickWall[i][j].y = y;

			brickWallCanDraw[i][j] = true;

			x += brickWidth+1;
		};
		x = 2;
		y+= 31;
	};
};

void drawBrickBreakingBall() {
	DrawCircleV(brickBreakingBallCenter, brickBreakingBallRadius, brickBreakingBallColor);
};

void drawPlayer() {
	DrawRectangleRec(player, playerColor);
};

void drawBrickWall() {
	for (int i=0; i<BRICK_ROWS; i++) {
		for (int j=0; j<BRICK_COLS; j++) {
			if (brickWallCanDraw[i][j]) DrawRectangleRec(brickWall[i][j], brickColor);				 
		};
	};
};

void updatePlayer() {
	if (IsKeyDown(KEY_LEFT) && player.x > 0) player.x -= velocityXPlayer; // Só se movimenta se estiver dentro do limite da tela
	else if (IsKeyDown(KEY_RIGHT) && player.x+player.width < SCREEN_WIDTH) player.x += velocityXPlayer; // Idem
};


void updateBrickBreakingBall() {
	brickBreakingBallCenter.x += brickBreakingBallVelocity.x;
	brickBreakingBallCenter.y += brickBreakingBallVelocity.y;

	if (brickBreakingBallCenter.x+15>SCREEN_WIDTH) brickBreakingBallVelocity.x *= -1;
	else if (brickBreakingBallCenter.x-15<0) brickBreakingBallVelocity.x *= -1;
	else if (brickBreakingBallCenter.y-15<0) brickBreakingBallVelocity.y *= -1;

	if ( // Checa a colisão entre a bola e o player
		CheckCollisionCircleRec(brickBreakingBallCenter,
		brickBreakingBallRadius, player)
		) brickBreakingBallVelocity.y *= -1; 
	

	if (checkCollisionBallBrick()->coll) { // Caso a bola colidiu com um tijolo
		brickBreakingBallVelocity.y *= -1;
	};

	if (brickBreakingBallCenter.y > SCREEN_HEIGHT) brickBreakingBallCenter.y = SCREEN_HEIGHT/2.0f; // A bolinha não ultrapassa a tela

};

void gameScene() {
	/*Updates*/
	updatePlayer();
	updateBrickBreakingBall();
	/*Draws*/
	drawPlayer();
	drawBrickBreakingBall();
	drawBrickWall();
};

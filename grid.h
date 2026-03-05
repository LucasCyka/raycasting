#ifndef GRID_H_
#define GRID_H_
#define TILE_SIZE 16 //for drawing only, for calculation each tile = 1

#include <raylib.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <raymath.h>

typedef struct ScreenBuffer{
	int *lines;
	unsigned int *colors;
	unsigned char xCell;
	
} ScreenBuffer;

void InitBoard(int width, int height, int screenWidth, int screenHeight);
void SetCasterPosition(Vector2 position);
void MoveCaster(Vector2 dir,float speed,float angularSpeed);
void UpdateBoard(Vector2 coordinates, int value);
void DrawBoard(void);
void FreeBoard(void);
ScreenBuffer CastToBuffer();

#endif 

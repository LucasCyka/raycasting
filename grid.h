#ifndef GRID_H_
#define GRID_H_
#define __USE_MISC
#define TILE_SIZE 16 //for drawing only, for calculation each tile = 1

#include <raylib.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <raymath.h>

void InitBoard(int width, int height, int screenWidth, int screenHeight);
void SetCasterPosition(Vector2 position);
void MoveCaster(Vector2 dir,float speed,float angularSpeed);
void UpdateBoard(Vector2 coordinates, int value);
void DrawBoard(void);
void FreeBoard(void);
int *CastToBuffer();

#endif 

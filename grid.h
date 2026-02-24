#ifndef GRID_H_
#define GRID_H_

#define TILE_SIZE 16 //for drawing only, for calculation each tile = 1

#include <raylib.h>
#include <memory.h>
#include <stdlib.h>

void InitBoard(int width, int height);
void SetCasterPosition(Vector2 position);
void MoveCaster(Vector2 dir,float speed);
void UpdateBoard(Vector2 coordinates, int value);
void DrawBoard(void);
void FreeBoard(void);
Vector2 CastRay(Vector2 dir);

#endif 

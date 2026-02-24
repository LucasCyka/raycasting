#include "grid.h"

int *pcells;
static int BoardWidth;
static int BoardHeight;
static Vector2 casterPos = {0.0f};

void InitBoard(int width, int height){
	BoardWidth  = width;
	BoardHeight = height; 	

	int cells_size = width * height;
	pcells = (int*) malloc(cells_size * sizeof(int)); 
	
	for (int id = 0; id < cells_size; id++){
		pcells[id] = 0;
	}	

}

void DrawBoard(void){
	for(int y = 0; y < BoardHeight; y++){
	
		for(int x = 0; x < BoardWidth; x++){
			DrawRectangleLines(x*TILE_SIZE,y*TILE_SIZE,TILE_SIZE,TILE_SIZE,(Color){255,0,0,128});

			if (pcells[y * BoardWidth + x] == 1) DrawRectangle(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE, YELLOW);
		}
	}
	//caster
	DrawCircleV((Vector2){casterPos.x*TILE_SIZE,casterPos.y*TILE_SIZE},(float) (TILE_SIZE / 2.0f),WHITE);

}

void SetCasterPosition(Vector2 position){
	casterPos = position;

}
void MoveCaster(Vector2 dir,float speed){
	float dt = GetFrameTime();
	casterPos.x += dir.x * speed * dt;
	casterPos.y += dir.y * speed * dt;
}

void UpdateBoard(Vector2 coordinates, int value){
	int x = coordinates.x;
	int y = coordinates.y;
	pcells[(int)(y * BoardWidth + x)] = value;

}


Vector2 CastRay(Vector2 dir){


}


void FreeBoard(){
	free(pcells);
}

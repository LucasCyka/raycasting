#include "grid.h"

int *pcells;
static int BoardWidth;
static int BoardHeight;

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
		}

	}


}

void SetCasterPosition(Vector2 position){


}
void MoveCaster(Vector2 dir,float speed){


}

void UpdateBoard(Vector2 coordinate, int value){


}


Vector2 CastRay(Vector2 dir){


}


void FreeBoard(){
	free(pcells);
}

#include "grid.h"

int *pcells;
static int BoardWidth;
static int BoardHeight;
static Vector2 casterPos = {0.0f};
static Vector2 casterDir = {-1.00f, 0.00f};
//camera plane is actually 2*0.66 = 1.32, but is centered at zero between 1 and -1
//FOV will be 2*atan(0.66/1.0) (plane size/casterDir)
//must always be perpendicular to casterDir
static Vector2 cameraPlane = {0,0.66};

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
	DrawCircleV((Vector2){casterPos.x*TILE_SIZE,casterPos.y*TILE_SIZE},(float) (TILE_SIZE / 4.0f),WHITE);
	DrawLineV(Vector2Scale(casterPos,TILE_SIZE), Vector2Add(Vector2Scale(casterPos,TILE_SIZE), Vector2Scale(casterDir,TILE_SIZE*2)), GREEN);
	
	DrawText(TextFormat("(%.2f,%.2f)",cameraPlane.x,cameraPlane.y),0,0,2,WHITE);
}

void SetCasterPosition(Vector2 position){
	casterPos = position;

}
void MoveCaster(Vector2 dir,float speed, float angularSpeed){
	float dt = GetFrameTime();
	Vector2 bdir = casterDir;
	Vector2 cdir = cameraPlane;	

	if(dir.x > 0.1f){
		casterDir.x = bdir.x*cosf(PI/180.0f*angularSpeed) - bdir.y*sinf(PI/180.0f*angularSpeed);
		casterDir.y = bdir.x*sinf(PI/180.0f*angularSpeed) + bdir.y*cosf(PI/180.0f*angularSpeed);
		casterDir   = Vector2Normalize(casterDir);

		cameraPlane.x = cdir.x*cosf(PI/180.0f*angularSpeed) - cdir.y*sinf(PI/180.0f*angularSpeed);
		cameraPlane.y = cdir.x*sinf(PI/180.0f*angularSpeed) + cdir.y*cosf(PI/180.0f*angularSpeed);
	}else if(dir.x < -0.1f){
		casterDir.x = bdir.x*cosf(PI/180.0f*-angularSpeed) - bdir.y*sinf(PI/180.0f*-angularSpeed);
		casterDir.y = bdir.x*sinf(PI/180.0f*-angularSpeed) + bdir.y*cosf(PI/180.0f*-angularSpeed);
		casterDir   = Vector2Normalize(casterDir);

		cameraPlane.x = cdir.x*cosf(PI/180.0f*-angularSpeed) - cdir.y*sinf(PI/180.0f*-angularSpeed);
		cameraPlane.y = cdir.x*sinf(PI/180.0f*-angularSpeed) + cdir.y*cosf(PI/180.0f*-angularSpeed);
	}
	
	if(dir.y < -0.1f) {
		casterPos.y += casterDir.y * speed * dt;
		casterPos.x += casterDir.x * speed * dt;
	}

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

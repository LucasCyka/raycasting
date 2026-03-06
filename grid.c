#include "grid.h"

int *pcells;
//int *screenBuffer;
Vector2 *rays;

static int BoardWidth;
static int BoardHeight;
static int ScreenWidth;
static int ScreenHeight;

static Vector2 casterPos = {0.0f};
static Vector2 casterDir = {-1.00f, 0.00f};
//camera plane is actually 2*0.66 = 1.32, but is centered at zero between 1 and -1
//FOV will be 2*atan(0.66/1.0) (plane size/casterDir)
//must always be perpendicular to casterDir
static Vector2 cameraPlane = {0,0.66};

ScreenBuffer buff;

void InitBoard(int width, int height, int screenWidth, int screenHeight){
	BoardWidth   = width;
	BoardHeight  = height; 	
	ScreenWidth  = screenWidth;
	ScreenHeight = screenHeight;

	int cells_size = width * height;
	pcells = (int*) malloc(cells_size * sizeof(int)); 
	
	for (int id = 0; id < cells_size; id++){
		pcells[id] = 0;
	}
	
	buff.lines  = (int*) malloc(screenWidth * sizeof(int));	
	buff.colors = (int*) malloc(screenWidth * sizeof(int));		
	buff.xCell  = (double*) malloc(screenWidth * sizeof(double));		
	//screenBuffer = (int*) malloc(screenWidth * sizeof(int));	
	rays         = (Vector2*) malloc(screenWidth * sizeof(Vector2));
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
	for(int i = 0; i < ScreenWidth; i++) {
		DrawLineV(Vector2Scale(casterPos,TILE_SIZE), Vector2Scale(rays[i], TILE_SIZE ) , PURPLE);
	}
	//DrawText(TextFormat("(%.2f,%.2f)",cameraPlane.x,cameraPlane.y),0,0,2,WHITE);
		
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
		int newX = casterPos.x + casterDir.x * speed * dt  * 3;
		int newY = casterPos.y + casterDir.y * speed * dt  * 3;
		
		if(pcells[newY * BoardWidth + newX] != 0){
			Vector2 wallNormal = {-1,0};

			Vector2 newDir = Vector2Subtract(casterDir, Vector2Scale(wallNormal, Vector2DotProduct(casterDir, wallNormal)));
			
			casterPos.x += newDir.x * speed * dt;
			casterPos.y += newDir.y * speed * dt;			

		}else{
			casterPos.x += casterDir.x * speed * dt;
			casterPos.y += casterDir.y * speed * dt;
		}		

		//casterPos.x += casterDir.x * speed * dt;

	}else if(dir.y >0.1f){
		casterPos.y += -casterDir.y * speed * dt;
		casterPos.x += -casterDir.x * speed * dt;
	}else if(dir.y >0.1f){
	}

}

void UpdateBoard(Vector2 coordinates, int value){
	int x = coordinates.x;
	int y = coordinates.y;
	pcells[(int)(y * BoardWidth + x)] = value;

}

ScreenBuffer CastToBuffer(){
	for(int x = 0; x < ScreenWidth; x++){
		Vector2 rayDir    = casterDir;
		Vector2 step      = {0.00f};
		Vector2 rayLenght = {0.00f};
		int casterMapX    = casterPos.x;
		int casterMapY    = casterPos.y;
		//float xNormalized = (float) (x/(ScreenWidth/2.00f) - 1.00f); //inverted duur
		float xNormalized = (float) (x/(ScreenWidth/-2.00f) + 1.00f);
		
		rayDir = Vector2Add(casterDir, Vector2Scale(cameraPlane,  xNormalized));
		//rayDir = Vector2Normalize(rayDir);
		//rays[x] = rayDir;
		
		//rayDir.x += 0.0000000000000001f;
		//rayDir.y +=	0.0000000000000001f;	

		Vector2 rayStepping = { sqrtf(1.00f + (rayDir.y/rayDir.x) * (rayDir.y/rayDir.x)),
		sqrtf(1.00f + (rayDir.x/rayDir.y) * (rayDir.x/rayDir.y))};
		
		if(rayDir.x > 0){
			step.x      = 1.00f;
			rayLenght.x = (float)(casterMapX + 1.00f - casterPos.x) * rayStepping.x; 
		}else if(rayDir.x < 0){
			step.x      = -1.00f;
			rayLenght.x = (float)(casterPos.x - casterMapX) * rayStepping.x;
		}

		if(rayDir.y > 0){
			step.y      = 1.00f;
			rayLenght.y = (float)(casterMapY + 1.00f - casterPos.y) * rayStepping.y; 
		}else if(rayDir.y < 0){
			step.y      = -1.00f;
			rayLenght.y = (float)(casterPos.y - casterMapY) * rayStepping.y;
		}
		
		bool found   = false;
		float maxDis = 100.00f;
		float travelledDistance = 0.00f;
		int   hitSide = 0; //0 = x, 1 = y
		while(!found && travelledDistance < maxDis){

			if(rayLenght.x < rayLenght.y){
				casterMapX += step.x;
				travelledDistance = rayLenght.x;
				rayLenght.x += rayStepping.x;
				hitSide = 0;
			}else{
				casterMapY += step.y;
				travelledDistance = rayLenght.y;
				rayLenght.y += rayStepping.y;
				hitSide = 1;
			}
			int id = (int)(casterMapY * BoardWidth + casterMapX);
			if(casterMapX >=0 && casterMapX <= BoardWidth-1 && casterMapY >= 0 && casterMapY <= BoardHeight-1  ){
				if(pcells[id] == 1){
					found = true;
				}
			}
		}	
		
		rays[x] = Vector2Add(Vector2Scale(Vector2Normalize(rayDir), travelledDistance),  casterPos);
		
		if(!found) buff.lines[x] =  0;
		else{
			float hDist = 1.00f;
			float distanceToPlane = 1.00f;
			if (hitSide == 0){
				hDist = (float)(casterMapX + ((step.x -1.00f) / -2.00f) - casterPos.x);
				distanceToPlane = hDist/rayDir.x;
			}else{
				hDist = (float)(casterMapY + ((step.y -1.00f) / -2.00f) - casterPos.y);
				distanceToPlane = hDist/rayDir.y;
			}
			
			int lineHeight  = ScreenHeight / distanceToPlane;
			buff.lines[x]   = lineHeight;
			buff.colors[x]  = 0xFFFFFFFF;
			if(hitSide == 1) buff.colors[x] -= 0xAA;
			
			if(hitSide == 0) buff.xCell[x] = (double)(rays[x].y - floor(rays[x].y)); 
			else 			 buff.xCell[x] = (double)(rays[x].x - floor(rays[x].x));
			
			if(hitSide == 0 && rayDir.x < 0) buff.xCell[x] *= -1;
			if(hitSide == 1 && rayDir.y > 0) buff.xCell[x] *= -1;

		}
	}	

	return buff;
}

void FreeBoard(){
	free(pcells);
	//free(screenBuffer);
	free(rays);
	free(buff.colors);
	free(buff.lines);
}

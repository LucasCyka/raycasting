#define TILES_NUM    1024
#define TILE_SIZE    16
#define PLAYER_SPEED 100

#include <stdio.h>
#include <raylib.h>
#include <math.h>
#include <raymath.h>

unsigned char grid[TILES_NUM];
Vector2 gridSize = {32,32};

void initGrid (void) {
	for (int i = 0; i < TILES_NUM; i++){
		grid[i] = 0;
	}
}

int main(){
	InitWindow(512,512,"Board");
	SetTargetFPS(30);
	initGrid();
	
	Vector2 playerPos = {(float)gridSize.x/2.0 * TILE_SIZE , (float)gridSize.y/2.0 * TILE_SIZE};
	Vector2 tested[256];
	int t = 0;	

	while(!WindowShouldClose()){
		Vector2 mousePos       = GetMousePosition();
		Vector2 mousePosCell   = {(int)(mousePos.x /TILE_SIZE),(int)(mousePos.y / TILE_SIZE)};
		int mouseiX            = mousePos.x;
		int mouseiY            = mousePos.y;
		int playeriX           = playerPos.x;
		int playeriY           = playerPos.y;
		int drawIntersection   = 0;
		float playerCellPosX   = (float) (playeriX/TILE_SIZE);
		float playerCellPosY   = (float) (playeriY/TILE_SIZE);
		Vector2 rayDir   = {0};
		Vector2 intersectionPos = {0};

		
		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			rayDir = Vector2Normalize(Vector2Subtract(mousePos,playerPos));
			rayDir.x += 0.0000001f; //prevents div. by zero ;) 
			rayDir.y += 0.0000001f;  
			Vector2 rayStepping = {sqrtf(1.0 + (rayDir.y/rayDir.x)*(rayDir.y/rayDir.x)),sqrtf(1.0+(rayDir.x/rayDir.y)*(rayDir.x/rayDir.y))};				
			
			Vector2 stepping = {0};
			Vector2 ray1Dlenght = {0};
			int cTileX = playeriX / TILE_SIZE;
			int cTileY = playeriY / TILE_SIZE;
			
			if(rayDir.x > 0){ //set starting position
				stepping.x = 1;
				ray1Dlenght.x = (float)((cTileX + 1.0) - playerCellPosX) * rayStepping.x;  
		
			}else{
				stepping.x = -1;
				ray1Dlenght.x =  (float)(playerCellPosX - cTileX) * rayStepping.x;
			}
			
			if(rayDir.y > 0){
				stepping.y = 1;
				ray1Dlenght.y = (float)((cTileY + 1.0) - playerCellPosY) * rayStepping.y;
			}else{
				stepping.y = -1;
				ray1Dlenght.y = (float)(playerCellPosY - cTileY) * rayStepping.y;
			}	

			//walk along path
			int foundTile = 0;
			float maxDistance = 100.00f;
			float travelledDistance = 0.00f;

			while(!foundTile && travelledDistance < maxDistance){
				if(ray1Dlenght.x < ray1Dlenght.y) {
					cTileX += stepping.x;
					travelledDistance = ray1Dlenght.x;				
					ray1Dlenght.x += rayStepping.x; 
				}else{
					cTileY += stepping.y;
					travelledDistance = ray1Dlenght.y;
					ray1Dlenght.y += rayStepping.y;	
				}
				int tVal = (int)(cTileY * gridSize.x + cTileX);
				if(tVal <= 1023 && tVal >= 0){
					if(grid[tVal] == 1 ){
						intersectionPos = Vector2Add(Vector2Scale(rayDir,travelledDistance*TILE_SIZE),playerPos);
						
						drawIntersection = 1;
						foundTile = 1;
						//return 1;
						//printf("found?!");
					}else{
						//tested[t] = (Vector2) {cTileX,cTileY};
						//t++;	
					}
				}

			}

		}

		BeginDrawing();
		ClearBackground(BLACK);

		if(IsKeyDown(KEY_LEFT)) playerPos.x -= PLAYER_SPEED * GetFrameTime(); 
		if(IsKeyDown(KEY_RIGHT)) playerPos.x += PLAYER_SPEED * GetFrameTime(); 
		if(IsKeyDown(KEY_UP)) playerPos.y -= PLAYER_SPEED * GetFrameTime(); 
		if(IsKeyDown(KEY_DOWN)) playerPos.y += PLAYER_SPEED * GetFrameTime(); 	

		for(int y = 0; y < gridSize.y; y++){
			for(int x = 0; x < gridSize.x; x++){
				DrawRectangleLines(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color) {255,0,0,64} );	
				if(grid[(int)(y * gridSize.x + x)] == 1){ 
					DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, (Color) {255,255,0,64} );
				}					
			}
		}

		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) DrawLineV(playerPos,GetMousePosition(),WHITE);
		if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) grid[(int)((mouseiY / TILE_SIZE) * gridSize.x + mouseiX/TILE_SIZE ) ] = 1; 

		DrawCircleV(playerPos,8,WHITE); //player
		if(drawIntersection){
			DrawCircleV(intersectionPos,2,YELLOW);
		}
		DrawText(TextFormat("x:%f , y:%f",intersectionPos.x,intersectionPos.y),0,0,20,WHITE);
		/*
		if(t > 0){	
			for (int id = 0; id < t; id++){
				DrawCircleV((Vector2) {tested[id].x * TILE_SIZE , tested[id].y * TILE_SIZE}   ,5,RED);
			}
			printf("ending it");
		}*/

		EndDrawing();
	}

	CloseWindow();


	return 0;
}

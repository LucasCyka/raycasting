#define WINDOW_WIDTH     800
#define WINDOW_HEIGHT    460
#define GRID_COLUMNS     20
#define GRID_ROWS        10
#define PLAYER_SPEED     5.00f
#define ANGULAR_SPEED    5.00f

#include <stdlib.h>
#include <stdbool.h>
#include <raylib.h>
#include "grid.h"

RenderTexture2D frameBufferRender;
static float boardScale = 1.0f;
static Vector2 gridSize = {GRID_COLUMNS * TILE_SIZE, GRID_ROWS * TILE_SIZE};

Vector2 getGridPosition(Vector2 _windowPosition){
	Vector2 worldMousePos;
	worldMousePos.x = (float)((_windowPosition.x - (WINDOW_WIDTH - gridSize.x*boardScale)*0.5f)/boardScale) / TILE_SIZE;
	worldMousePos.y = (float)((_windowPosition.y - (WINDOW_HEIGHT - gridSize.y*boardScale)*0.5f)/boardScale)/ TILE_SIZE;
	
	//clamp
	worldMousePos.x = (worldMousePos.x > GRID_COLUMNS) ? GRID_COLUMNS : worldMousePos.x;	
	worldMousePos.x = (worldMousePos.x < 0.00f) ? 0.00f : worldMousePos.x;	
	
	worldMousePos.y = (worldMousePos.y > GRID_ROWS) ? GRID_ROWS : worldMousePos.y;		
	worldMousePos.y = (worldMousePos.y < 0.00f) ? 0.00f : worldMousePos.y;	

	return worldMousePos;
}

int main() {
	float widthScale  = (float) (WINDOW_WIDTH  / gridSize.x);
	float heightScale = (float) (WINDOW_HEIGHT / gridSize.y);
	bool drawMap	  = false;

	boardScale = (widthScale < heightScale) ? widthScale : heightScale; 
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raycasting");
	SetTargetFPS(60);

	InitBoard(GRID_COLUMNS, GRID_ROWS,WINDOW_WIDTH,WINDOW_HEIGHT);
	SetCasterPosition((Vector2) {GRID_COLUMNS / 2.0, GRID_ROWS / 2.0});
	//MoveCaster((Vector2){1.0,1.0},100.00f);	
	
	frameBufferRender = LoadRenderTexture(GRID_COLUMNS * TILE_SIZE, GRID_ROWS * TILE_SIZE);
	SetTextureFilter(frameBufferRender.texture,TEXTURE_FILTER_BILINEAR);	

	while(!WindowShouldClose()){
		//Vector2 intersection = CastRay((Vector2){0.0f,0.0f});		
		Vector2 playerDir    = (Vector2) {0.0f};

		if(IsKeyDown(KEY_D)) playerDir.x -= 1.00f;	
		if(IsKeyDown(KEY_A)) playerDir.x += 1.00f;	
		if(IsKeyDown(KEY_W)) playerDir.y -= 1.00f;	
		if(IsKeyDown(KEY_S)) playerDir.y += 1.00f;	
		if(IsKeyPressed(KEY_M)) drawMap = !drawMap;
		
		if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) UpdateBoard(getGridPosition(GetMousePosition()),1);	

		MoveCaster(playerDir,PLAYER_SPEED,ANGULAR_SPEED);
		
		int *scr = CastToBuffer();
	
		BeginTextureMode(frameBufferRender);
			ClearBackground(BLACK);
			DrawBoard();
		EndTextureMode();
		
		BeginDrawing();
			ClearBackground(BLACK);
			
			for(int w = 0; w < WINDOW_WIDTH; w++){
				if(scr[w] == 0) continue;
				int startColumn = -scr[w] / 2 + WINDOW_HEIGHT / 2;
				int endColumn   = scr[w] / 2 + WINDOW_HEIGHT / 2;
				
				if (startColumn < 0) startColumn = 0;
				if (endColumn   > WINDOW_HEIGHT) endColumn = WINDOW_HEIGHT;				

				DrawLine(w, startColumn, w, endColumn, RED);
			}

			Rectangle sourceRect = {0.0f, 0.0f, frameBufferRender.texture.width,-frameBufferRender.texture.height};
			Rectangle destRect   = {(float)((WINDOW_WIDTH - gridSize.x* boardScale)*0.5), 
			 (float)((WINDOW_HEIGHT - gridSize.y * boardScale)*0.5),
			 (float)(gridSize.x * boardScale),  
			 (float)(gridSize.y * boardScale) };
			
			if(drawMap) DrawTexturePro(frameBufferRender.texture, sourceRect, destRect, (Vector2){0.0f,0.0f}, 0.0f, WHITE); 
			
			Vector2 mousePos = GetMousePosition();
			Vector2 tilePos  = getGridPosition(mousePos);
			DrawText(TextFormat("x: %.2f, y: %.2f",tilePos.x,tilePos.y),0,0,24,WHITE);
		EndDrawing();
		
	}
	
	UnloadRenderTexture(frameBufferRender);		
	CloseWindow();
	FreeBoard();

	return 0;
}

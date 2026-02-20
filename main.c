#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 460
#define GRID_WIDTH    30
#define GRID_HEIGHT   22

#include<raylib.h>
#include "grid.h"

RenderTexture2D frameBufferRender;
static float boardScale = 1.0f;

int main() {
	
	float widthScale  = (float) (WINDOW_WIDTH  / GRID_WIDTH);
	float heightScale = (float) (WINDOW_HEIGHT / GRID_HEIGHT);

	boardScale = (widthScale < heightScale) ? widthScale : heightScale; 
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raycasting");
	SetTargetFPS(30);

	InitBoard(GRID_WIDTH, GRID_HEIGHT);
	UpdateBoard((Vector2) {0,0},1); //TODO: read from a file
	SetCasterPosition((Vector2) {GRID_WIDTH / 2.0, GRID_HEIGHT / 2.0});
	MoveCaster((Vector2){1.0,1.0},100.00f);	
	
	frameBufferRender = LoadRenderTexture(GRID_WIDTH * TILE_SIZE, GRID_HEIGHT * TILE_SIZE);
	SetTextureFilter(frameBufferRender.texture,TEXTURE_FILTER_BILINEAR);	

	while(!WindowShouldClose()){
		Vector2 Intersection = CastRay((Vector2){0.0f,0.0f});		
		
		BeginTextureMode(frameBufferRender);
			ClearBackground(BLACK);
			DrawBoard();
		
		EndTextureMode();
		

		BeginDrawing();
			ClearBackground(BLACK);
			
			Rectangle sourceRect = {0.0f, 0.0f, frameBufferRender.texture.width,-frameBufferRender.texture.height};
			Rectangle destRect   = {(float)((WINDOW_WIDTH - GRID_WIDTH * boardScale)*0.5), 
			 (float)((WINDOW_HEIGHT - GRID_HEIGHT * boardScale)*0.5),
			 (float)(GRID_WIDTH * boardScale),  
			 (float)(GRID_HEIGHT * boardScale) };
			
			DrawTexturePro(frameBufferRender.texture, sourceRect, destRect, (Vector2){0.0f,0.0f}, 0.0f, WHITE); 
		EndDrawing();
		
	}
	
	UnloadRenderTexture(frameBufferRender);		
	CloseWindow();
	FreeBoard();

	return 0;
}

#include <stdio.h>
#include <raylib.h>
#include <math.h>

void DDALine(Vector2 Start, Vector2 End);

int main(int argc, char *argv){

	InitWindow(600,600,"Me window");
	SetTargetFPS(60);	
	
	float dangle = 0;
	int frames = 0;
	Vector2 EndLine = {0,0};
	while(!WindowShouldClose()){
		frames++;
		BeginDrawing();
		
		ClearBackground(BLACK);
		
		if (fmod(frames,5.0) == 0) dangle += 1;
		
		EndLine = (Vector2) {0.0+dangle,0.0}; 
		DDALine((Vector2){300,300}, EndLine );
		
		
		EndDrawing();
	}
		

	CloseWindow();

	return 0;

}


void DDALine(Vector2 Start, Vector2 End){
	
	int dx = End.x - Start.x;
	int dy = End.y - Start.y;

	int steps = dx > dy ? fabs(dx) :fabs(dy);

	float x_increment = 0;
	float y_increment = 0;

	x_increment = (float)dx / steps;

	y_increment = (float)dy / steps;
		
	Vector2 line = Start;
	for (int i = 0; i < steps; i++){
		DrawPixelV(line,GREEN);
			
		line.x += x_increment;
		line.y += y_increment;

	}
									
}


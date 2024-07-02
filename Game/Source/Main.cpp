#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"

#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>


using namespace std;

int main(int argc, char* argv[]) {

	//create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	//Game code

	Vector2 v1{ 400, 300};
	Vector2 v2{ 250, 375};

	vector<Vector2> points;

	/*for (int i=0; i < 100; i++) {
		points.push_back(Vector2{rand() % 800, rand() % 600});
	}*/

	//main loop
	bool kys = false;
	while (!kys) {
		// input
		// update
		// draw
		 
		//Input
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			kys = true;
		}

		//Update
		Vector2 mousePosition = input.GetMousePosition();
		//cout << mousePosition.x << " " << mousePosition.y << endl;

		if (input.getMouseButtonDown(0) && !input.getPrevMouseButtonDown(0)) {
			cout << "Mouse pressed" << endl;
			points.push_back(mousePosition);
		}
		if (input.getMouseButtonDown(0) && input.getPrevMouseButtonDown(0)) {
			float distance = (points.back() - mousePosition).length();
			if (distance > 5) {
				points.push_back(mousePosition);
			}
		}



		// [p,p,p,p]
	/*	Vector2 speed{ 0.1f, -0.1f };
		for (Vector2& point : points) {
			point = point + speed;
		}*/
		//Draw
		//clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		////draw line
		renderer.SetColor(255, 255, 255, 0);
		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++) {
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			renderer.DrawLine(points[i].x,points[i].y, points[i + 1].x, points[i + 1].y);
		}
		//renderer.DrawLine(v1.x,v1.y,v2.x,v2.y);

		//for (int i = 0; i < points.size() - 1; i++) {
		//	renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
		//	renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
		//}

		renderer.EndFrame();
	}
	return 0;
}
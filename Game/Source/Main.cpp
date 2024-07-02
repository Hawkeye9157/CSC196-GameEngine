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

	//main loop
	bool end = false;
	while (!end) {
		// input
		// update
		// draw
		 
		//Input
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			end = true;
		}

		//Update
		Vector2 mousePosition = input.GetMousePosition();

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

		//Draw
		//clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		////draw from mouse
		renderer.SetColor(255, 255, 255, 0);
		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++) {
			renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			renderer.DrawLine(points[i].x,points[i].y, points[i + 1].x, points[i + 1].y);
		}

		renderer.EndFrame();
	}
	return 0;
}
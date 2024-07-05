#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETimer.h"

#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>


using namespace std;

int main(int argc, char* argv[]) {

	//create engine systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);

	Input input;
	input.Initialize();

	Time time;

	vector<Particle> particles;

	vector<Vector2> points;
	
	//Game code

	//main loop
	bool end = false;
	while (!end) {
		// input
		// update
		// draw
		 
		//Input
		time.Tick();
		cout << time.GetTime() << endl;
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			end = true;
		}

		//Update
		renderer.SetColor(255, 255, 255, 0);
		for (Particle& particle : particles) {
			renderer.SetColor(255, 255, 255, 0);
			particle.update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		Vector2 mousePosition = input.GetMousePosition();
		if (input.getMouseButtonDown(0)) {
			particles.push_back(Particle{ {mousePosition.x,mousePosition.y},
				{randomf(-500.0f,500.0f), randomf(-500.0f,500.0f)},{randomf(1.0f,5.0f)},
				255,255,255,0 });
				//todo fix
				//random(0,255),random(0,255),random(0,255),random(0,255)});		
		}

		//Draw
		//clear screen
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		for (Particle particle : particles) {
			renderer.SetColor(particle.r,particle.g,particle.b,particle.a);
			particle.draw(renderer);
		}

		renderer.EndFrame();
	}
	return 0;
}
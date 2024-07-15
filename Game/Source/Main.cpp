#include "Engine.h"
//#include "Renderer.h"
//#include "Vector2.h"
//#include "Input.h"
//#include "Particle.h"
//#include "Random.h"
//#include "ETimer.h"
//#include "MathUtils.h"
//#include "Model.h"
//#include "Transform.h"
//#include "Player.h"
#include "Scene.h"

#include <iostream>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include <fmod.hpp>

using namespace std;

int main(int argc, char* argv[]) {

	g_engine.Initialize();

	//timing
	Time time;

	//particle system
	vector<Particle> particles;
	float offset = 0;

	//model system
	vector<Vector2> points;
	points.push_back(Vector2{ 0,0 });
	points.push_back(Vector2{ 3,0 });
	points.push_back(Vector2{ 0,3 });
	points.push_back(Vector2{ 0,0 });
	

	//actor
	Model* model = new Model{ points, Color(1,1,1,0) };


	//create scene
	Scene* scene = new Scene();
	for (int i = 0; i < 100; i++) {
		
		Transform transform{ Vector2{randomf(0,800),randomf(0,600)},0,randomf(1,5)};
		Player* player = new Player(randomf(100,200), transform, model);
		player->SetDamping(0.4f);
		scene->AddActor(player);
	}
	

	//main loop
	bool end = false;
	while (!end) {
		// input
		// update
		// draw
		 
		//Input
		time.Tick();
		g_engine.GetInput().Update();

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			end = true;
		}


		//Update
		scene->Update(time.GetDeltaTime());
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		for (Particle& particle : particles) {
			g_engine.GetRenderer().SetColor(255, 255, 255, 0);
			particle.update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
		if (g_engine.GetInput().getMouseButtonDown(0)) {
			particles.push_back(Particle{ {mousePosition.x,mousePosition.y},
				{randomf(-50.0f,50.0f), randomf(-50.0f,50.0f)},{randomf(1.0f,5.0f)},
				random(0,255),random(0,255),random(0,255),random(0,255)});		
		}

		//Draw
		//clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();
		//change screen
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		float radius = 60;
		offset += (45 * time.GetDeltaTime());
		for (float angle = 0; angle < 360; angle += 360 / 360) {
			float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle ) * 5) * radius;
			float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle ) * 5) * radius;

			g_engine.GetRenderer().SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			g_engine.GetRenderer().DrawRect(400 + x, 300 + y, 4.0f, 4.0f);
		}

		//drawing fireworks
		for (Particle particle : particles) {
			g_engine.GetRenderer().SetColor(particle.r,particle.g,particle.b,particle.a);
			particle.draw(g_engine.GetRenderer());
		}

		scene->Draw(g_engine.GetRenderer());

		//show screen
		g_engine.GetRenderer().EndFrame();

		//input
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Q))g_engine.GetAudio().PlaySound("bass.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_A))g_engine.GetAudio().PlaySound("snare.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Z) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Z))g_engine.GetAudio().AddSound("open-hat.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_X) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_X))g_engine.GetAudio().AddSound("close-hat.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_S))g_engine.GetAudio().AddSound("clap.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_W))g_engine.GetAudio().AddSound("cowbell.wav");

		g_engine.GetAudio().Update();
	}
	return 0;
}
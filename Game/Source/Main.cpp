#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "Font.h"
#include "Text.h"

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_main.h>
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

	

	//font
	Font* font = new Font;
	font->Load("MONIMONI.ttf", 20);

	

	Text* text = new Text(font);
	text->Create(g_engine.GetRenderer(), "Hello World!", Color{1,0,0,1});

	//model system
	vector<Vector2> points;
	points.push_back(Vector2{ 5,0 });
	points.push_back(Vector2{ -5,-5 });
	points.push_back(Vector2{ -5,5 });
	points.push_back(Vector2{ 5,0 });
	

	//actor
	Model* model = new Model{ points, Color(1,1,1,0) };
	Scene* scene = new Scene();

	Transform transform{ Vector2{randomf(0,800),randomf(0,600)},0,randomf(1,5)};
	Player* player = new Player(randomf(300,500), transform, model);
	player->SetDamping(2.0f);
	player->SetTag("Player");
	scene->AddActor(player);

	auto* enemyModel = new Model{ points, Color{1,0,1,0} };
	auto* enemy = new Enemy(400, Transform{ {g_engine.GetRenderer().GetWidth(),g_engine.GetRenderer().GetHeight()},0,2}, enemyModel);
	enemy->SetTag("Enemy");
	enemy->SetDamping(1.0f);
	scene->AddActor(enemy);


	float spawnTimer = 2;

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

		//mouse input
		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();

		//drum input
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Q))g_engine.GetAudio().PlaySound("bass.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_A) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_A))g_engine.GetAudio().PlaySound("snare.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Z) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Z))g_engine.GetAudio().PlaySound("open-hat.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_X) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_X))g_engine.GetAudio().PlaySound("close-hat.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_S) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_S))g_engine.GetAudio().PlaySound("clap.wav");
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_W))g_engine.GetAudio().PlaySound("cowbell.wav");
		
	//Update
		scene->Update(time.GetDeltaTime());

		spawnTimer -= time.GetDeltaTime();
		if (spawnTimer <= 0) {
			auto* enemy = new Enemy(400, Transform{ {g_engine.GetRenderer().GetWidth(),g_engine.GetRenderer().GetHeight()},0,2 }, enemyModel);
			enemy->SetTag("Enemy");
			enemy->SetDamping(1.0f);
			scene->AddActor(enemy);
			spawnTimer = 2;
		}

		text->Draw(g_engine.GetRenderer(), 40, 40);

		//screen wrap
		for (Particle& particle : particles) {
			g_engine.GetRenderer().SetColor(255, 255, 255, 0);
			particle.update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		//create particles
		if (g_engine.GetInput().getMouseButtonDown(0)) {
			particles.push_back(Particle{ {mousePosition.x,mousePosition.y},
				{randomf(-50.0f,50.0f), randomf(-50.0f,50.0f)},{randomf(1.0f,5.0f)},
				random(0,255),random(0,255),random(0,255),random(0,255)});		
		}

		//update drums
		g_engine.GetAudio().Update();

	//Draw
		//clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();
		//change screen
		g_engine.GetRenderer().SetColor(255, 255, 255, 0);
		
		text->Draw(g_engine.GetRenderer(), 40, 40);

		//drawing fireworks
		for (Particle particle : particles) {
			g_engine.GetRenderer().SetColor(particle.r,particle.g,particle.b,particle.a);
			particle.draw(g_engine.GetRenderer());
		}

		scene->Draw(g_engine.GetRenderer());

		//show screen
		g_engine.GetRenderer().EndFrame();
	}
	return 0;
}

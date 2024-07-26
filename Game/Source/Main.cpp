#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "Font.h"
#include "Text.h"
#include "ETimer.h"

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

	SpaceGame* game = new SpaceGame(&g_engine);
	game->Initialize();


	
	while (!game->close) {
		//input

		//update

		g_engine.Update();
		game->Update(g_engine.GetTime().GetDeltaTime());

		//draw
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();
		game->Draw(g_engine.GetRenderer());

		//display
		g_engine.GetRenderer().EndFrame();

	}
	g_engine.Shutdown();
	return 0;
}

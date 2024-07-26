#include "SpaceGame.h" 
#include "Scene.h" 
#include "Engine.h"
#include "Player.h" 
#include "Enemy.h"
#include "Game.h" 
#include "GameData.h"
#include "Transform.h" 
#include "Font.h"
#include "Text.h"
#include <Renderer.cpp>


bool SpaceGame::Initialize()
{

    m_scene = new Scene();

    m_font = new Font();
    m_font->Load("MONIMONI.ttf", 20);


    m_fontLarge = new Font();
    m_fontLarge->Load("MONIMONI.ttf", 200);

    m_textScore = new Text(m_font);
    m_textLives = new Text(m_font);
    m_textTitle = new Text(m_font);


    return true;
}

void SpaceGame::ShutDown()
{


}

void SpaceGame::Update(float dt)
{

    switch (m_state) {


    case SpaceGame::eState::Title:
        //draw text
        m_textTitle->Create(g_engine.GetRenderer(), "Space Game", Color{1,0,0,1});

        if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {
            m_state = eState::StartGame;
        }
        break;



    case SpaceGame::eState::StartGame:
        m_score = 0;
        m_lives = 3;


        m_state = eState::StartLevel;

        break;



    case SpaceGame::eState::StartLevel:
        m_scene->RemoveAll();
        {
            Transform transform{ Vector2{ 400, 300 }, 0, 3 };

            Model* model = new Model{ GameData::shipPoints, Color{0,0,1,0} };
            Transform transform{ Vector2{randomf(0,800),randomf(0,600)},0,randomf(1,5) };
            auto player = std::make_unique<Player>(randomf(300, 500), transform, model);
            player->SetDamping(2.0f);
            player->SetTag("Player");
            m_scene->AddActor(std::move(player));
        }


        break;




    case SpaceGame::eState::Game:

        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0) {
            m_spawnTimer = m_spawnTime;

            auto* enemyModel = new Model{ points, Color{1,0,1,0} };
            auto enemy = std::make_unique<Enemy>(400.0f, Transform{ {g_engine.GetRenderer().GetWidth(),g_engine.GetRenderer().GetHeight()},0.0f,2.0f }, enemyModel);
            enemy->SetTag("Enemy");
            enemy->SetDamping(1.0f);
            m_scene->AddActor(std::move(enemy));;

        }

        break;




    case SpaceGame::eState::PlayerDead:
        m_lives--;
        m_state = (m_lives == 0) ? eState::GameOver : eState::PlayerDead;
         m_statetimer = 3;

        break;




    case SpaceGame::eState::GameOver:
        m_textTitle->Create(g_engine.GetRenderer(), "Game over", Color{1,0,0,1});
        break;

    }



    m_scene->Update(dt);
}

void SpaceGame::Draw(Renderer& renderer)
{
    switch (m_state) {

    case SpaceGame::eState::Title:
        break;
    case SpaceGame::eState::GameOver:
        break;
    default:
        break;

    }
    //draw score 
    std::string text = "Score" + std::to_string(m_score);
    m_textScore->Create(renderer, text, { 0,1,0,1 });
    m_textScore->Draw(renderer, 20, 20);
    //draw lives
    text = "Lives" + std::to_string(m_score);
    m_textLives->Create(renderer, text, { 0,1,0,1 });
    m_textLives->Draw(renderer, 120, 20);


    m_scene->Draw(renderer);
}

// add to eState::Game
// new enemy(400, transform{ {random(g_engine.GetRenderer().GetWidth()), random(g_engine.GetRenderer().GetWidth());
//crete pickup


//case eState::PLAYER_DEAD:
// m_stateTimer -= dt;
// if (m_stateTimer <= 0) {
	//m_state = eState::START_LEVEL
//}
//break;



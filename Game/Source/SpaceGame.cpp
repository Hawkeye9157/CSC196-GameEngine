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
#include "Renderer.h"


bool SpaceGame::Initialize()
{
    m_scene = new Scene(this);
    

    m_font = new Font();
    m_font->Load("MONIMONI.ttf", 20);


    m_fontLarge = new Font();
    m_fontLarge->Load("MONIMONI.ttf", 50);

    m_textScore = new Text(m_font);
    m_textLives = new Text(m_font);
    m_textTitle = new Text(m_fontLarge);

    g_engine.GetAudio().AddSound("background.wav");

    return true;
}

void SpaceGame::ShutDown()
{


}

void SpaceGame::Update(float dt)
{
    if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        close = true;
    }
    
    switch (m_state) {


    case SpaceGame::eState::Title:
        //draw text
        m_textTitle->Create(g_engine.GetRenderer(), "Space Game", Color{1,0,0,1});
       // g_engine.GetAudio().PlaySound("background.wav",1);
        if (m_engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) {m_state = SpaceGame::eState::StartGame;}
        break;



    case SpaceGame::eState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_spawnTime = 1;
        m_spawnTimer = m_spawnTime;

        m_state = eState::StartLevel;

        break;

    case SpaceGame::eState::StartLevel:
        m_scene->RemoveAll();
        {
            Transform transform{ Vector2{ 400, 300 }, 0, 3 };
            std::vector<Vector2> shipPoints{
                {5,0},
                {-5,-5},
                {-5,5},
                {5,0}
            };
            Model* model = new Model{shipPoints, Color{1,0,1,1} };
            auto player = std::make_unique<Player>(400, transform, model);
            player->SetDamping(2.0f);
            player->SetTag("Player");
           
            m_scene->AddActor(std::move(player));

            m_scene->Draw(g_engine.GetRenderer());
            
        }
        m_state = eState::Game;
        break;

    case SpaceGame::eState::Game:

        m_spawnTimer -= dt;
        if (m_spawnTimer <= 0) {
            m_spawnTimer = m_spawnTime;

            std::vector<Vector2> shipPoints{
                {5,0},
                {-5,-5},
                {-5,5},
                {5,0}
            };
            auto* enemyModel = new Model{ shipPoints, Color{1,0,1,1} };
            auto enemy = std::make_unique<Enemy>(400.0f, Transform{ 
                {g_engine.GetRenderer().GetWidth(),g_engine.GetRenderer().GetHeight()},0.0f,2.0f }, enemyModel);
            enemy->SetTag("Enemy");
            enemy->SetDamping(1.0f);
            m_scene->AddActor(std::move(enemy));

        }
        break;

    case SpaceGame::eState::PlayerDead:
        m_lives--;
        m_state = (m_lives == 0) ? eState::GameOver : eState::PlayerDead;
         m_stateTimer = 3;
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
        m_textTitle->Draw(g_engine.GetRenderer(), g_engine.GetRenderer().GetWidth() / 2.25, g_engine.GetRenderer().GetHeight() / 2);
        break;
    case SpaceGame::eState::StartLevel:
        renderer.SetColor(1, 0, 0, 1);
        m_scene->Draw(g_engine.GetRenderer());
        break;
    case SpaceGame::eState::GameOver:
        break;
    default:
        break;

    }
    //draw score 
    std::string text = "Score: " + std::to_string(m_score);
    m_textScore->Create(renderer, text, { 0,1,0,1 });
    m_textScore->Draw(renderer, 20, 20);
    //draw lives
    text = "Lives: " + std::to_string(m_lives + (m_score / 100));
    m_textLives->Create(renderer, text, { 0,1,0,1 });
    m_textLives->Draw(renderer, 120, 20);

    m_scene->Draw(renderer);
}




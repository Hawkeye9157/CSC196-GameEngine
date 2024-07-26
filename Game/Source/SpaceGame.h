#pragma once
#include "Game.h"


class Font;
class Text;


class SpaceGame : public Game
{

public:
    enum class eState : char {
        Title,
        StartGame,
        StartLevel,
        Game,
        PlayerDead,
        GameOver

    };

public:
    SpaceGame(Engine* engine) : Game{ engine } {}

    bool Initialize() override;
    void ShutDown() override;



    void Update(float dt) override;
    void Draw(Renderer& renderer) override;



protected:
    eState m_state{ eState::Title };
    float m_spawnTimer{ 0 };
    float m_spawnTime{ 0 };

    Font* m_font{ nullptr };
    Text* m_textScore{ nullptr };
    Text* m_textLives{ nullptr };

    Text* m_textTitle{ nullptr };

    Font* m_fontLarge{ nullptr };
};
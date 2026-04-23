#include "Game.h"
#include "Application/SceneManager/SceneManager.h"
#include"Application/Character/Player/Player.h"


void Game::Init()
{

	m_player = new Player();
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_player->SetTex(&m_playerTex);
	m_player->Init();
}

void Game::Update()
{
	
	
	m_player->Update();
	
	
	//シーン切り替え
	if (GetAsyncKeyState('R') & 0x8000)
	{

		if (m_player)
		{
			delete m_player;
			m_playerTex.Release();
		}
		m_owner->ChangeScene(RESULT);
	}
}

void Game::Draw2D()
{

	m_player->Draw2D();

	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 100, "ゲーム Rで変更", Math::Vector4(1, 1, 0, 1));
}

void Game::Release()
{
	if (m_player)
	{
		delete m_player;
		m_playerTex.Release();
	}
}

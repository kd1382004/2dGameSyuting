#include "Game.h"
#include "Application/SceneManager/SceneManager.h"
#include"Application/Character/Player/Player.h"
#include"Application/Character/Enemy/EnemyBase.h"

void Game::Init()
{
	//プレイヤー初期化
	m_player = new Player();
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_player->SetTex(&m_playerTex);
	m_player->Init();


	//敵初期化
	m_enemyBaseTex.Load("Tex/Character/Enemy/enemy.png");
	m_enemyBase = new EnemyBase();
	m_enemyBase->SetTex(&m_enemyBaseTex);
}

void Game::Update()
{
	
	
	m_player->Update();
	
	m_enemyBase->Update();
	
	//シーン切り替え
	if (GetAsyncKeyState('R') & 0x8000)
	{

		if (m_enemyBase)
		{
			delete m_enemyBase;
			m_enemyBaseTex.Release();
		}

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

	m_enemyBase->Draw2D();

	m_player->Draw2D();

	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 100, "ゲーム Rで変更", Math::Vector4(1, 1, 0, 1));
}

void Game::Release()
{
	if (m_enemyBase)
	{
		delete m_enemyBase;
		m_enemyBaseTex.Release();
	}

	if (m_player)
	{
		delete m_player;
		m_playerTex.Release();
	}
}

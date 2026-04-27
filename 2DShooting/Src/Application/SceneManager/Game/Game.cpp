#include "Game.h"
#include "../SceneManager.h"
#include"../../Character/Player/Player.h"
#include"../../Character/Enemy/EnemyBase.h"
#include"../../Hit/CharaHit.h"
#include"../../Hit/Bullet/BulletHit.h"


void Game::Init()
{
	//プレイヤー初期化
	m_player = new Player();
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_player->SetTex(&m_playerTex);
	m_player->Init();


	//敵(ベース)初期化
	m_enemyBaseTex.Load("Tex/Character/Enemy/enemy.png");

	for (int i = 0; i < 1; i++)
	{
		m_enemy.push_back(new EnemyBase());
		m_enemy.back()->SetTex(&m_enemyBaseTex);
		m_enemy.back()->Init();
	}




	//当たり判定
	m_charaHit = new CharaHit();

	m_bulletHit = new BulletHit();
}

void Game::Update()
{
	
	if (m_player)
	{
		/////////////////////
		//プレイヤー　更新//
		////////////////////
		m_player->Update();
	}
	
	for (int i = 0; i < m_enemy.size(); i++)
	{
		if (m_enemy[i])
		{
			if (m_player)
			{
				////////////////////////////
				//敵にプレイヤー座標セット//
				////////////////////////////
				m_enemy[i]->SetPlayerPos(m_player->GetPos());
			}


			////////////
			//敵　更新//
			////////////
			m_enemy[i]->Update();
		}
	}
	

	//////////////
	//当たり判定//
	//////////////
	if (m_charaHit)
	{
		//////////////////
		//敵とプレイヤー//
		//////////////////
		for (int i = 0; i < m_enemy.size(); i++)
		{
			if (m_charaHit->Hit(m_enemy[i], m_player))
			{
				//当たったときの処理

				//プレイヤー


				//敵

			}

			//敵同士
			for (int j = i + 1; j < m_enemy.size(); j++)
			{
				if (m_charaHit->Hit(m_enemy[i], m_enemy[j]))
				{
					//重ならないように座標補正



				}
			}
		}

	}

	if (m_bulletHit)
	{
		//////////
		//敵と弾//
		//////////
		for (int i = 0; i < m_enemy.size(); i++)
		{
			for (int j = 0; j < m_player->GetBulletNum(); j++)
			{
				if (m_bulletHit->Hit(m_player->GetBullet(j), m_enemy[i]))
				{
					//当たったときの処理

					//弾

					//敵

				}
			}
		}
	}

	



	//シーン切り替え
	if (GetAsyncKeyState('R') & 0x8000)
	{
		m_owner->SetNextSceneType(RESULT);
	}
}

void Game::Draw2D()
{

	for (int i = 0; i < m_enemy.size(); i++)
	{
		if (m_enemy[i])
		{
			m_enemy[i]->Draw2D();
		}
	}


	if (m_player)
	{
		m_player->Draw2D();
	}


	// 文字列表示
	SHADER.m_spriteShader.DrawString(0, 100, "ゲーム Rで変更", Math::Vector4(1, 1, 0, 1));
}



EnemyBase* Game::GetEnemy(int num)
{
	if (num >= 0 && num < m_enemy.size())
	{
		return m_enemy[num];
	}

	return nullptr;
}

void Game::Release()
{
	PtrRelease();
}

void Game::PtrRelease()
{

	for (int i = 0; i < m_enemy.size(); i++)
	{
		if (m_enemy[i])
		{
			delete m_enemy[i];
			m_enemy.erase(m_enemy.begin() + i);
			i--;
		}
	}
	m_enemyBaseTex.Release();


	if (m_player)
	{
		delete m_player;
		m_playerTex.Release();
	}

	if (m_charaHit)
	{
		delete m_charaHit;
	}
}

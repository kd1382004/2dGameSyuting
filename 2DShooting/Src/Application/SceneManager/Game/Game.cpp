#include "Game.h"
#include "../SceneManager.h"
#include"../../Character/Player/Player.h"
#include"../../Character/Enemy/Slime/Slime.h"
#include"../../Character/Enemy/Skeleton/Skeleton.h"
#include"../../Hit/CharaHit.h"
#include"../../Map/Map.h"


void Game::Init()
{
	//プレイヤー初期化
	m_player = new Player();
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_player->SetTex(&m_playerTex);
	m_player->Init();


	//敵(ベース)初期化
	m_skeletonTex.Load("Tex/Character/Enemy/Skeleton/Skeleton.png");
	m_slimeTex.Load("Tex/Character/Enemy/Slime/Slime_Green.png");

	for (int i = 0; i < 50; i++)
	{
		m_enemy.push_back(new Slime());
		m_enemy.back()->SetTex(&m_slimeTex);
		m_enemy.back()->Init();
	}

	for (int i = 0; i < 5; i++)
	{
		m_enemy.push_back(new Skeleton());
		m_enemy.back()->SetTex(&m_skeletonTex);
		m_enemy.back()->Init();
	}

	//当たり判定
	m_charaHit = new CharaHit();


	//マップ
	m_map = new Map();
	m_map->Init(Map::MapType::Map1);
	m_map->setOwner(this);
}

void Game::Update()
{

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////


	//////////////
	//プレイヤー//
	//////////////
	if (m_player)
	{
		/////////////////////
		//プレイヤー　更新//
		////////////////////
		m_player->Update();
	}


	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////


	//////
	//敵//
	//////
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


	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////


	//////////////
	//当たり判定//
	//////////////
	if (m_charaHit)
	{
		for (int i = 0; i < m_enemy.size(); i++)
		{
			//////////////////
			//敵とプレイヤー//
			//////////////////
			if (m_charaHit->CharacterHit(m_enemy[i], m_player))
			{
				//当たったときの処理

				//プレイヤー



				//重ならないように座標補正				
				m_charaHit->Pushback(m_enemy[i], m_player);

			}

			//////////
			//敵同士//
			/////////
			for (int j = i; j < m_enemy.size(); j++)
			{
				if (j == i)
				{
					continue;
				}

				if (m_charaHit->CharacterHit(m_enemy[i], m_enemy[j]))
				{
					//重ならないように座標補正				
					m_charaHit->Pushback(m_enemy[i], m_enemy[j]);
				}
			}
		}

		//////////
		//敵と弾//
		//////////
		for (int i = 0; i < m_enemy.size(); i++)
		{
			for (int j = 0; j < m_player->GetBulletNum(); j++)
			{
				if (m_charaHit->BulletHit(m_player->GetBullet(j), m_enemy[i], i))
				{
					//当たったときの処理

					//弾
					m_player->PlayerBulletHit(j);

					//敵
					m_enemy[i]->PlayerBulletHit(m_player->GetBullet(j));
				}
			}
		}
	}

	if (m_map)
	{
		m_map->MapHit(m_player);
		for (int i = 0; i < m_enemy.size(); i++)
		{
			m_map->MapHit(m_enemy[i]);
		}

		for (int j = 0; j < m_player->GetBulletNum(); j++)
		{
			m_map->MapHit(m_player->GetBullet(j));
		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//マップ更新
	m_map->Updata();


	

	//////////////////////////////////////////////////////////////////////////////
	
	if (m_player)
	{
		m_player->MatConfirmed(m_map->GetScroll());
	}

	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->MatConfirmed(m_map->GetScroll());
	}



	//////////////////////////////////////////////////////////////////////////////
	//削除処理

	//敵
	for (int i = 0; i < m_enemy.size(); i++)
	{
		if (!m_enemy[i]->GetAliveFlg())
		{
			delete m_enemy[i];
			m_enemy.erase(m_enemy.begin() + i);
			i--;
		}
	}

	//球
	for (int i = 0; i < m_player->GetBulletNum(); i++)
	{
		m_player->ReleseBuleet(i);
	}



	//クリア処理
	if (m_enemy.size() == 0)
	{
		int a = 0;
	}



	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	//シーン切り替え
	if (GetAsyncKeyState('R') & 0x8000)
	{
		m_owner->SetNextSceneType(RESULT);
	}
}

void Game::Draw2D()
{
	//マップ描画
	m_map->Draw2D();

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

Math::Vector2 Game::GetPlayerPos()
{
	if (m_player)
	{
		return m_player->GetPos();
	}

	return Math::Vector2();
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
	m_skeletonTex.Release();
	m_slimeTex.Release();


	if (m_player)
	{
		delete m_player;
		m_playerTex.Release();
	}

	if (m_charaHit)
	{
		delete m_charaHit;
	}

	if (m_map)
	{
		delete m_map;
	}
}

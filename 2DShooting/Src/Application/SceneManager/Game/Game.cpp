#include "Game.h"
#include "../SceneManager.h"
#include"../../Character/Player/Player.h"
#include"../../Character/Enemy/Slime/Slime.h"
#include"../../Hit/CharaHit.h"


void Game::Init()
{
	//プレイヤー初期化
	m_player = new Player();
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_player->SetTex(&m_playerTex);
	m_player->Init();


	//敵(ベース)初期化
	m_enemyBaseTex.Load("Tex/Character/Enemy/enemy.png");

	for (int i = 0; i < 10; i++)
	{
		m_enemy.push_back(new Slime());
		m_enemy.back()->SetTex(&m_enemyBaseTex);
		m_enemy.back()->Init();
	}

	//当たり判定
	m_charaHit = new CharaHit();
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


				//敵
				//重ならないように座標補正				
				const float x = m_enemy[i]->GetPos().x - m_player->GetPos().x;
				const float y = m_enemy[i]->GetPos().y - m_player->GetPos().y;
				const float z = sqrt(x * x + y * y);

				//半径＋半径
				const float sum = m_enemy[i]->GetHitDetection() / 2 + m_player->GetHitDetection() / 2;

				//重なり具合
				float over = sum - z;

				//敵2から敵1への方向
				float nx = x / z;
				float ny = y / z;

				Math::Vector2 notMove = { 0,0 };
				if (m_enemy[i]->Getmove() != notMove)//iが動いている場合
				{
					Math::Vector2 enemyiPos = m_enemy[i]->GetPos();
					enemyiPos.x += nx * over;
					enemyiPos.y += ny * over;
					m_enemy[i]->SetPos(enemyiPos);
				}
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
					const float x = m_enemy[i]->GetPos().x - m_enemy[j]->GetPos().x;
					const float y = m_enemy[i]->GetPos().y - m_enemy[j]->GetPos().y;
					const float z = sqrt(x * x + y * y);

					//半径＋半径
					const float sum = m_enemy[i]->GetHitDetection() / 2 + m_enemy[j]->GetHitDetection() / 2;

					//重なり具合
					float over = sum - z;

					//敵2から敵1への方向
					float nx = x / z;
					float ny = y / z;


					Math::Vector2 notMove = { 0,0 };
					if (m_enemy[i]->Getmove() != notMove && m_enemy[j]->Getmove() != notMove)//両方動いてる敵
					{
						Math::Vector2 enemyiPos = m_enemy[i]->GetPos();
						Math::Vector2 enemyjPos = m_enemy[j]->GetPos();

						//お互いに半分ずつ押し返す
						enemyiPos.x += nx * (over * 0.5);
						enemyiPos.y += ny * (over * 0.5);
						enemyjPos.x -= nx * (over * 0.5);
						enemyjPos.y -= nx * (over * 0.5);

						m_enemy[i]->SetPos(enemyiPos);
						m_enemy[j]->SetPos(enemyjPos);
					}
					else if (m_enemy[i]->Getmove() != notMove)//iが動いている場合
					{
						Math::Vector2 enemyiPos = m_enemy[i]->GetPos();
						enemyiPos.x += nx * over;
						enemyiPos.y += ny * over;
						m_enemy[i]->SetPos(enemyiPos);
					}
					else if (m_enemy[j]->Getmove() != notMove)//jが動いている場合
					{
						Math::Vector2 enemyjPos = m_enemy[j]->GetPos();
						enemyjPos.x -= nx * (over * 0.5);
						enemyjPos.y -= nx * (over * 0.5);
						m_enemy[i]->SetPos(enemyjPos);
					}


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
				if (m_charaHit->BulletHit(m_player->GetBullet(j), m_enemy[i],i))
				{
					//当たったときの処理

					//弾
					m_player->PlayerBulletHit(j);

					//敵

				}
			}
		}
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

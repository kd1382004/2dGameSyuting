#include "Game.h"
#include "../SceneManager.h"
#include"../../Character/Player/Player.h"
#include"../../Character/Enemy/Slime/Slime.h"
#include"../../Character/Enemy/Skeleton/Skeleton.h"
#include"../../Hit/CharaHit.h"
#include"../../Map/Map.h"
#include"PowerUpScreen/PowerUpScreen.h"
#include"../../Info/InfoKey/InfoKey.h"
#include"../../Info/NumDraw/NumDraw.h"
#include"../../Character/Info/CharacterInfoBace.h"
#include"DefAnime/DefAnime.h"
#include"InfoGame/InfoGame.h"
#include "../../Info/GameResult/GameResult.h"
#include"../../Info/HighScore/HighScore.h"


void Game::Init()
{
	m_stageNum = 0;
	m_DEF = false;
	//プレイヤー初期化
	m_player = new Player();
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_playerShadowTex.Load("Tex/Character/Player/playerr-Shadow.png");
	m_player->SetTex(&m_playerTex);
	m_player->SetShadowTex(&m_playerShadowTex);
	m_player->Init();


	//敵(ベース)初期化
	m_skeletonTex.Load("Tex/Character/Enemy/Skeleton/Skeleton.png");
	m_slimeTex.Load("Tex/Character/Enemy/Slime/Slime_Green.png");

	//当たり判定
	m_charaHit = new CharaHit();

	m_infoGame = new InfoGame();
	m_infoGame->Init();

	//強化画面
	m_powerUpScreen = new PowerUpScreen();


	m_EnemyDeath = 0;
	m_powerUpNum = 0;
	m_stageClearNum = 0;
	m_score = 0;

	//ステージごとに変わるやつ
	InitStage(m_stageNum);

	m_nextStageTex.Load("Tex/NextStage/NextStage.png");
}

void Game::Update()
{

	if (m_nextStageAnimeFlg)
	{
		NextStagenimeUpdate();
		return;
	}

	if (m_stageStartAnimeFlg)
	{
		StageStartAnimeUpdate();
		return;
	}

	if (m_DEF)
	{
		if (m_defAnime)
		{
			m_defAnime->Update(this);
		}

		return;
	}

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//強化画面じゃなかったら
	if (!m_powerUpScreenFlg)
	{
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
					m_player->HPDown(m_enemy[i]->GetCharaInfo()->GetATK());


					//重ならないように座標補正				
					//m_charaHit->Pushback(m_enemy[i], m_player);

				}

				//////////////////////
				//敵の弾とプレイヤー//
				//////////////////////
				if (m_enemy[i]->GetBulletNum() > 0)
				{
					for (int j = 0; j < m_enemy[i]->GetBulletNum(); j++)
					{
						if (m_charaHit->BulletHit(m_enemy[i]->GetBullet(j), m_player, -1))
						{
							m_enemy[i]->BulletHit(m_enemy[i]->GetBullet(j));
   							m_player->HPDown(m_enemy[i]->GetCharaInfo()->GetATK());
						}

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
						m_charaHit->Pushback(m_enemy[i], m_enemy[j]);
						m_enemy[i]->EnemyHit();
						m_enemy[j]->EnemyHit();
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
				if (m_enemy[i]->GetBulletNum() > 0)
				{
					for (int j = 0; j < m_enemy[i]->GetBulletNum(); j++)
					{
						m_map->MapHit(m_enemy[i]->GetBullet(j));
					}
				}

			}

			for (int j = 0; j < m_player->GetBulletNum(); j++)
			{
				m_map->MapHit(m_player->GetBullet(j));
			}
		}


	}
	else
	{
		m_powerUpScreen->Update(m_player->GetPlayerPlayerPowerUpInfo(), this);
	}

	//////////////////////////////////////////////////////////////////////////////
	//マップ更新
	if (m_map)
	{
		m_map->Updata();
	}

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
		if (m_enemy[i]->GetDeleteFlg())
		{
			ScorePush(1);
			delete m_enemy[i];
			m_enemy.erase(m_enemy.begin() + i);
			i--;
			m_EnemyDeath++;

			if (m_player)
			{
				m_player->HPHeel(m_player->EnemyDehHeelAmount());
			}
		}
	}

	m_player->ReleseBuleet(0);
	


	//////////////////////////////////////////////////////////////////////////////
	//クリア処理(敵の数が0になる)
	if (m_enemy.size() == 0 && !m_stageClearFlg)
	{
		m_stageClearFlg = true;
		m_stageClearNum++;
		m_powerUpScreenNum++;
	}


	//強化が可能なら
	if (!m_powerUpScreenFlg && m_powerUpScreenNum > 0)
	{
		if (InfoKeyAPP.KeyPush(VK_RETURN, true, true))
		{
			m_powerUpScreenFlg = true;
			m_powerUpScreen->Init(m_player->GetPlayerPlayerPowerUpInfo());
			m_powerUpScreenNum--;
			m_powerUpNum++;
		}
	}


	if (m_player)
	{
		if (m_player->GetHP() <= 0)
		{
			m_DEF = true;
			m_defAnime = new DefAnime();
			m_defAnime->Init();
			GameResultInfoAPP.SetScroll(m_map->GetScroll());
			GameResultInfoAPP.SetplayerDefPos(m_player->GetPos());
		}
	}

	//情報画面更新
	if (m_infoGame)
	{
		m_infoGame->Update(m_player->GetPlayerPlayerPowerUpInfo());
		m_infoGame->SetPWUPNum(m_powerUpScreenNum);
		m_infoGame->SetPlyerHpHeel(m_player->GetEnemyDehHeelLv());
	}

	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
}

void Game::Draw2D()
{

	if (m_DEF && m_defAnime)
	{
		if (m_defAnime)
		{
			m_defAnime->Draw2D();
		}
		return;
	}


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

	if (m_infoGame)
	{
		m_infoGame->Drow2D();
	}

	if (m_powerUpScreenFlg)
	{
		m_powerUpScreen->Draw2D();
	}


	if (m_stageStartAnimeFlg)
	{
		StageStartAnimeDraw2D();
	}

	if (m_nextStageAnimeFlg)
	{
		NextStagenimeDraw2D();
	}
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

void Game::NextScene()
{
	HighScoreAPP.nowScre.score = m_score;
	HighScoreAPP.nowScre.clearNum = m_stageClearNum;
	HighScoreAPP.nowScre.enemyNum = m_EnemyDeath;
	HighScoreAPP.nowScre.powerUpNum = m_powerUpNum;
	if (m_player->GetCharaInfo()->Get3WShotFlg())
	{
		HighScoreAPP.nowScre._3wShotLv = 1;
	}
	else
	{
		HighScoreAPP.nowScre._3wShotLv = 0;
	}

	if (m_player->GetCharaInfo()->GetLRShotFlg())
	{
		HighScoreAPP.nowScre._LRShotLv = 1;
	}
	else
	{
		HighScoreAPP.nowScre._LRShotLv = 0;
	}


	HighScoreAPP.nowScre.peneLv = m_player->GetCharaInfo()->GetBuletPeneNum();
	HighScoreAPP.nowScre.bounLv = m_player->GetCharaInfo()->GetBoundNum();
	HighScoreAPP.nowScre.ATKUpLv = m_player->GetCharaInfo()->GetATKLV();
	HighScoreAPP.nowScre.hpHeelLv = m_player->GetEnemyDehHeelLv();
	HighScoreAPP.HighScoreNew();

	GameResultInfoAPP.SetEnemyDeath(m_EnemyDeath);
	GameResultInfoAPP.SetScore(m_score);
	GameResultInfoAPP.SetmStageClearNum(m_stageClearNum);
	GameResultInfoAPP.SetPowerUpNum(m_powerUpNum);
	m_owner->SetNextSceneType(RESULT);
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
		m_playerShadowTex.Release();
	}

	if (m_charaHit)
	{
		delete m_charaHit;
	}

	if (m_map)
	{
		delete m_map;
	}

	m_nextStageTex.Release();

	if (m_defAnime)
	{
		delete m_defAnime;
	}
}

void Game::StageStartAnimeUpdate()
{

	m_stageStartAnimeCnt -= 1.0 / 60;

	if (m_stageStartAnimeCnt < 0)
	{
		m_stageStartAnimeFlg = false;
	}

}

void Game::StageStartAnimeDraw2D()
{
	int num = m_stageStartAnimeCnt;
	if (num < 4)
	{
		NumDrawAPP.Drow(num, LAligned, Math::Vector2{ 0,0 }, &Math::Color{ 1,1,1,1 }, 10);
	}
}

void Game::InitStage(int StageNum)
{
	//マップ
	if (m_map)
	{
		delete m_map;
	}

	m_map = new Map();
	m_map->setOwner(this);
	m_map->Init((Map::MapType)(StageNum % 3));
	GameResultInfoAPP.SetMapNum((StageNum % 3));
	m_stageClearFlg = false;
	if (m_player)
	{
		m_player->SetPos(m_map->PlayerSpawnPos());
	}
	m_map->Updata();

	int slimeNum = m_map->GetConSlimeSpawnNum() + m_stageNum;

	if (slimeNum > m_map->GetSlimeSpawnNum())
	{
		slimeNum = m_map->GetSlimeSpawnNum();
	}
	for (int i = 0; i < slimeNum; i++)
	{
		m_enemy.push_back(new Slime());
		m_enemy.back()->SetTex(&m_slimeTex);
		m_enemy.back()->Init();
		m_enemy.back()->SetPos(m_map->SlimeSpawnPos());
	}


	int skeletonNum = m_map->GetConSkeletonSpawnNum() + m_stageNum;

	if (skeletonNum > m_map->GetSkeletonSpawnNum())
	{
		skeletonNum = m_map->GetSkeletonSpawnNum();
	}
	for (int i = 0; i < skeletonNum; i++)
	{
		m_enemy.push_back(new Skeleton());
		m_enemy.back()->SetTex(&m_skeletonTex);
		m_enemy.back()->Init();
		m_enemy.back()->SetPos(m_map->SkeletonSpawnPos());
	}

	if (m_player)
	{
		m_player->ReleseBuleet();
		m_player->MatConfirmed(m_map->GetScroll());
	}

	for (int i = 0; i < m_enemy.size(); i++)
	{
		m_enemy[i]->MatConfirmed(m_map->GetScroll());
		m_enemy[i]->SetStatus(StageNum);
	}


	m_stageStartAnimeCnt = 4;
	m_stageStartAnimeFlg = true;
}

void Game::NextStagenimeUpdate()
{
	m_nextStageAlh += m_nextStageAlhPu;
	if (m_nextStageAlh > 2)
	{
		//次のStageに変更する関数を呼び出す
		m_stageNum++;
		m_nextStageAlhPu *= -1;
		InitStage(m_stageNum);
	}

	if (m_nextStageAlh < 0)
	{
		m_nextStageAnimeFlg = false;
		m_nextStageAlh = 0;
		m_nextStageAlhPu *= -1;
	}
}

void Game::NextStagenimeDraw2D()
{
	Math::Matrix mat = Math::Matrix::CreateTranslation(0, 0, 0);
	SHADER.m_spriteShader.SetMatrix(mat);
	SHADER.m_spriteShader.DrawTex(&m_nextStageTex, Math::Rectangle{ 0,0,1280,720 }, m_nextStageAlh);
}

void Game::ScorePush(int lv)
{
	int scorePush;
	scorePush = 100 + 10 * lv + 5 * m_powerUpScreenNum;
	m_score += scorePush;
}

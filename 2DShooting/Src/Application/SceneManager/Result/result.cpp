#include "result.h"
#include "../SceneManager.h"
#include"../../Info/GameResult/GameResult.h"
#include"../../Info/NumDraw/NumDraw.h"
#include"../../Info/InfoKey/InfoKey.h"
#include"../../Button/PlayButton/PlayButton.h"
#include"../../Button/TitleButton/TitleButton.h"
#include"../../Map/Map.h"

void Result::Init()
{
	m_back = new Map();
	m_back->Init((Map::MapType)GameResultInfoAPP.GetMapNum());
	m_back->ResultUpdata(GameResultInfoAPP.GetScroll());

	m_playerTex.Load("Tex/Character/Player/Soldier-Death.png");
	m_playerPos = GameResultInfoAPP.GetplayerDefPos();
	m_playerMat = Math::Matrix::CreateScale(3, 3, 0) * Math::Matrix::CreateTranslation(m_playerPos.x - GameResultInfoAPP.GetScroll(), m_playerPos.y, 0);

	m_resultTex.Load("Tex/Result/Result.png");
	m_resultPos = { 0,300 };
	m_resultMat = Math::Matrix::CreateScale(0.9, 0.9, 0) * Math::Matrix::CreateTranslation(m_resultPos.x, m_resultPos.y, 0);

	m_stageClearTex.Load("Tex/Result/StageClear.png");
	m_stageClearPos = { -350,180 };
	m_stageClearMat = Math::Matrix::CreateScale(m_nameSiz, m_nameSiz, 0) * Math::Matrix::CreateTranslation(m_stageClearPos.x, m_stageClearPos.y, 0);
	m_stageClearNumPos = { m_stageClearPos.x + m_numXGap,m_stageClearPos.y, 0 };
	m_stageClearNumDigit = GetDigit(GameResultInfoAPP.GetmStageClearNum());

	m_EnemyTex.Load("Tex/Result/Enemy.png");
	m_EnemyPos = { m_stageClearPos.x,m_stageClearPos.y + m_yPosGap * m_nameSiz };
	m_EnemyMat = Math::Matrix::CreateScale(m_nameSiz, m_nameSiz, 0) * Math::Matrix::CreateTranslation(m_EnemyPos.x, m_EnemyPos.y, 0);
	m_EnemyNumPos = { m_EnemyPos.x + m_numXGap,m_EnemyPos.y, 0 };
	m_EnemyNumDigit = GetDigit(GameResultInfoAPP.GetEnemyDeath());

	m_PowerUpTex.Load("Tex/Result/PowerUp.png");
	m_PowerUpPos = { m_stageClearPos.x,m_EnemyPos.y + m_yPosGap * m_nameSiz };
	m_PowerUpMat = Math::Matrix::CreateScale(m_nameSiz, m_nameSiz, 0) * Math::Matrix::CreateTranslation(m_PowerUpPos.x, m_PowerUpPos.y, 0);
	m_PowerUpNumPos = { m_PowerUpPos.x + m_numXGap,m_PowerUpPos.y, 0 };
	m_PowerUpNumDigit = GetDigit(GameResultInfoAPP.GetPowerUpNum());

	m_ScoreTex.Load("Tex/Result/Score.png");
	m_ScorePos = { m_stageClearPos.x,m_PowerUpPos.y + m_yPosGap * m_nameSiz * m_ScoreSiz };
	m_ScoreMat = Math::Matrix::CreateScale(m_ScoreSiz, m_ScoreSiz, 0) * Math::Matrix::CreateTranslation(m_ScorePos.x, m_ScorePos.y, 0);
	m_ScoreNumPos = { m_ScorePos.x + m_numXGap,m_ScorePos.y, 0 };
	m_ScoreNumDigit = GetDigit(GameResultInfoAPP.GetScore());

	////////////////
	//ボタン
	m_slect = 0;
	std::shared_ptr<PlayButton> playButton;
	playButton = std::make_shared<PlayButton>();
	playButton->SetOwner(m_owner);
	playButton->Init(Math::Vector2{ -300,-300 });
	playButton->SetDefaultSiz(3);
	playButton->SetSelectSiz(1.5);
	playButton->SetSelectFlg(false);;
	m_button.push_back(playButton);

	std::shared_ptr<TitleButton> titleButton;
	titleButton = std::make_shared<TitleButton>();
	titleButton->SetOwner(m_owner);
	titleButton->Init(Math::Vector2{ 300,-300 });
	titleButton->SetDefaultSiz(3);
	titleButton->SetSelectSiz(1.5);
	titleButton->SetSelectFlg(false);
	m_button.push_back(titleButton);
}

void Result::Update()
{
	m_alpha += m_alphaPush;
	if (m_alpha > 1)
	{
		m_alpha = 1;
		m_alphaPush *= -1;
	}
	if (m_alpha < 0.3)
	{
		m_alpha = 0.3;
		m_alphaPush *= -1;
	}

	if (m_animeFlg)
	{
		Anime();
	}
	else
	{
		//////////////////////////
		//ボタン
		if (InfoKeyAPP.KeyPush(VK_LEFT, true))
		{
			m_slect--;

			if (m_slect < 0)
			{
				m_slect = 0;
			}
		}

		if (InfoKeyAPP.KeyPush(VK_RIGHT, true))
		{
			m_slect++;

			if (m_slect >= m_button.size())
			{
				m_slect = m_button.size() - 1;
			}
		}


		for (int i = 0; i < m_button.size(); i++)
		{
			if (m_button[i])
			{
				if (i == m_slect)
				{
					m_button[i]->SetSelectFlg(true);
					if (InfoKeyAPP.KeyPush(VK_RETURN, true, true))
					{
						m_button[i]->Update();
					}
				}
				else
				{
					m_button[i]->SetSelectFlg(false);
				}
			}
		}
	}	
}

void Result::Draw2D()
{
	////背景
	m_back->Draw2D();

	SHADER.m_spriteShader.SetMatrix(m_playerMat);
	SHADER.m_spriteShader.DrawTex(&m_playerTex, Math::Rectangle{ 300,0,100,100 });

	//リザルト
	SHADER.m_spriteShader.SetMatrix(m_resultMat);
	SHADER.m_spriteShader.DrawTex(&m_resultTex, Math::Rectangle{ 0,0,828,150 });

	//Score
	SHADER.m_spriteShader.SetMatrix(m_ScoreMat);
	m_nameRec = { 0,0,341,60 };
	SHADER.m_spriteShader.DrawTex(&m_ScoreTex, m_nameRec);
	NumDrawAPP.Drow(m_ScoreNum, RAligned, m_ScoreNumPos, &Math::Color{ 1,1,1,m_alpha }, m_numSiz * m_ScoreSiz, true);

	//stageClear
	SHADER.m_spriteShader.SetMatrix(m_stageClearMat);
	m_nameRec = { 0,0,511,60 };
	SHADER.m_spriteShader.DrawTex(&m_stageClearTex, m_nameRec);
	NumDrawAPP.Drow(m_stageClearNum, RAligned, m_stageClearNumPos, &Math::Color{ 1,1,1,m_alpha }, m_numSiz * m_nameSiz, true);

	//Enemy
	SHADER.m_spriteShader.SetMatrix(m_EnemyMat);
	m_nameRec = { 0,0,376,60 };
	SHADER.m_spriteShader.DrawTex(&m_EnemyTex, m_nameRec);
	NumDrawAPP.Drow(m_EnemyNum, RAligned, m_EnemyNumPos, &Math::Color{ 1,1,1,m_alpha }, m_numSiz * m_nameSiz, true);

	//PowerUp
	SHADER.m_spriteShader.SetMatrix(m_PowerUpMat);
	m_nameRec = { 0,0,475,60 };
	SHADER.m_spriteShader.DrawTex(&m_PowerUpTex, m_nameRec);
	NumDrawAPP.Drow(m_PowerUpNum, RAligned, m_PowerUpNumPos, &Math::Color{ 1,1,1,m_alpha }, m_numSiz * m_nameSiz, true);

	//ボタン
	for (int i = 0; i < m_button.size(); i++)
	{
		if (m_button[i])
		{
			m_button[i]->Draw2D();
		}
	}

}

void Result::Release()
{
	m_playerTex.Release();
	m_ScoreTex.Release();
	m_stageClearTex.Release();
	m_EnemyTex.Release();
	m_PowerUpTex.Release();
}

void Result::Anime()
{
	std::random_device rand_dev{};
	std::mt19937 rand_engine(rand_dev());
	int siz = 1000 - 1;
	m_animeCnt++;

	if (m_stageClearNumRand)
	{
		std::uniform_int_distribution<int> dist(0, m_stageClearNumDigit);
		m_stageClearNum = dist(rand_engine);
	}

	if (m_EnemyNumRand)
	{
		std::uniform_int_distribution<int> dist(0, m_EnemyNumDigit);
		m_EnemyNum = dist(rand_engine);
	}

	if (m_PowerUpNumRand)
	{
		std::uniform_int_distribution<int> dist(0, m_PowerUpNumDigit);
		m_PowerUpNum = dist(rand_engine);;
	}

	if (m_ScoreNumRand)
	{
		std::uniform_int_distribution<int> dist(0, m_ScoreNumDigit);
		m_ScoreNum = dist(rand_engine);;
	}

	if (m_animeCnt > m_FlgChangeCnt)
	{
		if (m_stageClearNumRand)
		{
			m_stageClearNumRand = false;
			m_stageClearNum = GameResultInfoAPP.GetmStageClearNum();
		}
	}

	if (m_animeCnt > m_FlgChangeCnt * 2)
	{
		if (m_EnemyNumRand)
		{
			m_EnemyNumRand = false;
			m_EnemyNum = GameResultInfoAPP.GetEnemyDeath();
		}
	}

	if (m_animeCnt > m_FlgChangeCnt * 3)
	{
		if (m_PowerUpNumRand)
		{
			m_PowerUpNumRand = false;
			m_PowerUpNum = GameResultInfoAPP.GetPowerUpNum();
		}
	}


	if (m_animeCnt > m_FlgChangeCnt * 4)
	{
		if (m_ScoreNumRand)
		{
			m_ScoreNumRand = false;
			m_ScoreNum = GameResultInfoAPP.GetScore();
			m_animeFlg = false;
		}
	}

	//アニメーションスキップ
	if(InfoKeyAPP.KeyPush(VK_RETURN, true, true))
	{
		m_stageClearNum = GameResultInfoAPP.GetmStageClearNum();
		m_EnemyNum = GameResultInfoAPP.GetEnemyDeath();
		m_PowerUpNum = GameResultInfoAPP.GetPowerUpNum();
		m_ScoreNum = GameResultInfoAPP.GetScore();
		m_animeFlg = false;
	}
}

int Result::GetDigit(int num)
{

	//桁数を入れるワークspace
	long w = 0;

	//桁数を求める
	for (long long i = 1; i <= num; i *= 10)
	{
		w++;
	}

	if (w == 0)
	{
		w = 1;
	}

	int Num = 1;
	for (int i = 0; i < w; i++)
	{
		Num *= 10;
	}
	Num--;
	return Num;
}

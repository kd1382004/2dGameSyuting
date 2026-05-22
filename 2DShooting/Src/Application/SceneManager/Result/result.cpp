#include "result.h"
#include "../SceneManager.h"
#include"../../Info/GameResult/GameResult.h"
#include"../../Info/NumDraw/NumDraw.h"
#include"../../Info/InfoKey/InfoKey.h"
#include"../../Button/PlayButton/PlayButton.h"
#include"../../Button/TitleButton/TitleButton.h"
#include"../../Map/Map.h"
#include"../../Sound/Button/ButtonSelectionSE.h"
#include"../../Sound/Result/DrumRoll/DrumRollSE.h"
#include"../../Sound/Result/ResultBGM.h"

void Result::Init()
{
	//音
	m_buttonSelectionSE = new ButtonSelectionSE();
	m_drumRollSE = new DrumRollSE();
	m_drumRollSE->Play();

	m_resultBGM = new ResultBGM();
	m_resultBGM->Play();

	m_digit = GetDigit(NumMax);

	MAPAPP.ResultUpdata(GameResultInfoAPP.GetScroll());
	MAPAPP.setOwner(nullptr);

	m_playerTex.Load("Tex/Character/Player/Soldier.png");
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
	m_ScorePos = { m_stageClearPos.x,m_PowerUpPos.y + m_yPosGap * m_nameSiz * m_ScoreSiz*1.2f };
	m_ScoreMat = Math::Matrix::CreateScale(m_ScoreSiz, m_ScoreSiz, 0) * Math::Matrix::CreateTranslation(m_ScorePos.x, m_ScorePos.y, 0);
	m_ScoreNumPos = { m_ScorePos.x + m_numXGap,m_ScorePos.y, 0 };
	m_ScoreNumDigit = GetDigit(GameResultInfoAPP.GetScore());


	m_aliveFlg = GameResultInfoAPP.GetAliveFlg();


	//Bonus
	m_ClearBonusTex.Load("Tex/Result/ClearBonus.png");
	m_ClearBonusPos = { m_ScorePos.x,m_ScorePos.y + m_yPosGap * m_nameSiz * m_ScoreSiz };
	m_ClearBonusMat = Math::Matrix::CreateScale(1, 1, 0) * Math::Matrix::CreateTranslation(m_ClearBonusPos.x, m_ClearBonusPos.y, 0);
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



	m_rodTex.Load("Tex/Result/rod.png");
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
			m_buttonSelectionSE->Stop();
			m_buttonSelectionSE->Play();
		}

		if (InfoKeyAPP.KeyPush(VK_RIGHT, true))
		{
			m_slect++;

			if (m_slect >= m_button.size())
			{
				m_slect = m_button.size() - 1;
			}

			m_buttonSelectionSE->Stop();
			m_buttonSelectionSE->Play();
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
	MAPAPP.Draw2D();

	if (m_aliveFlg)
	{
		m_playerAnime += 0.1;
		if (m_playerAnime > 8)
		{
			m_playerAnime = 0;
		}

		Math::Rectangle m_rec = { 100 * (int)m_playerAnime,100 * 1,100,100 };

		SHADER.m_spriteShader.SetMatrix(m_playerMat);
		SHADER.m_spriteShader.DrawTex(&m_playerTex, m_rec);
	}
	else
	{
		SHADER.m_spriteShader.SetMatrix(m_playerMat);
		SHADER.m_spriteShader.DrawTex(&m_playerTex, Math::Rectangle{ 300,600,100,100 });
	}


	//リザルト
	SHADER.m_spriteShader.SetMatrix(m_resultMat);
	SHADER.m_spriteShader.DrawTex(&m_resultTex, Math::Rectangle{ 0,0,828,150 });

	//Score
	SHADER.m_spriteShader.SetMatrix(m_ScoreMat);
	m_nameRec = { 0,0,284,60 };
	SHADER.m_spriteShader.DrawTex(&m_ScoreTex, m_nameRec);
	NumDrawAPP.Drow(m_ScoreNum, RAligned, m_ScoreNumPos, &Math::Color{ 1,1,1,m_alpha }, m_numSiz * m_ScoreSiz, true, 0, m_digit);
	m_rodMat = Math::Matrix::CreateTranslation(-10, m_ScoreNumPos.y-50, 0);
	SHADER.m_spriteShader.SetMatrix(m_rodMat);
	SHADER.m_spriteShader.DrawTex(&m_rodTex, Math::Rectangle{ 0,0,1000,5 });

	if (m_ClearBonusFlg)
	{
		m_ClearBonusPos.y++;

		SHADER.m_spriteShader.SetMatrix(m_ClearBonusMat);
		m_nameRec = { 0,0,431,60 };
		SHADER.m_spriteShader.DrawTex(&m_ClearBonusTex, m_nameRec);
		NumDrawAPP.Drow(m_ClearBonus, RAligned, Math::Vector2{ m_ClearBonusPos.x + m_numXGap,m_ClearBonusPos.y }, &Math::Color{ 1,1,1,m_alpha }, m_numSiz * m_ScoreSiz, true);
	}


	//stageClear
	SHADER.m_spriteShader.SetMatrix(m_stageClearMat);
	m_nameRec = { 0,0,483,60 };
	SHADER.m_spriteShader.DrawTex(&m_stageClearTex, m_nameRec);
	NumDrawAPP.Drow(m_stageClearNum, RAligned, m_stageClearNumPos, &Math::Color{ 1,1,1,m_alpha }, m_numSiz * m_nameSiz, true, 0, m_digit);

	m_rodMat = Math::Matrix::CreateTranslation(-10, m_stageClearNumPos.y - 30, 0);
	SHADER.m_spriteShader.SetMatrix(m_rodMat);
	SHADER.m_spriteShader.DrawTex(&m_rodTex, Math::Rectangle{ 0,0,1000,5 });

	//Enemy
	SHADER.m_spriteShader.SetMatrix(m_EnemyMat);
	m_nameRec = { 0,0,394,60 };
	SHADER.m_spriteShader.DrawTex(&m_EnemyTex, m_nameRec);
	NumDrawAPP.Drow(m_EnemyNum, RAligned, m_EnemyNumPos, &Math::Color{ 1,1,1,m_alpha }, m_numSiz * m_nameSiz, true, 0, m_digit);

	m_rodMat = Math::Matrix::CreateTranslation(-10, m_EnemyNumPos.y - 30, 0);
	SHADER.m_spriteShader.SetMatrix(m_rodMat);
	SHADER.m_spriteShader.DrawTex(&m_rodTex, Math::Rectangle{ 0,0,1000,5 });

	//PowerUp
	SHADER.m_spriteShader.SetMatrix(m_PowerUpMat);
	m_nameRec = { 0,0,397,60 };
	SHADER.m_spriteShader.DrawTex(&m_PowerUpTex, m_nameRec);
	NumDrawAPP.Drow(m_PowerUpNum, RAligned, m_PowerUpNumPos, &Math::Color{ 1,1,1,m_alpha }, m_numSiz * m_nameSiz, true, 0, m_digit);

	m_rodMat = Math::Matrix::CreateTranslation(-10, m_PowerUpNumPos.y - 30, 0);
	SHADER.m_spriteShader.SetMatrix(m_rodMat);
	SHADER.m_spriteShader.DrawTex(&m_rodTex, Math::Rectangle{ 0,0,1000,5 });

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
	m_ClearBonusTex.Release();

	m_resultBGM->Stop();
	m_rodTex.Release();
	delete m_buttonSelectionSE;
	delete m_drumRollSE;
	delete m_resultBGM;
}

void Result::Anime()
{
	std::random_device rand_dev{};
	std::mt19937 rand_engine(rand_dev());
	int siz = 1000 - 1;
	m_animeCnt++;

	if (m_stageClearNumRand)
	{
		std::uniform_int_distribution<int> dist(0, NumMax);
		m_stageClearNum = dist(rand_engine);
	}

	if (m_EnemyNumRand)
	{
		std::uniform_int_distribution<int> dist(0, NumMax);
		m_EnemyNum = dist(rand_engine);
	}

	if (m_PowerUpNumRand)
	{
		std::uniform_int_distribution<int> dist(0, NumMax);
		m_PowerUpNum = dist(rand_engine);;
	}

	if (m_ScoreNumRand)
	{
		std::uniform_int_distribution<int> dist(0, NumMax);
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

			if (m_aliveFlg)
			{
				m_ScoreNum -= m_ClearBonus;
				m_ClearBonusPushFlg = true;
			}
			else
			{
				m_animeFlg = false;
			}
		}
	}


	if (m_animeCnt > m_FlgChangeCnt * 5)
	{
		if (!m_ClearBonusFlg)
		{
			m_ClearBonusFlg = true;
		}
	}

	if (m_animeCnt > m_FlgChangeCnt * 6)
	{
		if (m_ClearBonusPushFlg)
		{
			m_ScoreNum += m_ClearBonus;
			m_ClearBonusPushFlg = false;
		}
		m_animeFlg = false;
		m_ClearBonusFlg = false;
	}

	if (m_animeCnt < m_FlgChangeCnt * 5)
	{
		//アニメーションスキップ
		if (InfoKeyAPP.KeyPush(VK_RETURN, true, true))
		{
			m_stageClearNum = GameResultInfoAPP.GetmStageClearNum();
			m_EnemyNum = GameResultInfoAPP.GetEnemyDeath();
			m_PowerUpNum = GameResultInfoAPP.GetPowerUpNum();

			m_animeFlg = false;
			m_drumRollSE->Stop();
			if (m_aliveFlg && m_ClearBonusPushFlg)
			{
				m_ScoreNum += m_ClearBonus;
				m_ClearBonusPushFlg = false;
			}
			else
			{
				m_ScoreNum = GameResultInfoAPP.GetScore();
			}
		}
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

	return w;
}

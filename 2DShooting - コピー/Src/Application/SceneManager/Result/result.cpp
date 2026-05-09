#include "result.h"
#include "../SceneManager.h"
#include"../../Info/GameResult/GameResult.h"
#include"../../Info/NumDraw/NumDraw.h"
#include"../../Info/InfoKey/InfoKey.h"
#include"../../Button/PlayButton/PlayButton.h"
#include"../../Button/TitleButton/TitleButton.h"


void Result::Init()
{
	m_backTex.Load("Tex/Result/ResultBack.png");
	m_backMat = Math::Matrix::CreateTranslation(0, 0, 0);

	m_resultTex.Load("Tex/Result/Result.png");
	m_resultPos = { 0,300 };
	m_resultMat = Math::Matrix::CreateTranslation(m_resultPos.x, m_resultPos.y, 0);

	m_ScoreTex.Load("Tex/Result/Score.png");
	m_ScorePos = { -350,250 + m_yPosGap };
	m_ScoreMat = Math::Matrix::CreateTranslation(m_ScorePos.x, m_ScorePos.y, 0);
	m_ScoreNum = GameResultInfoAPP.GetmScore();
	if (m_ScoreNum > NumMax) { m_ScoreNum = NumMax; }
	m_ScoreNumPos = { m_ScorePos.x + m_NumXGap,m_ScorePos.y, 0 };

	m_stageClearTex.Load("Tex/Result/StageClear.png");
	m_stageClearPos = { m_ScorePos.x,m_ScorePos.y + m_yPosGap };
	m_stageClearMat = Math::Matrix::CreateTranslation(m_stageClearPos.x, m_stageClearPos.y, 0);
	m_stageClearNum = GameResultInfoAPP.GetmStageClearNum();
	if (m_stageClearNum > NumMax) { m_stageClearNum = NumMax; }
	m_stageClearNumPos = { m_stageClearPos.x + m_NumXGap,m_stageClearPos.y, 0 };


	m_EnemyTex.Load("Tex/Result/Enemy.png");
	m_EnemyPos = { m_ScorePos.x,m_stageClearPos.y + m_yPosGap };
	m_EnemyMat = Math::Matrix::CreateTranslation(m_EnemyPos.x, m_EnemyPos.y, 0);
	m_EnemyNum = GameResultInfoAPP.GetEnemyDeath();
	if (m_EnemyNum > NumMax) { m_EnemyNum = NumMax; }
	m_EnemyNumPos = { m_EnemyPos.x + m_NumXGap,m_EnemyPos.y, 0 };

	m_PowerUpTex.Load("Tex/Result/PowerUp.png");
	m_PowerUpPos = { m_ScorePos.x,m_EnemyPos.y + m_yPosGap };
	m_PowerUpMat = Math::Matrix::CreateTranslation(m_PowerUpPos.x, m_PowerUpPos.y, 0);
	m_PowerUpNum = GameResultInfoAPP.GetPowerUpNum();
	if (m_PowerUpNum > NumMax) { m_PowerUpNum = NumMax; }
	m_PowerUpNumPos = { m_PowerUpPos.x + m_NumXGap,m_PowerUpPos.y, 0 };

	////////////////
	//ボタン
	m_slect = 0;
	std::shared_ptr<PlayButton> playButton;
	playButton = std::make_shared<PlayButton>();
	playButton->SetOwner(m_owner);
	playButton->Init(Math::Vector2{ -300,-300 });
	playButton->SetDefaultSiz(3);
	playButton->SetSelectSiz(1.5);
	m_button.push_back(playButton);

	std::shared_ptr<TitleButton> titleButton;
	titleButton = std::make_shared<TitleButton>();
	titleButton->SetOwner(m_owner);
	titleButton->Init(Math::Vector2{ 300,-300 });
	titleButton->SetDefaultSiz(3);
	titleButton->SetSelectSiz(1.5);
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

void Result::Draw2D()
{
	////背景
	//SHADER.m_spriteShader.SetMatrix(m_backMat);
	//SHADER.m_spriteShader.DrawTex(&m_backTex, Math::Rectangle{ 0,0,1280,720 });

	//リザルト
	SHADER.m_spriteShader.SetMatrix(m_resultMat);
	SHADER.m_spriteShader.DrawTex(&m_resultTex, Math::Rectangle{ 0,0,600,150 });

	//Score
	SHADER.m_spriteShader.SetMatrix(m_ScoreMat);
	SHADER.m_spriteShader.DrawTex(&m_ScoreTex, m_nameRec);
	NumDrawAPP.Drow(m_ScoreNum, RAligned, m_ScoreNumPos, &Math::Color{ 1,1,1,m_alpha }, m_NumSiz, true);

	//stageClear
	SHADER.m_spriteShader.SetMatrix(m_stageClearMat);
	SHADER.m_spriteShader.DrawTex(&m_stageClearTex, m_nameRec);
	NumDrawAPP.Drow(m_stageClearNum, RAligned, m_stageClearNumPos, &Math::Color{ 1,1,1,m_alpha }, m_NumSiz, true);

	//Enemy
	SHADER.m_spriteShader.SetMatrix(m_EnemyMat);
	SHADER.m_spriteShader.DrawTex(&m_EnemyTex, m_nameRec);
	NumDrawAPP.Drow(m_EnemyNum, RAligned, m_EnemyNumPos, &Math::Color{ 1,1,1,m_alpha }, m_NumSiz, true);

	//PowerUp
	SHADER.m_spriteShader.SetMatrix(m_PowerUpMat);
	SHADER.m_spriteShader.DrawTex(&m_PowerUpTex, m_nameRec);
	NumDrawAPP.Drow(m_PowerUpNum, RAligned, m_PowerUpNumPos, &Math::Color{ 1,1,1,m_alpha }, m_NumSiz, true);

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
	m_backTex.Release();
	m_ScoreTex.Release();
	m_stageClearTex.Release();
	m_EnemyTex.Release();
	m_PowerUpTex.Release();
}

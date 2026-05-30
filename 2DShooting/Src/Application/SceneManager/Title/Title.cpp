#include "Title.h"
#include "../SceneManager.h"
#include"../../Button/PlayButton/PlayButton.h"
#include"../../Button/ScoreButton/ScoreButton.h"
#include"../../Info/InfoKey/InfoKey.h"
#include"../../Map/Map.h"
#include"../../Character/Player/Player.h"
#include"../../Sound/Button/ButtonSelectionSE.h"

void Title::Init()
{
	m_buttonSelectionSE = new ButtonSelectionSE();

	//背景
	MAPAPP.Updata();
	MAPAPP.setOwner(nullptr);

	//ゲーム名
	m_titleTex.Load("Tex/Title/Title.png");
	m_titlePos = { 0,200 };
	m_titleMat = Math::Matrix::CreateTranslation(m_titlePos.x, m_titlePos.y, 0);


	m_playerTex.Load("Tex/Character/Player/Soldier.png");
	m_playerPos = MAPAPP.PlayerSpawnPos();
	m_playerMat = Math::Matrix::CreateScale(3, 3, 0) * Math::Matrix::CreateTranslation(m_playerPos.x, m_playerPos.y, 0);


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

	std::shared_ptr<ScoreButton> scoreButton;
	scoreButton = std::make_shared<ScoreButton>();
	scoreButton->SetOwner(m_owner);
	scoreButton->Init(Math::Vector2{ 300,-300 });
	scoreButton->SetDefaultSiz(3);
	scoreButton->SetSelectSiz(1.5);
	m_button.push_back(scoreButton);

}

void Title::Update()
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
				if (InfoKeyAPP.KeyPush(VK_SPACE, true, true))
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


	m_playerAnime += 0.1;
	if (m_playerAnime > 8)
	{
		m_playerAnime = 0;
	}
}

void Title::Draw2D()
{
	MAPAPP.Draw2D();

	SHADER.m_spriteShader.SetMatrix(m_titleMat);
	SHADER.m_spriteShader.DrawTex(&m_titleTex, Math::Rectangle{ 0,0,600,260 });


	Math::Rectangle m_rec = { 100 * (int)m_playerAnime,100 * 1,100,100 };
	SHADER.m_spriteShader.SetMatrix(m_playerMat);
	SHADER.m_spriteShader.DrawTex(&m_playerTex, m_rec);


	//ボタン
	for (int i = 0; i < m_button.size(); i++)
	{
		if (m_button[i])
		{
			m_button[i]->Draw2D();
		}
	}
}

void Title::Release()
{
	m_titleTex.Release();

	delete m_buttonSelectionSE;

	m_playerTex.Release();
}

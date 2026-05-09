#include "Title.h"
#include "../SceneManager.h"
#include"../../Button/PlayButton/PlayButton.h"
#include"../../Button/ScoreButton/ScoreButton.h"
#include"../../Info/InfoKey/InfoKey.h"
#include"../../Map/Map.h"
#include"../../Character/Player/Player.h"

void Title::Init()
{


	//背景
	m_back = new Map();
	m_back->Init(Map::MapType::Map1);
	m_back->Updata();

	//ゲーム名
	m_titleTex.Load("Tex/Title/Title.png");
	m_titlePos = { 0,200 };
	m_titleMat = Math::Matrix::CreateTranslation(m_titlePos.x, m_titlePos.y, 0);


	m_player = new Player();
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_playerShadowTex.Load("Tex/Character/Player/playerr-Shadow.png");
	m_player->SetTex(&m_playerTex);
	m_player->SetShadowTex(&m_playerShadowTex);
	m_player->Init();
	m_player->SetPos(m_back->PlayerSpawnPos());

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


	m_player->AnimeRec();
	m_player->MatConfirmed(0);
}

void Title::Draw2D()
{
	m_back->Draw2D();

	SHADER.m_spriteShader.SetMatrix(m_titleMat);
	SHADER.m_spriteShader.DrawTex(&m_titleTex, Math::Rectangle{ 0,0,600,260 });


	m_player->Draw2D();

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
}

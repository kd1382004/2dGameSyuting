#include "DefAnime.h"
#include"../../../Info/InfoKey/InfoKey.h"
#include"../Game.h"

void DefAnime::Init()
{
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_backTex.Load("Tex/NextStage/NextStage.png");


}

void DefAnime::Update(Game* m_owner)
{

	if (m_PlayerDefAnime < m_PlayerDefAnimeMax)
	{
		m_PlayerDefAnime += 0.1;

	}
	else
	{
		m_nextStageFlg = true;
		m_PlayerDefAnime = m_PlayerDefAnimeMax ;
	}


	if (InfoKeyAPP.KeyPush(VK_RETURN, true, true))
	{
		if (m_nextStageFlg)
		{
			m_owner->NextScene();
		}
		else
		{
			m_PlayerDefAnime = m_PlayerDefAnimeMax;
		}
	}


	m_playerTexRec = { 100 * (int)m_PlayerDefAnime,100 * 6,100,100 };
	m_pkayerTexMat = Math::Matrix::CreateScale(10, 10, 0) * Math::Matrix::CreateTranslation(0, -100, 0);
	m_backTexMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void DefAnime::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_backTexMat);
	SHADER.m_spriteShader.DrawTex(&m_backTex, Math::Rectangle{ 0,0,1280,720 });

	SHADER.m_spriteShader.SetMatrix(m_pkayerTexMat);
	SHADER.m_spriteShader.DrawTex(&m_playerTex, m_playerTexRec);

	SHADER.m_spriteShader.DrawString(-100, 100, "Defeat", Math::Color{1,0,0,1});


	SHADER.m_spriteShader.DrawString(100, -200, "Enter To Results", Math::Color{ 1,0,0,1 });
}

void DefAnime::Release()
{
	m_playerTex.Release();
	m_backTex.Release();
}

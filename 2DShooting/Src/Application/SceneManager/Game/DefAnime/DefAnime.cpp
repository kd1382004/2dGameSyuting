#include "DefAnime.h"
#include"../../../Info/InfoKey/InfoKey.h"
#include"../Game.h"
#include"../../../Sound/Game/DefAnime/DefAnimeBGM.h"

void DefAnime::Init()
{
	m_defAnimeBgm = new DefAnimeBGM();
	m_defAnimeBgm->Play();
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_backTex.Load("Tex/NextStage/NextStage.png");
	m_fnishTex.Load("Tex/DefAnime/Finish.png");
	m_fnishTexPos = { 0,100 };
	m_fnishSiz = 0.1;
	m_fnishTexMat = Math::Matrix::CreateScale(m_fnishSiz, m_fnishSiz, 0) * Math::Matrix::CreateTranslation(m_fnishTexPos.x, m_fnishTexPos.y, 0);


	m_EntToresTex.Load("Tex/DefAnime/EnterToResults.png");
	m_EntToresTexPos = { 350,-280 };
	m_EntToreseTexMat = Math::Matrix::CreateScale(0.5, 0.5, 0) * Math::Matrix::CreateTranslation(m_EntToresTexPos.x, m_EntToresTexPos.y, 0);

	m_defTex.Load("Tex/DefAnime/Def.png");
}

void DefAnime::Update(Game* m_owner, bool flg)
{
	m_playerFlg = flg;

	if (!m_playerFlg)
	{
		if (m_PlayerDefAnime < m_PlayerDefAnimeMax)
		{
			m_PlayerDefAnime += 0.05;
		}
		else
		{
			m_nextStageFlg = true;
			m_PlayerDefAnime = m_PlayerDefAnimeMax;
		}

		m_playerTexRec = { 100 * (int)m_PlayerDefAnime,100 * 6,100,100 };
	}
	else
	{
		if (m_PlayerDefAnime < 8)
		{
			m_PlayerDefAnime += 0.05;

		}
		else
		{
			m_nextStageFlg = true;
			m_PlayerDefAnime = 9;
		}

		m_playerTexRec = { 100 * (int)m_PlayerDefAnime,100 * 4,100,100 };
	}

	if (m_fnishSiz >= 1)
	{
		m_fnishSiz = 1;
	}
	else
	{
		m_fnishSiz += 0.01;
	}

	m_fnishTexMat = Math::Matrix::CreateScale(m_fnishSiz, m_fnishSiz, 0) * Math::Matrix::CreateTranslation(m_fnishTexPos.x, m_fnishTexPos.y, 0);

	m_EntToresAlpha += m_EntToresAlphaPush;
	if (m_EntToresAlpha > 1)
	{
		m_EntToresAlpha = 1;
		m_EntToresAlphaPush *= -1;
	}

	if (m_EntToresAlpha < 0.3)
	{
		m_EntToresAlpha = 0.3;
		m_EntToresAlphaPush *= -1;
	}

	if (InfoKeyAPP.KeyPush(VK_RETURN, true, true))
	{
		m_owner->NextScene();
	}

	m_pkayerTexMat = Math::Matrix::CreateScale(10, 10, 0) * Math::Matrix::CreateTranslation(0, -100, 0);
	m_backTexMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void DefAnime::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_backTexMat);
	SHADER.m_spriteShader.DrawTex(&m_backTex, Math::Rectangle{ 0,0,1280,720 });

	SHADER.m_spriteShader.SetMatrix(m_pkayerTexMat);
	SHADER.m_spriteShader.DrawTex(&m_playerTex, m_playerTexRec);

	if (!m_playerFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_fnishTexMat);
		SHADER.m_spriteShader.DrawTex(&m_defTex, Math::Rectangle{ 0,0,632,102 });
	}
	else
	{
		SHADER.m_spriteShader.SetMatrix(m_fnishTexMat);
		SHADER.m_spriteShader.DrawTex(&m_fnishTex, Math::Rectangle{ 0,0,664,102 });
	}
	SHADER.m_spriteShader.SetMatrix(m_EntToreseTexMat);
	SHADER.m_spriteShader.DrawTex(&m_EntToresTex, Math::Rectangle{ 0,0,778,92 }, m_EntToresAlpha);
}

void DefAnime::Release()
{
	m_playerTex.Release();
	m_backTex.Release();
	m_fnishTex.Release();
	m_EntToresTex.Release();
	m_defTex.Release();
	delete m_defAnimeBgm;
}

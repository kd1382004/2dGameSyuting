#include "InfoGame.h"
#include"../../../Info/NumDraw/NumDraw.h"
#include"../../../Character/Info/CharacterInfoBace.h"

void InfoGame::Init()
{
	m_VLTex.Load("Tex/Game/GameInfo/LV.png");
	m_Xmark.Load("Tex/Game/GameInfo/Xmark.png");

	m_backTex.Load("Tex/Game/GameInfo/GameInfoBack.png");
	m_backPos = { 0,-307 };
	m_backMat = Math::Matrix::CreateTranslation(m_backPos.x, m_backPos.y, 0);


	m_3WShotIconTex.Load("Tex/PowerUpScreen/Powerup3WShot/Powerup3WShotIcon.png");
	m_3WShotIconPos = { -620,-280 };
	m_3WShotIconMat = Math::Matrix::CreateTranslation(m_3WShotIconPos.x, m_3WShotIconPos.y, 0);

	m_3WShotLVPos = { m_3WShotIconPos.x + 35,m_3WShotIconPos.y - 5 };
	m_3WShotLVMat = Math::Matrix::CreateTranslation(m_3WShotLVPos.x, m_3WShotLVPos.y, 0);


	m_LRShotIconTex.Load("Tex/PowerUpScreen/PowerupRLShot/PowerupRLShotIcon.png");
	m_LRShotIconPos = { -620,-340 };
	m_LRShotIconMat = Math::Matrix::CreateTranslation(m_LRShotIconPos.x, m_LRShotIconPos.y, 0);

	m_LRShotLVPos = { m_LRShotIconPos.x + 35,m_LRShotIconPos.y - 5 };
	m_LRShotLVMat = Math::Matrix::CreateTranslation(m_LRShotLVPos.x, m_LRShotLVPos.y, 0);


	m_PeneNumIconTex.Load("Tex/PowerUpScreen/PowerupPeneShot/PowerupPeneShotIcon.png");
	m_PeneNumIconPos = { -500,-280 };
	m_PeneNumIconMat = Math::Matrix::CreateTranslation(m_PeneNumIconPos.x, m_PeneNumIconPos.y, 0);

	m_PeneNumLVPos = { m_PeneNumIconPos.x + 35,m_PeneNumIconPos.y - 5 };
	m_PeneNumLVMat = Math::Matrix::CreateTranslation(m_PeneNumLVPos.x, m_PeneNumLVPos.y, 0);

	m_BoundNumIconTex.Load("Tex/PowerUpScreen/PowerupBound/PowerupBoundIcon.png");
	m_BoundNumIconPos = { -500,-340 };
	m_BoundNumIconMat = Math::Matrix::CreateTranslation(m_BoundNumIconPos.x, m_BoundNumIconPos.y, 0);

	m_BoundNumLVPos = { m_BoundNumIconPos.x + 35,m_BoundNumIconPos.y - 5 };
	m_BoundNumLVMat = Math::Matrix::CreateTranslation(m_BoundNumLVPos.x, m_BoundNumLVPos.y, 0);


	m_PWUPNumIconTex.Load("Tex/PowerUpScreen/PWUPNum/PWUPNum.png");
	m_PWUPNumIconPos = { 400,-280 };
	m_PWUPNumIconMat = Math::Matrix::CreateTranslation(m_PWUPNumIconPos.x, m_PWUPNumIconPos.y, 0);

	m_PWUPNumLVPos = { m_PWUPNumIconPos.x + 35,m_PWUPNumIconPos.y - 5 };
	m_PWUPNumLVMat = Math::Matrix::CreateTranslation(m_PWUPNumLVPos.x, m_PWUPNumLVPos.y, 0);

	m_ENTERTex.Load("Tex/Key/ENTER.png");
	m_ENTERTPos = { m_PWUPNumLVPos.x + 50,m_PWUPNumLVPos.y };
	m_ENTERTMat = Math::Matrix::CreateTranslation(m_ENTERTPos.x, m_ENTERTPos.y, 0);
}

void InfoGame::Release()
{
	m_VLTex.Release();
	m_Xmark.Release();
	m_backTex.Release();
	m_3WShotIconTex.Release();
	m_LRShotIconTex.Release();
	m_PeneNumIconTex.Release();
	m_BoundNumIconTex.Release();
	m_PWUPNumIconTex.Release();
	m_ENTERTex.Release();
}

void InfoGame::Update(CharacterInfo* info)
{
	if (!m_3wShotFlg)
	{
		m_3wShotFlg = info->Get3WShotFlg();
	}

	if (!m_LRShotFlg)
	{
		m_LRShotFlg = info->GetLRShotFlg();
	}

	m_PeneNum = info->GetBuletPeneNum();

	m_BoundNum = info->GetBoundNum();

	if (m_PWUPNum != 0)
	{
		m_ENTERTexFlg = true;
		m_ENTERAlf += m_ENTERAlfPush;
		if (m_ENTERAlf > 1)
		{
			m_ENTERAlf = 1;
			m_ENTERAlfPush *= -1;
		}
		else if(m_ENTERAlf<0)
		{
			m_ENTERAlf = 0;
			m_ENTERAlfPush *= -1;
		}

	}else
	{
		m_ENTERTexFlg = false;
	}
}

void InfoGame::Drow2D()
{
	SHADER.m_spriteShader.SetMatrix(m_backMat);
	SHADER.m_spriteShader.DrawTex(&m_backTex, Math::Rectangle{ 0,0,1280,120 });


	SHADER.m_spriteShader.SetMatrix(m_3WShotIconMat);
	SHADER.m_spriteShader.DrawTex(&m_3WShotIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_3WShotLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	if (!m_3wShotFlg)
	{
		NumDrawAPP.Drow(0, LAligned, Math::Vector2{ m_3WShotLVPos.x + 20,m_3WShotLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);
	}
	else
	{
		NumDrawAPP.Drow(1, LAligned, Math::Vector2{ m_3WShotLVPos.x + 20,m_3WShotLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);
	}


	SHADER.m_spriteShader.SetMatrix(m_LRShotIconMat);
	SHADER.m_spriteShader.DrawTex(&m_LRShotIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_LRShotLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	if (!m_LRShotFlg)
	{
		NumDrawAPP.Drow(0, LAligned, Math::Vector2{ m_LRShotLVPos.x + 20,m_LRShotLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);
	}
	else
	{
		NumDrawAPP.Drow(1, LAligned, Math::Vector2{ m_LRShotLVPos.x + 20,m_LRShotLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);
	}

	SHADER.m_spriteShader.SetMatrix(m_PeneNumIconMat);
	SHADER.m_spriteShader.DrawTex(&m_PeneNumIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_PeneNumLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(m_PeneNum, LAligned, Math::Vector2{ m_PeneNumLVPos.x + 20,m_PeneNumLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);



	SHADER.m_spriteShader.SetMatrix(m_BoundNumIconMat);
	SHADER.m_spriteShader.DrawTex(&m_BoundNumIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_BoundNumLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(m_BoundNum, LAligned, Math::Vector2{ m_BoundNumLVPos.x + 20,m_BoundNumLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);


	SHADER.m_spriteShader.SetMatrix(m_PWUPNumIconMat);
	SHADER.m_spriteShader.DrawTex(&m_PWUPNumIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_PWUPNumLVMat);
	SHADER.m_spriteShader.DrawTex(&m_Xmark, Math::Rectangle{ 0,0,21,21 });
	NumDrawAPP.Drow(m_PWUPNum, LAligned, Math::Vector2{ m_PWUPNumLVPos.x + 20,m_PWUPNumLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);

	if (m_ENTERTexFlg)
	{
		SHADER.m_spriteShader.SetMatrix(m_ENTERTMat);
		SHADER.m_spriteShader.DrawTex(&m_ENTERTex, Math::Rectangle{ 0,0,64,64 }, m_ENTERAlf);
	}
}



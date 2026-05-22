#include "InfoGame.h"
#include"../../../Info/NumDraw/NumDraw.h"
#include"../../../Info/InfoKey/InfoKey.h"
#include"../../../Character/Info/CharacterInfoBace.h"
#include"../../../Character/Player/Player.h"

void InfoGame::Init()
{
	m_VLTex.Load("Tex/Game/GameInfo/LV.png");
	m_Xmark.Load("Tex/Game/GameInfo/Xmark.png");
	m_KeyArrowTex.Load("Tex/Key/26053154.png");
	m_KeySpaceTex.Load("Tex/Key/27244530.png");



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


	m_PlyerHpHeelIconTex.Load("Tex/PowerUpScreen/PlayerHeel/PlayerHeelIcon.png");
	m_PlyerHpHeelIconPos = { -380,-280 };
	m_PlyerHpHeelIconMat = Math::Matrix::CreateTranslation(m_PlyerHpHeelIconPos.x, m_PlyerHpHeelIconPos.y, 0);

	m_PlyerHpHeelLVPos = { m_PlyerHpHeelIconPos.x + 35,m_PlyerHpHeelIconPos.y - 5 };
	m_PlyerHpHeelLVMat = Math::Matrix::CreateTranslation(m_PlyerHpHeelLVPos.x, m_PlyerHpHeelLVPos.y, 0);

	m_ATKUPIconTex.Load("Tex/PowerUpScreen/ATKUP/ATKUPIcon.png");
	m_ATKUPIconPos = { -380,-340 };
	m_ATKUPIconMat = Math::Matrix::CreateTranslation(m_ATKUPIconPos.x, m_ATKUPIconPos.y, 0);

	m_ATKUPLVPos = { m_ATKUPIconPos.x + 35,m_ATKUPIconPos.y - 5 };
	m_ATKUPLVMat = Math::Matrix::CreateTranslation(m_ATKUPLVPos.x, m_ATKUPLVPos.y, 0);


	m_FireArrowIconTex.Load("Tex/PowerUpScreen/PowerupFireArrow/PowerupFireArrowIcon.png");
	m_FireArrowIconPos = { -260,-280 };
	m_FireArrowIconMat = Math::Matrix::CreateTranslation(m_FireArrowIconPos.x, m_FireArrowIconPos.y, 0);

	m_FireArrowLVPos = { m_FireArrowIconPos.x + 35,m_FireArrowIconPos.y - 5 };
	m_FireArrowLVMat = Math::Matrix::CreateTranslation(m_FireArrowLVPos.x, m_FireArrowLVPos.y, 0);

	m_PowerUPScoreIconTex.Load("Tex/PowerUpScreen/PowerUPScore/PowerUPScoreIcon.png");
	m_PowerUPScoreIconPos = { -260,-340 };
	m_PowerUPScoreIconMat = Math::Matrix::CreateTranslation(m_PowerUPScoreIconPos.x, m_PowerUPScoreIconPos.y, 0);

	m_PowerUPScoreLVPos = { m_PowerUPScoreIconPos.x + 35,m_PowerUPScoreIconPos.y - 5 };
	m_PowerUPScoreLVMat = Math::Matrix::CreateTranslation(m_PowerUPScoreLVPos.x, m_PowerUPScoreLVPos.y, 0);

	//Key

	//UP
	m_keyPos[0] = { 100,-275 };
	m_keyMat[0] = Math::Matrix::CreateScale(0.1, 0.1, 0) * Math::Matrix::CreateTranslation(m_keyPos[0].x, m_keyPos[0].y, 0);

	//LEFT
	m_keyPos[1] = { m_keyPos[0].x - 50,m_keyPos[0].y - 50 };
	m_keyMat[1] = Math::Matrix::CreateScale(0.1, 0.1, 0) * Math::Matrix::CreateTranslation(m_keyPos[1].x, m_keyPos[1].y, 0);

	//DDOWN
	m_keyPos[2] = { m_keyPos[0].x,m_keyPos[0].y - 50 };
	m_keyMat[2] = Math::Matrix::CreateScale(0.1, 0.1, 0) * Math::Matrix::CreateTranslation(m_keyPos[2].x, m_keyPos[2].y, 0);

	//RIGHT
	m_keyPos[3] = { m_keyPos[0].x + 50,m_keyPos[0].y - 50 };
	m_keyMat[3] = Math::Matrix::CreateScale(0.1, 0.1, 0) * Math::Matrix::CreateTranslation(m_keyPos[3].x, m_keyPos[3].y, 0);

	//SPACE
	m_keyPos[4] = { m_keyPos[0].x - 170,m_keyPos[0].y - 50 };
	m_keyMat[4] = Math::Matrix::CreateScale(0.02, 0.02, 0) * Math::Matrix::CreateTranslation(m_keyPos[4].x, m_keyPos[4].y, 0);

	for (int i = 0; i < 5; i++)
	{
		m_keyAlpha[i] = 1;
	}



	m_scoreTex.Load("Tex/Result/Score.png");
	m_scoreMat = Math::Matrix::CreateScale(0.5, 0.5, 0) * Math::Matrix::CreateTranslation(300, m_PeneNumLVPos.y - 50, 0);

}

void InfoGame::Release()
{
	m_scoreTex.Release();
	m_VLTex.Release();
	m_Xmark.Release();
	m_KeyArrowTex.Release();
	m_backTex.Release();
	m_3WShotIconTex.Release();
	m_LRShotIconTex.Release();
	m_PeneNumIconTex.Release();
	m_BoundNumIconTex.Release();
}

void InfoGame::KeyDraw()
{
	SHADER.m_spriteShader.SetMatrix(m_keyMat[0]);
	SHADER.m_spriteShader.DrawTex(&m_KeyArrowTex, Math::Rectangle{ 3005,0,465,465 }, m_keyAlpha[0]);

	SHADER.m_spriteShader.SetMatrix(m_keyMat[1]);
	SHADER.m_spriteShader.DrawTex(&m_KeyArrowTex, Math::Rectangle{ 2305,693,465,465 }, m_keyAlpha[1]);

	SHADER.m_spriteShader.SetMatrix(m_keyMat[2]);
	SHADER.m_spriteShader.DrawTex(&m_KeyArrowTex, Math::Rectangle{ 3005,693,465,465 }, m_keyAlpha[2]);

	SHADER.m_spriteShader.SetMatrix(m_keyMat[3]);
	SHADER.m_spriteShader.DrawTex(&m_KeyArrowTex, Math::Rectangle{ 3705,693,465,465 }, m_keyAlpha[3]);

	SHADER.m_spriteShader.SetMatrix(m_keyMat[4]);
	SHADER.m_spriteShader.DrawTex(&m_KeySpaceTex, Math::Rectangle{ 0,0,8000,3160 }, m_keyAlpha[4]);

}

void InfoGame::Update(CharacterInfo* info, Player *player,int sc)
{
	m_score = sc;

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

	m_ATKUP = info->GetATKLV();

	m_FireArrow = player->GetFireArrow();

	m_PowerUPScore = player->GetScoreUpLV();

	if (InfoKeyAPP.GetKeyPush(VK_UP))
	{
		m_keyAlpha[0] = 0.5f;
	}
	else
	{
		m_keyAlpha[0] = 1;
	}

	if (InfoKeyAPP.GetKeyPush(VK_LEFT))
	{
		m_keyAlpha[1] = 0.5f;
	}
	else
	{
		m_keyAlpha[1] = 1;
	}

	if (InfoKeyAPP.GetKeyPush(VK_DOWN))
	{
		m_keyAlpha[2] = 0.5f;
	}
	else
	{
		m_keyAlpha[2] = 1;
	}

	if (InfoKeyAPP.GetKeyPush(VK_RIGHT))
	{
		m_keyAlpha[3] = 0.5f;
	}
	else
	{
		m_keyAlpha[3] = 1;
	}

	if (InfoKeyAPP.GetKeyPush(VK_SPACE))
	{
		m_keyAlpha[4] = 0.5f;
	}
	else
	{
		m_keyAlpha[4] = 1;
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

	SHADER.m_spriteShader.SetMatrix(m_PlyerHpHeelIconMat);
	SHADER.m_spriteShader.DrawTex(&m_PlyerHpHeelIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_PlyerHpHeelLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(m_PlyerHpHeel, LAligned, Math::Vector2{ m_PlyerHpHeelLVPos.x + 20,m_PlyerHpHeelLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);

	SHADER.m_spriteShader.SetMatrix(m_ATKUPIconMat);
	SHADER.m_spriteShader.DrawTex(&m_ATKUPIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_ATKUPLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(m_ATKUP, LAligned, Math::Vector2{ m_ATKUPLVPos.x + 20,m_ATKUPLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);

	SHADER.m_spriteShader.SetMatrix(m_FireArrowIconMat);
	SHADER.m_spriteShader.DrawTex(&m_FireArrowIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_FireArrowLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(m_FireArrow, LAligned, Math::Vector2{ m_FireArrowLVPos.x + 20,m_FireArrowLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);

	SHADER.m_spriteShader.SetMatrix(m_PowerUPScoreIconMat);
	SHADER.m_spriteShader.DrawTex(&m_PowerUPScoreIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_PowerUPScoreLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(m_PowerUPScore, LAligned, Math::Vector2{ m_PowerUPScoreLVPos.x + 20,m_PowerUPScoreLVPos.y }, &Math::Color{ 1,1,1,1 }, 1.5, false);


	KeyDraw();


	SHADER.m_spriteShader.SetMatrix(m_scoreMat);
	SHADER.m_spriteShader.DrawTex(&m_scoreTex, Math::Rectangle{ 0,0,284,60 });
	NumDrawAPP.Drow(m_score, RAligned, Math::Vector2{ m_scoreMat.Translation().x + 270,m_PeneNumLVPos.y - 50 }, &Math::Color{ 1,1,1,1 }, 2, false);

}



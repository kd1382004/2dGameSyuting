#include "Score.h"
#include "../SceneManager.h"
#include"../../Button/TitleButton/TitleButton.h"
#include"../../Info/InfoKey/InfoKey.h"
#include"../../Info/HighScore/HighScore.h"
#include"../../Info/NumDraw/NumDraw.h"
#include"../../Map/Map.h"
#include"../../Character/Player/Player.h"

void Score::Init()
{
	//”wŒi
	m_back = new Map();
	m_back->Init(Map::MapType::Map1);
	m_back->Updata();

	m_player = new Player();
	m_playerTex.Load("Tex/Character/Player/player.png");
	m_playerShadowTex.Load("Tex/Character/Player/playerr-Shadow.png");
	m_player->SetTex(&m_playerTex);
	m_player->SetShadowTex(&m_playerShadowTex);
	m_player->Init();
	m_player->SetPos(m_back->PlayerSpawnPos());

	////////////////
	//ƒ{ƒ^ƒ“
	m_slect = 0;
	std::shared_ptr<TitleButton> titleButton;
	titleButton = std::make_shared<TitleButton>();
	titleButton->SetOwner(m_owner);
	titleButton->Init(Math::Vector2{ 0,-300 });
	titleButton->SetDefaultSiz(3);
	titleButton->SetSelectSiz(1.5);
	m_button = titleButton;

	m_NoBackTex.Load("Tex/Score/Score.NoBack.png");

	for (int i = 0; i < m_NoBackMax; i++)
	{
		m_NoBackPos[i] = { -380,250.0f - i * 200 };
		m_NoBackMat[i] = Math::Matrix::CreateTranslation(m_NoBackPos[i].x, m_NoBackPos[i].y, 0);
	}


	m_VLTex.Load("Tex/Game/GameInfo/LV.png");
	m_3WShotIconTex.Load("Tex/PowerUpScreen/Powerup3WShot/Powerup3WShotIcon.png");
	m_3WShotIconPos = { -100,0 };
	m_3WShotIconMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_3WShotIconPos.x, m_3WShotIconPos.y, 0);

	m_3WShotLVPos = { m_3WShotIconPos.x + 35 * 2,m_3WShotIconPos.y - 5 };
	m_3WShotLVMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_3WShotLVPos.x, m_3WShotLVPos.y, 0);


	m_LRShotIconTex.Load("Tex/PowerUpScreen/PowerupRLShot/PowerupRLShotIcon.png");
	m_LRShotIconPos = { -100,-120 };
	m_LRShotIconMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_LRShotIconPos.x, m_LRShotIconPos.y, 0);

	m_LRShotLVPos = { m_LRShotIconPos.x + 35 * 2,m_LRShotIconPos.y - 5 };
	m_LRShotLVMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_LRShotLVPos.x, m_LRShotLVPos.y, 0);


	m_PeneNumIconTex.Load("Tex/PowerUpScreen/PowerupPeneShot/PowerupPeneShotIcon.png");
	m_PeneNumIconPos = { 100,0 };
	m_PeneNumIconMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_PeneNumIconPos.x, m_PeneNumIconPos.y, 0);

	m_PeneNumLVPos = { m_PeneNumIconPos.x + 35 * 2,m_PeneNumIconPos.y - 5 };
	m_PeneNumLVMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_PeneNumLVPos.x, m_PeneNumLVPos.y, 0);

	m_BoundNumIconTex.Load("Tex/PowerUpScreen/PowerupBound/PowerupBoundIcon.png");
	m_BoundNumIconPos = { 100,-120 };
	m_BoundNumIconMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_BoundNumIconPos.x, m_BoundNumIconPos.y, 0);

	m_BoundNumLVPos = { m_BoundNumIconPos.x + 35 * 2,m_BoundNumIconPos.y - 5 };
	m_BoundNumLVMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_BoundNumLVPos.x, m_BoundNumLVPos.y, 0);


	m_PlyerHpHeelIconTex.Load("Tex/PowerUpScreen/PlayerHeel/PlayerHeelIcon.png");
	m_PlyerHpHeelIconPos = { 300,0 };
	m_PlyerHpHeelIconMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_PlyerHpHeelIconPos.x, m_PlyerHpHeelIconPos.y, 0);

	m_PlyerHpHeelLVPos = { m_PlyerHpHeelIconPos.x + 35 * 2,m_PlyerHpHeelIconPos.y - 5 };
	m_PlyerHpHeelLVMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_PlyerHpHeelLVPos.x, m_PlyerHpHeelLVPos.y, 0);

	m_ATKUPIconTex.Load("Tex/PowerUpScreen/ATKUP/ATKUPIcon.png");
	m_ATKUPIconPos = { 300,-120 };
	m_ATKUPIconMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_ATKUPIconPos.x, m_ATKUPIconPos.y, 0);

	m_ATKUPLVPos = { m_ATKUPIconPos.x + 35 * 2,m_ATKUPIconPos.y - 5 };
	m_ATKUPLVMat = Math::Matrix::CreateScale(2, 2, 0) * Math::Matrix::CreateTranslation(m_ATKUPLVPos.x, m_ATKUPLVPos.y, 0);




	m_stageClearTex.Load("Tex/Result/StageClear.png");
	m_stageClearPos = { 50,200 };
	m_stageClearMat = Math::Matrix::CreateTranslation(m_stageClearPos.x, m_stageClearPos.y, 0);
	m_stageClearNumPos = { m_stageClearPos.x + m_NumXGap,m_stageClearPos.y, 0 };


	m_EnemyTex.Load("Tex/Result/Enemy.png");
	m_EnemyPos = { m_stageClearPos.x,m_stageClearPos.y + m_yPosGap };
	m_EnemyMat = Math::Matrix::CreateTranslation(m_EnemyPos.x, m_EnemyPos.y, 0);
	m_EnemyNumPos = { m_EnemyPos.x + m_NumXGap,m_EnemyPos.y, 0 };
}

void Score::Update()
{
	//////////////////////////
	//select‚ª‚Ç‚±‚É‚ ‚é‚©
	if (InfoKeyAPP.KeyPush(VK_DOWN, true))
	{
		m_slect++;


		if (m_slect >= 3)
		{
			m_slect = 3;
		}

	}

	if (InfoKeyAPP.KeyPush(VK_UP, true))
	{
		m_slect--;

		if (m_slect < 0)
		{
			m_slect = 0;
		}


	}

	m_alpha += m_alphaPush;
	if (m_alpha > 1)
	{
		m_alphaPush *= -1;
		m_alpha = 1;
	}

	if (m_alpha < 0.3)
	{
		m_alphaPush *= -1;
		m_alpha = 0.3;
	}

	m_player->AnimeRec();
	m_player->MatConfirmed(0);

	if (m_slect == 3)
	{
		m_button->SetSelectFlg(true);
		if (InfoKeyAPP.KeyPush(VK_RETURN, true, true))
		{
			m_button->Update();
		}
	}
	else
	{
		m_button->SetSelectFlg(false);
	}
}

void Score::Draw2D()
{
	m_back->Draw2D();


	for (int i = 0; i < m_NoBackMax; i++)
	{
		if (i == m_slect)
		{
			SHADER.m_spriteShader.SetMatrix(m_NoBackMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_NoBackTex, Math::Rectangle{ 0,0,327,100 }, m_alpha);
			NumDrawAPP.Drow(i + 1, LAligned, Math::Vector2{ m_NoBackPos[i].x - 115,m_NoBackPos[i].y }, &Math::Color(1, 1, 1, m_alpha), 2.5);
			NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i).score, RAligned, Math::Vector2{ m_NoBackPos[i].x + 122,m_NoBackPos[i].y - 10 }, &Math::Color(1, 1, 1, m_alpha), 2, true);
			DrawScore(i);
		}
		else
		{
			SHADER.m_spriteShader.SetMatrix(m_NoBackMat[i]);
			SHADER.m_spriteShader.DrawTex(&m_NoBackTex, Math::Rectangle{ 0,0,327,100 });
			NumDrawAPP.Drow(i + 1, LAligned, Math::Vector2{ m_NoBackPos[i].x - 115,m_NoBackPos[i].y }, &Math::Color(1, 1, 1, 1), 2.5);
			NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i).score, RAligned, Math::Vector2{ m_NoBackPos[i].x + 122,m_NoBackPos[i].y - 10 }, &Math::Color(1, 1, 1, 1), 2, true);
		}
		if (m_slect == 3)
		{
			DrawScore(2);
		}

	}

	//ƒ{ƒ^ƒ“
	if (m_button)
	{
		m_button->Draw2D();
	}

	m_player->Draw2D();
}

void Score::Release()
{
	m_NoBackTex.Release();
	m_VLTex.Release();
	m_3WShotIconTex.Release();
	m_LRShotIconTex.Release();
	m_PeneNumIconTex.Release();
	m_BoundNumIconTex.Release();
	m_PlyerHpHeelIconTex.Release();
	m_ATKUPIconTex.Release();
	m_stageClearTex.Release();
	m_EnemyTex.Release();

	if (m_back)
	{
		delete m_back;
	}
}

void Score::DrawScore(int i)
{
	SHADER.m_spriteShader.SetMatrix(m_3WShotIconMat);
	SHADER.m_spriteShader.DrawTex(&m_3WShotIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_3WShotLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i)._3wShotLv, LAligned, Math::Vector2{ m_3WShotLVPos.x + 20 * 2,m_3WShotLVPos.y }, &Math::Color{ 1,1,1,1 }, 2.5, false);



	SHADER.m_spriteShader.SetMatrix(m_LRShotIconMat);
	SHADER.m_spriteShader.DrawTex(&m_LRShotIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_LRShotLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i)._LRShotLv, LAligned, Math::Vector2{ m_LRShotLVPos.x + 20 * 2,m_LRShotLVPos.y }, &Math::Color{ 1,1,1,1 }, 2.5, false);



	SHADER.m_spriteShader.SetMatrix(m_PeneNumIconMat);
	SHADER.m_spriteShader.DrawTex(&m_PeneNumIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_PeneNumLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i).peneLv, LAligned, Math::Vector2{ m_PeneNumLVPos.x + 20 * 2,m_PeneNumLVPos.y }, &Math::Color{ 1,1,1,1 }, 2.5, false);



	SHADER.m_spriteShader.SetMatrix(m_BoundNumIconMat);
	SHADER.m_spriteShader.DrawTex(&m_BoundNumIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_BoundNumLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i).bounLv, LAligned, Math::Vector2{ m_BoundNumLVPos.x + 20 * 2,m_BoundNumLVPos.y }, &Math::Color{ 1,1,1,1 }, 2.5, false);

	SHADER.m_spriteShader.SetMatrix(m_PlyerHpHeelIconMat);
	SHADER.m_spriteShader.DrawTex(&m_PlyerHpHeelIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_PlyerHpHeelLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i).hpHeelLv, LAligned, Math::Vector2{ m_PlyerHpHeelLVPos.x + 20 * 2,m_PlyerHpHeelLVPos.y }, &Math::Color{ 1,1,1,1 }, 2.5, false);

	SHADER.m_spriteShader.SetMatrix(m_ATKUPIconMat);
	SHADER.m_spriteShader.DrawTex(&m_ATKUPIconTex, Math::Rectangle{ 0,0,32,32 });

	SHADER.m_spriteShader.SetMatrix(m_ATKUPLVMat);
	SHADER.m_spriteShader.DrawTex(&m_VLTex, Math::Rectangle{ 0,0,21,17 });
	NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i).ATKUpLv, LAligned, Math::Vector2{ m_ATKUPLVPos.x + 20 * 2,m_ATKUPLVPos.y }, &Math::Color{ 1,1,1,1 }, 2.5, false);

	//stageClear
	SHADER.m_spriteShader.SetMatrix(m_stageClearMat);
	m_nameRec = { 0,0,416,60 };
	SHADER.m_spriteShader.DrawTex(&m_stageClearTex, m_nameRec);
	NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i).clearNum, RAligned, m_stageClearNumPos, &Math::Color{ 1,1,1,1 }, 2.5, true);

	//Enemy
	SHADER.m_spriteShader.SetMatrix(m_EnemyMat);
	m_nameRec = { 0,0,376,60 };
	SHADER.m_spriteShader.DrawTex(&m_EnemyTex, m_nameRec);
	NumDrawAPP.Drow(HighScoreAPP.GetScoreSave(i).enemyNum, RAligned, m_EnemyNumPos, &Math::Color{1,1,1,1}, 2.5, true);
}

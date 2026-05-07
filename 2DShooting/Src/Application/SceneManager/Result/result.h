#pragma once
#include"../SceneBase.h"

class ButtonBase;

class Result :public SceneBase
{
public:

	Result() {};
	~Result() { Release(); }

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;

private:

	/////////
	//背景//
	////////
	KdTexture m_backTex;
	Math::Matrix m_backMat;


	////////////////////
	//画像切り取り範囲//
	////////////////////
	const Math::Rectangle m_nameRec = { 0,0,400,60 };

	//////////////////////////
	//それぞれの画像同士の差//
	//////////////////////////
	const float m_yPosGap = -100.0f;

	const float m_NumXGap = 800;

	const float m_NumSiz = 4.5f;

	const int NumMax = 999999999;


	float m_alpha = 0;
	float m_alphaPush = 0.01;


	///////////
	//RESULT///
	///////////
	KdTexture m_resultTex;
	Math::Vector2 m_resultPos;
	Math::Matrix m_resultMat;




	//////////
	//スコア//
	//////////
	KdTexture m_ScoreTex;
	Math::Vector2 m_ScorePos;
	Math::Matrix m_ScoreMat;
	int m_ScoreNum;
	Math::Vector2 m_ScoreNumPos;

	//////////////////
	//ステージクリア//
	//////////////////
	KdTexture m_stageClearTex;
	Math::Vector2 m_stageClearPos;
	Math::Matrix m_stageClearMat;
	int m_stageClearNum;
	Math::Vector2 m_stageClearNumPos;

	////////////////
	//倒した敵の数//
	////////////////
	KdTexture m_EnemyTex;
	Math::Vector2 m_EnemyPos;
	Math::Matrix m_EnemyMat;
	int m_EnemyNum;
	Math::Vector2 m_EnemyNumPos;

	/////////////
	//強化回数//
	////////////
	KdTexture m_PowerUpTex;
	Math::Vector2 m_PowerUpPos;
	Math::Matrix m_PowerUpMat;
	int m_PowerUpNum;
	Math::Vector2 m_PowerUpNumPos;


	// 解放
	void Release()override;



	//ボタン
	std::vector<std::shared_ptr<ButtonBase>> m_button;
	int m_slect;
};
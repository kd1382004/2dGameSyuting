#pragma once
#include"../SceneBase.h"

class ButtonBase;
class Map;
class Player;
class SoundBase;

class Score :public SceneBase
{
public:

	Score() {};
	~Score()override { Release(); };

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;

private:

	// 解放
	void Release()override;

	//プレイヤー
	KdTexture m_playerTex;
	Math::Vector2 m_playerPos;
	Math::Matrix m_playerMat;
	bool m_aliveFlg = false;
	float m_playerAnime = 0;

	static const int m_NoBackMax = 3;

	KdTexture m_NoBackTex;
	Math::Vector2 m_NoBackPos[m_NoBackMax];
	Math::Matrix m_NoBackMat[m_NoBackMax];

	float m_alpha = 1;
	float m_alphaPush = 0.01;

	void DrawScore(int i);


	KdTexture m_VLTex;
	KdTexture m_Xmark;

	KdTexture m_3WShotIconTex;
	Math::Vector2 m_3WShotIconPos;
	Math::Matrix m_3WShotIconMat;
	Math::Vector2 m_3WShotLVPos;
	Math::Matrix m_3WShotLVMat;
	bool m_3wShotFlg = false;


	KdTexture m_LRShotIconTex;
	Math::Vector2 m_LRShotIconPos;
	Math::Matrix m_LRShotIconMat;
	Math::Vector2 m_LRShotLVPos;
	Math::Matrix m_LRShotLVMat;
	bool m_LRShotFlg = false;


	KdTexture m_PeneNumIconTex;
	Math::Vector2 m_PeneNumIconPos;
	Math::Matrix m_PeneNumIconMat;
	Math::Vector2 m_PeneNumLVPos;
	Math::Matrix m_PeneNumLVMat;
	int m_PeneNum = 0;


	KdTexture m_BoundNumIconTex;
	Math::Vector2 m_BoundNumIconPos;
	Math::Matrix m_BoundNumIconMat;
	Math::Vector2 m_BoundNumLVPos;
	Math::Matrix m_BoundNumLVMat;
	int m_BoundNum = 0;

	KdTexture m_ATKUPIconTex;
	Math::Vector2 m_ATKUPIconPos;
	Math::Matrix m_ATKUPIconMat;
	Math::Vector2 m_ATKUPLVPos;
	Math::Matrix m_ATKUPLVMat;
	int m_ATKUP = 0;

	KdTexture m_PlyerHpHeelIconTex;
	Math::Vector2 m_PlyerHpHeelIconPos;
	Math::Matrix m_PlyerHpHeelIconMat;
	Math::Vector2 m_PlyerHpHeelLVPos;
	Math::Matrix m_PlyerHpHeelLVMat;
	int m_PlyerHpHeel = 0;

	KdTexture m_FireArrowIconTex;
	Math::Vector2 m_FireArrowIconPos;
	Math::Matrix m_FireArrowIconMat;
	Math::Vector2 m_FireArrowLVPos;
	Math::Matrix m_FireArrowLVMat;
	int m_FireArrow = 0;

	KdTexture m_PowerUPScoreIconTex;
	Math::Vector2 m_PowerUPScoreIconPos;
	Math::Matrix m_PowerUPScoreIconMat;
	Math::Vector2 m_PowerUPScoreLVPos;
	Math::Matrix m_PowerUPScoreLVMat;
	int m_PowerUPScore = 0;

	//ボタン
	std::shared_ptr<ButtonBase> m_button;
	int m_slect;


	////////////////////
	//画像切り取り範囲//
	////////////////////
	Math::Rectangle m_nameRec = { 0,0,0,0 };

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



	/////////
	//SCORE//
	/////////
	KdTexture m_ScoreTex;
	Math::Vector2 m_ScorePos;
	Math::Matrix m_ScoreMat;
	int m_ScoreNum;
	Math::Vector2 m_ScoreNumPos;

	const float m_yPosGap = -100.0f;
	const float m_NumXGap = 550;


	//音
	SoundBase* m_buttonSelectionSE;
};

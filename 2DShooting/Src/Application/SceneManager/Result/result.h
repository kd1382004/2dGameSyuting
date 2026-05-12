#pragma once
#include"../SceneBase.h"

class ButtonBase;
class Map;

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
	Map* m_back;

	//プレイヤー
	KdTexture m_playerTex;
	Math::Vector2 m_playerPos;
	Math::Matrix m_playerMat;



	////////////////////
	//画像切り取り範囲//
	////////////////////
	Math::Rectangle m_nameRec = { 0,0,0,0 };

	//////////////////////////
	//それぞれの画像同士の差//
	//////////////////////////
	const float m_yPosGap = -100.0f;

	const float m_numXGap = 800;

	const float m_numSiz = 4.5f;

	const int NumMax = 999999999;

	const float m_nameSiz = 0.6;

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
	int m_ScoreNumDigit = 0;//桁数
	bool m_ScoreNumRand = true;//ランダムにするか
	Math::Vector2 m_ScoreNumPos;

	const float m_ScoreSiz = 1.5;

	//////////////////
	//ステージクリア//
	//////////////////
	KdTexture m_stageClearTex;
	Math::Vector2 m_stageClearPos;
	Math::Matrix m_stageClearMat;
	int m_stageClearNum = 0;
	int m_stageClearNumDigit = 0;//桁数
	bool m_stageClearNumRand = true;//ランダムにするか
	Math::Vector2 m_stageClearNumPos;

	////////////////
	//倒した敵の数//
	////////////////
	KdTexture m_EnemyTex;
	Math::Vector2 m_EnemyPos;
	Math::Matrix m_EnemyMat;
	int m_EnemyNum = 0;
	int m_EnemyNumDigit = 0;//桁数
	bool m_EnemyNumRand = true;//ランダムにするか
	Math::Vector2 m_EnemyNumPos;

	/////////////
	//強化回数//
	////////////
	KdTexture m_PowerUpTex;
	Math::Vector2 m_PowerUpPos;
	Math::Matrix m_PowerUpMat;
	int m_PowerUpNum = 0;
	int m_PowerUpNumDigit = 0;//桁数
	bool m_PowerUpNumRand = true;//ランダムにするか
	Math::Vector2 m_PowerUpNumPos;


	// 解放
	void Release()override;



	//ボタン
	std::vector<std::shared_ptr<ButtonBase>> m_button;
	int m_slect;

	//リザルトアニメーション
	void Anime();
	bool m_animeFlg = true;;
	int m_animeCnt = 0;
	int m_FlgChangeCnt = 60;

	//その桁の最大数を返す
	int GetDigit(int num);
};
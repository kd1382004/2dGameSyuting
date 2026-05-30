#pragma once
#include"../SceneBase.h"


class Player;
class EnemyBase;
class CharaHit;
class PowerUpScreen;
class DefAnime;
class InfoGame;
class SoundBase;


class Game :public SceneBase
{
public:

	Game() {};
	~Game()override { Release(); };

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;


	//敵の数を返す
	int EnemyNum() { return m_enemy.size(); }

	EnemyBase* GetEnemy(int num);

	Math::Vector2 GetPlayerPos();

	void SetNextStageFlg(bool flg) { m_nextStageAnimeFlg = flg; }

	bool GetStageClearFlg() { return m_stageClearFlg;}

	void NextScene();

	void PowerUpNumUP() { m_powerUpNum++; }

	void PowerUpScreenFlg() { m_powerUpScreenFlg = false; }

	Player* GetPlayer() { return m_player; }

	int GetScore() { return m_score; }

	void SetpowerUpScreenNum(int num) { m_powerUpScreenNum = num; }
private:

	// 解放
	void Release()override;


	//このクラス内で作ったポインタ消去関数
	void PtrRelease();

	//////////////////////////////////
	//ステージスタートアニメーション//
	//////////////////////////////////

	void StageStartAnimeUpdate();
	void StageStartAnimeDraw2D();
	bool m_stageStartAnimeFlg = true;
	float m_stageStartAnimeCnt = 0;


	//////////////////
	//ステージ初期化//
	//////////////////
	//StageNum...ステージ番号
	void InitStage(int StageNum);

	//ステージ番号
	int m_stageNum = 0;


	static const int m_stageMax = 20;

	//ゲームクリア
	void GeameClearUpdata();
	void GeameClearDraw2D();


	//////////////
	//プレイヤー//
	//////////////
	KdTexture m_playerTex;
	KdTexture m_playerShadowTex;
	Player* m_player = nullptr;

	//////
	//敵//
	//////
	std::vector<EnemyBase*> m_enemy;

	//スライム画像
	KdTexture m_slimeTex;

	//スケルトン画像
	KdTexture m_skeletonTex;

	//オーク画像
	KdTexture m_orcTex;


	//////////////
	//当たり判定//
	//////////////
	CharaHit* m_charaHit = nullptr;

	//ステージクリアフラグ
	bool m_stageClearFlg = false;

	////////////
	//強化画面//
	////////////
	PowerUpScreen* m_powerUpScreen=nullptr;
	bool m_powerUpScreenFlg = false;
	int m_powerUpScreenNum = 0;

	///////////////////////
	//clearアニメーション//
	//////////////////////
	bool m_nextStageAnimeFlg = false;
	float m_nextStageAlh = 0;
	float m_nextStageAlhPu = 0.05;
	KdTexture m_nextStageTex;
	void NextStagenimeUpdate();
	void NextStagenimeDraw2D();

	////////
	//敗北//
	////////
	bool m_DEF = false;
	DefAnime* m_defAnime = nullptr;

	////////////////////////
	//ゲーム中に見せる情報//
	////////////////////////
	InfoGame* m_infoGame = nullptr;


	//////////////////////////
	//リザルトに持ってく情報//
	//////////////////////////

	//敵を倒した数
	int m_EnemyDeath = 0;

	//強化した数
	int m_powerUpNum = 0;

	//ステージクリア数
	int m_stageClearNum = 0;

	int m_score = 0;

	//スコアを増やす
	//lv...敵のレベルを入れる
	void ScorePush(int lv);

	//敵が死んだ一
	Math::Vector2 m_EnemydefPos = {};


	//音
	SoundBase* m_gameeBgm;
	SoundBase* m_powerUpwindoSe;
	SoundBase* m_warpSe;
};

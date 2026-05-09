#pragma once
#include"../SceneBase.h"


class Player;
class EnemyBase;
class CharaHit;
class Map;
class PowerUpScreen;
class DefAnime;
class InfoGame;


class Game :public SceneBase
{
public:

	Game() {};
	~Game() { Release(); };

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

	bool GetStageClearFlg() { return m_stageClearFlg; }

	void NextScene();

	void PowerUpNumUP() { m_powerUpNum++; }

	void PowerUpScreenFlg() { m_powerUpScreenFlg = false; }

	Player* GetPlayer() { return m_player; }
private:

	// 解放
	void Release()override;


	//このクラス内で作ったポインタ消去関数
	void PtrRelease();

	//////////////////
	//ステージ初期化//
	//////////////////
	//StageNum...ステージ番号
	void InitStage(int StageNum);

	//ステージ番号
	int m_stageNum = 1;

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


	//////////////
	//当たり判定//
	//////////////
	CharaHit* m_charaHit = nullptr;

	//////////
	//マップ//
	//////////
	Map* m_map = nullptr;



	//ステージクリアフラグ
	bool m_stageClearFlg = false;

	////////////
	//強化画面//
	////////////
	PowerUpScreen* m_powerUpScreen;
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
	DefAnime* m_defAnime;

	////////////////////////
	//ゲーム中に見せる情報//
	////////////////////////
	InfoGame* m_infoGame;


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
};
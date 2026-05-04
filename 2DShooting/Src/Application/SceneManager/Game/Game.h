#pragma once
#include"../SceneBase.h"


class Player;
class EnemyBase;
class CharaHit;
class Map;
class PowerUpScreen;

class Game :public SceneBase
{
public:

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

private:

	// 解放
	void Release()override;


	//このクラス内で作ったポインタ消去関数
	void PtrRelease();

	//////////////
	//プレイヤー//
	//////////////
	KdTexture m_playerTex;
	KdTexture m_playerShadowTex;
	Player* m_player;

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
	CharaHit* m_charaHit;

	//////////
	//マップ//
	//////////
	Map* m_map;



	//ステージクリアフラグ
	bool m_stageClearFlg = false;

	////////////
	//強化画面//
	////////////
	PowerUpScreen* m_powerUpScreen;
	bool m_powerUpScreenFlg;
};
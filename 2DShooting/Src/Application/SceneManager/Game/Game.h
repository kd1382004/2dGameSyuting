#pragma once
#include"../SceneBase.h"


class Player;
class EnemyBase;
class CharaHit;

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

private:

	// 解放
	void Release()override;


	//このクラス内で作ったポインタ消去関数
	void PtrRelease();

	//////////////
	//プレイヤー//
	//////////////
	KdTexture m_playerTex;
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
};
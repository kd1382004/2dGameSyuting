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
	KdTexture m_enemyBaseTex;
	EnemyBase* m_enemyBase;

	//////////////
	//当たり判定//
	//////////////
	CharaHit* m_charaHit;
};
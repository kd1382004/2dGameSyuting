#pragma once

#include"../EnemyBase.h"


enum Mode
{
	MOVE,
	ATK,

};


class Orc :public EnemyBase
{
public:
	Orc() {}
	~Orc() {}

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;

	void MatConfirmed(float scroll)override;

	void SetStatus(int stage)override;
private:

	// 解放
	void Release()override;

	//プレイヤーを追跡する
	void PlayerTrackingMove();

	void MODEMove();
	void MODEATK();

	Mode m_mode = MOVE;
	void ChangeMode(Mode mode);

	float m_ATKWaitMax = 60;
	float m_ATKWait = 0;
};



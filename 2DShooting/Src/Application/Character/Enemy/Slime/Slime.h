#pragma once

#include"../EnemyBase.h"

class Slime:public EnemyBase
{
public:
	Slime() {}
	~Slime(){}

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;

private:

	// 解放
	virtual void Release()override;

	//プレイヤーを追跡する
	void PlayerTrackingMove();

};

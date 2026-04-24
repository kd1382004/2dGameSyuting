#pragma once
#include "../CharacterBase.h"

class EnemyBase :public CharacterBase
{
public:
	EnemyBase() { m_speed = { 1, 1 }; }
	~EnemyBase() { Release(); }

	// 初期設定
	virtual void Init()override;

	// 更新処理
	virtual void Update()override;

	// 描画処理
	void Draw2D()override;


	//追跡用等にプレイヤー座標セット
	void SetPlayerPos(Math::Vector2 playerPos) {m_plaeyrPos = playerPos;};

protected:

	// 解放
	void Release()override;

	//プレイヤーを追跡する
	void PlayerTrackingMove();

	//追跡用等のプレイヤー座標
	Math::Vector2 m_plaeyrPos = { 0,0 };
private:

};


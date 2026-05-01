#pragma once
#include "../CharacterBase.h"

class EnemyBase :public CharacterBase
{
public:
	EnemyBase() { m_speed = { 1, 1 }; }
	~EnemyBase() { Release(); }

	// 初期設定
	virtual void Init() {}

	// 更新処理
	virtual void Update(){}

	// 描画処理
	virtual void Draw2D(){}


	//追跡用等にプレイヤー座標セット
	void SetPlayerPos(Math::Vector2 playerPos) {m_plaeyrPos = playerPos;};;

	Math::Vector2 Getmove() { return m_move; }

	void SetPos(Math::Vector2 pos) { m_pos = pos; }


protected:

	// 解放
	virtual void Release(){}

	//追跡用等のプレイヤー座標
	Math::Vector2 m_plaeyrPos = { 0,0 };
private:

};


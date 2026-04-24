#pragma once
#include "../CharacterBase.h"

class Player: public CharacterBase
{
public:

	Player() {};
	~Player() { Release(); };

	// 初期設定
	void Init()override;

	// 更新処理
	void Update()override;

	// 描画処理
	void Draw2D()override;

private:

	void Release()override;

	//プレイヤー移動関数
	void Move();


	//プレイヤーキー操作
	int m_moveUp;		//上移動
	int m_moveDown;		//下移動
	int m_moveLeft;		//左移動
	int m_moveRight;	//右移動


};


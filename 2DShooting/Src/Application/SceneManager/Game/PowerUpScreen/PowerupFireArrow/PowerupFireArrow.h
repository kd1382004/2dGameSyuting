#pragma once

#include"../PowerUpBase.h"

class PowerupFireArrow :public PowerUpBase
{
public:
	PowerupFireArrow() {};
	~PowerupFireArrow()override { Release(); };


	//表示場所をセット
	void Init(Math::Vector2 pos)override;
	void Update(Player* player)override;
	void Draw2D()override;

	void DrawEX()override;

private:
	void Release()override;
};

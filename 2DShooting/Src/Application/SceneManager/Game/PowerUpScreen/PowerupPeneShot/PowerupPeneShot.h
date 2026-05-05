#pragma once

#include"../PowerUpBase.h"

class PowerupPeneShot :public PowerUpBase
{
public:
	PowerupPeneShot() {};
	~PowerupPeneShot()override { Release(); };


	//表示場所をセット
	void Init(Math::Vector2 pos)override;
	void Update(PlayerPowerUpInfo* playerInfo)override;
	void Draw2D()override;

	void DrawEX()override;

private:
	void Release()override;
};

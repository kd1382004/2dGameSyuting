#pragma once

#include"../PowerUpBase.h"

class PowerupBound :public PowerUpBase
{
public:
	PowerupBound() {};
	~PowerupBound()override { Release(); };


	//表示場所をセット
	void Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player)override;
	void Update(CharacterInfo* playerInfo)override;
	void Draw2D()override;

	void DrawEX()override;

private:
	void Release()override;
};

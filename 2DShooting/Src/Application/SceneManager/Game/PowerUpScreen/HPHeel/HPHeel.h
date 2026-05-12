#pragma once

#include"../PowerUpBase.h"

class HPHeel :public PowerUpBase
{
public:
	HPHeel() {};
	~HPHeel()override { Release(); };


	//表示場所をセット
	void Init(Math::Vector2 pos, CharacterInfo* playerInfo, Player* player)override;
	void Update(Player* player)override;
	void Draw2D()override;

	void DrawEX()override;

private:
	void Release()override;
};

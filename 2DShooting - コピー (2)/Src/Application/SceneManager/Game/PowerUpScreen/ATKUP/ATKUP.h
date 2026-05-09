#pragma once

#include"../PowerUpBase.h"

class ATKUP :public PowerUpBase
{
public:
	ATKUP() {};
	~ATKUP()override { Release(); };


	//表示場所をセット
	void Init(Math::Vector2 pos)override;
	void Update(CharacterInfo* playerInfo)override;
	void Draw2D()override;

	void DrawEX()override;

private:
	void Release()override;
};
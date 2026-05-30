#pragma once

#include"../../SoundBase.h"

class PlayerHitSE :public SoundBase
{
public:
	PlayerHitSE() { Init(); };
	~PlayerHitSE() {};


private:

	void Init()override;

};


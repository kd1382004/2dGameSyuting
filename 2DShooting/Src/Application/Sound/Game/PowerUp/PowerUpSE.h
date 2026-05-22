#pragma once

#include"../../SoundBase.h"

class PowerUpSE :public SoundBase
{
public:
	PowerUpSE() { Init(); };
	~PowerUpSE() {};


private:

	void Init()override;

};

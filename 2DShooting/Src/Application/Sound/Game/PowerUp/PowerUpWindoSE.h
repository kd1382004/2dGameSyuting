#pragma once

#include"../../SoundBase.h"

class PowerUpWindoSE :public SoundBase
{
public:
	PowerUpWindoSE() { Init(); };
	~PowerUpWindoSE() {};


private:

	void Init()override;

};

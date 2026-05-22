#pragma once

#include"../../../SoundBase.h"

class FireSE :public SoundBase
{
public:
	FireSE() { Init(); };
	~FireSE() {};


private:

	void Init()override;

};

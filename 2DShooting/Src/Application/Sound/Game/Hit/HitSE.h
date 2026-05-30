#pragma once

#include"../../SoundBase.h"

class HitSE :public SoundBase
{
public:
	HitSE() { Init(); };
	~HitSE() {};


private:

	void Init()override;

};

#pragma once

#include"../../../SoundBase.h"

class BowSE :public SoundBase
{
public:
	BowSE() { Init(); };
	~BowSE() {};


private:

	void Init()override;

};

#pragma once

#include"../../../SoundBase.h"

class HeelSE :public SoundBase
{
public:
	HeelSE() { Init(); };
	~HeelSE() {};


private:

	void Init()override;

};

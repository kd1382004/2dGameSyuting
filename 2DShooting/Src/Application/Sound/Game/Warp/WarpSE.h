#pragma once

#include"../../SoundBase.h"

class WarpSE :public SoundBase
{
public:
	WarpSE() { Init(); };
	~WarpSE() {};


private:

	void Init()override;

};

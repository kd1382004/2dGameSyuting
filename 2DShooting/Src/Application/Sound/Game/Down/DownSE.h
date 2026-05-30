#pragma once

#include"../../SoundBase.h"

class DownSE :public SoundBase
{
public:
	DownSE() { Init(); };
	~DownSE() {};


private:

	void Init()override;

};

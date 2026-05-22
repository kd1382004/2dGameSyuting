#pragma once

#include"../../SoundBase.h"

class DrumRollSE :public SoundBase
{
public:
	DrumRollSE() { Init(); };
	~DrumRollSE() {};


private:

	void Init()override;

};

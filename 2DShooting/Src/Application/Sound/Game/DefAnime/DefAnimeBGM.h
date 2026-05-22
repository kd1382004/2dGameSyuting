#pragma once

#include"../../SoundBase.h"

class DefAnimeBGM :public SoundBase
{
public:
	DefAnimeBGM() { Init(); };
	~DefAnimeBGM() {};


private:

	void Init()override;

};

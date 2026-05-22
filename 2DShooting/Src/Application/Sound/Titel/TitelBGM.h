#pragma once

#include"../SoundBase.h"

class TitelBGM :public SoundBase
{
public:
	TitelBGM() { Init(); };
	~TitelBGM() {};


private:

	void Init()override;

};

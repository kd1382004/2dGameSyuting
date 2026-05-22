#pragma once

#include"../SoundBase.h"

class ResultBGM :public SoundBase
{
public:
	ResultBGM() { Init(); };
	~ResultBGM() {};


private:

	void Init()override;

};

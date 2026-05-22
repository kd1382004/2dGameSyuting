#pragma once

#include"../SoundBase.h"

class GameBGM :public SoundBase
{
public:
	GameBGM() { Init(); };
	~GameBGM() {};


private:

	void Init()override;

};

#pragma once

#include"../SoundBase.h"

class ButtonDECSE :public SoundBase
{
public:
	ButtonDECSE() { Init(); };
	~ButtonDECSE() {};


private:

	void Init()override;

};

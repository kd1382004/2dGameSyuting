#pragma once

#include"../SoundBase.h"

class ButtonSelectionSE :public SoundBase
{
public:
	ButtonSelectionSE() { Init(); };
	~ButtonSelectionSE() {};


private:

	void Init()override;

};

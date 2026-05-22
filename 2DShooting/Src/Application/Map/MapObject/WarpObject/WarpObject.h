#pragma once
#include"../MapObject.h"



class WarpObject :public MapObject
{
public:
	WarpObject(){}
	~WarpObject()override { Release(); }

	void Init(Math::Vector2 pos)override;
	void Updata(float scroll)override;
	void Draw2D()override;

private:

void Release()override;


float m_siz = 1;
float m_sizPush = 0.01;
};


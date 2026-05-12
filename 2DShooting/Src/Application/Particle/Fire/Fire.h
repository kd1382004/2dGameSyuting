#pragma once

#include"../ParticleBase.h"

class Fire :public Praticle
{
public:
	Fire();
	~Fire() override;


	void Update(Math::Vector2 pos, float scroll)override;
};


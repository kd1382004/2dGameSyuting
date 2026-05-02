#pragma once

#include"../EnemyBase.h"

class Skeleton :public EnemyBase
{
public:
	Skeleton() {}
	~Skeleton() {}

	// ‰Šúİ’è
	void Init()override;

	// XVˆ—
	void Update()override;

	// •`‰æˆ—
	void Draw2D()override;

private:

	// ‰ğ•ú
	void Release()override;

	//’e‚ğŒ‚‚Â
	void shot();

};
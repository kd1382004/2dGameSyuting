#include "BulletHit.h"
#include"../../Character/CharacterBase.h"
#include"../../Character/Player/Bullet/PlayerBullet.h"

bool BulletHit::Hit(PlayerBullet* bullet, CharacterBase* Chara)
{
	bool HitFlg = false;

	float a = bullet->GetPos().x - Chara->GetPos().x;
	float b = bullet->GetPos().y - Chara->GetPos().y;
	float c = sqrtf(a * a + b * b);

	if (c < bullet->GetHitDetection() + Chara->GetHitDetection())
	{
		HitFlg = true;
	}

    return HitFlg;
}

#include "CharaHit.h"
#include"../Character/CharacterBase.h"
#include "../Character/Player/Bullet/PlayerBullet.h"


bool CharaHit::CharacterHit(CharacterBase* chara1, CharacterBase* chara2)
{
	if (!chara1->GetAliveFlg() && !chara2->GetAliveFlg())
	{
		return false;
	}



	bool hitFlg = false;

	Math::Vector2 charaPos1 = chara1->GetPos();
	Math::Vector2 charaPos2 = chara2->GetPos();


	int a = charaPos1.x - charaPos2.x;
	int b = charaPos1.y - charaPos2.y;
	float c = sqrt(a * a + b * b);

	if (c < chara1->GetHitDetection() / 2 + chara2->GetHitDetection() / 2)
	{
		hitFlg = true;
	}


	return hitFlg;
}

bool CharaHit::BulletHit(PlayerBullet* bullet, CharacterBase* enemy,int enemyNum)
{
	if (!bullet->GetAliveFlg() && !enemy->GetAliveFlg())
	{
		return false;
	}

	if (bullet->GetEnemyNum() == enemyNum)
	{
		return false;
	}

	bool hitFlg = false;


	Math::Vector2 charaPos1 = bullet->GetPos();
	Math::Vector2 charaPos2 = enemy->GetPos();


	int a = charaPos1.x - charaPos2.x;
	int b = charaPos1.y - charaPos2.y;
	float c = sqrt(a * a + b * b);

	if (c < bullet->GetHitDetection() / 2 + enemy->GetHitDetection() / 2)
	{
		hitFlg = true;
		bullet->SetEnemyNum(enemyNum);
	}

	return hitFlg;
}

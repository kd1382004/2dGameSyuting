#include "CharaHit.h"
#include"Application/Character/CharacterBase.h"


bool CharaHit::Hit(CharacterBase* chara1, CharacterBase* chara2)
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

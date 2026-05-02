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

	//Math::Vector2 charaPos1 = chara1->GetPos();
	//Math::Vector2 charaPos2 = chara2->GetPos();


	//int a = charaPos1.x - charaPos2.x;
	//int b = charaPos1.y - charaPos2.y;
	//float c = sqrt(a * a + b * b);

	Math::Vector2 c = chara1->GetPos() - chara2->GetPos();

	if (c.Length() < chara1->GetHitDetection() / 2 + chara2->GetHitDetection() / 2)
	{
		hitFlg = true;
	}


	return hitFlg;
}

void CharaHit::Pushback(CharacterBase* chara1, CharacterBase* chara2)
{
	const float x = chara1->GetPos().x - chara2->GetPos().x;
	const float y = chara1->GetPos().y - chara2->GetPos().y;
	const float z = sqrt(x * x + y * y);

	//”¼Œa{”¼Œa
	const float sum = chara1->GetHitDetection() / 2 + chara2->GetHitDetection() / 2;

	//d‚È‚è‹ï‡
	float over = sum - z;

	//“G2‚©‚ç“G1‚Ö‚Ì•ûŒü
	float nx = x / z;
	float ny = y / z;


	Math::Vector2 notMove = { 0,0 };
	if (chara1->Getmove() != notMove && chara2->Getmove() != notMove)//—¼•û“®‚¢‚Ä‚é“G
	{
		Math::Vector2 enemyiPos = chara1->GetPos();
		Math::Vector2 enemyjPos = chara2->GetPos();

		//‚¨ŒÝ‚¢‚É”¼•ª‚¸‚Â‰Ÿ‚µ•Ô‚·
		enemyiPos.x += nx * (over * 0.5);
		enemyiPos.y += ny * (over * 0.5);
		enemyjPos.x -= nx * (over * 0.5);
		enemyjPos.y -= nx * (over * 0.5);

		chara1->SetPos(enemyiPos);
		chara2->SetPos(enemyjPos);
	}
	else if (chara1->Getmove() != notMove)//chara1‚ª“®‚¢‚Ä‚¢‚éê‡
	{
		Math::Vector2 enemyiPos = chara1->GetPos();
		enemyiPos.x += nx * over;
		enemyiPos.y += ny * over;
		chara1->SetPos(enemyiPos);
	}
	else if (chara2->Getmove() != notMove)//chara2‚ª“®‚¢‚Ä‚¢‚éê‡
	{
		Math::Vector2 enemyjPos = chara2->GetPos();
		enemyjPos.x -= nx * over;
		enemyjPos.y -= nx * over;
		chara2->SetPos(enemyjPos);
	}
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

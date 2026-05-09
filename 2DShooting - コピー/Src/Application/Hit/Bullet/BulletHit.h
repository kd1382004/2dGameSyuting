#pragma once

class  PlayerBullet;
class CharacterBase;


class BulletHit
{
public:
	BulletHit() {}
	~BulletHit() {	}

	//当たったかどうかを返す関数
	bool Hit(PlayerBullet *bullet, CharacterBase* Chara);

private:

};

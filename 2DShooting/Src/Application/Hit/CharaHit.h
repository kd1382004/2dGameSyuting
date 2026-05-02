#pragma once
//キャラクターの当たり判定
class  CharacterBase;
class  PlayerBullet;

class CharaHit
{
public:
	CharaHit() {}
	~CharaHit(){}

	//キャラ同士当たったかどうかを返す
	//true...当たった
	//false...当たってない
	bool CharacterHit(CharacterBase *chara1, CharacterBase *chara2);

	//敵同士の反発処理
	void Pushback(CharacterBase* chara1, CharacterBase* chara2);


	//弾とキャラが当たったかどうかを返す
	//true...当たった
	//false...当たってない
	bool BulletHit(PlayerBullet* bullet, CharacterBase* enemy,int enemyNum);

private:

};
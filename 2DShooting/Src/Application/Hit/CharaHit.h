#pragma once
//キャラクター同士の当たり判定
class  CharacterBase;

class CharaHit
{
public:
	CharaHit() {}
	~CharaHit(){}

	//当たったかどうかを返す
	//true...当たった
	//false...当たってない
	bool Hit(CharacterBase *chara1, CharacterBase *chara2);

private:

};
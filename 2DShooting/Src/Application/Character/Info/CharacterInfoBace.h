#pragma once

class CharacterInfo
{
public:
	CharacterInfo() {};
	~CharacterInfo() {};

	//前方2方向+ショット
	bool Get3WShotFlg() { return m_3WShotFlg; }
	void Set3WShotFlg(bool flg) { m_3WShotFlg = flg; }

	//左右2方向+ショット
	bool GetLRShotFlg() { return m_LRShotFlg; }
	void SetLRShotFlg(bool flg) { m_LRShotFlg = flg; }

	//弾の貫通回数
	int GetBuletPeneNum() { return m_buletPeneNum; }
	void SetBuletPeneNum(int i) { m_buletPeneNum += i; if (m_buletPeneNum > 99) { m_buletPeneNum = 99; } }//増やす回数入れる

	//弾の反射回数
	int GetBoundNum() { return m_boundNum; }
	void SetBoundNum(int i) { m_boundNum += i; if (m_boundNum > 99) { m_boundNum = 99; }}//増やす回数入れる

	//攻撃力
	int GetATK() { return m_atk; }
	int GetATKLV() { return m_atkLV; }
	void SetATKLV(int atk) {
		m_atkLV += atk;
		if (m_atkLV > 99) { m_atkLV = 99; }
		m_atk = m_atkLV * 10 + 10;
	}//増やす量を入れる
protected:


	//前方2方向+ショット
	bool m_3WShotFlg = false;

	//左右2方向+ショット
	bool m_LRShotFlg = false;

	//弾の貫通回数
	int m_buletPeneNum = 0;

	//弾のバウンド回数
	int m_boundNum = 0;

	//攻撃力LV
	int m_atkLV = 0;

	//攻撃力
	int m_atk = 10;
};

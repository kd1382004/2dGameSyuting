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
	bool Get3LRShotFlg() { return m_3LRShotFlg; }
	void Set3LRShotFlg(bool flg) { m_3LRShotFlg = flg; }

	//弾の貫通回数
	int GetBuletPeneNum() { return m_buletPeneNum; }
	void SetBuletPeneNum(int i) { m_buletPeneNum += i; }//増やす回数入れる

	//弾の貫通回数
	int GetBoundNum() { return m_boundNum; }
	void SetBoundNum(int i) { m_boundNum += i; }//増やす回数入れる

protected:


	//前方2方向+ショット
	bool m_3WShotFlg = false;

	//左右2方向+ショット
	bool m_3LRShotFlg = false;

	//弾の貫通回数
	int m_buletPeneNum = 0;

	//弾のバウンド回数
	int m_boundNum = 0;

	//攻撃力
	int m_atk = 0;
};

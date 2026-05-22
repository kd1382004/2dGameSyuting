#pragma once

struct Key
{
	//押されてるかどうか
	bool m_pushFlg = false;

	//押されてどのくらいか
	int m_pushS = 0;

	//ゲッター用
	bool m_getPushFlg;
};

class InfoKey
{
public:

	~InfoKey() {};

	//キー制御
	//Key...Key番号
	//hold...長押しを防ぐかどうか
	// ture...防ぐ(m_pushSMax後に長押しが復活)
	// false...防がない
	//
	//holdFlg...Keyを1度離さないと復活しない( hold=true && ture でなる )
	bool KeyPush(int Key, bool hold = false, bool holdFlg = false);

	bool GetKeyPush(int Key);

private:


	void Init();

	bool KeyPush(Key* key, int num, bool hold, bool holdFlg);

	//大文字アルファベット
	Key KeyAlphabet[26];

	//矢印
	Key KeyArrow[4];

	//スペースキー
	Key KeySpace;

	//エンターキー
	Key KeyEnter;

	static const int m_pushSMax = 20;


private:

	InfoKey() { Init(); }



public:
	static InfoKey& GetInstance()
	{
		static InfoKey instance;
		return instance;
	}
};

//シーンを管理するクラスにアクセスするためのマクロ
#define InfoKeyAPP InfoKey::GetInstance()
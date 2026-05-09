#include "InfoKey.h"

bool InfoKey::KeyPush(int Key, bool hold, bool holdFlg)
{
	bool flg = false;

	if (Key >= 'A' && Key <= 'Z')//アルファベット
	{
		int Num = Key - 'A';
		KeyAlphabet[Num];

		flg = KeyPush(&KeyAlphabet[Num], Key, hold, holdFlg);
	}
	else if (Key >= VK_LEFT && Key <= VK_DOWN)//矢印
	{
		int Num = Key - VK_LEFT;
		KeyArrow[Num];

		flg = KeyPush(&KeyArrow[Num], Key, hold, holdFlg);
	}
	else if (Key == VK_SPACE)//スペース
	{
		flg = KeyPush(&KeySpace, Key, hold, holdFlg);
	}
	else if (Key == VK_RETURN)
	{
		flg = KeyPush(&KeyEnter, Key, hold, holdFlg);
	}

	return flg;
}

bool InfoKey::GetKeyPush(int Key)
{
	bool flg = false;

	if (Key >= 'A' && Key <= 'Z')//アルファベット
	{
		int Num = Key - 'A';
		KeyAlphabet[Num];

		flg = KeyAlphabet[Num].m_getPushFlg;
	}
	else if (Key >= VK_LEFT && Key <= VK_DOWN)//矢印
	{
		int Num = Key - VK_LEFT;
		KeyArrow[Num];

		flg = KeyArrow[Num].m_getPushFlg;
	}
	else if (Key == VK_SPACE)//スペース
	{
		flg = KeySpace.m_getPushFlg;
	}
	else if (Key == VK_RETURN)
	{
		flg = KeyEnter.m_getPushFlg;
	}

	return flg;
}

void InfoKey::Init()
{

}

bool InfoKey::KeyPush(Key* key, int num, bool hold, bool holdFlg)
{
	bool flg = false;

	if (GetAsyncKeyState(num) & 0x8000)
	{
		key->m_getPushFlg = true;

		if (hold)
		{
			if (!holdFlg)
			{
				if (!key->m_pushFlg)
				{
					key->m_pushFlg = true;
					flg = true;
					key->m_pushS = 0;
				}

				key->m_pushS++;

				if (key->m_pushS > m_pushSMax)
				{
					key->m_pushFlg = false;
					key->m_pushS = 0;
				}
			}
			else
			{
				if (!key->m_pushFlg)
				{
					key->m_pushFlg = true;
					flg = true;
					key->m_pushS = 0;
				}
			}

		}
		else
		{
			flg = true;
			key->m_pushS = 0;
		}
	}
	else
	{
		key->m_getPushFlg = false;
		key->m_pushFlg = false;
		flg = false;
	}

	return flg;
}

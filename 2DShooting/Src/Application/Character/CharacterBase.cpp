#include "CharacterBase.h"

void CharacterBase::HPDown(int dmg)
{
	if (m_HPDownCoolTime == m_HPDownCoolTimeMax)
	{
		m_HPDownCoolTime = 0;
		m_HP -= dmg;
	}

}

void CharacterBase::HPCoolTimeManager()
{
	m_HPDownCoolTime++;

	if (m_HPDownCoolTime > m_HPDownCoolTimeMax)
	{
		m_HPDownCoolTime = m_HPDownCoolTimeMax;
		m_charaAlpha = 1;
	}

	if (m_HPDownCoolTime < m_HPDownCoolTimeMax)
	{
		m_charaAlpha += m_charaAlphaPush;

		if (m_charaAlpha > 1)
		{
			m_charaAlpha = 1;
			m_charaAlphaPush *= -1;
		}

		if (m_charaAlpha < 0.3)
		{
			m_charaAlpha = 0.3;
			m_charaAlphaPush *= -1;
		}

	}

}

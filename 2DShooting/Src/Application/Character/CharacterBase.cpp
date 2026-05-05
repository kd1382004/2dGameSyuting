#include "CharacterBase.h"

void CharacterBase::HPDown(int dmg)
{
	if (m_HPDownCoolTime > m_HPDownCoolTimeMax)
	{
		m_HPDownCoolTime = 0;
		m_HP -= dmg;
	}

}

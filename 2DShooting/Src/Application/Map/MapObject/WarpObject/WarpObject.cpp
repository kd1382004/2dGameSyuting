#include"WarpObject.h"

void  WarpObject::Init(Math::Vector2 pos, Math::Rectangle rec)
{
	m_pos = pos;
	m_rec = rec;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void WarpObject::Updata()
{
}

void WarpObject::Draw2D()
{
}

void WarpObject::Release()
{

}

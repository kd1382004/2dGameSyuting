#include"MapObject.h"


void MapObject::Init(Math::Vector2 pos)
{
	m_pos = pos;

	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
}

void MapObject::Updata(float scroll)
{

}

void MapObject::Release()
{

}

void MapObject::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_tex, m_rec, 1.0f);
}
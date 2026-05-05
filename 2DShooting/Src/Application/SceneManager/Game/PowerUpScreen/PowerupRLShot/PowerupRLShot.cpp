#include"PowerupRLShot.h"
#include"../../../../Character/Player/PowerUpInfo/PowerUpInfo.h"

void PowerupRLShot::Init(Math::Vector2 pos)
{
	m_tex.Load("Tex/PowerUpScreen/PowerupRLShot/PowerupRLShot.png");
	m_iconTex.Load("Tex/PowerUpScreen/PowerupRLShot/PowerupRLShotIcon.png");
	m_pos = pos;
	m_mat = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_iconMat = Math::Matrix::CreateTranslation(m_pos.x - 42, m_pos.y + 75, 0);

}

void PowerupRLShot::Update(PlayerPowerUpInfo* playerInfo)
{
	playerInfo->Set3LRShotFlg(true);
}

void PowerupRLShot::Draw2D()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(&m_tex, m_rec);

	SHADER.m_spriteShader.SetMatrix(m_iconMat);
	SHADER.m_spriteShader.DrawTex(&m_iconTex, m_iconRec);
}

void PowerupRLShot::DrawEX()
{
	DrawEXBack();
	SHADER.m_spriteShader.DrawString(-350, -100, "ç∂âEÇ©ÇÁÇ‡íeÇ™î≠éÀÇ≥ÇÍÇÈ", Math::Vector4(0, 0, 0, 1));
}

void PowerupRLShot::Release()
{
	m_tex.Release();
	m_iconTex.Release();
}
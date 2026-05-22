#include "Fire.h"

Fire::Fire()
{
	m_tex.Load("Tex/Percent/smoke_transparent.png");
	m_srcRect = { 0,0,32,32 };
	m_percentType = percentType::percentTypeFire;
}

Fire::~Fire()
{
	m_tex.Release();
}

void Fire::Update(Math::Vector2 pos, float scroll)
{
	for (int i = 0; i < m_maxSiz; i++)
	{

		//有効期間の処理
		m_lifespan[i]--;
		if (m_lifespan[i] <= 0)
		{
			//リピート無しならリターン
			if (!m_RepeatFlg) { return; }

			//リピート処理
			Emit({ pos.x,pos.y }, { Rnd() * 2 - 1,Rnd() * 2 }, Rnd() * 7 - 3, Math::Color{ 1,Rnd(),0.3f,0.1f }, Rnd() * 30 + 10, true, i, m_deg);
		}

		//サイズ変更(徐々に小さく)
		//m_size *= 0.98f;

		//サイズ変更(徐々に大きく)
		m_size[i] *= 1.02f;

		//座標更新
		m_pos[i].x = pos.x;
		m_pos[i] += m_move[i];

		//行列作成
		Math::Matrix tMat = Math::Matrix::CreateTranslation(m_pos[i].x - scroll, m_pos[i].y, 1);

		Math::Matrix sMat = Math::Matrix::CreateScale(m_sizeX[i], m_sizeY[i], 0);

		Math::Matrix reMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_deg));


		m_mat[i] = sMat * reMat * tMat;
	}


}

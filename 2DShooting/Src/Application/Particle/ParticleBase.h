#pragma once

enum percentType
{
	percentTypeNO,
	percentTypeFire
};


class Praticle
{
public:
	Praticle() {};
	virtual ~Praticle() {};

	//発生
	//pos...座標
	//move...移動量
	//size...大きさ
	//color...色
	//lifespan...有効期間(活動限界時間)
	//RepeatFlg...繰り返しフラグ
	void Emit(Math::Vector2 pos, Math::Vector2 move, float size, Math::Color color, int lifespan, bool RepeatFlg, int i, int deg = 0);

	//表示位置を入れる
	virtual void Update(Math::Vector2 pos, float scroll) {};

	void Draw();

	float Rnd();

	void SetdefSiz(Math::Vector2 defSiz) { m_defSiz = defSiz; };

	percentType GetmPercentType() { return m_percentType; }
private:



protected:

	percentType m_percentType = percentTypeNO;

	//テクスチャ
	KdTexture m_tex;
	static const int m_maxSiz = 30;

	Math::Vector2 m_defSiz = { 1,1 };

	//座標
	Math::Vector2	m_pos[m_maxSiz];

	//移動量
	Math::Vector2	m_move[m_maxSiz];

	//サイズ
	float			m_size[m_maxSiz];
	float			m_sizeX[m_maxSiz];
	float			m_sizeY[m_maxSiz];

	//色
	Math::Color		m_color[m_maxSiz];

	//有効期間(活動限界時間)
	int				m_lifespan[m_maxSiz];

	//繰り返しフラグ
	bool			m_RepeatFlg;

	//生存フラグ
	bool lifFlg;

	//行列
	Math::Matrix	m_mat[m_maxSiz];

	//切り取り範囲
	Math::Rectangle m_srcRect = { };

	float m_deg = 0;
};


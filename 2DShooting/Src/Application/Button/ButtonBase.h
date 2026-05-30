#pragma once

class SoundBase;

class ButtonBase
{
public:
	ButtonBase() { BaseInit(); }
	virtual ~ButtonBase() { Release(); delete m_DECSE; }

	void BaseInit();

	// 初期設定
	// ボタン表示の座標を入れる
	virtual void Init(Math::Vector2 pos) {};

	// ボタンが押された後の処理
	virtual void Update() {};

	// 描画処理
	void Draw2D();

	void SetSelectFlg(bool flg);

	//デフォルトのサイズ
	void SetDefaultSiz(float siz) { m_defaultSiz = siz; }

	//選択されてる時のサイズ
	void SetSelectSiz(float siz) { m_selectSiz = siz; }

	void SoundPlay();
protected:

	KdTexture m_tex;

	//デフォルトのサイズ
	float m_defaultSiz = 1;

	//選択されてる時のサイズ
	float m_selectSiz = 1;

	//選択されているかどうか
	bool m_selectFlg = false;

	virtual void Release() {};

	Math::Vector2 m_pos;
	Math::Matrix m_sMat;
	Math::Matrix m_tMat;
	Math::Matrix m_Mat;

	SoundBase* m_DECSE;

private:

	float m_alpha = 1;
	float m_alphaPush = 0.01;
	Math::Rectangle m_rec = { 0,0,0,0 };
};
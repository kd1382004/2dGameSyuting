#pragma once


class CharacterInfo;
class  Praticle;

enum StateType
{
	TypeNORMAL,
	TypeFIRE
};

//キャラクターの親クラス
class CharacterBase
{
public:
	CharacterBase() {};
	virtual ~CharacterBase() {};

	// 初期設定
	virtual void Init() = 0;

	// 更新処理
	virtual void Update() = 0;

	// 描画処理
	virtual void Draw2D() = 0;


	//キャラの画像をアドレスでセット
	void SetTex(KdTexture* tex) { m_charaTex = tex; }

	Math::Vector2 GetPos() { return m_pos; }

	//当たり判定用変数(直径)を返す
	float GetHitDetection() { return HitDetection; }

	//生存フラグを返す
	bool GetAliveFlg() { return m_aliveFlg; }

	void SetPos(Math::Vector2 pos) { m_pos = pos; }

	Math::Vector2 Getmove() { return m_move; }

	virtual void MatConfirmed(float scroll) = 0;

	bool GetDeleteFlg() { return m_deleteFlg; }

	virtual void BlockHit() {};

	CharacterInfo* GetCharaInfo() { return m_info; }


	virtual void HPDown(int dmg);

	void HPCoolTimeManager();
protected:

	// 解放
	virtual void Release() = 0;

	//画像アドレス
	KdTexture* m_charaTex = nullptr;

	//キャラの座標
	Math::Vector2 m_pos;

	//キャラの切り取り範囲
	Math::Rectangle m_rec;

	//キャラのスピード
	Math::Vector2 m_speed;

	//キャラの移動量
	Math::Vector2 m_move;

	//キャラサイズ
	Math::Vector2 m_siz = { 1,1 };


	//合成行列
	Math::Matrix m_mat;

	//移動行列
	Math::Matrix m_transMat;

	//拡大行列
	Math::Matrix m_scaleMat;

	//回転行列
	Math::Matrix m_rotationMat;

	//生存フラグ
	bool m_aliveFlg;

	//削除フラグ
	bool m_deleteFlg = false;



	static const int m_HPDownCoolTimeMax = 60;
	int m_HPDownCoolTime = m_HPDownCoolTimeMax;

	//円当たり判定用変数(直径を入れる)
	float HitDetection;

	//HP
	float m_HP = 0;

	int m_MaxHP = 0;

	//角度
	float m_deg = 0.0f;

	float m_anime = 0;

	CharacterInfo* m_info;

	float m_charaAlpha = 1;
	float m_charaAlphaPush = 0.1;

	std::vector< Praticle*> m_praticle;

	StateType m_statetype = TypeNORMAL;
	float m_stateTime = 0;
	int m_stateTimeMax = 0;
private:

};


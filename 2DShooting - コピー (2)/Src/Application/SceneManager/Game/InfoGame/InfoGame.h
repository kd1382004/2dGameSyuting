#pragma once

class CharacterInfo;

class InfoGame
{
public:
	InfoGame() {}
	~InfoGame() { Release(); }

	void Init();
	void Update(CharacterInfo* info);
	void Drow2D();


	void SetPWUPNum(int num) { m_PWUPNum = num; }
	void SetPlyerHpHeel(int num) { m_PlyerHpHeel = num; }
private:

	void Release();

	KdTexture m_VLTex;
	KdTexture m_Xmark;
	KdTexture m_KeyArrowTex;
	KdTexture m_KeySpaceTex;

	Math::Vector2 m_keyPos[5];
	Math::Matrix m_keyMat[5];
	float m_keyAlpha[5];

	void KeyDraw();


	KdTexture m_backTex;
	Math::Vector2 m_backPos;
	Math::Matrix m_backMat;

	KdTexture m_3WShotIconTex;
	Math::Vector2 m_3WShotIconPos;
	Math::Matrix m_3WShotIconMat;
	Math::Vector2 m_3WShotLVPos;
	Math::Matrix m_3WShotLVMat;
	bool m_3wShotFlg = false;


	KdTexture m_LRShotIconTex;
	Math::Vector2 m_LRShotIconPos;
	Math::Matrix m_LRShotIconMat;
	Math::Vector2 m_LRShotLVPos;
	Math::Matrix m_LRShotLVMat;
	bool m_LRShotFlg = false;


	KdTexture m_PeneNumIconTex;
	Math::Vector2 m_PeneNumIconPos;
	Math::Matrix m_PeneNumIconMat;
	Math::Vector2 m_PeneNumLVPos;
	Math::Matrix m_PeneNumLVMat;
	int m_PeneNum = 0;


	KdTexture m_BoundNumIconTex;
	Math::Vector2 m_BoundNumIconPos;
	Math::Matrix m_BoundNumIconMat;
	Math::Vector2 m_BoundNumLVPos;
	Math::Matrix m_BoundNumLVMat;
	int m_BoundNum = 0;


	KdTexture m_ENTERTex;
	Math::Vector2 m_ENTERTPos;
	Math::Matrix m_ENTERTMat;
	bool m_ENTERTexFlg = false;
	float m_ENTERAlf = 1;
	float m_ENTERAlfPush = 0.01;


	KdTexture m_PWUPNumIconTex;
	Math::Vector2 m_PWUPNumIconPos;
	Math::Matrix m_PWUPNumIconMat;
	Math::Vector2 m_PWUPNumLVPos;
	Math::Matrix m_PWUPNumLVMat;
	int m_PWUPNum = 0;

	KdTexture m_ATKUPIconTex;
	Math::Vector2 m_ATKUPIconPos;
	Math::Matrix m_ATKUPIconMat;
	Math::Vector2 m_ATKUPLVPos;
	Math::Matrix m_ATKUPLVMat;
	int m_ATKUP = 0;

		KdTexture m_PlyerHpHeelIconTex;
	Math::Vector2 m_PlyerHpHeelIconPos;
	Math::Matrix m_PlyerHpHeelIconMat;
	Math::Vector2 m_PlyerHpHeelLVPos;
	Math::Matrix m_PlyerHpHeelLVMat;
	int m_PlyerHpHeel = 0;
};

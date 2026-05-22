#pragma once

class CharacterInfo;
class Player;

class InfoGame
{
public:
	InfoGame() {}
	~InfoGame() { Release(); }

	void Init();
	void Update(CharacterInfo* info, Player *player, int sc);
	void Drow2D();

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

	KdTexture m_FireArrowIconTex;
	Math::Vector2 m_FireArrowIconPos;
	Math::Matrix m_FireArrowIconMat;
	Math::Vector2 m_FireArrowLVPos;
	Math::Matrix m_FireArrowLVMat;
	int m_FireArrow = 0;

	KdTexture m_PowerUPScoreIconTex;
	Math::Vector2 m_PowerUPScoreIconPos;
	Math::Matrix m_PowerUPScoreIconMat;
	Math::Vector2 m_PowerUPScoreLVPos;
	Math::Matrix m_PowerUPScoreLVMat;
	int m_PowerUPScore = 0;

	KdTexture m_scoreTex;
	Math::Matrix m_scoreMat;
	int m_score = 0;
};

#pragma once

class GameResultInfo
{
public:

	~GameResultInfo() {}



	void SetEnemyDeath(int Num) { m_EnemyDeath = Num; }
	int GetEnemyDeath() { return m_EnemyDeath; }


	void SetPowerUpNum(int Num) { m_powerUpNum = Num; }
	int GetPowerUpNum() { return m_powerUpNum; }

	void SetmStageClearNum(int Num) { m_stageClearNum = Num; }
	int GetmStageClearNum() { return m_stageClearNum; }

	void SetScore(int Num) { m_score = Num; }
	int GetScore() { return m_score; }

	void SetMapNum(int Num) { m_mapNum = Num; }
	int GetMapNum() { return m_mapNum; }

	void SetScroll(float scroll) { m_scroll = scroll; }
	float GetScroll() { return m_scroll; }

	void SetplayerDefPos(Math::Vector2 Pos) { m_playerDefPos = Pos; }
	Math::Vector2 GetplayerDefPos() { return m_playerDefPos; }

	bool GetAliveFlg() { return m_aliveFlg; }
	void SetAliveFlg(bool flg) { m_aliveFlg = flg; }
private:


	//敵を倒した数
	int m_EnemyDeath = 0;

	//強化した数
	int m_powerUpNum = 0;

	//ステージクリア数
	int m_stageClearNum = 0;

	int m_score = 0;

	//マップステージ
	int m_mapNum = 0;

	Math::Vector2 m_playerDefPos;

	//
	float m_scroll = 0;
	void Init() {};

	bool m_aliveFlg = false;
private:

	GameResultInfo() { Init(); }

public:
	static GameResultInfo& GetInstance()
	{
		static GameResultInfo instance;
		return instance;
	}
};

//シーンを管理するクラスにアクセスするためのマクロ
#define GameResultInfoAPP GameResultInfo::GetInstance()
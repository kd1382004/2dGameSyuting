#pragma once

class GameResultInfo
{
public:
	
	~GameResultInfo(){}



	void SetEnemyDeath(int Num) { m_EnemyDeath = Num; }
	int GetEnemyDeath() { return m_EnemyDeath; }


	void SetPowerUpNum(int Num) { m_powerUpNum = Num; }
	int GetPowerUpNum() {return m_powerUpNum;}

	void SetmStageClearNum(int Num) { m_stageClearNum = Num; }
	int GetmStageClearNum() { return m_stageClearNum; }

	void SetmScore(int Num) { m_score = Num; }
	int GetmScore() { return m_score; }
private:


	//敵を倒した数
	int m_EnemyDeath = 0;

	//強化した数
	int m_powerUpNum = 0;

	//ステージクリア数
	int m_stageClearNum = 0;

	int m_score = 0;


	void Init() {};
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
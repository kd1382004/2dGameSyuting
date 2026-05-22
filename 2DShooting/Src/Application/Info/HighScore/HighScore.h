#pragma once

struct scoreT
{
	int score = 0;
	int clearNum=0;
	int enemyNum = 0;
	int powerUpNum = 0;
	int _3wShotLv = 0;
	int _LRShotLv = 0;
	int peneLv = 0;
	int bounLv = 0;
	int hpHeelLv = 0;
	int ATKUpLv = 0;
	int FireArrowUpLv = 0;
	int ScoreUpLv = 0;
};



class HighScore
{
public:

	~HighScore() { Save(); };

	static const int m_scoreSavemax = 3;
	void HighScoreNew();


	scoreT GetScoreSave(int i);

	scoreT nowScre;
private:

	void Init();
	void Save();



	std::vector<scoreT> m_scoreSave;


private:

	HighScore() { Init(); }

public:
	static HighScore& GetInstance()
	{
		static HighScore instance;
		return instance;
	}
};

//シーンを管理するクラスにアクセスするためのマクロ
#define HighScoreAPP HighScore::GetInstance()
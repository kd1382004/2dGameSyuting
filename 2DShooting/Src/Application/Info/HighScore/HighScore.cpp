#include "HighScore.h"

void HighScore::HighScoreNew()
{
	if (m_scoreSave[0].score < nowScre.score)
	{
		m_scoreSave.insert(m_scoreSave.begin(), nowScre);
		m_scoreSave.erase(m_scoreSave.begin() + m_scoreSavemax);
	}
	else if (m_scoreSave[1].score < nowScre.score)
	{
		m_scoreSave.insert(m_scoreSave.begin() + 1, nowScre);
		m_scoreSave.erase(m_scoreSave.begin() + m_scoreSavemax);
	}
	else if (m_scoreSave[2].score < nowScre.score)
	{
		m_scoreSave.insert(m_scoreSave.begin() + 2, nowScre);
		m_scoreSave.erase(m_scoreSave.begin() + m_scoreSavemax);

	}
	int i = 0;
}

scoreT HighScore::GetScoreSave(int i)
{

	if (i < m_scoreSave.size())
	{
		return m_scoreSave[i];
	}


	return scoreT();
}

void HighScore::Init()
{
	FILE* fp;
	int score = 0;
	int clearNum = 0;
	int enemyNum = 0;
	int powerUpNum = 0;
	int _3wShotLv = -0;
	int _LRShotLv = 0;
	int peneLv = 0;
	int bounLv = 0;
	int hpHeelLv = 0;
	int ATKUpLv = 0;
	int i = 0;
	if (fopen_s(&fp, "Data/HighScore/Score/Score.csv", "r") == 0)
	{
		// 1行目を読み飛ばす
		while (fgetc(fp) != '\n');

		while (true)
		{
			scoreT nowScore;

			fscanf_s(fp, "%d,", &score);
			fscanf_s(fp, "%d,", &clearNum);
			fscanf_s(fp, "%d,", &enemyNum);
			fscanf_s(fp, "%d,", &powerUpNum);
			fscanf_s(fp, "%d,", &_3wShotLv);
			fscanf_s(fp, "%d,", &_LRShotLv);
			fscanf_s(fp, "%d,", &peneLv);
			fscanf_s(fp, "%d,", &bounLv);
			fscanf_s(fp, "%d,", &hpHeelLv);
			fscanf_s(fp, "%d", &ATKUpLv);

			if (i < m_scoreSavemax)
			{
				nowScore.score = score;
				nowScore.clearNum = clearNum;
				nowScore.enemyNum = enemyNum;
				nowScore.powerUpNum = powerUpNum;
				nowScore._3wShotLv = _3wShotLv;
				nowScore._LRShotLv = _LRShotLv;
				nowScore.peneLv = peneLv;
				nowScore.bounLv = bounLv;
				nowScore.hpHeelLv = hpHeelLv;
				nowScore.ATKUpLv = ATKUpLv;
				m_scoreSave.push_back(nowScore);
			}
			else
			{
				break;
			}
			i++;
		}

		fclose(fp);
	}

	int a = 0;
}

void HighScore::Save()
{
	FILE* fp;
	if (fopen_s(&fp, "Data/HighScore/Score/Score.csv", "w") == 0)
	{
		fprintf(fp, "スコア,ステージクリア,敵,パワーアップ,3方向ショット,左右弾,貫通,バウンド,HP吸収,攻撃力上昇\n");
		for (int i = 0; i < m_scoreSavemax; i++)
		{
			fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n")
				m_scoreSave[i].score, m_scoreSave[i].clearNum,
				m_scoreSave[i].enemyNum, m_scoreSave[i].powerUpNum,
				m_scoreSave[i]._3wShotLv, m_scoreSave[i]._LRShotLv,
				m_scoreSave[i].peneLv, m_scoreSave[i].bounLv,
				m_scoreSave[i].hpHeelLv, m_scoreSave[i].ATKUpLv
			);

		}

		fclose(fp);
	}

}

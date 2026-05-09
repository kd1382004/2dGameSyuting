class HighScore
{
public:

	~HighScore() {};

	void HighScoreNew();

private:


	void Init();

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
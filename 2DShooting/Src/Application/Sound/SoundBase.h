#pragma once

class SoundBase
{
public:
	SoundBase() {};
	virtual ~SoundBase() {};
	
	
	//音を鳴らす
	void Play();
	
	void Stop();
protected:

	std::shared_ptr<KdSoundEffect>   se;		//音データ
	std::shared_ptr<KdSoundInstance> seInst;	//音を鳴らすための変数

	//音データ読み込み
	//*Sound...音データアドレス
	//*SoundInst...音変数アドレス
	//vol...初期音量
	//*SoundData...音データファイル名
	//flg...ループするか
	void LaodBGM(std::shared_ptr<KdSoundEffect>* Sound, std::shared_ptr<KdSoundInstance >* SoundInst, float vol, char* SoundData,bool flg);


	virtual void Init();

	bool m_loopFlg = false;
private:


	};

#include "SoundBase.h"

void SoundBase::Init()
{

}

void SoundBase::Play()
{
	if (seInst->IsPlay() == false)
	{
		seInst->Play(m_loopFlg);	//最初から再生
	}
}

void SoundBase::Stop()
{
	seInst->Stop();	//Stop()で停止
}

void SoundBase::LaodBGM(std::shared_ptr<KdSoundEffect>* Sound, std::shared_ptr<KdSoundInstance>* SoundInst, float vol, char* SoundData, bool flg)
{
	std::shared_ptr<KdSoundEffect> bgm;
	std::shared_ptr<KdSoundInstance> bgmInst;

	//1:領域確保
	bgm = std::make_shared<KdSoundEffect>();

	//2:音データ読み込み
	bgm->Load(SoundData);

	//3:実体化(インスタンス化)
	bgmInst = bgm->CreateInstance(false);

	//4:音量設定(0～1の範囲)
	bgmInst->SetVolume(vol);

	m_loopFlg = flg;

	*Sound = bgm;
	*SoundInst = bgmInst;
}

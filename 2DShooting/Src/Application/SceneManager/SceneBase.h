#pragma once

class SceneManager;

//シーンの親クラス
class SceneBase
{
public:
	// 初期設定
	virtual void Init() = 0;

	// 更新処理
	virtual void Update() = 0;

	// 描画処理
	virtual void Draw2D() = 0;

	void SetOwner(SceneManager* manager) { m_owner = manager; }



protected:

	virtual void Release() = 0;

	//シーンマネージャーのアドレス
	SceneManager* m_owner = nullptr;

private:

};

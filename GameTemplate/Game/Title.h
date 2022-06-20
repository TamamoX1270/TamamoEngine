#pragma once
#include "sound/SoundSource.h"

class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_titleSpriteRender;			//タイトル画像。

	SoundSource* titleBGM;						//タイトルのBGM。
	SoundSource* switchSE;						//Aボタンを押したときの効果音。
};


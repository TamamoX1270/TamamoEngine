#pragma once
#include "sound/SoundSource.h"

class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender spriteRender;
	SpriteRender spriteRender2;
	SoundSource* titleBGM;
	SoundSource* se;
};


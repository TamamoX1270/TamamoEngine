#pragma once
#include "sound/SoundSource.h"

class Result :public IGameObject
{
public:
	Result();
	~Result();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender spriteRender;
	SoundSource* titleBGM;
	SoundSource* se;
};


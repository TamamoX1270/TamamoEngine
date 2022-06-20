#pragma once
#include "sound/SoundSource.h"

class Title:public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender m_titleSpriteRender;			//�^�C�g���摜�B

	SoundSource* titleBGM;						//�^�C�g����BGM�B
	SoundSource* switchSE;						//A�{�^�����������Ƃ��̌��ʉ��B
};


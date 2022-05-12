#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Title::Title()
{
	spriteRender.Init("Assets/sprite/sushifighter.dds", 1600.0f, 900.0f);

	//�^�C�g����BGM��ǂݍ���
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/title_bgm.wav");
	//���艹��ǂݍ���
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/kettei_se.wav");
	//�^�C�g����BGM���Đ�����
	titleBGM = NewGO<SoundSource>(1);
	titleBGM->Init(1);
	titleBGM->Play(true);
}

Title::~Title()
{
	DeleteGO(titleBGM);
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA)|| g_pad[1]->IsTrigger(enButtonA) || g_pad[2]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0,"game");
		DeleteGO(this);
		//���艹���Đ�
		SoundSource* se = NewGO<SoundSource>(2);
		se->Init(2);
		se->Play(false);

	}
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
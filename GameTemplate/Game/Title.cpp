#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Title::Title()
{
	m_titleSpriteRender.Init("Assets/sprite/title.dds");

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
	if (g_pad[0]->IsTrigger(enButtonA) || g_pad[1]->IsTrigger(enButtonA) || g_pad[2]->IsTrigger(enButtonA) || g_pad[3]->IsTrigger(enButtonA)) {

		//Game���n�߂�B
		NewGO<Game>(0, "game");
		DeleteGO(this);
		//���艹���Đ�
		switchSE = NewGO<SoundSource>(2);
		switchSE->Init(2);
		switchSE->Play(false);
	}
}

void Title::Render(RenderContext& rc)
{
	m_titleSpriteRender.Draw(rc);
}
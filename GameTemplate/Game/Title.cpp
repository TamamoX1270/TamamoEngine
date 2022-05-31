#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Title::Title()
{
	spriteRender.Init("Assets/sprite/sushifighter.dds", 1600.0f, 900.0f);
	spriteRender2.Init("Assets/sprite/Apress.dds", 1600.0f, 400.0f);
	spriteRender2.SetPosition(Vector3(0.0f, -300.0f, 0.0f));

	spriteRender2.Update();

	//タイトルのBGMを読み込む
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/title_bgm.wav");
	//決定音を読み込む
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/kettei_se.wav");
	//タイトルのBGMを再生する
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
	if (g_pad[0]->IsTrigger(enButtonA)|| g_pad[1]->IsTrigger(enButtonA) || g_pad[2]->IsTrigger(enButtonA) || g_pad[3]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0,"game");
		DeleteGO(this);
		//決定音を再生
		SoundSource* se = NewGO<SoundSource>(2);
		se->Init(2);
		se->Play(false);

	}
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
	spriteRender2.Draw(rc);
}
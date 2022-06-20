#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Title::Title()
{
	m_titleSpriteRender.Init("Assets/sprite/title.dds");

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
	if (g_pad[0]->IsTrigger(enButtonA) || g_pad[1]->IsTrigger(enButtonA) || g_pad[2]->IsTrigger(enButtonA) || g_pad[3]->IsTrigger(enButtonA)) {

		//Gameを始める。
		NewGO<Game>(0, "game");
		DeleteGO(this);
		//決定音を再生
		switchSE = NewGO<SoundSource>(2);
		switchSE->Init(2);
		switchSE->Play(false);
	}
}

void Title::Render(RenderContext& rc)
{
	m_titleSpriteRender.Draw(rc);
}
#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Title::Title()
{
	spriteRender.Init("Assets/sprite/Title.dds", 1600.0f, 900.0f);

}

Title::~Title()
{

}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0,"game");
		DeleteGO(this);

	}
}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}
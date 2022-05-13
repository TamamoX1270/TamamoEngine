#pragma once
#include "sound/SoundSource.h"

class Result :public IGameObject
{
public:
	Result();
	~Result();
	void Update();
	void Render(RenderContext& rc);
	/// <summary>
	/// ���������Ȃ���������Ɗi�[����B
	/// </summary>
	void SetDrawFlag()
	{
		m_draw = true;
	}
	void SetWinPlayer(const int winp)
	{
		m_winplayer = winp;
	}

private:
	ModelRender* m_player;								//�v���C���[
	SpriteRender spriteRender;
	FontRender	 m_fontRender;
	SoundSource* titleBGM;
	SoundSource* se;

	int m_draw = false;
	int m_winplayer = 0;
};


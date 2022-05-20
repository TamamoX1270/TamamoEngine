#pragma once
#include "sound/SoundSource.h"

class PlayerPoint;

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
	SpriteRender m_magurowin;
	SpriteRender m_samonwin;
	SpriteRender m_tamagowin;
	SpriteRender m_ebiwin;
	SpriteRender m_select;
	PlayerPoint* m_playerpoint;
	FontRender	 m_fontRender;
	SoundSource* titleBGM;
	SoundSource* se;

	int m_draw = false;
	int m_winplayer = 0;
	int m_pointwinplayer = 0;
};


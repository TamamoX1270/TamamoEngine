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
	/// 引き分けなら引き分けと格納する。
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
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : 待機アニメーション、
		enAnimClip_Num,		// 14 : アニメーションクリップの数。
	};

	ModelRender* m_player;								//プレイヤー
	Model				m_model;
	ModelRender			m_salmon;								//プレイヤー
	Animation		m_animation;							// アニメーション
	AnimationClip	m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	SpriteRender m_magurowin;
	SpriteRender m_samonwin;
	SpriteRender m_tamagowin;
	SpriteRender m_ebiwin;
	SpriteRender m_select;
	SpriteRender m_spriteset;
	PlayerPoint* m_playerpoint;
	FontRender	 m_fontRender;
	SoundSource* titleBGM;
	SoundSource* se2;
	SoundSource* se3;

	int m_draw = false;
	int m_winplayer = 0;
	int m_pointwinplayer = 0;
};


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
	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : �ҋ@�A�j���[�V�����A
		enAnimClip_Num,		// 14 : �A�j���[�V�����N���b�v�̐��B
	};

	ModelRender* m_player;								//�v���C���[
	Model				m_model;
	ModelRender			m_salmon;								//�v���C���[
	Animation		m_animation;							// �A�j���[�V����
	AnimationClip	m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v
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


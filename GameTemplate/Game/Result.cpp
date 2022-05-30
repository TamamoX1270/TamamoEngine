#include "stdafx.h"
#include "Result.h"
#include "PlayerPoint.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Result::Result()
{
	m_spriteset.SetSetUPSpriteRender(true);
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);

	m_samonwin.Init("Assets/sprite/samonwin.dds", 1600.0f, 900.0f);
	m_magurowin.Init("Assets/sprite/Maguro_win.dds", 1600.0f, 900.0f);
	m_tamagowin.Init("Assets/sprite/Tamago_win.dds", 1600.0f, 900.0f);
	m_ebiwin.Init("Assets/sprite/Ebi_win.dds", 1600.0f, 900.0f);
	m_select.Init("Assets/sprite/select.dds", 1600.0f, 900.0f);

	//���f���̓ǂݍ���
	m_salmon.Init("Assets/purototype/model2/salmon.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);

	//�^�C�g����BGM��ǂݍ���
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/title_bgm.wav");
	//���艹��ǂݍ���
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/game_mouitido.wav");
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/game_titlemodoru.wav");


	m_playerpoint = FindGO<PlayerPoint>("playerpoint");
	//�^�C�g����BGM���Đ�����
	titleBGM = NewGO<SoundSource>(1);
	titleBGM->Init(1);
	titleBGM->Play(true);
}

Result::~Result()
{
	DeleteGO(titleBGM);
	DeleteGO(m_playerpoint);
}

void Result::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA) || g_pad[1]->IsTrigger(enButtonA) || g_pad[2]->IsTrigger(enButtonA)|| g_pad[3]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		m_spriteset.SetSetUPSpriteRender(false);
		DeleteGO(this);
		//���艹���Đ�
		se2 = NewGO<SoundSource>(11);
		se2->Init(11);
		se2->Play(false);
	}
	else if (g_pad[0]->IsTrigger(enButtonB) || g_pad[1]->IsTrigger(enButtonA) || g_pad[2]->IsTrigger(enButtonA)|| g_pad[3]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "title");
		DeleteGO(this);
		//���艹���Đ�
		se3 = NewGO<SoundSource>(12);
		se3->Init(12);
		se3->Play(false);
	}


	/*if (m_draw == true)
	{*/
		//PHP�Ƀ|�C���g���i�[����B
		int MaxP = 0;

		float P[4];
		P[0] = m_playerpoint->GetPoint1();
		P[1] = m_playerpoint->GetPoint2();
		P[2] = m_playerpoint->GetPoint3();
		P[3] = m_playerpoint->GetPoint4();

		for (int i = 0; i < 4; i++) {
			if (MaxP < P[i]) {
				MaxP = P[i];
				m_winplayer = i;
			}
			else if (MaxP == P[i]) {
				m_winplayer = 4;
			}
		}
	//}
}

void Result::Render(RenderContext& rc)
{
	//�v���C���[�P�̏���
	if (m_winplayer == 0)
	{
		m_samonwin.Draw(rc);
	}
	//�v���C���[�Q�̏���
	if (m_winplayer == 1)
	{
		m_magurowin.Draw(rc);
	}
	//�v���C���[�R�̏���
	if (m_winplayer == 2)
	{
		m_tamagowin.Draw(rc);
	}
	//�v���C���[�S�̏���
	if (m_winplayer == 3)
	{
		m_ebiwin.Draw(rc);
	}
	//��������
	if (m_winplayer == 4)
	{
		m_select.Draw(rc);
	}
	//m_salmon.Draw(rc);
	m_select.Draw(rc);
}
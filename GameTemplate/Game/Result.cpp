#include "stdafx.h"
#include "Result.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Result::Result()
{
	spriteRender.Init("Assets/sprite/Result.dds", 1600.0f, 900.0f);

	//�^�C�g����BGM��ǂݍ���
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/title_bgm.wav");
	//���艹��ǂݍ���
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/kettei_se.wav");
	//�^�C�g����BGM���Đ�����
	titleBGM = NewGO<SoundSource>(1);
	titleBGM->Init(1);
	titleBGM->Play(true);
}

Result::~Result()
{
	DeleteGO(titleBGM);
}

void Result::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA) || g_pad[1]->IsTrigger(enButtonA) || g_pad[2]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
		//���艹���Đ�
		SoundSource* se = NewGO<SoundSource>(2);
		se->Init(2);
		se->Play(false);
	}
	if (m_draw == true)
	{
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"��������");

		//�\������e�L�X�g��ݒ�B
		m_fontRender.SetText(wcsbuf);
		//�t�H���g�̈ʒu��ݒ�B
		m_fontRender.SetPosition(Vector3(-95.0f, 500.0f, 0.0f));
		//�t�H���g�̑傫����ݒ�B
		m_fontRender.SetScale(3.0f);
	}
	else if (m_draw == false)
	{
		int winp;
		wchar_t wcsbuf[256];
		if (m_winplayer == 0)
		{
			swprintf_s(wcsbuf, 256, L"1P�̏���", m_winplayer);
		}
		else if (m_winplayer == 1)
		{
			swprintf_s(wcsbuf, 256, L"2P�̏���", m_winplayer);
		}
		else if (m_winplayer == 2)
		{
			swprintf_s(wcsbuf, 256, L"3P�̏���", m_winplayer);
		}
		else if (m_winplayer == 3)
		{
			swprintf_s(wcsbuf, 256, L"4P�̏���", m_winplayer);
		}

		//�\������e�L�X�g��ݒ�B
		m_fontRender.SetText(wcsbuf);
		//�t�H���g�̈ʒu��ݒ�B
		m_fontRender.SetPosition(Vector3(-95.0f, 500.0f, 0.0f));
		//�t�H���g�̑傫����ݒ�B
		m_fontRender.SetScale(3.0f);
	}
}

void Result::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
	m_fontRender.Draw(rc);
	//�v���C���[�P�̏���
	if (m_winplayer == 0)
	{

	}
	//�v���C���[�Q�̏���
	if (m_winplayer == 1)
	{

	}
	//�v���C���[�R�̏���
	if (m_winplayer == 2)
	{

	}
	//�v���C���[�S�̏���
	if (m_winplayer == 3)
	{

	}
}
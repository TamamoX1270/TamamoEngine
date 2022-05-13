#include "stdafx.h"
#include "Result.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Result::Result()
{
	m_samonwin.Init("Assets/sprite/samonwin.dds", 1600.0f, 900.0f);
	m_magurowin.Init("Assets/sprite/magurowin.dds", 1600.0f, 900.0f);
	m_tamagowin.Init("Assets/sprite/tamagowin.dds", 1600.0f, 900.0f);
	m_ebiwin.Init("Assets/sprite/ebiwin.dds", 1600.0f, 900.0f);
	m_select.Init("Assets/sprite/select.dds", 1600.0f, 900.0f);
	//タイトルのBGMを読み込む
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/title_bgm.wav");
	//決定音を読み込む
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/kettei_se.wav");
	//タイトルのBGMを再生する
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
		//決定音を再生
		SoundSource* se = NewGO<SoundSource>(2);
		se->Init(2);
		se->Play(false);
	}
	else if (g_pad[0]->IsTrigger(enButtonB) || g_pad[1]->IsTrigger(enButtonA) || g_pad[2]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "title");
		DeleteGO(this);
		//決定音を再生
		SoundSource* se = NewGO<SoundSource>(2);
		se->Init(2);
		se->Play(false);
	}
	if (m_draw == true)
	{
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"引き分け");

		//表示するテキストを設定。
		m_fontRender.SetText(wcsbuf);
		//フォントの位置を設定。
		m_fontRender.SetPosition(Vector3(-95.0f, 500.0f, 0.0f));
		//フォントの大きさを設定。
		m_fontRender.SetScale(3.0f);
	}
	else if (m_draw == false)
	{
		int winp;
		wchar_t wcsbuf[256];
		if (m_winplayer == 0)
		{
			swprintf_s(wcsbuf, 256, L"1Pの勝ち", m_winplayer);
		}
		else if (m_winplayer == 1)
		{
			swprintf_s(wcsbuf, 256, L"2Pの勝ち", m_winplayer);
		}
		else if (m_winplayer == 2)
		{
			swprintf_s(wcsbuf, 256, L"3Pの勝ち", m_winplayer);
		}
		else if (m_winplayer == 3)
		{
			swprintf_s(wcsbuf, 256, L"4Pの勝ち", m_winplayer);
		}

		//表示するテキストを設定。
		m_fontRender.SetText(wcsbuf);
		//フォントの位置を設定。
		m_fontRender.SetPosition(Vector3(-95.0f, 500.0f, 0.0f));
		//フォントの大きさを設定。
		m_fontRender.SetScale(3.0f);
	}
}

void Result::Render(RenderContext& rc)
{
	//プレイヤー１の勝ち
	if (m_winplayer == 0)
	{
		m_samonwin.Draw(rc);
	}
	//プレイヤー２の勝ち
	if (m_winplayer == 1)
	{
		m_magurowin.Draw(rc);
	}
	//プレイヤー３の勝ち
	if (m_winplayer == 2)
	{
		m_tamagowin.Draw(rc);
	}
	//プレイヤー４の勝ち
	if (m_winplayer == 3)
	{
		m_ebiwin.Draw(rc);
	}
	m_select.Draw(rc);
}
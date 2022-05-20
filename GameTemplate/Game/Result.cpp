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
	//アニメーションクリップをロードする。
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);

	m_samonwin.Init("Assets/sprite/samonwin.dds", 1600.0f, 900.0f);
	m_magurowin.Init("Assets/sprite/magurowin.dds", 1600.0f, 900.0f);
	m_tamagowin.Init("Assets/sprite/tamagowin.dds", 1600.0f, 900.0f);
	m_ebiwin.Init("Assets/sprite/ebiwin.dds", 1600.0f, 900.0f);
	m_select.Init("Assets/sprite/select.dds", 1600.0f, 900.0f);

	//モデルの読み込み
	m_salmon.Init("Assets/purototype/model2/salmon.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);

	//タイトルのBGMを読み込む
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/title_bgm.wav");
	//決定音を読み込む
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/kettei_se.wav");
	m_playerpoint = FindGO<PlayerPoint>("playerpoint");
	//タイトルのBGMを再生する
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
	if (g_pad[0]->IsTrigger(enButtonA) || g_pad[1]->IsTrigger(enButtonA) || g_pad[2]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		m_spriteset.SetSetUPSpriteRender(false);
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
		//PHPにポイントを格納する。
		int MaxP = 0;
		//int P  = m_playerpoint->GetPoint1();
		int P = 999;
		int P2 = m_playerpoint->GetPoint2();
		int P3 = m_playerpoint->GetPoint3();
		int P4 = m_playerpoint->GetPoint4();
		//一番大きいHPの奴を格納する。
		if (MaxP < P)
		{
			MaxP = P;
			m_winplayer = 0;
		}
		if (MaxP < P2)
		{
			MaxP = P2;
			m_winplayer = 1;
		}
		if (MaxP < P3)
		{
			MaxP = P3;
			m_winplayer = 2;
		}
		if (MaxP < P4)
		{
			MaxP = P4;
			m_winplayer = 3;
		}
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
	m_salmon.Draw(rc);
	//m_select.Draw(rc);
}
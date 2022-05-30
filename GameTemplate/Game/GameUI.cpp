#include "stdafx.h"
#include "GameUI.h"
#include "Game.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

namespace
{
	//醤油さしの外側の透明度の設定
	Vector4 Transparent = { 1.0f, 1.0f, 1.0f, 0.5f };
	//最大HP。
	const int P1MAXIMUM_HP = 100;
	const int P2MAXIMUM_HP = 100;
	const int P3MAXIMUM_HP = 100;
	const int P4MAXIMUM_HP = 100;
}

bool GameUI::Start()
{
	m_player1 = FindGO<Player1>("player1");
	m_player2 = FindGO<Player2>("player2");
	m_player3 = FindGO<Player3>("player3");
	m_player4 = FindGO<Player4>("player4");

	m_hajime.Init("Assets/sprite/hajime.dds", 1600.0f, 900.0f);
	m_count1.Init("Assets/sprite/one.dds", 500.0f, 500.0f);
	m_count2.Init("Assets/sprite/two.dds", 500.0f, 500.0f);
	m_count3.Init("Assets/sprite/three.dds", 500.0f, 500.0f);

	//m_ui.Init("Assets/sprite/ComprehensiveUI.dds", 1600.0f, 900.0f);
	m_spriteRendersamonhuda.Init("Assets/sprite/samonhuda.dds", 100.0f, 200.0f);
	m_spriteRendersamonhuda.SetPosition(Vector3(-730.0f, -340.0f, 0.0f));

	m_spriteRendermagurohuda.Init("Assets/sprite/magurohuda.dds", 100.0f, 200.0f);
	m_spriteRendermagurohuda.SetPosition(Vector3(-335.0f, -340.0f, 0.0f));

	m_spriteRendertamagohuda.Init("Assets/sprite/tamagohuda.dds", 100.0f, 200.0f);
	m_spriteRendertamagohuda.SetPosition(Vector3(65.0f, -340.0f, 0.0f));

	m_spriteRenderebihuda.Init("Assets/sprite/ebihuda.dds", 100.0f, 200.0f);
	m_spriteRenderebihuda.SetPosition(Vector3(460.0f, -340.0f, 0.0f));

	m_spriteRendertime.Init("Assets/sprite/timer_UI2.dds", 520.0f, 300.0f);
	m_spriteRendertime.SetPosition(Vector3(0.0f, 375.0f, 0.0f));

	for (int i = 0; i < 4; i++)
	{
		m_spriteRenderslash[i].Init("Assets/sprite/slash.dds", 100.0f, 200.0f);
		switch (i)
		{
		case 0:
			m_spriteRenderslash[0].SetPosition(Vector3(-730.0f, -340.0f, 0.0f));
			m_spriteRenderslash[0].Update();
		case 1:
			m_spriteRenderslash[1].SetPosition(Vector3(-335.0f, -340.0f, 0.0f));
			m_spriteRenderslash[1].Update();
		case 2:
			m_spriteRenderslash[2].SetPosition(Vector3(65.0f, -340.0f, 0.0f));
			m_spriteRenderslash[2].Update();
		case 3:
			m_spriteRenderslash[3].SetPosition(Vector3(460.0f, -340.0f, 0.0f));
			m_spriteRenderslash[3].Update();
		}
	}

	m_spriteRendersokomade.Init("Assets/sprite/sokomade.dds", 1600.0f, 900.0f);
	SoyCT();
	SushiHPBar();

	m_spriteRendersamonhuda.Update();
	m_spriteRendermagurohuda.Update();
	m_spriteRendertamagohuda.Update();
	m_spriteRenderebihuda.Update();
	m_spriteRendertime.Update();

	//戦闘終了SEを読み込む。
	g_soundEngine->ResistWaveFileBank(999, "Assets/sound/fightend.wav");

	GameBGM();

	return true;
}

GameUI::~GameUI()
{
	DeleteGO(gameBGM);
}

void GameUI::SoyCT()
{

	m_syouyusasi.Init("Assets/sprite/syouyusasi1.dds", 280.0f, 280.0f);
	m_syouyusasi2.Init("Assets/sprite/syouyusasi2.dds", 280.0f, 280.0f);
	m_syouyusasi3.Init("Assets/sprite/syouyusasi3.dds", 280.0f, 280.0f);
	m_syouyusasi4.Init("Assets/sprite/syouyusasi4.dds", 280.0f, 280.0f);

	m_syouyusasi_kara.Init("Assets/sprite/syouyusasi1_kara.dds", 280.0f, 280.0f);
	m_syouyusasi_kara2.Init("Assets/sprite/syouyusasi2_kara.dds", 280.0f, 280.0f);
	m_syouyusasi_kara3.Init("Assets/sprite/syouyusasi3_kara.dds", 280.0f, 280.0f);
	m_syouyusasi_kara4.Init("Assets/sprite/syouyusasi4_kara.dds", 280.0f, 280.0f);

	m_syouyusasi.SetPosition({ -430.0f,-330.0f,0.0f });
	m_syouyusasi2.SetPosition({ -35.0f,-330.0f,0.0f });
	m_syouyusasi3.SetPosition({ 365.0f,-330.0f,0.0f });
	m_syouyusasi4.SetPosition({ 750.0f,-330.0f,0.0f });

	m_syouyusasi_kara.SetPosition({ -430.0f,-330.0f,0.0f });
	m_syouyusasi_kara2.SetPosition({ -35.0f,-330.0f,0.0f });
	m_syouyusasi_kara3.SetPosition({ 365.0f,-330.0f,0.0f });
	m_syouyusasi_kara4.SetPosition({ 750.0f,-330.0f,0.0f });

	//更新処理
	m_syouyusasi.Update();
	m_syouyusasi2.Update();
	m_syouyusasi3.Update();
	m_syouyusasi4.Update();

	m_syouyusasi_kara.Update();
	m_syouyusasi_kara2.Update();
	m_syouyusasi_kara3.Update();
	m_syouyusasi_kara4.Update();

}

void GameUI::SushiHPBar()
{
	m_sushihpbar.Init("Assets/sprite/hpbar().DDS", 150.0f, 90.0f);
	m_sushihpbar2.Init("Assets/sprite/hpbar().DDS", 150.0f, 90.0f);
	m_sushihpbar3.Init("Assets/sprite/hpbar().DDS", 150.0f, 90.0f);
	m_sushihpbar4.Init("Assets/sprite/hpbar().DDS", 150.0f, 90.0f);

	m_sushihpbar_kuro.Init("Assets/sprite/Hpbar_1.DDS", 150.0f, 90.0f);
	m_sushihpbar_kuro2.Init("Assets/sprite/Hpbar_1.DDS", 150.0f, 90.0f);
	m_sushihpbar_kuro3.Init("Assets/sprite/Hpbar_1.DDS", 150.0f, 90.0f);
	m_sushihpbar_kuro4.Init("Assets/sprite/Hpbar_1.DDS", 150.0f, 90.0f);

	m_sushihpbarwaku.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	m_sushihpbarwaku2.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	m_sushihpbarwaku3.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	m_sushihpbarwaku4.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	//HPバーのピボットを設定。
	//m_sushihpbar.SetPivot(Vector2(0.5f, 0.5f));
	m_sushihpbar.SetPosition(Vector3(-660.0f, -363.0f, 0.0f));
	m_sushihpbar2.SetPosition(Vector3(-260.0f, -363.0f, 0.0f));
	m_sushihpbar3.SetPosition(Vector3(140.0f, -363.0f, 0.0f));
	m_sushihpbar4.SetPosition(Vector3(530.0f, -363.0f, 0.0f));

	m_sushihpbar_kuro.SetPosition(Vector3(-585.0f, -363.0f, 0.0f));
	m_sushihpbar_kuro2.SetPosition(Vector3(-185.0f, -363.0f, 0.0f));
	m_sushihpbar_kuro3.SetPosition(Vector3(215.0f, -363.0f, 0.0f));
	m_sushihpbar_kuro4.SetPosition(Vector3(605.0f, -363.0f, 0.0f));

	m_sushihpbarwaku.SetPosition(Vector3(-585.0f, -355.0f, 0.0f));
	m_sushihpbarwaku2.SetPosition(Vector3(-185.0f, -355.0f, 0.0f));
	m_sushihpbarwaku3.SetPosition(Vector3(215.0f, -355.0f, 0.0f));
	m_sushihpbarwaku4.SetPosition(Vector3(605.0f, -355.0f, 0.0f));
	
	m_sushihpbar.Update();
	m_sushihpbar2.Update();
	m_sushihpbar3.Update();
	m_sushihpbar4.Update();

	m_sushihpbar_kuro.Update();
	m_sushihpbar_kuro2.Update();
	m_sushihpbar_kuro3.Update();
	m_sushihpbar_kuro4.Update();

	m_sushihpbarwaku.Update();
	m_sushihpbarwaku2.Update();
	m_sushihpbarwaku3.Update();
	m_sushihpbarwaku4.Update();
}

void GameUI::GameBGM()
{
	//ゲームのBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/game_bgm.wav");
	//ゲームのBGMを再生する。
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(0);
	gameBGM->Play(true);
}

void GameUI::Timer()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%3d", int(game_timer));

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-95.0f, 500.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(3.0f);
	if (m_gamestart == false)
	{
		gamestart_timer -= g_gameTime->GetFrameDeltaTime();
	}
	if (gamestart_timer > 2.0f&& gamestart_timer <= 3.0f)
	{
		m_countstate = 3;
	}
	if (gamestart_timer > 1.0f && gamestart_timer <= 2.0f)
	{
		m_countstate = 2;
	}
	if (gamestart_timer > 0.0f && gamestart_timer <= 1.0f)
	{
		m_countstate = 1;
	}
	if (m_hajimestate == false && gamestart_timer <= 0.0f)
	{
		gamestart_timer = 0.0f;
		m_countstate = 0;
		m_hajimestate = true;
	}
	if (m_hajimestate == true && hajime_timer < 1.0f)
	{
		hajime_timer += g_gameTime->GetFrameDeltaTime();
	}
	if (hajime_timer >= 1.0f&& m_countstate == 0)
	{
		m_countstate = 4;
		m_gamestart = true;
	}
	if (m_gamestart == false)
	{
		return;
	}
	if (m_sokomade == false)
	{
		game_timer -= g_gameTime->GetFrameDeltaTime();
	}
	if (m_sokomade == true && sokomade_timer <= 0.1f)
	{
		m_gameendse = true;
	}
	else if (m_sokomade == true && m_gameendse == true)
	{
		m_gameendse = false;
		endSE = NewGO<SoundSource>(0);
		endSE->Init(999);
		endSE->Play(false);
	}

	//タイマーが0になったらゲームを削除
	if (game_timer <= 0.0f)
	{
		m_sokomade = true;
	}
}

void GameUI::GameHP()
{
	m_p1hp = m_player1->GetPlayerHP();
	m_p2hp = m_player2->GetPlayer2HP();
	m_p3hp = m_player3->GetPlayer3HP();
	m_p4hp = m_player4->GetPlayer4HP();
	/*
	//HPが0より減っていたら。
	if (m_p1hp < 0)
	{
		//HPを0にする。
		m_p1hp = 0;
	}
	//HPが最大値を超えていたら。
	else if (m_p1hp > P1MAXIMUM_HP)
	{
		//HPを最大値にする。
		m_p1hp = P1MAXIMUM_HP;
	}*/

	Vector3 p1scale = Vector3::One;
	Vector3 p2scale = Vector3::One;
	Vector3 p3scale = Vector3::One;
	Vector3 p4scale = Vector3::One;
	//現HP/最大HPをHPバーのスケールにする。
	//int型同士の計算だと、小数点以下切り捨てになるので。
	//float型に変換して計算を行う。
	p1scale.x = float(m_p1hp) / float(P1MAXIMUM_HP);
	p2scale.x = float(m_p2hp) / float(P2MAXIMUM_HP);
	p3scale.x = float(m_p3hp) / float(P3MAXIMUM_HP);
	p4scale.x = float(m_p4hp) / float(P4MAXIMUM_HP);
	//スケールを設定。
	m_sushihpbar.SetScale(p1scale);
	m_sushihpbar2.SetScale(p2scale);
	m_sushihpbar3.SetScale(p3scale);
	m_sushihpbar4.SetScale(p4scale);


	m_sushihpbar.SetPivot(Vector2(0.0f, 0.5f));
	m_sushihpbar2.SetPivot(Vector2(0.0f, 0.5f));
	m_sushihpbar3.SetPivot(Vector2(0.0f, 0.5f));
	m_sushihpbar4.SetPivot(Vector2(0.0f, 0.5f));
	//更新処理。
	m_sushihpbar.Update();
	m_sushihpbar2.Update();
	m_sushihpbar3.Update();
	m_sushihpbar4.Update();
}

void GameUI::Update()
{

	GameHP();
	Timer();
	if (m_sokomade == true)
	{
		sokomade_timer += g_gameTime->GetFrameDeltaTime();
	}
	if (m_sokomade == true && sokomade_timer >= 2.0f)
	{
		FindGO<Game>("game")->SetGameDelete(true);
	}

	//醤油差しの画像切り替え
	if (m_player1->GetSoySauceCount() > 0)
	{
		m_soysaucecountstate = true;
	}
	if (m_player1->GetSoySauceCount() <= 0)
	{
		m_soysaucecountstate = false;
	}

	if (m_player2->GetSoySauceCount() > 0)
	{
		m_soysaucecountstate2 = true;
	}
	if (m_player2->GetSoySauceCount() <= 0)
	{
		m_soysaucecountstate2 = false;
	}

	if (m_player3->GetSoySauceCount() > 0)
	{
		m_soysaucecountstate3 = true;
	}
	if (m_player3->GetSoySauceCount() <= 0)
	{
		m_soysaucecountstate3 = false;
	}

	if (m_player4->GetSoySauceCount() > 0)
	{
		m_soysaucecountstate4 = true;
	}
	if (m_player4->GetSoySauceCount() <= 0)
	{
		m_soysaucecountstate4 = false;
	}

}

void GameUI::Render(RenderContext& rc)
{
	//m_ui.Draw(rc);

	//m_spriteRender99.Draw(rc);
	m_spriteRendersamonhuda.Draw(rc);
	m_spriteRendermagurohuda.Draw(rc);
	m_spriteRendertamagohuda.Draw(rc);
	m_spriteRenderebihuda.Draw(rc);
	m_spriteRendertime.Draw(rc);

	if (m_soysaucecountstate == false)
	{
		m_syouyusasi_kara.Draw(rc);
	}
	if (m_soysaucecountstate == true)
	{
		m_syouyusasi.Draw(rc);
	}

	if (m_soysaucecountstate2 == false)
	{
		m_syouyusasi_kara2.Draw(rc);
	}
	if (m_soysaucecountstate2 == true)
	{
		m_syouyusasi2.Draw(rc);
	}

	if (m_soysaucecountstate3 == false)
	{
		m_syouyusasi_kara3.Draw(rc);
	}
	if (m_soysaucecountstate3 == true)
	{
		m_syouyusasi3.Draw(rc);
	}

	if (m_soysaucecountstate4 == false)
	{
		m_syouyusasi_kara4.Draw(rc);
	}
	if (m_soysaucecountstate4 == true)
	{
		m_syouyusasi4.Draw(rc);
	}

	m_sushihpbar_kuro.Draw(rc);
	m_sushihpbar_kuro2.Draw(rc);
	m_sushihpbar_kuro3.Draw(rc);
	m_sushihpbar_kuro4.Draw(rc);

	m_sushihpbar.Draw(rc);
	m_sushihpbar2.Draw(rc);
	m_sushihpbar3.Draw(rc);
	m_sushihpbar4.Draw(rc);

	m_sushihpbarwaku.Draw(rc);
	m_sushihpbarwaku2.Draw(rc);
	m_sushihpbarwaku3.Draw(rc);
	m_sushihpbarwaku4.Draw(rc);

	m_fontRender.Draw(rc);
	if (m_sokomade == true)
	{
		m_spriteRendersokomade.Draw(rc);
	}
	if (m_countstate == 0)
	{
		m_hajime.Draw(rc);
	}
	if (m_countstate == 1)
	{
		m_count1.Draw(rc);
	}
	if (m_countstate == 2)
	{
		m_count2.Draw(rc);
	}
	if (m_countstate == 3)
	{
		m_count3.Draw(rc);
	}

	if (m_player1->GetPlayerHP() <= 0)
	{
		m_spriteRenderslash[0].Draw(rc);
	}
	if (m_player2->GetPlayer2HP() <= 0)
	{
		m_spriteRenderslash[1].Draw(rc);
	}
	if (m_player3->GetPlayer3HP() <= 0)
	{
		m_spriteRenderslash[2].Draw(rc);
	}
	if (m_player4->GetPlayer4HP() <= 0)
	{
		m_spriteRenderslash[3].Draw(rc);
	}
}
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
	//�ݖ������̊O���̓����x�̐ݒ�
	Vector4 Transparent = { 1.0f, 1.0f, 1.0f, 0.5f };
	//�ő�HP�B
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
	m_count1.Init("Assets/sprite/1.dds", 1600.0f, 900.0f);
	m_count2.Init("Assets/sprite/2.dds", 1600.0f, 900.0f);
	m_count3.Init("Assets/sprite/3.dds", 1600.0f, 900.0f);

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

	m_spriteRendersokomade.Init("Assets/sprite/sokomade.dds", 1600.0f, 900.0f);
	SoyCT();
	SushiHPBar();

	m_spriteRender.Update();
	m_spriteRender2.Update();
	m_spriteRender3.Update();
	m_spriteRender4.Update();
	m_spriteRendersamonhuda.Update();
	m_spriteRendermagurohuda.Update();
	m_spriteRendertamagohuda.Update();
	m_spriteRenderebihuda.Update();
	m_spriteRendertime.Update();

	//�퓬�I��SE��ǂݍ��ށB
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
	//�ݖ�����
	m_spriteRender.Init("Assets/sprite/soysaucecontainer_1P.dds", 220.0f, 220.0f);
	m_spriteRender.SetPosition({ -450.0f,-350.0f,0.0f });
	m_spriteRender2.Init("Assets/sprite/soysaucecontainer_2P.dds", 220.0f, 220.0f);
	m_spriteRender2.SetPosition({ -55.0f,-350.0f,0.0f });
	m_spriteRender3.Init("Assets/sprite/soysaucecontainer_3P.dds", 220.0f, 220.0f);
	m_spriteRender3.SetPosition({ 345.0f,-350.0f,0.0f });
	m_spriteRender4.Init("Assets/sprite/soysaucecontainer_4P.dds", 220.0f, 220.0f);
	m_spriteRender4.SetPosition({ 735.0f,-350.0f,0.0f });
	//�ݖ��������΁[
	m_soyct.Init("Assets/sprite/soysaucecontainercover.dds", 220.0f, 220.0f);
	m_soyct.SetPosition({ -450.0f,-350.0f,0.0f });
	m_soyct.SetMulColor({ Transparent });
	m_soyct2.Init("Assets/sprite/soysaucecontainercover.dds", 220.0f, 220.0f);
	m_soyct2.SetPosition({ -55.0f,-350.0f,0.0f });
	m_soyct2.SetMulColor({ Transparent });
	m_soyct3.Init("Assets/sprite/soysaucecontainercover.dds", 220.0f, 220.0f);
	m_soyct3.SetPosition({ 345.0f,-350.0f,0.0f });
	m_soyct3.SetMulColor({ Transparent });
	m_soyct4.Init("Assets/sprite/soysaucecontainercover.dds", 220.0f, 220.0f);
	m_soyct4.SetPosition({ 735.0f,-350.0f,0.0f });
	m_soyct4.SetMulColor({ Transparent });
	//�X�V����
	m_soyct.Update();
	m_soyct2.Update();
	m_soyct3.Update();
	m_soyct4.Update();
}

void GameUI::SushiHPBar()
{
	m_sushihpbar.Init("Assets/sprite/hpbar.DDS", 150.0f, 90.0f);
	m_sushihpbarwaku.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	m_sushihpbar2.Init("Assets/sprite/hpbar.DDS", 150.0f, 90.0f);
	m_sushihpbarwaku2.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	m_sushihpbar3.Init("Assets/sprite/hpbar.DDS", 150.0f, 90.0f);
	m_sushihpbarwaku3.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	m_sushihpbar4.Init("Assets/sprite/hpbar.DDS", 150.0f, 90.0f);
	m_sushihpbarwaku4.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	//HP�o�[�̃s�{�b�g��ݒ�B
	//m_sushihpbar.SetPivot(Vector2(0.5f, 0.5f));
	m_sushihpbar.SetPosition(Vector3(-660.0f, -363.0f, 0.0f));
	m_sushihpbarwaku.SetPosition(Vector3(-585.0f, -355.0f, 0.0f));
	m_sushihpbar2.SetPosition(Vector3(-260.0f, -363.0f, 0.0f));
	m_sushihpbarwaku2.SetPosition(Vector3(-185.0f, -355.0f, 0.0f));
	m_sushihpbar3.SetPosition(Vector3(140.0f, -363.0f, 0.0f));
	m_sushihpbarwaku3.SetPosition(Vector3(215.0f, -355.0f, 0.0f));
	m_sushihpbar4.SetPosition(Vector3(530.0f, -363.0f, 0.0f));
	m_sushihpbarwaku4.SetPosition(Vector3(605.0f, -355.0f, 0.0f));
	m_sushihpbar.Update();
	m_sushihpbarwaku.Update();
	m_sushihpbar2.Update();
	m_sushihpbarwaku2.Update();
	m_sushihpbar3.Update();
	m_sushihpbarwaku3.Update();
	m_sushihpbar4.Update();
	m_sushihpbarwaku4.Update();
}

void GameUI::GameBGM()
{
	//�Q�[����BGM��ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/game_bgm.wav");
	//�Q�[����BGM���Đ�����B
	gameBGM = NewGO<SoundSource>(0);
	gameBGM->Init(0);
	gameBGM->Play(true);
}

void GameUI::Timer()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%3d", int(game_timer));

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(-95.0f, 500.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
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

	//�^�C�}�[��0�ɂȂ�����Q�[�����폜
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
	//HP��0��茸���Ă�����B
	if (m_p1hp < 0)
	{
		//HP��0�ɂ���B
		m_p1hp = 0;
	}
	//HP���ő�l�𒴂��Ă�����B
	else if (m_p1hp > P1MAXIMUM_HP)
	{
		//HP���ő�l�ɂ���B
		m_p1hp = P1MAXIMUM_HP;
	}*/

	Vector3 p1scale = Vector3::One;
	Vector3 p2scale = Vector3::One;
	Vector3 p3scale = Vector3::One;
	Vector3 p4scale = Vector3::One;
	//��HP/�ő�HP��HP�o�[�̃X�P�[���ɂ���B
	//int�^���m�̌v�Z���ƁA�����_�ȉ��؂�̂ĂɂȂ�̂ŁB
	//float�^�ɕϊ����Čv�Z���s���B
	p1scale.x = float(m_p1hp) / float(P1MAXIMUM_HP);
	p2scale.x = float(m_p2hp) / float(P2MAXIMUM_HP);
	p3scale.x = float(m_p3hp) / float(P3MAXIMUM_HP);
	p4scale.x = float(m_p4hp) / float(P4MAXIMUM_HP);
	//�X�P�[����ݒ�B
	m_sushihpbar.SetScale(p1scale);
	m_sushihpbar2.SetScale(p2scale);
	m_sushihpbar3.SetScale(p3scale);
	m_sushihpbar4.SetScale(p4scale);


	m_sushihpbar.SetPivot(Vector2(0.0f, 0.5f));
	m_sushihpbar2.SetPivot(Vector2(0.0f, 0.5f));
	m_sushihpbar3.SetPivot(Vector2(0.0f, 0.5f));
	m_sushihpbar4.SetPivot(Vector2(0.0f, 0.5f));
	//�X�V�����B
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
}

void GameUI::Render(RenderContext& rc)
{
	//m_ui.Draw(rc);

	//m_spriteRender99.Draw(rc);
	m_spriteRendersamonhuda.Draw(rc);
	m_spriteRendermagurohuda.Draw(rc);
	m_spriteRendertamagohuda.Draw(rc);
	m_spriteRenderebihuda.Draw(rc);
	m_spriteRender.Draw(rc);                 //�`��
	m_spriteRender2.Draw(rc);
	m_spriteRender3.Draw(rc);
	m_spriteRender4.Draw(rc);
	m_spriteRendertime.Draw(rc);

	m_soyct.Draw(rc);
	m_soyct2.Draw(rc);
	m_soyct3.Draw(rc);
	m_soyct4.Draw(rc);

	m_sushihpbar.Draw(rc);
	m_sushihpbarwaku.Draw(rc);
	m_sushihpbar2.Draw(rc);
	m_sushihpbarwaku2.Draw(rc);
	m_sushihpbar3.Draw(rc);
	m_sushihpbarwaku3.Draw(rc);
	m_sushihpbar4.Draw(rc);
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
}
#include "stdafx.h"
#include "GameUI.h"
#include "Game.h"

namespace
{
	//�ݖ������̊O���̓����x�̐ݒ�
	Vector4 Transparent = { 1.0f, 1.0f, 1.0f, 0.5f };
	//�ő�HP�B
	const int MAXIMUM_HP = 50;
}

bool GameUI::Start()
{
	m_ui.Init("Assets/sprite/ComprehensiveUI.dds", 1600.0f, 900.0f);
	m_spriteRender99.Init("Assets/sprite/game4P.dds", 1600.0f, 900.0f);
	SoyCT();
	SushiHPBar();

	m_spriteRender.Update();
	m_spriteRender2.Update();
	m_spriteRender3.Update();
	m_spriteRender4.Update();
	m_spriteRender99.Update();

	return true;
}

void GameUI::SoyCT()
{
	//�ݖ�����
	m_spriteRender.Init("Assets/sprite/soysaucecontainer_1P.dds", 200.0f, 200.0f);
	m_spriteRender.SetPosition({ -450.0f,-340.0f,0.0f });
	m_spriteRender2.Init("Assets/sprite/soysaucecontainer_2P.dds", 200.0f, 200.0f);
	m_spriteRender2.SetPosition({ -55.0f,-340.0f,0.0f });
	m_spriteRender3.Init("Assets/sprite/soysaucecontainer_3P.dds", 200.0f, 200.0f);
	m_spriteRender3.SetPosition({ 345.0f,-340.0f,0.0f });
	m_spriteRender4.Init("Assets/sprite/soysaucecontainer_4P.dds", 200.0f, 200.0f);
	m_spriteRender4.SetPosition({ 730.0f,-340.0f,0.0f });
	//�ݖ��������΁[
	m_soyct.Init("Assets/sprite/soysaucecontainercover.dds", 200.0f, 200.0f);
	m_soyct.SetPosition({ -450.0f,-340.0f,0.0f });
	m_soyct.SetMulColor({ Transparent });
	m_soyct2.Init("Assets/sprite/soysaucecontainercover.dds", 200.0f, 200.0f);
	m_soyct2.SetPosition({ -55.0f,-340.0f,0.0f });
	m_soyct2.SetMulColor({ Transparent });
	m_soyct3.Init("Assets/sprite/soysaucecontainercover.dds", 200.0f, 200.0f);
	m_soyct3.SetPosition({ 345.0f,-340.0f,0.0f });
	m_soyct3.SetMulColor({ Transparent });
	m_soyct4.Init("Assets/sprite/soysaucecontainercover.dds", 200.0f, 200.0f);
	m_soyct4.SetPosition({ 730.0f,-340.0f,0.0f });
	m_soyct4.SetMulColor({ Transparent });
	//�X�V����
	m_soyct.Update();
	m_soyct2.Update();
	m_soyct3.Update();
	m_soyct4.Update();
}

void GameUI::SushiHPBar()
{
	m_sushihpbar.Init("Assets/sprite/baran.DDS", 180.0f, 80.0f);
	//HP�o�[�̃s�{�b�g��ݒ�B
	//m_sushihpbar.SetPivot(Vector2(0.5f, 0.5f));
	m_sushihpbar.SetPosition(Vector3(-670.0f, -350.0f, 0.0f));
	m_sushihpbar.Update();
}

void GameUI::GameHP()
{
	//A�{�^������������,�̗͉񕜁B
	if (g_pad[0]->IsPress(enButtonA))
	{
		m_hp += 1;
	}
	//B�{�^������������A�̗͂����炷�B
	else if (g_pad[0]->IsPress(enButtonB))
	{
		m_hp -= 1;
	}

	//HP��0��茸���Ă�����B
	if (m_hp < 0)
	{
		//HP��0�ɂ���B
		m_hp = 0;
	}
	//HP���ő�l�𒴂��Ă�����B
	else if (m_hp > MAXIMUM_HP)
	{
		//HP���ő�l�ɂ���B
		m_hp = MAXIMUM_HP;
	}

	Vector3 scale = Vector3::One;
	//��HP/�ő�HP��HP�o�[�̃X�P�[���ɂ���B
	//int�^���m�̌v�Z���ƁA�����_�ȉ��؂�̂ĂɂȂ�̂ŁB
	//float�^�ɕϊ����Čv�Z���s���B
	scale.x = float(m_hp) / float(MAXIMUM_HP);
	//�X�P�[����ݒ�B
	//m_sushihpbar.SetScale(scale);

	m_sushihpbar.SetPivot(Vector2(0.0f, 0.5f));
	m_sushihpbar.SetLimitedX(0.5f);
	m_sushihpbar.SetIsDisplayRestrictionLeftSide(0.5f);
	//�X�V�����B
	m_sushihpbar.Update();
}

void GameUI::Update()
{
	int b = m_hp;
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", b);

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf1);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(1.5f);
	//���F�ɐݒ�
	m_fontRender.SetColor(g_vec4White);
	GameHP();
}

void GameUI::Render(RenderContext& rc)
{
	m_ui.Draw(rc);

	//m_spriteRender99.Draw(rc);
	m_spriteRender.Draw(rc);                 //�`��
	m_spriteRender2.Draw(rc);
	m_spriteRender3.Draw(rc);
	m_spriteRender4.Draw(rc);

	m_soyct.Draw(rc);
	m_soyct2.Draw(rc);
	m_soyct3.Draw(rc);
	m_soyct4.Draw(rc);

	m_sushihpbar.Draw(rc);
	m_fontRender.Draw(rc);
}
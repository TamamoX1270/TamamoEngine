#include "stdafx.h"
#include "Game.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "GameCamera2P.h"
#include "GameCamera3P.h"

namespace
{
	//�ő�HP�B
	const int MAXIMUM_HP = 200;
}

bool Game::Start()
{
	//m_spriteRender.Init("Assets/sprite/gameclear.dds", 1600.0f, 900.0f);
	//m_spriteRender.Init("Assets/sprite/hpbar.DDS", 1024.0f, 512.0f);
	m_spriteRender.Init("Assets/sprite/game4P.dds", 1600.0f, 900.0f);
	//�v���C���[�I�u�W�F�N�g���쐬����B
	m_player = NewGO<Player1>(0, "player1");
	m_player2 = NewGO<Player2>(0, "player2");
	//m_player3 = NewGO<Player3>(0, "player3");
	//m_player4 = NewGO<Player4>(0, "player4");
	//�w�i�I�u�W�F�N�g���쐬����B
	m_backGround = NewGO<BackGround>(0, "background");

	//m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//m_gameCamera3 = NewGO<GameCamera3P>(0, "gamecamera3");
	m_gameCamera2 = NewGO<GameCamera2P>(0, "gamecamera2");
	
	
	/*//HP�o�[�̃s�{�b�g��ݒ�B
	m_spriteRender.SetPivot(Vector2(0.0f, 0.5f));
	m_spriteRender.SetPosition(Vector3(-550.0f, 465.0f, 0.0f));*/
	m_spriteRender.Update();

	return true;
}

Game::Game()
{
/*	//A�{�^������������,�̗͉񕜁B
	if (g_pad[0]->IsPress(enButtonRight))
	{
		m_hp += 1;
	}
	//B�{�^������������A�̗͂����炷�B
	else if (g_pad[0]->IsPress(enButtonLeft))
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
	//m_spriteRender.SetScale(scale);

	//�X�V�����B
	m_spriteRender.Update();*/
}

void Game::Update()
{
	int b = 4;
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
	//(*��֥)/ʰ�
	/*
	// ���X�e�B�b�N(�L�[�{�[�h�FWASD)�ŕ��s�ړ��B
	m_pointligpos.x += g_pad[0]->GetLStickXF();
	m_pointligpos.z += g_pad[0]->GetLStickYF();
	*/
	//m_pointligpos.y = 50.0f;
	m_pointligpos.x = 5000.0f;
	g_directionLig.SetPointPos(m_pointligpos);

	m_spPosition.y = 50.0f;
	m_spPosition.x = 5000.0f;
	//���̃A�i���O�X�e�B�b�N�œ������B
	//m_spPosition.x -= g_pad[0]->GetLStickXF();
	/*
	if (g_pad[0]->IsPress(enButtonB)) {
		//B�{�^�����ꏏ�ɉ�����Ă�����Y�������ɓ������B
		m_spPosition.y += g_pad[0]->GetLStickYF();
	}
	else {
		//Z�������ɓ������B
		m_spPosition.z -= g_pad[0]->GetLStickYF();
	}
	*/
	g_directionLig.SetSpotPos(m_spPosition);//�X�|�b�g���C�g�̈ʒu��ݒ�
	
	/*
	//���������͎΂߉��ɂ���B
	m_spDirection.x = 1.0f;
	m_spDirection.y = -1.0f;
	m_spDirection.z = 1.0f;
	*/

	//�f�B���N�V�������C�g�̓���������ƃJ���[���Z�b�g�ł����Ⴂ�܂�
	//g_directionLig.SetLigDirection({ 0.0f,1.0f,-1.0f });


	/*if (g_pad[0]->IsPress(enButtonB))
	{
		m_directionligColor.x += 0.1f;
	}
	if (g_pad[0]->IsPress(enButtonA))
	{
		m_directionligColor.y += 0.1f;
		m_directionligColor.z += 0.1f;
	}
	g_directionLig.SetLigColor({ m_directionligColor });*/
	g_directionLig.SetLigColor({0.5f,0.5f,0.5f});
}

void Game::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);                 //�^�C�g���̕`��
	//m_fontRender.Draw(rc);
}
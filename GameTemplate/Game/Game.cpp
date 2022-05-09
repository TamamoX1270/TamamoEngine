#include "stdafx.h"
#include "Game.h"
#include "GameUI.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "GameCamera2P.h"
#include "GameCamera3P.h"
#include "SoySauce.h"
#include "SoySauceBullet.h"
#include "SideWall.h"
#include "Title.h"
#include "Result.h"
#include"SpecialCamera.h"

bool Game::Start()
{
	//�v���C���[�I�u�W�F�N�g���쐬����B
	m_player = NewGO<Player1>(0, "player1");
	m_player2 = NewGO<Player2>(0, "player2");
	//m_player3 = NewGO<Player3>(0, "player3");
	//m_player4 = NewGO<Player4>(0, "player4");

	//GameUI�̐���
	m_gamingshigureui = NewGO<GameUI>(0, "gameui");
	//�ݖ��I�u�W�F�N�g�𐶐�����B
	m_soysauce = NewGO<SoySauce>(0, "soysauce");
	//���E�̕ǃI�u�W�F�N�g�𐶐�����B
	m_sidewall = NewGO<SideWall>(0, "sidewall");
	//�w�i�I�u�W�F�N�g���쐬����B
	m_backGround = NewGO<BackGround>(0, "background");

	sscamera = NewGO<SpecialCamera>(0, "specialcamera");

	//m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//m_gameCamera3 = NewGO<GameCamera3P>(0, "gamecamera3");
	m_gameCamera2 = NewGO<GameCamera2P>(0, "gamecamera2");

	return true;
}

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_gameCamera);
	DeleteGO(m_gameCamera2);
	DeleteGO(sscamera);
	DeleteGO(m_backGround);
	DeleteGO(m_sidewall);
	DeleteGO(m_gamingshigureui);
}
void Game::Update()
{
	GameDelete();
	Camera();

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

	m_pointligpos.y = 0.0f;
	m_pointligpos.x = 20000.0f;
	g_directionLig.SetPointPos(m_pointligpos);

	m_spPosition.x = 0.0f;
	m_spPosition.y = 250.0f;
	m_spPosition.z = 100.0f;

	//m_spDirection = { 1.0f,0.0f,1.0f };
	//m_spDirection.Normalize();

	//g_directionLig.SetSpotAngle(100.0f);
	//g_directionLig.SetSpotRange(100.0f);
	//g_directionLig.SetSpotDir({ m_spDirection });
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
//	g_directionLig.SetLigColor({0.5f,0.5f,0.5f});
}

void Game::Camera()
{
	//�Q�[���f���[�g�X�e�[�g��true����Ȃ���
	if (m_gamedelete == true)
	{
		return;
	}

		if (g_pad[0]->IsPress(enButtonUp)) {
			m_cameraState = 1;
		}
		else {
			m_cameraState = 0;
		}

		switch (m_cameraState) {
		case 0:
			m_gameCamera2 = NewGO<GameCamera2P>(0, "gamecamera2");
			break;
		case 1:
			sscamera = NewGO<SpecialCamera>(0, "specialcamera");
			break;
		}
}

void Game::GameDelete()
{
	//�Q�[���f���[�g�X�e�[�g��true�̎�
	if (m_gamedelete == true)
	{
		NewGO<Result>(0, "result");
	const auto& soysauces = FindGOs<SoySauce>("soysauce");
	//�z��̌����擾����
	int number = soysauces.size();
	for (int i = 0; i < number; i++)
	{
		DeleteGO(soysauces[i]);
	}
	const auto& soysaucebullets = FindGOs<SoySauceBullet>("soysaucebullet");
	//�z��̌����擾����
	int number2 = soysaucebullets.size();
	for (int s = 0; s < number2; s++)
	{
		DeleteGO(soysaucebullets[s]);
	}
	const auto& gamecamera2 = FindGOs<GameCamera2P>("gamecamera2");
	//�z��̌����擾����
	int number3 = gamecamera2.size();
	for (int c = 0; c < number3; c++)
	{
		DeleteGO(gamecamera2[c]);
	}
	DeleteGO(m_player);
	DeleteGO(m_player2);
	DeleteGO(this);
	}
	//�Q�[���f���[�g�X�e�[�g��true����Ȃ���
	else
	{
		if (FindGO<Player1>("player1")->GetPlayerHP() <= 0)
		{
			m_gamedelete = true;
		}
		else if (FindGO<Player2>("player2")->GetPlayer2HP() <= 0)
		{
			m_gamedelete = true;
		}
	}
}
void Game::Render(RenderContext& rc)
{
	//m_fontRender.Draw(rc);
}
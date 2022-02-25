#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"

bool Game::Start()
{
	//�v���C���[�I�u�W�F�N�g���쐬����B
	m_player = NewGO<Player>(0, "player");
	//�w�i�I�u�W�F�N�g���쐬����B
	m_backGround = NewGO<BackGround>(0, "background");

	return true;
}
void Game::Update()
{
	//(*��֥)/ʰ�
	/*
	// ���X�e�B�b�N(�L�[�{�[�h�FWASD)�ŕ��s�ړ��B
	m_pointligpos.x += g_pad[0]->GetLStickXF();
	m_pointligpos.z += g_pad[0]->GetLStickYF();
	*/
	m_pointligpos.y = 50.0f;
	
	g_directionLig.SetPointPos(m_pointligpos);

	m_spPosition.y = 50.0f;
	//���̃A�i���O�X�e�B�b�N�œ������B
	m_spPosition.x -= g_pad[0]->GetLStickXF();

	if (g_pad[0]->IsPress(enButtonB)) {
		//B�{�^�����ꏏ�ɉ�����Ă�����Y�������ɓ������B
		m_spPosition.y += g_pad[0]->GetLStickYF();
	}
	else {
		//Z�������ɓ������B
		m_spPosition.z -= g_pad[0]->GetLStickYF();
	}
	g_directionLig.SetSpotPos(m_spPosition);//�X�|�b�g���C�g�̈ʒu��ݒ�
	
	//���������͎΂߉��ɂ���B
	m_spDirection.x = 1.0f;
	m_spDirection.y = -1.0f;
	m_spDirection.z = 1.0f;
	
	//�f�B���N�V�������C�g�̓���������ƃJ���[���Z�b�g�ł����Ⴂ�܂�
	//g_directionLig.SetLigDirection({ -1.0f,-1.0f,-1.0f });
	//g_directionLig.SetLigColor({0.5f,0.5f,0.5f});
}
void Game::Render(RenderContext& rc)
{
}
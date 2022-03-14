#include "stdafx.h"
#include "GameCamera.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(0.0f, 180.0f, -300.0f);

	//�v���C���[�̃C���X�^���X��T���B
	m_player1 = FindGO<Player1>("player1");
	m_player2 = FindGO<Player2>("player2");
	m_player3 = FindGO<Player3>("player3");
	m_player4 = FindGO<Player4>("player4");

	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ肷��B
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(60000.0f);

	return true;
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{
	//�J�������X�V�B
	//�����_���v�Z����B
	Vector3 target;

	//4�l�̃v���C���[�̈ʒu��z��ɓ����B	
	float m_getPosition[4];
	m_getPosition[0] = m_player1->GetPlayer1Position().x;
	m_getPosition[1] = m_player2->GetPlayer2Position().x;
	m_getPosition[2] = m_player3->GetPlayer3Position().x;
	m_getPosition[3] = m_player4->GetPlayer4Position().x;

	//��ԉE�̂��T���B
	m_max = m_getPosition[0];

	for (int i = 0; i < 4; i++) {
		if (m_max <= m_getPosition[i]) {
			m_max = m_getPosition[i];
		}
	}

	//��ԍ��̂��T���B
	m_min = m_getPosition[0];

	for (int i = 0; i < 4; i++) {
		if (m_min >= m_getPosition[i]) {
			m_min = m_getPosition[i];
		}
	}

	//���̒��S�𒍎��_�ɂ���B
	target.x = (m_max + m_min) / 2;


	//�v���C���̑������炿����Ə�𒍎��_�Ƃ���B
	//�v���C���[�̋����ɉ����ď�����ɏオ��B
	target.y = (m_max - m_min) * 0.05f + 100.0f;

	//��ԍ��ƈ�ԉE�̃v���C���[�̋����ɉ����ăJ�����������B
	target.z = (m_max - m_min) * -0.6f;

	//����B
	if (target.z <= -750.0f) {
		target.z = -749.0f;
	}
	else if (target.z >= 30.0f) {
		target.z = 29.0f;
	}

	//���_���v�Z����B
	Vector3 pos = target + m_toCameraPos;

	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//�J�����̍X�V�B
	g_camera3D->Update();
}
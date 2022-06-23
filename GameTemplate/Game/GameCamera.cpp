#include "stdafx.h"
#include "GameCamera.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"

namespace
{
	Vector3 TO_CAMERA_POS = { 0.0f,0.0f,-200.0f };
	float PLAYER_HEIGHT = 100.0f;
}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�B
	m_toCameraPos.Set(TO_CAMERA_POS);

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

void GameCamera::Update()
{
	//4�l�̃v���C���[�̈ʒu��z��ɓ����B
	//�����Ă���v���C���[�𐔂���B
	float m_getPosition[4];
	int numActivePlayer = 0;
	if (m_player1->GetPlayerHP() >= 0) {
		m_getPosition[numActivePlayer] = m_player1->GetPlayer1Position().x;
		numActivePlayer++;
	}
	if (m_player2->GetPlayer2HP() >= 0) {
		m_getPosition[numActivePlayer] = m_player2->GetPlayer2Position().x;
		numActivePlayer++;
	}
	if (m_player3->GetPlayer3HP() >= 0) {
		m_getPosition[numActivePlayer] = m_player3->GetPlayer3Position().x;
		numActivePlayer++;
	}
	if (m_player4->GetPlayer4HP() >= 0) {
		m_getPosition[numActivePlayer] = m_player4->GetPlayer4Position().x;
		numActivePlayer++;
	}

	//��ԉE��player��T���B
	m_xPosMax = m_getPosition[0];

	for (int i = 0; i < numActivePlayer; i++) {
		if (m_xPosMax <= m_getPosition[i]) {
			m_xPosMax = m_getPosition[i];
		}
	}

	//��ԍ���pleyer��T���B
	m_xPosMin = m_getPosition[0];

	for (int i = 0; i < numActivePlayer; i++) {
		if (m_xPosMin >= m_getPosition[i]) {
			m_xPosMin = m_getPosition[i];
		}
	}

	//���̒��S�𒍎��_�ɂ���B
	target.x = (m_xPosMax + m_xPosMin) / 2;


	//�v���C���[�̓���𒍎��_�Ƃ���B
	//�v���C���[�̋����ɉ����ď�����ɏオ��B
	target.y = (m_xPosMax - m_xPosMin) * 0.05f + PLAYER_HEIGHT;

	//��ԍ��ƈ�ԉE�̃v���C���[�̋����ɉ����ăJ�����������B
	target.z = (m_xPosMax - m_xPosMin) * -0.6f;

	//�J�����̈����̏���B
	if (target.z <= -750.0f) {
		target.z = -749.0f;
	}

	//���_���v�Z����B
	Vector3 CameraPos = target + m_toCameraPos;

	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(CameraPos);

	//�J�����̍X�V�B
	g_camera3D->Update();
}
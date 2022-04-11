#include "stdafx.h"
#include "Player4.h"
#include "Game.h"

bool Player4::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/purototype/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	//���f���̓ǂݍ���
	m_player4.Init("Assets/purototype/sushi.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);
	//�L�����R��������������B
	m_characterController.Init(25.0f, 75.0f, { 0.0f, 0.0f, 0.0f });
	m_rotation.SetRotationDegX(-90.0f);

	//m_player4.SetPosition(500.0f, 0.0f, 500.0f);
	//m_player4.Update();
	return true;
}

void Player4::Update()
{
	//m_player4.Update();
	Move();
	AnimationState();
}

void Player4::Move()
{

	Vector3 moveSpeed;
	moveSpeed.x = g_pad[3]->GetLStickXF() * 120.0f;
	//moveSpeed.z = g_pad[1]->GetLStickYF() * 120.0f;

	/*
	m_player.UpdateWorldMatrix(
		m_characterController.GetPosition(),
		m_rotation,
		g_vec3One
	);
	*/


	/* ���X�e�B�b�N(�L�[�{�[�h�FWASD)�ŕ��s�ړ��B
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.y += g_pad[0]->GetLStickYF();

	// �E�X�e�B�b�N(�L�[�{�[�h�F�㉺���E)�ŉ�]�B
	m_rotation.AddRotationY(g_pad[0]->GetRStickXF() * 0.05f);
	m_rotation.AddRotationX(g_pad[0]->GetRStickYF() * 0.05f);*/

	// �㉺���E�L�[(�L�[�{�[�h�F2, 4, 6, 8)�Ŋg��
	if (g_pad[3]->IsPress(enButtonUp)) {
		m_scale.y += 0.02f;
	}
	if (g_pad[3]->IsPress(enButtonDown)) {
		m_scale.y -= 0.02f;
	}
	if (g_pad[3]->IsPress(enButtonRight)) {
		m_scale.x += 0.02f;
	}
	if (g_pad[3]->IsPress(enButtonLeft)) {
		m_scale.x -= 0.02f;
	}

	/* �A�j���[�V�����̐؂�ւ��B
	if (g_pad[0]->IsPress(enButtonA)) {
		m_player.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
	if (g_pad[0]->IsPress(enButtonB)) {
		m_player.PlayAnimation(enAnimClip_Run, 0.2f);
	}
	*/


	// ���s�ړ�
	m_position.x += g_pad[3]->GetLStickXF();
	m_position.y += g_pad[3]->GetLStickYF();


	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_player4.SetScale(m_scale);
	m_player4.SetPosition(m_position);
	m_player4.SetRotation(m_rotation);
	m_player4.Update();
}

void Player4::AnimationState()
{
	/* �A�j���[�V�����̐؂�ւ��B
	if (g_pad[0]->IsPress(enButtonA)) {
		m_player.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
	if (g_pad[0]->IsPress(enButtonB)) {
		m_player.PlayAnimation(enAnimClip_Run, 0.2f);
	}*/

	if (g_pad[3]->GetLStickXF() || g_pad[3]->GetLStickYF()) {
		m_player4.PlayAnimation(enAnimClip_Run, 0.2f);
	}

	else {
		m_player4.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
}

void Player4::Render(RenderContext& rc)
{
	m_player4.Draw(rc);
}
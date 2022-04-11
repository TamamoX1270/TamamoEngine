#include "stdafx.h"
#include "Player2.h"
#include "Game.h"

#include "Player1.h"

bool Player2::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/purototype/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Hit].Load("Assets/purototype/hit.tka");
	m_animationClipArray[enAnimClip_Hit].SetLoopFlag(false);
	//���f���̓ǂݍ���
	m_player2.Init("Assets/purototype/sushi.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);
	//�L�����R��������������B
	m_characterController.Init(25.0f, 75.0f, { 0.0f, 0.0f, 0.0f });
	m_rotation.SetRotationDegX(-90.0f);

	//m_player2.SetPosition(500.0f, 0.0f, 500.0f);
	//m_player2.Update();
	return true;
}

void Player2::Update()
{
	if (shine == true) {
		AfterCatch();
		return;
	}


	int x;
	x = FindGO<Player1>("player1")->GetPlayer1State();
	if (x == 6) {
		//�G�̍U���p�̃R���W�����̔z����擾����B
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_catch");
		//�z���for���ŉ񂷁B
		for (auto collision : collisions)
		{
			//�R���W�����ƃL�����R�����Փ˂�����B
			if (collision->IsHit(m_characterController))
			{
				m_timer = 0.0f;
				shine = true;
			}
		}
	}


	Hit();
	Guard();

	//m_player2.Update();
	Move();
	AnimationState();
}

void Player2::Move()
{

	Vector3 moveSpeed;
	moveSpeed.x = g_pad[1]->GetLStickXF() * 120.0f;


	// ���s�ړ�
	m_position.x += g_pad[1]->GetLStickXF();
	m_position.y += g_pad[1]->GetLStickYF();


	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_player2.SetScale(m_scale);
	m_player2.SetPosition(m_position);
	m_player2.SetRotation(m_rotation);
	m_player2.Update();
}

void Player2::Guard()
{

	if (!g_pad[1]->IsPress(enButtonLB1) && m_playerState == 0) {
		aaa = 0;
		return;
	}

	aaa = 1;

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto col = NewGO<CollisionObject>(0);

		Vector3 collisionPosition = m_position;
		//���W���v���C���[�̏����O�ɐݒ肷��B
		collisionPosition.y += 60.0f;

		//�J�v�Z����̃R���W�������쐬����B
		col->CreateCapsule(collisionPosition,
			Quaternion::Identity,
			35.0f,
			75.0f
		);

		col->SetName("P2_Guard");

}

void Player2::AnimationState()
{

	if (g_pad[1]->GetLStickXF() || g_pad[1]->GetLStickYF()) {
		m_player2.PlayAnimation(enAnimClip_Run, 0.2f);
	}
	else if (m_playerState == 1) {
		m_player2.PlayAnimation(enAnimClip_Hit, 0.2f);
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
	}

	else {
		m_player2.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
}

void Player2::ManageState()
{
	switch (m_playerState)
	{
	case0:
		break;
	case1:
		break;
	case2:
		break;
	}
}

void Player2::Hit()
{
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", m_hp);

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf1);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(1.5f);
	//���F�ɐݒ�
	m_fontRender.SetColor(g_vec4White);

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_attack");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (aaa != 1) {
				m_hp += 1;
				m_playerState = 1;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player_attack2");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions2)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (aaa != 1) {
				m_hp += 1;
				m_playerState = 1;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player_attack3");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions3)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (aaa != 1) {
				m_hp += 1;
				m_playerState = 1;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player_cpunch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions4)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{

			//HP�����炷�B
			if (aaa != 1) {
				//m_hp += 1;
				m_playerState = 1;
			}
		}

	}
}

void Player2::AfterCatch()
{
	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player_cpunch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions4)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			
			//HP�����炷�B
			if (aaa != 1) {
				shine = false;
				m_hp += 1;
				m_playerState = 1;
			}
		}

	}

	m_timer += g_gameTime->GetFrameDeltaTime();
	if (m_timer >= 3.0f){
		shine = false;
	}
}

void Player2::Render(RenderContext& rc)
{
	m_player2.Draw(rc);
	m_fontRender.Draw(rc);
}
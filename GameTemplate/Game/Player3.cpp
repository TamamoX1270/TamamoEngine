#include "stdafx.h"
#include "Player3.h"
#include "Game.h"

#include "Player1.h"
#include "Player2.h"
#include "SoySauceBullet.h"

//CollisionObject���g�p���������߁A�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"

bool Player3::Start()
{
	//�A�j���[�V�����N���b�v�����[�h����B
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/purototype/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Guard].Load("Assets/purototype/guard.tka");
	m_animationClipArray[enAnimClip_Guard].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Punch].Load("Assets/purototype/punch.tka");
	m_animationClipArray[enAnimClip_Punch].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Jump].Load("Assets/purototype/jump.tka");
	m_animationClipArray[enAnimClip_Jump].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Hit].Load("Assets/purototype/hit.tka");
	m_animationClipArray[enAnimClip_Hit].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Catch].Load("Assets/purototype/catch.tka");
	m_animationClipArray[enAnimClip_Catch].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Punch2].Load("Assets/purototype/punch2.tka");
	m_animationClipArray[enAnimClip_Punch2].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Kick3].Load("Assets/purototype/kick3.tka");
	m_animationClipArray[enAnimClip_Kick3].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_CPunch].Load("Assets/purototype/cpunch.tka");
	m_animationClipArray[enAnimClip_CPunch].SetLoopFlag(false);

	//���f���̓ǂݍ���
	m_player3.Init("Assets/purototype/sushi.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);

	//�L�����R��������������B
	m_characterController.Init(25.0f, 75.0f, m_position);

	//�����ɉE����������B
	m_rotation.SetRotationDegX(-90.0f);
	m_rotation.AddRotationDegZ(180.0f);

	m_player3.SetPosition(m_position);
	m_player3.SetRotation(m_rotation);

	//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
	m_player3.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);

		});

	//Sword�v�{�[����ID(�ԍ�)���擾����B
	m_handBoneId = m_player3.FindBoneID(L"mixamorig:RightHandIndex1");
	m_handBoneIdCatch = m_player3.FindBoneID(L"mixamorig:RightHandIndex1");
	m_handBoneId2 = m_player3.FindBoneID(L"mixamorig:LeftHandIndex1");
	m_handBoneId3 = m_player3.FindBoneID(L"mixamorig:RightToeBase");
	m_handBoneIdCPunch = m_player3.FindBoneID(L"mixamorig:RightHandIndex1");


	return true;
}

void Player3::Update()
{
	if (shine == true) {
		AfterCatch();
		return;
	}

	p1_Catch = FindGO<Player1>("player1")->GetPlayer1State();
	p2_Catch = FindGO<Player2>("player2")->GetPlayer2State();

	int soysoysoysoy = m_soysaucecount;
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", soysoysoysoy);

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf1);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(-570.0f, -400.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(1.5f);
	//���F�ɐݒ�
	m_fontRender.SetColor(g_vec4White);

	if (p1_Catch != true && p2_Catch != true) {
		Move();
		Rotation();
	}

	AnimationState();
	ManageState();
	ManageJump();

	Hit1();
	Hit2();
	MakeGuardCollision();
	MakeCatchCollision();

	MakeCollision();
	MakeCollision2();
	MakeCollision3();
	CatchAttackCollision();

	m_player3.Update();
}

void Player3::Move()
{
	//�K�[�h���Ȃ�B
	if (m_playerState == 2) {
		//�����Ȃ��B
		return;
	}

	//�U�����Ȃ�B
	if (m_playerState == 3 || m_playerState == 7 || m_playerState == 8) {
		//�����Ȃ��B
		return;
	}

	//�͂ݒ��Ȃ�B
	if (m_playerState == 6) {
		//�����Ȃ��B
		return;
	}

	//�_���[�W��H����Ă���Ȃ�B
	if (m_playerState == 5) {
		//�����Ȃ��B
		return;
	}

	//Y�{�^���������ꂽ���ɏݖ��̃X�g�b�N���P�ȏ�Ȃ�
	if (g_pad[2]->IsTrigger(enButtonY) && m_soysaucecount >= 1)
	{
		m_soysaucecount--;
		m_soysaucebullet = NewGO<SoySauceBullet>(0, "soysaucebullet");
		//bullet�̃��[�u�X�s�[�h�Ƀv���C���[�̑O�����̃x�N�g�������Ă��B
		m_soysaucebullet->m_moveSpeed = m_forward;
	}

	//�ړ��B
	moveSpeed.x = g_pad[2]->GetLStickXF() * 120.0f;

	//�L�����̓����蔻��̍X�V�B
	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());

	m_player3.SetScale(m_scale);
	m_player3.SetPosition(m_position);
}

void Player3::Rotation()
{
	//�K�[�h���Ȃ�B
	if (m_playerState == 2) {
		//������ς����Ȃ��B
		return;
	}

	//�U�����Ȃ�B
	if (m_playerState == 3 || m_playerState == 7 || m_playerState == 8) {
		//�����Ȃ��B
		return;
	}

	//�͂ݒ��Ȃ�B
	if (m_playerState == 6) {
		//�����Ȃ��B
		return;
	}

	//�_���[�W��H����Ă���Ȃ�B
	if (m_playerState == 5) {
		//�����Ȃ��B
		return;
	}

	//�X�e�B�b�N�����ɓ|���ƁB
	if (g_pad[2]->GetLStickXF() < 0) {
		m_charaRotState = 1;
	}

	//�X�e�B�b�N���E�ɓ|���ƁB
	else if (g_pad[2]->GetLStickXF() > 0) {
		m_charaRotState = 0;
	}

	//�X�e�[�g�ɂ���ăL�����̌�����ς���B
	switch (m_charaRotState) {
	case 0:
		m_rotation.SetRotationDegX(-90.0f);
		m_rotation.AddRotationDegZ(180.0f);
		//�v���C���[�̑O�����̃x�N�g����ݒ肷��B
		m_forward = Vector3(0.0f, -1.0f, 0.0f);
		//�x�N�g���ɃN�E�H�[�^�j�I����K�����ăv���C���[�̌����ɉ�]������
		m_rotation.Apply(m_forward);
		break;
	case 1:
		m_rotation.SetRotationDegX(-90.0f);
		m_rotation.AddRotationDegZ(-180.0f);
		//�v���C���[�̑O�����̃x�N�g����ݒ肷��B
		m_forward = Vector3(0.0f, -1.0f, 0.0f);
		//�x�N�g���ɃN�E�H�[�^�j�I����K�����ăv���C���[�̌����ɉ�]������
		m_rotation.Apply(m_forward);
		break;
	}

	m_player3.SetRotation(m_rotation);
}

void Player3::AnimationState()
{

	if (m_playerState == 4) {

		m_timer += g_gameTime->GetFrameDeltaTime();
		if (m_timer >= 1.5f) {
			m_playerState = 0;
		}
	}

	//�͂�
	if (g_pad[2]->IsTrigger(enButtonRB1) || g_pad[2]->IsTrigger(enButtonRB2)) {
		m_playerState = 6;
	}

	//�͂ݍU��
	if (p1_Catch == true || p2_Catch == true) {
		if (g_pad[2]->IsTrigger(enButtonB)) {
			m_playerState = 9;
		}
	}
	//�ʏ�U��
	else if (g_pad[2]->IsTrigger(enButtonB) && atkState == 2) {
		m_playerState = 8;
	}
	else if (g_pad[2]->IsTrigger(enButtonB) && atkState == 1) {
		m_playerState = 7;
	}
	else if (g_pad[2]->IsTrigger(enButtonB)) {
		m_timer = 0.0f;
		m_playerState = 3;
	}


	if (m_playerState != 3 && m_playerState != 4 && m_playerState != 5 && m_playerState != 6 && m_playerState != 7 && m_playerState != 8 && m_playerState != 9) {

		if (g_pad[2]->IsPress(enButtonLB1) || g_pad[2]->IsPress(enButtonLB2)) {
			m_playerState = 2;
		}

		else if (g_pad[2]->IsTrigger(enButtonX)) {
			m_timer = 0.0f;
			m_playerState = 4;
		}

		else if (g_pad[2]->GetLStickXF() || g_pad[2]->GetLStickYF()) {
			m_playerState = 1;
		}

		else if (!g_pad[2]->IsPressAnyKey()) {
			m_playerState = 0;
		}
	}
}

void Player3::ManageState()
{
	//�X�e�[�g�ɂ��A�j���[�V�����̊Ǘ��B
	switch (m_playerState)
	{
	case 0:
		m_player3.PlayAnimation(enAnimClip_Idle, 0.2f);
		m_isUnderAttack = false;
		m_catch = false;
		m_2 = false;
		m_3 = false;
		break;

	case 1:
		m_player3.PlayAnimation(enAnimClip_Run, 0.2f);
		break;

	case 2:
		m_player3.PlayAnimation(enAnimClip_Guard, 0.2f);
		m_catch = false;
		break;

	case 3:
		m_player3.PlayAnimation(enAnimClip_Punch, 0.2f);
		m_catch = false;
		if (m_player3.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 4:
		m_player3.PlayAnimation(enAnimClip_Jump, 0.2f);
		m_catch = false;
		moveSpeed.y -= 80.0f;
		if (m_player3.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;

	case 5:
		m_player3.PlayAnimation(enAnimClip_Hit, 0.2f);
		if (m_player3.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		m_catch = false;
		break;

	case 6:
		m_player3.PlayAnimation(enAnimClip_Catch, 0.2f);
		if (m_player3.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;

	case 7:
		m_player3.PlayAnimation(enAnimClip_Punch2, 0.2f);
		m_catch = false;
		if (m_player3.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 8:
		m_player3.PlayAnimation(enAnimClip_Kick3, 0.2f);
		m_catch = false;
		if (m_player3.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 9:
		m_player3.PlayAnimation(enAnimClip_CPunch, 0.2f);
		m_catch = false;
		if (m_player3.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;
	}
}

void Player3::ManageJump()
{
	//�W�����v�̎����]�[��
	if (g_pad[2]->IsTrigger(enButtonX)) {
		m_jumpState = 1;
		m_jumpTimer = 0.0f;
	}

	/*else {
		moveSpeed.y -= 80.0f;
		//80
	}*/


	if (m_jumpState == 1) {

		m_jumpTimer += g_gameTime->GetFrameDeltaTime();

		if (m_jumpTimer >= 0.48f) {
			m_jumpState = 2;
		}
	}

	if (m_jumpState == 2) {
		moveSpeed.y += 1200.0f;
		//1200
		m_jumpState = 0;
	}
}

void Player3::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//�L�[�̖��O���uattack_start�v�̎��B
	if (wcscmp(eventName, L"Punch_Start") == 0)
	{
		//�U�����ɂ���B
		m_isUnderAttack = true;
	}
	//�L�[�̖��O���uattack_end�v�̎��B
	else if (wcscmp(eventName, L"Punch_End") == 0)
	{
		//�U�����I���B
		m_isUnderAttack = false;
		atkState = 1;
	}

	//�L�[�̖��O���uattack_start�v�̎��B
	if (wcscmp(eventName, L"Catch_Start") == 0)
	{
		//�U�����ɂ���B
		m_catch = true;
	}
	//�L�[�̖��O���uattack_end�v�̎��B
	else if (wcscmp(eventName, L"Catch_End") == 0)
	{
		//�U�����I���B
		m_catch = false;
	}

	if (wcscmp(eventName, L"Punch2_Start") == 0)
	{
		//�U�����ɂ���B
		m_2 = true;
	}
	//�L�[�̖��O���uattack_end�v�̎��B
	else if (wcscmp(eventName, L"Punch2_End") == 0)
	{
		//�U�����I���B
		m_2 = false;
		atkState = 2;
	}

	if (wcscmp(eventName, L"Kick3_Start") == 0)
	{
		//�U�����ɂ���B
		m_3 = true;
	}
	//�L�[�̖��O���uattack_end�v�̎��B
	else if (wcscmp(eventName, L"Kick3_End") == 0)
	{
		//�U�����I���B
		m_3 = false;
	}

	if (wcscmp(eventName, L"CPunch_Start") == 0)
	{
		//�U�����ɂ���B
		m_cpunch = true;
	}
	//�L�[�̖��O���uattack_end�v�̎��B
	else if (wcscmp(eventName, L"CPunch_End") == 0)
	{
		//�U�����I���B
		m_cpunch = false;
	}
}

void Player3::MakeCollision()
{

	if (m_isUnderAttack == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player3_attack");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player3.GetBone(m_handBoneId)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player3::MakeCollision2()
{

	if (m_2 == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player3_attack2");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player3.GetBone(m_handBoneId2)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}


void Player3::MakeCollision3()
{

	if (m_3 == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player3_attack3");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player3.GetBone(m_handBoneId3)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}


void Player3::MakeGuardCollision()
{
	if (m_playerState != 2 && m_playerState != 5) {
		guard = false;
		return;
	}
	guard = true;

	//�R���W�����I�u�W�F�N�g���쐬����B
	auto collisionObject = NewGO<CollisionObject>(0);

	Vector3 collisionPosition = m_position;
	//���W���v���C���[�̏����O�ɐݒ肷��B
	collisionPosition.y += 60.0f;

	//�J�v�Z����̃R���W�������쐬����B
	collisionObject->CreateCapsule(collisionPosition,
		Quaternion::Identity,
		35.0f,
		75.0f
	);

	collisionObject->SetName("P3_Guard");
}

void Player3::Hit1()
{
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", m_hp);

	//�\������e�L�X�g��ݒ�B
	m_fontHPRender.SetText(wcsbuf1);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontHPRender.SetPosition(Vector3(50.0f, 0.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontHPRender.SetScale(1.5f);
	//���F�ɐݒ�
	m_fontHPRender.SetColor(g_vec4White);

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player1_attack");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions1)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player1_attack2");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions2)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player1_attack3");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions3)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player1_catch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions4)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			m_Catchtimer = 0.0f;
			shine = true;
		}
	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions5 = g_collisionObjectManager->FindCollisionObjects("player1_cpunch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions5)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{

			//HP�����炷�B
			if (guard != true) {
				//m_hp += 1;
				////////////////////////////////////////////////////
				///���������P���ׂ��_�I�I�I
				//////////////////////////////////////////////////// 
				m_playerState = 5;
			}
		}

	}

	//�ݖ��U���p�̃R���W�����̔z����擾����B
	const auto& collisions6 = g_collisionObjectManager->FindCollisionObjects("SoysauceAttack");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions6)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}
}

void Player3::Hit2()
{

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player2_attack");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions1)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player2_attack2");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions2)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player2_attack3");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions3)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player2_catch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions4)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			m_Catchtimer = 0.0f;
			shine = true;
		}
	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions5 = g_collisionObjectManager->FindCollisionObjects("player2_cpunch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions5)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{

			//HP�����炷�B
			if (guard != true) {
				//m_hp += 1;
				////////////////////////////////////////////////////
				///���������P���ׂ��_�I�I�I
				//////////////////////////////////////////////////// 
				m_playerState = 5;
			}
		}

	}

}

void Player3::AfterCatch()
{
	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player1_cpunch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions1)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{

			//HP�����炷�B
			if (guard != true) {
				shine = false;
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player2_cpunch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions2)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{

			//HP�����炷�B
			if (guard != true) {
				shine = false;
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	m_Catchtimer += g_gameTime->GetFrameDeltaTime();
	if (m_Catchtimer >= 3.0f) {
		shine = false;
	}
}

void Player3::MakeCatchCollision()
{
	if (m_catch == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player3_catch");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player3.GetBone(m_handBoneIdCatch)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player3::CatchAttackCollision()
{
	if (m_cpunch == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player3_cpunch");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player3.GetBone(m_handBoneIdCatch)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player3::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	m_fontHPRender.Draw(rc);
	m_player3.Draw(rc);
}
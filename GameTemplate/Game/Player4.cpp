#include "stdafx.h"
#include "Player4.h"
#include "Game.h"
#include "GameUI.h"

#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "SoySauceBullet.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "PlayerPoint.h"

//CollisionObject���g�p���������߁A�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"

//EffectEmitter���g�p���鎞�̓t�@�C�����C���N���[�h����K�v������B
#include "graphics/effect/EffectEmitter.h"


bool Player4::Start()
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
	m_animationClipArray[enAnimClip_FlyAway].Load("Assets/purototype/hardhit.tka");
	m_animationClipArray[enAnimClip_FlyAway].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_RiseUp].Load("Assets/purototype/riseup.tka");
	m_animationClipArray[enAnimClip_RiseUp].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Death].Load("Assets/purototype/death.tka");
	m_animationClipArray[enAnimClip_Death].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_RingOut].Load("Assets/purototype/ringout.tka");
	m_animationClipArray[enAnimClip_RingOut].SetLoopFlag(false);

	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/bigkome.efk");
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/smallkome.efk");

	//���f���̓ǂݍ���
	m_player4.Init("Assets/purototype/model4/ebi.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);

	m_position = Vector3(300.0f, 0.0f, 0.0f);
	m_playerpoint = FindGO<PlayerPoint>("playerpoint");

	//�L�����R��������������B
	m_characterController.Init(25.0f, 75.0f, m_position);

	//�����ɉE����������B
	m_rotation.SetRotationDegX(-90.0f);
	m_rotation.AddRotationDegZ(-180.0f);

	m_player4.SetPosition(m_position);
	m_player4.SetRotation(m_rotation);
	m_player4.Update();

	//�A�j���[�V�����C�x���g�p�̊֐���ݒ肷��B
	m_player4.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);

		});

	//Sword�v�{�[����ID(�ԍ�)���擾����B
	m_handBoneId = m_player4.FindBoneID(L"mixamorig:RightHandIndex1");
	m_handBoneIdCatch = m_player4.FindBoneID(L"mixamorig:RightHandIndex1");
	m_handBoneId2 = m_player4.FindBoneID(L"mixamorig:LeftHandIndex1");
	m_handBoneId3 = m_player4.FindBoneID(L"mixamorig:RightToeBase");
	m_handBoneIdCPunch = m_player4.FindBoneID(L"mixamorig:RightHandIndex1");

	//���ʉ���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/jump_2.wav");
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/punch_1.wav");
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/punch_2.wav");
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/punch_3.wav");
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/punch_suburi1.wav");
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/punch_suburi2.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/kick_suburi.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/syouyu_beam.wav");
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/soysauce_damage.wav");
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/syouyu_charge.wav");

	return true;
}

void Player4::Update()
{
	int soysoysoysoy = m_soysaucecount;
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%3d", soysoysoysoy);

	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf1);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(805.0f, -400.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(1.5f);
	//���F�ɐݒ�
	m_fontRender.SetColor(g_vec4White);
	m_player4.Update();
	//�Q�[���J�n�J�E���g�̎������Ȃ��悤�ɂ���B
	if (FindGO<GameUI>("gameui")->GetGameStart() == false)
	{
		return;
	}
	if (m_getsoyplayernumber == 1 && getsauce == 0) {
		m_effectEmitter = NewGO<EffectEmitter>(0);
		m_effectEmitter->Init(999);
		m_effectEmitter->SetScale({ 50.0f,50.0f,50.0f });
		m_effectEmitter->SetPosition(m_position);
		m_effectEmitter->Play();
		getsauce = 1;
	}
	if (getsauce == 1 && m_effectEmitter->IsPlay() == true) {
		m_effectEmitter->SetPosition(m_position);
		m_effectEmitter->Update();
		m_getsoyplayernumber = 0;
	}
	else {
		m_getsoyplayernumber = 0;
		getsauce = 0;
	}

	//�����O�A�E�g������B
	if (m_out == true) {
		m_player4.PlayAnimation(enAnimClip_RingOut, 0.2f);
		if (m_player4.IsPlayingAnimation() == false) {
			m_hp = -1;
		}
		m_characterController.RemoveRigidBoby();
		m_player4.Update();
		return;
	}

	else if (m_hp <= 0) {
		m_player4.PlayAnimation(enAnimClip_Death, 0.2f);
		if (m_player4.IsPlayingAnimation() == false) {
			m_hp = -1;
		}
		m_characterController.RemoveRigidBoby();
		m_player4.Update();
		return;
	}

	else if (m_owaowari == true) {
		m_player4.PlayAnimation(enAnimClip_Idle, 0.2f);
		m_player4.Update();
		return;
	}
	m_owaowari = FindGO<GameUI>("gameui")->GetSokomade();

	if (shine == true) {
		AfterCatch();
		return;
	}

	p1_Catch = FindGO<Player1>("player1")->GetPlayer1State();
	p2_Catch = FindGO<Player2>("player2")->GetPlayer2State();
	p3_Catch = FindGO<Player3>("player3")->GetPlayer3State();


	if (p1_Catch != true && p2_Catch != true && p3_Catch != true) {
		Move();
		Rotation();
	}

	AnimationState();
	ManageState();

	Hit1();
	Hit2();
	Hit3();
	MakeGuardCollision();
	autoGuard();
	MakeCatchCollision();

	ManageJump();
	MakeCollision();
	MakeCollision2();
	MakeCollision3();
	CatchAttackCollision();

	RingOut();
}

void Player4::Move()
{
	/*
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
	if (m_playerState == 5 || m_playerState == 10) {
		//�����Ȃ��B
		return;
	}

	//�N���オ���Ă���Ȃ�B
	if (m_playerState == 11) {
		//�����Ȃ��B
		return;
	}*/

	//Y�{�^���������ꂽ���ɏݖ��̃X�g�b�N���P�ȏ�Ȃ�
	if (g_pad[3]->IsTrigger(enButtonY) && m_soysaucecount >= 1)
	{
		m_soysaucecount--;
		m_soysaucebullet = NewGO<SoySauceBullet>(0, "soysaucebullet");
		//bullet�̃��[�u�X�s�[�h�Ƀv���C���[�̑O�����̃x�N�g�������Ă��B
		m_soysaucebullet->SetMoveSpeed(m_forward);
		//4P���ݖ��e���������B
		m_soysaucebullet->SetSoySauceNewGOPlayer(4);
		//���ʉ����Đ�����B
		SoundSource* P4se = NewGO<SoundSource>(10);
		P4se->Init(10);
		P4se->Play(false);
	}

	if (m_playerState == 0 || m_playerState == 1 || m_playerState == 4 || m_playerState == 9) {
		//�ړ��B
		moveSpeed.x = g_pad[3]->GetLStickXF() * 120.0f;
	}

	//�L���������������ɂ����̂�h���R�[�h
	if (m_position.z > 0.01f || m_position.z < -0.01f) {
		m_position.z = 0.0f;
	}

	if (m_playerState == 0 || m_playerState == 1 || m_playerState == 4 || m_playerState == 9) {
		//�L�����̓����蔻��̍X�V�B
		m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());

	}

	m_player4.SetScale(m_scale);
	m_player4.SetPosition(m_position);
}

void Player4::Rotation()
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
	if (m_playerState == 5 || m_playerState == 10) {
		//�����Ȃ��B
		return;
	}

	//�N���オ���Ă���Ȃ�B
	if (m_playerState == 11) {
		//�����Ȃ��B
		return;
	}

	//�X�e�B�b�N�����ɓ|���ƁB
	if (g_pad[3]->GetLStickXF() < 0) {
		m_charaRotState = 1;
	}

	//�X�e�B�b�N���E�ɓ|���ƁB
	else if (g_pad[3]->GetLStickXF() > 0) {
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

	m_player4.SetRotation(m_rotation);
}

void Player4::AnimationState()
{
	if (m_playerState == 4 || m_playerState == 5 || m_playerState == 10 || m_playerState == 11) {
		return;
	}

	//�͂�
	if (g_pad[3]->IsTrigger(enButtonRB1) || g_pad[3]->IsTrigger(enButtonRB2)) {
		m_playerState = 6;
	}

	//�͂ݍU��
	if (p1_Catch == true || p2_Catch == true || p3_Catch == true) {
		if (g_pad[3]->IsTrigger(enButtonB)) {
			m_playerState = 9;
		}
	}
	//�ʏ�U��
	else if (g_pad[3]->IsTrigger(enButtonB) && atkState == 2) {
		/*SoundSource* P1se = NewGO<SoundSource>(13);
		P1se->Init(13);
		P1se->Play(false);*/
		m_playerState = 8;
	}
	else if (g_pad[3]->IsTrigger(enButtonB) && atkState == 1) {
		/*SoundSource* P1se = NewGO<SoundSource>(12);
		P1se->Init(12);
		P1se->Play(false);*/
		m_playerState = 7;
	}
	else if (g_pad[3]->IsTrigger(enButtonB)) {
		SoundSource* P1se = NewGO<SoundSource>(11);
		P1se->Init(11);
		P1se->Play(false);
		m_playerState = 3;
	}


	if (m_playerState != 3 && m_playerState != 4 && m_playerState != 5 && m_playerState != 6 && m_playerState != 7 && m_playerState != 8 && m_playerState != 9) {

		if (g_pad[3]->IsPress(enButtonLB1) || g_pad[3]->IsPress(enButtonLB2)) {
			m_playerState = 2;
		}

		else if (g_pad[3]->IsTrigger(enButtonX)) {
			//���ʉ����Đ�����B
			SoundSource* P4se = NewGO<SoundSource>(3);
			P4se->Init(3);
			P4se->Play(false);
			m_playerState = 4;
		}

		else if (g_pad[3]->GetLStickXF() || g_pad[3]->GetLStickYF()) {
			m_playerState = 1;
		}

		else if (!g_pad[3]->IsPressAnyKey()) {
			m_playerState = 0;
		}
	}
}

void Player4::ManageState()
{
	//�X�e�[�g�ɂ��A�j���[�V�����̊Ǘ��B
	switch (m_playerState)
	{
	case 0:
		m_player4.PlayAnimation(enAnimClip_Idle, 0.2f);
		m_isUnderAttack = false;
		m_catch = false;
		m_2 = false;
		m_3 = false;
		break;

	case 1:
		m_player4.PlayAnimation(enAnimClip_Run, 0.2f);
		m_isUnderAttack = false;
		m_catch = false;
		m_2 = false;
		m_3 = false;
		break;

	case 2:
		m_player4.PlayAnimation(enAnimClip_Guard, 0.2f);
		m_catch = false;
		break;

	case 3:
		m_player4.PlayAnimation(enAnimClip_Punch, 0.2f);
		m_catch = false;
		if (m_player4.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 4:
		m_player4.PlayAnimation(enAnimClip_Jump, 0.2f);
		m_catch = false;
		if (m_player4.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;

	case 5:
		m_player4.PlayAnimation(enAnimClip_Hit, 0.2f);
		m_jumpState = false;
		atkState = 0;
		if (m_player4.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		m_catch = false;
		break;

	case 6:
		m_player4.PlayAnimation(enAnimClip_Catch, 0.2f);
		atkState = 0;
		if (m_player4.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;

	case 7:
		m_player4.PlayAnimation(enAnimClip_Punch2, 0.2f);
		m_catch = false;
		if (m_player4.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 8:
		m_player4.PlayAnimation(enAnimClip_Kick3, 0.2f);
		m_catch = false;
		if (m_player4.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 9:
		m_player4.PlayAnimation(enAnimClip_CPunch, 0.2f);
		m_catch = false;
		if (m_player4.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 10:
		m_player4.PlayAnimation(enAnimClip_FlyAway, 0.2f);
		m_catch = false;
		if (m_player4.IsPlayingAnimation() == false) {
			m_playerState = 11;
			atkState = 0;
		}
		break;

	case 11:
		m_player4.PlayAnimation(enAnimClip_RiseUp, 0.2f);
		if (m_player4.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;
	}

}

void Player4::ManageJump()
{
	//�W�����v�B
	if (m_jumpState == true) {
		moveSpeed.y = 450.0f;
	}
	//�o�O���N����Ȃ��d�́B
	else if (m_position.y > 20.0f || m_position.y < -20.0f) {
		moveSpeed.y -= 80.0f;
	}
	else {
		moveSpeed.y = -250.0f;
	}
}

void Player4::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//�L�[�̖��O���uattack_start�v�̎��B
	if (wcscmp(eventName, L"Punch_Start") == 0)
	{
		//���ʉ�������B
		SoundSource* P1se = NewGO<SoundSource>(7);
		P1se->Init(7);
		P1se->Play(false);

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
		SoundSource* P1se = NewGO<SoundSource>(8);
		P1se->Init(8);
		P1se->Play(false);

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
		SoundSource* P1se = NewGO<SoundSource>(9);
		P1se->Init(9);
		P1se->Play(false);

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

	if (wcscmp(eventName, L"Jump_Start") == 0)
	{
		//�U�����ɂ���B
		m_jumpState = true;
	}
	//�L�[�̖��O���uattack_end�v�̎��B
	else if (wcscmp(eventName, L"Jump_End") == 0)
	{
		//�U�����I���B
		m_jumpState = false;
	}
}

void Player4::MakeCollision()
{

	if (m_isUnderAttack == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player4_attack");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player4.GetBone(m_handBoneId)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player4::MakeCollision2()
{

	if (m_2 == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player4_attack2");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player4.GetBone(m_handBoneId2)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player4::MakeCollision3()
{

	if (m_3 == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player4_attack3");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player4.GetBone(m_handBoneId3)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player4::MakeGuardCollision()
{
	if (m_playerState != 2) {
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

	collisionObject->SetName("P4_Guard");

	//////////////////////////////////////////////////////////////////////////////////////////////

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player2_attack");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions1)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(collisionObject))
		{
			//�v���C���[�̓����X�R�A���_
			m_playerpoint->Set2PPoint();
			//FindGO<Player2>("player2")->SetPlayer2PlayerState14();
		}

	}

	/////////////////////////////////////////////////////////////////////////////////////////
}

void Player4::autoGuard()
{
	if (m_playerState != 5 && m_playerState != 10 && m_playerState != 11) {
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

	collisionObject->SetName("P4_autoGuard");
}

void Player4::Hit1()
{
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
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set1PPoint();
				//�G�t�F�N�g�B
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(1);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player1����player2�������x�N�g�������߂�B
				Vector3 a = m_position - FindGO<Player1>("player1")->GetPlayer1Position();
				a.Normalize();
				if (a.x > 0) {
					//�̂̌�����ς���B
					m_charaRotState = 1;

					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 200.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 200.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//���ʉ����Đ�����B
				SoundSource* P4se = NewGO<SoundSource>(4);
				P4se->Init(4);
				P4se->Play(false);

				//HP�̌����B
				m_hp -= 2;

				//��_�����[�V�����̍Đ��B
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
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set1PPoint();
				//�G�t�F�N�g�B
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(1);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player1����player2�������x�N�g�������߂�B
				Vector3 a = m_position - FindGO<Player1>("player1")->GetPlayer1Position();
				a.Normalize();
				if (a.x > 0) {
					//�̂̌�����ς���B
					m_charaRotState = 1;

					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 500.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 500.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//���ʉ����Đ�����B
				SoundSource* P4se = NewGO<SoundSource>(5);
				P4se->Init(5);
				P4se->Play(false);

				m_hp -= 5;
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
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set1PPoint();
				//�G�t�F�N�g�B
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(0);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player1����player2�������x�N�g�������߂�B
				Vector3 a = m_position - FindGO<Player1>("player1")->GetPlayer1Position();
				a.Normalize();
				if (a.x > 0) {
					//�̂̌�����ς���B
					m_charaRotState = 1;

					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 800.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 800.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//���ʉ����Đ�����B
				SoundSource* P4se = NewGO<SoundSource>(6);
				P4se->Init(6);
				P4se->Play(false);

				m_hp -= 8;
				m_playerState = 10;
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
			//�v���C���[�̓����X�R�A���_
			m_playerpoint->Set1PPoint();
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
				//m_hp -= 1;
				////////////////////////////////////////////////////
				///���������P���ׂ��_�I�I�I
				//////////////////////////////////////////////////// 
				m_playerState = 5;
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set1PPoint();
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

				SoundSource* P4se = NewGO<SoundSource>(13);
				P4se->Init(13);
				P4se->Play(false);

				m_hp -= 2;
				m_playerState = 5;
			}
		}
	}

	//HP�̏�������̐ݒ�B
	if (m_hp > m_max) {
		m_hp = m_max;
	}
	else if (m_hp < m_min) {
		m_hp = m_min;
	}
}

void Player4::Hit2()
{
	/*wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", m_hp);

	//�\������e�L�X�g��ݒ�B
	m_fontHPRender.SetText(wcsbuf1);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontHPRender.SetPosition(Vector3(690.0f, -400.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontHPRender.SetScale(1.5f);
	//���F�ɐݒ�
	m_fontHPRender.SetColor(g_vec4White);*/

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
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set2PPoint();
				//�G�t�F�N�g�B
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(1);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player1����player2�������x�N�g�������߂�B
				a = m_position - FindGO<Player2>("player2")->GetPlayer2Position();
				a.Normalize();
				if (a.x > 0) {
					//�̂̌�����ς���B
					m_charaRotState = 1;

					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 200.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 200.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//���ʉ����Đ�����B
				SoundSource* P4se = NewGO<SoundSource>(4);
				P4se->Init(4);
				P4se->Play(false);

				//HP�̌����B
				m_hp -= 2;

				//��_�����[�V�����̍Đ��B
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
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set2PPoint();
				//�G�t�F�N�g�B
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(1);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player2����player1�������x�N�g�������߂�B
				Vector3 a = m_position - FindGO<Player2>("player2")->GetPlayer2Position();
				a.Normalize();
				if (a.x > 0) {
					//�̂̌�����ς���B
					m_charaRotState = 1;

					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 500.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 500.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//���ʉ����Đ�����B
				SoundSource* P4se = NewGO<SoundSource>(5);
				P4se->Init(5);
				P4se->Play(false);

				m_hp -= 5;
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
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set2PPoint();
				//�G�t�F�N�g�B
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(0);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player2����player1�������x�N�g�������߂�B
				Vector3 a = m_position - FindGO<Player2>("player2")->GetPlayer2Position();
				a.Normalize();
				if (a.x > 0) {
					//�̂̌�����ς���B
					m_charaRotState = 1;

					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 800.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 800.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//���ʉ����Đ�����B
				SoundSource* P4se = NewGO<SoundSource>(6);
				P4se->Init(6);
				P4se->Play(false);

				m_hp -= 8;
				m_playerState = 10;
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
			//�v���C���[�̓����X�R�A���_
			m_playerpoint->Set2PPoint();
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
				//m_hp -= 1;
				////////////////////////////////////////////////////
				///���������P���ׂ��_�I�I�I
				//////////////////////////////////////////////////// 
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set2PPoint();
				m_playerState = 5;
			}
		}
	}

	//HP�̏�������̐ݒ�B
	if (m_hp > m_max) {
		m_hp = m_max;
	}
	else if (m_hp < m_min) {
		m_hp = m_min;
	}
}

void Player4::Hit3()
{
	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player3_attack");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions1)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set3PPoint();

				//���ʉ����Đ�����B
				SoundSource* P4se = NewGO<SoundSource>(4);
				P4se->Init(4);
				P4se->Play(false);

				m_hp -= 2;
				m_playerState = 5;
			}
		}
	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player3_attack2");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions2)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set3PPoint();

				//���ʉ����Đ�����B
				SoundSource* P4se = NewGO<SoundSource>(5);
				P4se->Init(5);
				P4se->Play(false);

				m_hp -= 5;
				m_playerState = 5;
			}
		}
	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player3_attack3");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions3)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set3PPoint();

				//���ʉ����Đ�����B
				SoundSource* P4se = NewGO<SoundSource>(6);
				P4se->Init(6);
				P4se->Play(false);

				m_hp -= 8;
				m_playerState = 5;
			}
		}
	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player3_catch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions4)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//�v���C���[�̓����X�R�A���_
			m_playerpoint->Set3PPoint();
			m_Catchtimer = 0.0f;
			shine = true;
		}
	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions5 = g_collisionObjectManager->FindCollisionObjects("player3_cpunch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions5)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				//m_hp -= 1;
				////////////////////////////////////////////////////
				///���������P���ׂ��_�I�I�I
				//////////////////////////////////////////////////// 
				m_playerState = 5;
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set3PPoint();
			}
		}
	}
}

void Player4::AfterCatch()
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
				m_hp -= 1;
				m_playerState = 5;
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set1PPoint();
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
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set2PPoint();
				//�G�t�F�N�g�B
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(0);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player2����player1�������x�N�g�������߂�B
				Vector3 a = m_position - FindGO<Player2>("player2")->GetPlayer2Position();
				a.Normalize();
				if (a.x > 0) {
					//�̂̌�����ς���B
					m_charaRotState = 1;

					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 2000.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//�����m�b�N�o�b�N����B
					moveSpeed.x += a.x * 2000.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//���ʉ����Đ�����B
				SoundSource* P2se = NewGO<SoundSource>(6);
				P2se->Init(6);
				P2se->Play(false);

				m_hp -= 5;
				m_playerState = 5;
			}
		}
	}

	//�G�̍U���p�̃R���W�����̔z����擾����B
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player3_cpunch");
	//�z���for���ŉ񂷁B
	for (auto collision : collisions3)
	{
		//�R���W�����ƃL�����R�����Փ˂�����B
		if (collision->IsHit(m_characterController))
		{
			//HP�����炷�B
			if (guard != true) {
				//�v���C���[�̓����X�R�A���_
				m_playerpoint->Set3PPoint();
				shine = false;
				m_hp -= 1;
				m_playerState = 5;
			}
		}
	}

	m_Catchtimer += g_gameTime->GetFrameDeltaTime();

	if (m_Catchtimer >= 3.0f) {
		shine = false;
	}
}

void Player4::MakeCatchCollision()
{
	if (m_catch == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player4_catch");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player4.GetBone(m_handBoneIdCatch)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player4::CatchAttackCollision()
{
	if (m_cpunch == true) {

		//�R���W�����I�u�W�F�N�g���쐬����B
		auto collisionObject = NewGO<CollisionObject>(0);

		//����̃R���W�������쐬����B
		collisionObject->CreateSphere(m_position,				//���W�B
			Quaternion::Identity,                               //��]�B
			10.0f                                               //���a�B
		);

		collisionObject->SetName("player4_cpunch");

		//�uSword�v�{�[���̃��[���h�s����擾����B
		Matrix matrix = m_player4.GetBone(m_handBoneIdCatch)->GetWorldMatrix();
		//�uSword�v�{�[���̃��[���h�s����R���W�����ɓK�p����B
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player4::RingOut()
{
	//���[�B
	if (m_position.x < -705.0f && m_position.y < -105.0f) {
		m_out = true;
		m_hp = 0;
	}
	//�E�[�B
	if (m_position.x > 700.0f && m_position.y < -105.0f) {
		m_out = true;
		m_hp = 0;
	}
}

void Player4::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	m_fontHPRender.Draw(rc);
	m_player4.Draw(rc);
}
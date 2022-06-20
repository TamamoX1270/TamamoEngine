#include "stdafx.h"
#include "SoySauceBullet.h"
#include "stdafx.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"

//CollisionObject���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"
//EffectEmitter���g�p���鎞�̓t�@�C�����C���N���[�h����K�v������B
#include "graphics/effect/EffectEmitter.h"

bool SoySauceBullet::Start()
{
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(777, u"Assets/effect/syouyu.efk");
	switch (m_soynewgoplayer)
	{
	case 0:
		break;
	case 1:
		//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
		m_position = FindGO<Player1>("player1")->GetPlayer1Position();
		m_position.y += 70.0f;
		//�v���C���[�����������Ă���Ȃ獶�ɁA�E�������Ă���Ȃ�E�ɒe���΂�
		if (FindGO<Player1>("player1")->GetPlayerforward().x < 0.0f)
		{
			m_position.x -= 60.0f;
		}
		else
		{
			m_position.x += 60.0f;
		}
		m_playerposition = FindGO<Player1>("player1")->GetPlayer1Position();
		break;
	case 2:
		//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
		m_position = FindGO<Player2>("player2")->GetPlayer2Position();
		m_position.y += 70.0f;
		//�v���C���[�����������Ă���Ȃ獶�ɁA�E�������Ă���Ȃ�E�ɒe���΂�
		if (FindGO<Player2>("player2")->GetPlayerforward().x < 0.0f)
		{
			m_position.x -= 60.0f;
		}
		else
		{
			m_position.x += 60.0f;
		}
		m_playerposition = FindGO<Player2>("player2")->GetPlayer2Position();
		break;
	case 3:
		//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
		m_position = FindGO<Player3>("player3")->GetPlayer3Position();
		m_position.y += 70.0f;
		//�v���C���[�����������Ă���Ȃ獶�ɁA�E�������Ă���Ȃ�E�ɒe���΂�
		if (FindGO<Player3>("player3")->GetPlayerforward().x < 0.0f)
		{
			m_position.x -= 60.0f;
		}
		else
		{
			m_position.x += 60.0f;
		}
		m_playerposition = FindGO<Player3>("player3")->GetPlayer3Position();
		break;
	case 4:
		//FindGO��Player�N���X����m_position(�v���C���[�̈ʒu)��ǂݍ��ށB
		m_position = FindGO<Player4>("player4")->GetPlayer4Position();
		m_position.y += 70.0f;
		//�v���C���[�����������Ă���Ȃ獶�ɁA�E�������Ă���Ȃ�E�ɒe���΂�
		if (FindGO<Player4>("player4")->GetPlayerforward().x < 0.0f)
		{
			m_position.x -= 60.0f;
		}
		else
		{
			m_position.x += 60.0f;
		}
		m_playerposition = FindGO<Player4>("player4")->GetPlayer4Position();
		break;
	}
	//�e�̃��f����ǂݍ��ށB
	m_modelRender.Init("Assets/modelData/SoySauceBullet.tkm");
	m_modelRender.SetScale({ 0.5f,0.5f,0.5f });
	//FindGO�œǂݍ���œ��ꂽm_position�ɒe��z�u����B
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	//�R���C�_�[���������B
	m_sphereCollider.Create(48.0f);

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	//���W��G�̈ʒu�ɐݒ肷��B
	collisionPosition = m_position;
	//����̃R���W�������쐬����B
	m_collisionObject->CreateSphere(collisionPosition,       //���W�B
		Quaternion::Identity,                                   //��]�B
		30.0f);                                                //���̑傫��(���a)�B
		//���O��t����B
	m_collisionObject->SetName("SoysauceAttack");
	//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
	m_collisionObject->SetIsEnableAutoDelete(false);
	return true;
}

SoySauceBullet::SoySauceBullet()
{

}

SoySauceBullet::~SoySauceBullet()
{
	DeleteGO(m_collisionObject);
}

void SoySauceBullet::Update() 
{
	Move();
	
	m_modelRender.Update();
}

void SoySauceBullet::Move()
{
	//�e�̍��W��movespeed��+���Ă���āA�e�𓮂����B
	m_position += m_moveSpeed * 15.0f;
	m_modelRender.SetPosition(m_position);
	//setposition�œ������e�̓����蔻��̔��f
	m_collisionObject->SetPosition(m_position);
	//�v���C���[�̍��W�ƒe�̋����̃x�N�g�������߂�B
	Vector3 diff = m_playerposition - m_position;

	//��������Ă���5�b�o�߂�����
	if (m_deletetimer >= 5.0f)
	{
		DeleteGO(this);
	}
	if (m_collisionObject->IsHit(FindGO<Player1>("player1")->GetCharacterController()) == true)
	{
		m_efpos1 = m_position;
		m_efpos1.y = 60.0f;
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(777);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->SetPosition(m_efpos1);
		effectEmitter->Play();
		DeleteGO(this);
	}
	if (m_collisionObject->IsHit(FindGO<Player2>("player2")->GetCharacterController()) == true)
	{
		m_efpos1 = m_position;
		m_efpos1.y = 60.0f;
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(777);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->SetPosition(m_efpos1);
		effectEmitter->Play();
		DeleteGO(this);
	}
	if (m_collisionObject->IsHit(FindGO<Player3>("player3")->GetCharacterController()) == true)
	{
		m_efpos1 = m_position;
		m_efpos1.y = 60.0f;
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(777);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->SetPosition(m_efpos1);
		effectEmitter->Play();
		DeleteGO(this);
	}
	if (m_collisionObject->IsHit(FindGO<Player4>("player4")->GetCharacterController()) == true)
	{
		m_efpos1 = m_position;
		m_efpos1.y = 60.0f;
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(777);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->SetPosition(m_efpos1);
		effectEmitter->Play();
		DeleteGO(this);
	}

	m_deletetimer += g_gameTime->GetFrameDeltaTime();

}

void SoySauceBullet::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
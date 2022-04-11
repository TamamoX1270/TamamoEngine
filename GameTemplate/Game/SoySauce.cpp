#include "stdafx.h"
#include "SoySauce.h"
#include "Game.h"
#include "Player1.h"
//CollisionObject���g�p���������߁A�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"

bool SoySauce::Start()
{
	m_player1 = FindGO<Player1>("player1");
	//���f���̓ǂݍ���
	m_soysauce.Init("Assets/modelData/SoySauce.tkm");
	m_position.x = -150.0f;
	m_rotation.AddRotationDegY(180.0f);
	m_soysauce.SetScale(1.0, 1.0, 1.0);
	m_soysauce.SetPosition(m_position);
	m_soysauce.SetRotation(m_rotation);
	m_soysauce.Update();

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
	m_collisionObject->SetName("bullet_hit");
	//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
	m_collisionObject->SetIsEnableAutoDelete(false);
	return true;
}

SoySauce::~SoySauce()
{
	DeleteGO(m_collisionObject);
}

void SoySauce::Update()
{
	Move();
}

void SoySauce::Move()
{
	//�R���W�����I�u�W�F�N�g�ƃv���C���[�̃L�����N�^�[�R���g���[���[���B
	//�Փ˂��Ă�����B(�������ŏݖ����Ɏ������Ă邯�ǌ�Ńv���C���[���Ŕ�����悤�ɂ�������������)
	if (m_collisionObject->IsHit(m_player1->GetCharacterController()) == true)
	{
		//�ݖ��J�E���g���P���₷�B
		m_player1->AddSoySauceCount();
		DeleteGO(this);
	}

}
void SoySauce::Render(RenderContext& rc)
{
	m_soysauce.Draw(rc);
}

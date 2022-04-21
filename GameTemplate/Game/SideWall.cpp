#include "stdafx.h"
#include "SideWall.h"
#include "Player1.h"
#include "Player2.h"

//CollisionObject���g�p���邽�߂ɁA�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"

SideWall::SideWall()
{

}

SideWall::~SideWall()
{
	DeleteGO(m_collisionObject);
}
bool   SideWall::Start()
{
	m_sidewall.Init("Assets/modelData/SideWall.tkm");
	m_position.x = 950.0f;
	m_position.y = 0.0f;
	m_sidewall.SetPosition(m_position);
	m_sidewall.SetRotation(m_rotation);
	m_sidewall.SetScale(m_scale);
	m_sidewall.Update();

	//�R���W�����I�u�W�F�N�g���쐬����B
	m_collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	//Box��̃R���W�������쐬����B
	m_collisionObject->CreateBox(collisionPosition,       //���W�B
		Quaternion::Identity,                             //��]�B
		{ 100.0f,500.0f,100.0f });                                  //�傫���B

		//���O��t����B
	m_collisionObject->SetName("player_touch");
	//�����ō폜�𖳌��ɂ���(DeleteGO�ō폜����K�v������)�B
	m_collisionObject->SetIsEnableAutoDelete(false);

	createstate = true;
	Create();

	return true;
}

void SideWall::GetCreate()
{

	//�R���W�����I�u�W�F�N�g�ƃv���C���[�̃L�����N�^�[�R���g���[���[���B
	//�Փ˂��Ă�����Đ������Ȃ��B
	if (m_collisionObject->IsHit(FindGO<Player1>("player1")->GetCharacterController()) == true)
	{
		return;
	}

	//createstate��false��5.0f���z���Ă�����Đ�������B
	if (createstate == false && m_timer >= 5.0f)
	{
		m_timer = 0.0f;
		createstate = true;
		Create();
	}
}

void SideWall::Create()
{
	if (createstate == true)
	{
		//PhysicsStaticObject���������B
		m_physicsStaticObject.CreateFromModel(
			m_sidewall.GetModel(),
			m_sidewall.GetModel().GetWorldMatrix());
		m_wallhp = 1;
	}
}

void  SideWall::Break()
{
	if (m_wallhp <= 0)
	{
		//PhysicsStaticObject�������[�X
		m_physicsStaticObject.Release();
		createstate = false;
	}
	if (m_walldamagestate == true)
	{
		m_walltimer += g_gameTime->GetFrameDeltaTime();
	}
	if (m_walltimer >= 1.0f)
	{
		m_walldamagestate = false;
		m_walltimer = 0.0f;
	}
	//Player���쐬�����A�U���̃q�b�g����p�̃R���W�����̔z����擾�B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player1_attack");
	//for���Ŕz����񂷁B
	for (auto collision : collisions)
	{
		//Player�̍U���̃R���W�����ƕǂ̃R���W�������B
		//�Փ˂��Ă�����B
		if (collision->IsHit(m_collisionObject) == true)
		{
			if (m_walldamagestate == false)
			{
				if (m_walldamagestate == false)
				{
					m_wallhp--;
					m_walldamagestate = true;
				}
			}
		}
	}
	//Player���쐬�����A�U���̃q�b�g����p�̃R���W����2�̔z����擾�B
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player1_attack2");
	//for���Ŕz����񂷁B
	for (auto collision : collisions2)
	{
		//�U���̃R���W�����ƕǂ̃R���W�������B
		//�Փ˂��Ă�����B
		if (collision->IsHit(m_collisionObject) == true)
		{
			if (m_walldamagestate == false)
			{
				if (m_walldamagestate == false)
				{
					m_wallhp--;
					m_walldamagestate = true;
				}
			}
		}
	}

	if (createstate == false)
	{
		m_timer += g_gameTime->GetFrameDeltaTime();
	}
}

void  SideWall::Update()
{
	Break();
	GetCreate();
	//���f���̍X�V�����B
	m_sidewall.Update();
}

void SideWall::Render(RenderContext& rc)
{
	if (createstate ==true)
	{
		m_sidewall.Draw(rc);    //���f����`�悷��B
	}
}
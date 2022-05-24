#include "stdafx.h"
#include "SoySauce.h"
#include "Game.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
//CollisionObject���g�p���������߁A�t�@�C�����C���N���[�h����B
#include "CollisionObject.h"
//�������g����悤�ɂ���
#include <random>
//EffectEmitter���g�p���鎞�̓t�@�C�����C���N���[�h����K�v������B
#include "graphics/effect/EffectEmitter.h"

namespace
{
	//�����𐶐�
	constexpr int MIN = -600;//�����͈͍̔Œ�l
	constexpr int MAX = 600;//�����͈͍̔ő�l
	constexpr int RAND_NUMS_TO_GENERATE = 1;//�����𐶐������
}


bool SoySauce::Start()
{
	m_position.y = 500.0f;
	//�G�̗����B
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(MIN, MAX);
	int soypos = 0;
	for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
		m_position.x = distr(eng);
		break;
	}
	m_player1 = FindGO<Player1>("player1");
	m_player2 = FindGO<Player2>("player2");
	m_player3 = FindGO<Player3>("player3");
	m_player4 = FindGO<Player4>("player4");
	//���f���̓ǂݍ���
	m_soysauce.Init("Assets/modelData/SoySauce.tkm");
	EffectEngine::GetInstance()->ResistEffect(999, u"Assets/effect/Getsoysauce.efk");
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/syouyu_charge.wav");
	//m_position.x = -150.0f;
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
	//�R���W�����I�u�W�F�N�g�̍폜
	DeleteGO(m_collisionObject);
}

void SoySauce::Update()
{
	Move();
	//�v���C���[���擾�ς݂��Đ����I�������폜����B
	if (m_player1->GetSauce()== 1  ||
		m_player2->GetSauce() == 1 ||
		m_player3->GetSauce() == 1 ||
		m_player4->GetSauce() == 1)
	{
		DeleteGO(this);
	}
}

void SoySauce::Move()
{
	m_position.y -= 5.0f;
	
	if (m_position.y <= 0.0f)
	{
		m_position.y = 0.0f;
	}
	//�R���W�����I�u�W�F�N�g�ƃv���C���[�̃L�����N�^�[�R���g���[���[���G�ꂽ�����s�B
	if (m_collisionObject->IsHit(m_player1->GetCharacterController()) == true)
	{

		//���ʉ�������B
		SoundSource* Pse = NewGO<SoundSource>(14);
		Pse->Init(14);
		Pse->SetVolume(10.0f);
		Pse->Play(false);

		//�ݖ��J�E���g���P���₷�B
		m_player1->AddSoySauceCount();
		m_player1->AddSauce();
		//�R���W�����I�u�W�F�N�g���폜
		DeleteGO(m_collisionObject);
	}
	//�R���W�����I�u�W�F�N�g�ƃv���C���[�̃L�����N�^�[�R���g���[���[���G�ꂽ�����s�B
	if (m_collisionObject->IsHit(m_player2->GetCharacterController()) == true)
	{

		//���ʉ�������B
		SoundSource* Pse = NewGO<SoundSource>(14);
		Pse->Init(14);
		Pse->Play(false);

		//�ݖ��J�E���g���P���₷�B
		m_player2->AddSoySauceCount();
		m_player2->AddSauce();
		//�R���W�����I�u�W�F�N�g���폜
		DeleteGO(m_collisionObject);
	}
	//�R���W�����I�u�W�F�N�g�ƃv���C���[�̃L�����N�^�[�R���g���[���[���G�ꂽ�����s�B
	if (m_collisionObject->IsHit(m_player3->GetCharacterController()) == true)
	{

		//���ʉ�������B
		SoundSource* Pse = NewGO<SoundSource>(14);
		Pse->Init(14);
		Pse->Play(false);

		//�ݖ��J�E���g���P���₷�B
		m_player3->AddSoySauceCount();
		m_player3->AddSauce();
		//�R���W�����I�u�W�F�N�g���폜
		DeleteGO(m_collisionObject);
	}
	//�R���W�����I�u�W�F�N�g�ƃv���C���[�̃L�����N�^�[�R���g���[���[���G�ꂽ�����s�B
	if (m_collisionObject->IsHit(m_player4->GetCharacterController()) == true)
	{

		//���ʉ�������B
		SoundSource* Pse = NewGO<SoundSource>(14);
		Pse->Init(14);
		Pse->Play(false);

		//�ݖ��J�E���g���P���₷�B
		m_player4->AddSoySauceCount();
		m_player4->AddSauce();
		//�R���W�����I�u�W�F�N�g���폜
		DeleteGO(m_collisionObject);
	}
	
	m_soysauce.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position);
	m_soysauce.Update();
}
void SoySauce::Render(RenderContext& rc)
{
	//�擾���Ă��Ȃ����̂ݏݖ��I�u�W�F�N�g��`�悷��B
	if (m_player1->GetSauce() == 0 ||
		m_player2->GetSauce() == 0 ||
		m_player3->GetSauce() == 0 ||
		m_player4->GetSauce() == 0)
	{
		m_soysauce.Draw(rc);
	}
}

#pragma once
#include "sound/SoundSource.h"

class Player1;
class Player2;
class Player3;
class Player4;

class SoySauce : public IGameObject
{
public:
	~SoySauce();
	/// <summary>
	/// �J�n�̏���
	/// </summary>
	/// <returns></returns>
	bool Start() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update() override;

	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;

public:
	/// <summary>
	/// �ݖ��̍��W���擾����B
	/// </summary>
	/// <returns>�ݖ��̍��W�B</returns>
	const Vector3& GetSoySaucePosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �ݖ��̍��W��ݒ肷��B
	/// </summary>
	/// <param name="position">�ݖ��̍��W�B</param>
	void SetSoySaucePosition(const Vector3& position)
	{
		m_position = position;
	}


private:

	Player1* m_player1 = nullptr;;								//�v���C���[�P
	Player2* m_player2 = nullptr;;								//�v���C���[�P
	Player3* m_player3 = nullptr;;								//�v���C���[�P
	Player4* m_player4 = nullptr;;								//�v���C���[�P

	SoundSource* Pse;											// �v���C���[�̌��ʉ�

	ModelRender			m_soysauce;								//�ݖ�
	Vector3				m_efpos;								//�G�t�F�N�g�p�̃|�W�V����
	Vector3				m_position = Vector3::Zero;				// ���W
	Vector3				m_moveSpeed;							//�ړ����x�B
	Quaternion			m_rotation = Quaternion::Identity;;		// ��]
	Vector3				m_scale = Vector3::One;					// �g�嗦  
	EffectEmitter*		m_effectEmitter;						//�G�t�F�N�g
	CollisionObject*	m_collisionObject;						//�R���W����
};


#pragma once

class Player1;

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
	ModelRender			m_soysauce;								//�ݖ�
	Vector3				m_position = Vector3::Zero;				// ���W
	Quaternion			m_rotation = Quaternion::Identity;;		// ��]
	Vector3				m_scale = Vector3::One;					// �g�嗦  
	CollisionObject* m_collisionObject;							//�R���W����
};

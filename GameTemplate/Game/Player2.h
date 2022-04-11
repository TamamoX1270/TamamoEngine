#pragma once

class Player1;

class Player2 : public IGameObject
{
public:
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
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;

public:
	/// <summary>
	/// �v���C���[�̍��W���擾����B
	/// </summary>
	/// <returns>�v���C���[�̍��W�B</returns>
	const Vector3 & GetPlayer2Position() const
	{
		return m_position;
	}

	/// <summary>
	/// �v���C���[�̍��W��ݒ肷��B
	/// </summary>
	/// <param name="position">�v���C���[�̍��W�B</param>
	void SetPlayer2Position(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// �v���C���[�̃X�e�[�g���擾����B
	/// </summary>
	/// <returns>�v���C���[�̃X�e�[�g�B</returns>
	const float& GetPlayer2State() const
	{
		return shine;
	}

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �A�j���[�V�����Ǘ�
	/// </summary>
	void AnimationState();

	/// <summary>
	/// �X�e�[�g�Ǘ�
	/// </summary>
	void ManageState();

	/// <summary>
	/// �K�[�h�Ǘ�
	/// </summary>
	void Guard();

	/// <summary>
	/// ��_���[�W���[�V�����Ǘ�
	/// </summary>
	void Hit();

	/// <summary>
	/// �͂܂��̊Ǘ�
	/// </summary>
	void AfterCatch();
private:
	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : �ҋ@�A�j���[�V�����A
		enAnimClip_Run,		// 1 : ����A�j���[�V�����B
		enAnimClip_Hit,		// 2 : ��_���[�W�A�j���[�V�����B
		enAnimClip_Num,		// 3 :�A�j���[�V�����N���b�v�̐��B
	};
	Model m_model;
	ModelRender m_player2;                             //�v���C���[
	Animation m_animation;	// �A�j���[�V����
	AnimationClip m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v
	CharacterController m_characterController;       //�L�����N�^�[�R���g���[���[�B
	Vector3 m_position = Vector3::Zero;				   // ���W
	Quaternion m_rotation = Quaternion::Identity;;     // ��]
	Vector3 m_scale = Vector3::One;	                   // �g�嗦

	int m_hp = 0;
	FontRender      m_fontRender;					//�t�H���g�����_�[

	int aaa = 0;
	int m_playerState = 0;

	//�͂ݏ����̊֐�
	float shine = false;
	float m_timer = 0.0f;
};
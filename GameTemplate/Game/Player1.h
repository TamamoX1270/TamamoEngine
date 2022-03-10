#pragma once

class Player2;

class Player1 : public IGameObject
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
	const Vector3& GetPlayer1Position() const
	{
		return m_position;
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
	/// �W�����v�Ǘ�
	/// </summary>
	void ManageJump();

	// �A�j���[�V�����C�x���g�p�̊֐��B
	//void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	/// <summary>
	/// �U���p�̃R���W�������쐬����B
	/// </summary>
	void MakeAttackCollision();

private:
	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : �ҋ@�A�j���[�V�����A
		enAnimClip_Run,		// 1 : ����A�j���[�V�����B
		enAnimClip_Guard,	// 2 : �K�[�h�A�j���[�V�����B
		enAnimClip_Punch,	// 3 : �U���A�j���[�V�����B
		enAnimClip_Jump,	// 4 : �W�����v�A�j���[�V�����B
		enAnimClip_Hit,		// 5 : ��_���[�W�A�j���[�V�����B
		enAnimClip_Num,		// 6 : �A�j���[�V�����N���b�v�̐��B
	};
	Model m_model;
	ModelRender m_player;								//�v���C���[
	Animation m_animation;								// �A�j���[�V����
	AnimationClip m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v
	CharacterController m_characterController;			//�L�����N�^�[�R���g���[���[�B
	Vector3 m_position= Vector3::Zero;					// ���W
	Quaternion m_rotation = Quaternion::Identity;;		// ��]
	Vector3 m_scale=Vector3::One;						// �g�嗦

	Vector3 moveSpeed;	//�v���C���[�̑����B

	int m_playerState; //�v���C���[�X�e�[�g�B
	float m_timer = 0.0f; //�A�j���[�V�����p�^�C�}�[�B

	int m_jumpState = 0;	//�W�����v�����p�X�e�[�g�B
	float m_jumpTimer = 0.0f;	//�W�����v�����p�^�C�}�[�B

};
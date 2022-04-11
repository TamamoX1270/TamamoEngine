#pragma once

class SoySauceBullet;

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

	/// <summary>
	/// �L�����N�^�[�R���g���[���[���擾�B
	/// </summary>
	/// <returns>�L�����N�^�[�R���g���[���[�B</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	/// <summary>
	/// �v���C���[�̍��W��ݒ肷��B
	/// </summary>
	/// <param name="position">�v���C���[�̍��W�B</param>
	void SetPlayer1Position(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// �U���X�e�[�g��ݒ肷��B
	/// </summary>
	/// <param name="position">�U���X�e�[�g�B</param>
	void SetPlayer1atkState(const float& state)
	{
		m_isUnderAttack = state;
	}

	/// <summary>
	/// �v���C���[�̃X�e�[�g���擾����B
	/// </summary>
	/// <returns>�v���C���[�̃X�e�[�g�B</returns>
	const int& GetPlayer1State() const
	{
		return m_playerState;
	}

	/// <summary>
	/// �ݖ��J�E���g+1
	/// </summary>
	void AddSoySauceCount()
	{
		m_soysaucecount++;
	}


private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// ��]����
	/// </summary>
	void Rotation();

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
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	void MakeCollision();

	void MakeCollision2();

	void MakeCollision3();

	/// <summary>
	/// �h��p�̃R���W�������쐬����B
	/// </summary>
	void MakeGuardCollision();

	/// <summary>
	/// �͂ݗp�̃R���W�������쐬����B
	/// </summary>
	void MakeCatchCollision();

	/// <summary>
	/// �͂ݍU��������R���W�������쐬����B
	/// </summary>
	void CatchAttackCollision();

private:
	// �A�j���[�V�����N���b�v�̔ԍ���\���񋓌^�B
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : �ҋ@�A�j���[�V�����A
		enAnimClip_Run,		// 1 : ����A�j���[�V�����B
		enAnimClip_Guard,	// 2 : �K�[�h�A�j���[�V�����B
		enAnimClip_Punch,	// 3 : �U���A�j���[�V�����B
		enAnimClip_Jump,	// 4 : �W�����v�A�j���[�V�����B
		enAnimClip_Hit,		// 5 : ��_���[�W�A�j���[�V�����B
		enAnimClip_Catch,	// 6 : �͂݃A�j���[�V�����B
		enAnimClip_Punch2,	// 7 : �U���Q�A�j���[�V�����B
		enAnimClip_Kick3,	// 8 : �U���R�A�j���[�V�����B
		enAnimClip_CPunch,	// 9 : �͂ݍU���A�j���[�V�����B
		enAnimClip_Num,		// 10 : �A�j���[�V�����N���b�v�̐��B
	};
	Model				m_model;
	ModelRender			m_player;								//�v���C���[
	SoySauceBullet*		m_soysaucebullet;                       //�ݖ��e
	FontRender			m_fontRender;							//����
	Animation			m_animation;							// �A�j���[�V����
	AnimationClip		m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v
	CharacterController m_characterController;					//�L�����N�^�[�R���g���[���[�B
	Vector3				m_position= Vector3::Zero;				// ���W
	Quaternion			m_rotation = Quaternion::Identity;;		// ��]
	Vector3				m_scale = Vector3::One;					// �g�嗦
	Vector3				m_forward;								//�L�����N�^�[�̑O�����̃x�N�g��



	Vector3		moveSpeed;				//�v���C���[�̑����B

	int			m_playerState;			//�v���C���[�X�e�[�g�B
	float		m_timer = 0.0f;			//�A�j���[�V�����p�^�C�}�[�B

	int			m_jumpState = 0;		//�W�����v�����p�X�e�[�g�B
	float		m_jumpTimer = 0.0f;		//�W�����v�����p�^�C�}�[�B

	int			m_charaRotState = 0;	//�L�����̌�����ς���X�e�[�g�B


	float		m_isUnderAttack;
	int			m_handBoneId = -1;		//�uHand�v�{�[����ID�B  

	float		m_catch;
	int			m_handBoneIdCatch = -1;		//�uHand�v�{�[����ID�B 

	float		m_2;
	int			m_handBoneId2 = -1;		//�uHand�v�{�[����ID�B  

	float		m_3;
	int			m_handBoneId3 = -1;		//�uHand�v�{�[����ID�B  

	float		m_cpunch;
	int			m_handBoneIdCPunch = -1;	//�uHand�v�{�[����ID�B  

	int atkState = 0;

	float a;							//shine�X�e�[�g�B

	int m_soysaucecount = 0;			//�ݖ��J�E���g
};
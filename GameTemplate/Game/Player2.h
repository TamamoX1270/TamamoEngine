#pragma once

class SoySauceBullet;

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
	const Vector3& GetPlayer2Position() const
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
	/// �v���C���[�̒͂܂�X�e�[�g���擾����B
	/// </summary>
	/// <returns>�v���C���[�̃X�e�[�g�B</returns>
	const float& GetPlayer2State() const
	{
		return shine;
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

	/// <summary>
	/// �U���P�̃R���W�������쐬����B
	/// </summary>
	void MakeCollision();

	/// <summary>
	/// �U���Q�̃R���W�������쐬����B
	/// </summary>
	void MakeCollision2();

	/// <summary>
	/// �U���R�̃R���W�������쐬����B
	/// </summary>
	void MakeCollision3();

	/// <summary>
	/// �h��p�̃R���W�������쐬����B
	/// </summary>
	void MakeGuardCollision();

	/// <summary>
	/// �v���C���[1����̔�_���[�W���[�V�����Ǘ�
	/// </summary>
	void Hit1();

	/// <summary>
	/// �v���C���[3����̔�_���[�W���[�V�����Ǘ�
	/// </summary>
	void Hit3();

	/// <summary>
	/// �͂܂��̊Ǘ�
	/// </summary>
	void AfterCatch();

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
	ModelRender			m_player2;								//�v���C���[
	Animation			m_animation;							// �A�j���[�V����
	AnimationClip		m_animationClipArray[enAnimClip_Num];	// �A�j���[�V�����N���b�v
	CharacterController m_characterController;					//�L�����N�^�[�R���g���[���[�B
	Vector3				m_position = Vector3::Zero;				// ���W
	Quaternion			m_rotation = Quaternion::Identity;;		// ��]
	Vector3				m_scale = Vector3::One;					// �g�嗦

	//�ݖ��e�̊֐�
	SoySauceBullet* m_soysaucebullet;   //�ݖ��e
	Vector3			m_forward;			//�L�����N�^�[�̑O�����̃x�N�g��
	FontRender		m_fontRender;		//����
	int m_soysaucecount = 0;			//�ݖ��J�E���g

	//HP�̉��\��
	int m_hp = 0;
	FontRender      m_fontHPRender;					//�t�H���g�����_�[

	Vector3		moveSpeed;				//�v���C���[�̑����B

	int			m_playerState;			//�v���C���[�X�e�[�g�B
	float		m_timer = 0.0f;			//�A�j���[�V�����p�^�C�}�[�B

	int			m_jumpState = 0;		//�W�����v�����p�X�e�[�g�B
	float		m_jumpTimer = 0.0f;		//�W�����v�����p�^�C�}�[�B

	int			m_charaRotState = 0;	//�L�����̌�����ς���X�e�[�g�B


	float		m_isUnderAttack;		//1�Ԗڂ̍U���B
	int			m_handBoneId = -1;		//�uHand�v�{�[����ID�B  

	float		m_catch;					//�͂݁B
	int			m_handBoneIdCatch = -1;		//�uHand�v�{�[����ID�B 

	float		m_2;					//2�Ԗڂ̍U���B
	int			m_handBoneId2 = -1;		//�uHand�v�{�[����ID�B  

	float		m_3;					//3�Ԗڂ̍U���B
	int			m_handBoneId3 = -1;		//�uHand�v�{�[����ID�B  

	float		m_cpunch;					//�͂ݍU���B
	int			m_handBoneIdCPunch = -1;	//�uHand�v�{�[����ID�B  

	int atkState = 0;					//�A���U���̂��߂̃X�e�[�g�B

	float guard = false;				//�K�[�h�����Ă��邩�ǂ����B

	float p1_Catch;		//P1��shine�X�e�[�g�B
	float p3_Catch;		//P3��shine�X�e�[�g�B

	//�͂ݏ����̊֐�
	float shine = false;		//�͂܂�Ă��邩�B
	float m_Catchtimer = 0.0f;		//�͂܂�Ă���̃^�C�}�[�B
};
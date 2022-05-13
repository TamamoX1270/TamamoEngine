#pragma once
class Player1;
class Player2;
class Player3;
class Player4;
class BackGround;
class GameUI;
class GameCamera;

class GameCamera2P;
class GameCamera3P;

class SpecialCamera;

class SoySauce;
class SideWall;
class Title;

class Game : public IGameObject
{
public:
	Game();
	~Game();
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

	/// <summary>
	/// �Q�[���������B
	/// </summary>
	/// <param name="kill">�Q�[���폜�B</param>
	void SetGameDelete(const int& kill)
	{
		m_gamedelete = kill;
	}

private:
	void Camera();
	//�����Ƃ��ɉ񂷔z��ׂ̈̊֐�
	void GameDelete();


private:
	BackGround*		m_backGround;					//�w�i�B
	Title*			m_title;						//�^�C�g��
	FontRender      m_fontRender;					//�t�H���g�����_�[
	ModelRender     m_modelRender;					//���f�������_�[
	Player1*        m_player;						//�v���C���[1
	Player2*		m_player2;						//�v���C���[2
	Player3*		m_player3;						//�v���C���[3
	Player4*		m_player4;						//�v���C���[4
	GameUI*			m_gamingshigureui;				//�Q�[�~���O�Ȃ����}�}(GameUI)
	SoySauce*		m_soysauce;						//�ݖ�����
	SideWall*		m_sidewall;						//���E�̕�
	Vector3         m_pointligpos;                  //�|�C���g���C�g�̍��W
	Vector3         m_directionligColor;		    //�Z�b�g����F
	Vector3			m_spPosition;					//�X�|�b�g���C�g�̃|�W�V����
	Vector3			m_spDirection;                  //�X�|�b�g���C�g�̕���
	
	//HP�o�[�̎����̂��߂̊֐�
	int m_hp = 0;

	//�J�����̃|�C���^�֐�
	GameCamera* m_gameCamera;

	GameCamera2P* m_gameCamera2;
	GameCamera3P* m_gameCamera3;

	SpecialCamera* sscamera;
	int m_cameraState = 0;
	int m_gamedelete = false;							//�Q�[���폜�X�e�[�g
};


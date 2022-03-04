#pragma once
class Player;
class BackGround;

class Game : public IGameObject
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
private:
	BackGround* m_backGround;					    //�w�i�B
	SpriteRender	m_spriteRender;
	ModelRender     m_modelRender;					//���f�������_�[
	Player*         m_player;						//�v���C���[
	Vector3         m_pointligpos;                  //�|�C���g���C�g�̍��W
	Vector3         m_directionligColor;		    //�Z�b�g����F
	Vector3			m_spPosition;					//�X�|�b�g���C�g�̃|�W�V����
	Vector3			m_spDirection;                  //�X�|�b�g���C�g�̕���
};


#pragma once
class Player;
class DirectionLite;

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
	ModelRender     m_modelRender;  //���f�������_�[
	Player*         m_player;       //�v���C���[
	Vector3         m_directionligColor;     //�Z�b�g����F
	
};


#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Render(RenderContext& rc);

private:
	ModelRender			m_stage;				//�X�e�[�W�B
	PhysicsStaticObject m_physicsStaticObject;  //�ÓI�����I�u�W�F�N�g�B
};
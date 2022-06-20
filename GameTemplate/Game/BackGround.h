#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Render(RenderContext& rc);

private:
	ModelRender			m_stage;				//ステージ。
	PhysicsStaticObject m_physicsStaticObject;  //静的物理オブジェクト。
};
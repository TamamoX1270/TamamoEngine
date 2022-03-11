#include "stdafx.h"
#include "BackGround.h"

#include "Game.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{
	m_backGround.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	m_backGround.SetPosition(0.0f, -160.0f, 150.0f);

	m_backGround.Init("Assets/modelData/stage/susigeta.tkm");

	//	m_backGround.SetScale(m_scale);
	//	m_backGround.Update();
	//PhysicsStaticObject‚ð‰Šú‰»B
	m_physicsStaticObject.CreateFromModel(
		m_backGround.GetModel(),
		m_backGround.GetModel().GetWorldMatrix());
	//“–‚½‚è”»’è‚Ì‰ÂŽ‹‰»B
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}
void BackGround::Render(RenderContext& rc)
{
	m_backGround.Draw(rc);
}

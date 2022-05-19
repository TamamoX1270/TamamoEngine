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
	m_backGround.SetScale(Vector3(0.65f, 0.65f, 0.65f));
	m_backGround.SetPosition(0.0f, 0.0f, 90.0f);
	
	//m_backGround.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	//m_backGround.SetPosition(0.0f, 0.0f, 150.0f);

	m_backGround.Init("Assets/stageff/stage.tkm");

	//	m_backGround.SetScale(m_scale);
	//	m_backGround.Update();
	//PhysicsStaticObjectを初期化。
	m_physicsStaticObject.CreateFromModel(
		m_backGround.GetModel(),
		m_backGround.GetModel().GetWorldMatrix());
	//当たり判定の可視化。
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	return true;
}
void BackGround::Render(RenderContext& rc)
{
	m_backGround.Draw(rc);
}

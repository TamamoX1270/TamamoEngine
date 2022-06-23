#include "stdafx.h"
#include "BackGround.h"

namespace
{
	const Vector3 STAGE_SCALE = { 0.65f,0.65f,0.65f };
	const Vector3 STAGE_POSITION = { 0.0f, 0.0f, 90.0f };
}

bool BackGround::Start()
{
	m_stage.SetScale(STAGE_SCALE);
	m_stage.SetPosition(STAGE_POSITION);

	m_stage.Init("Assets/modelData/stage/stage.tkm");
	
	//PhysicsStaticObject‚ð‰Šú‰»B
	m_physicsStaticObject.CreateFromModel(
		m_stage.GetModel(),
		m_stage.GetModel().GetWorldMatrix()
	);

	//“–‚½‚è”»’è‚Ì‰ÂŽ‹‰»B
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

void BackGround::Render(RenderContext& rc)
{
	m_stage.Draw(rc);
}

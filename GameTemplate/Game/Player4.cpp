#include "stdafx.h"
#include "Player4.h"
#include "Game.h"

bool Player4::Start()
{
	//アニメーションクリップをロードする。
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/purototype/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	//モデルの読み込み
	m_player4.Init("Assets/purototype/sushi.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);
	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, { 0.0f, 0.0f, 0.0f });
	m_rotation.SetRotationDegX(-90.0f);

	//m_player4.SetPosition(500.0f, 0.0f, 500.0f);
	//m_player4.Update();
	return true;
}

void Player4::Update()
{
	//m_player4.Update();
	Move();
	AnimationState();
}

void Player4::Move()
{

	Vector3 moveSpeed;
	moveSpeed.x = g_pad[3]->GetLStickXF() * 120.0f;
	//moveSpeed.z = g_pad[1]->GetLStickYF() * 120.0f;

	/*
	m_player.UpdateWorldMatrix(
		m_characterController.GetPosition(),
		m_rotation,
		g_vec3One
	);
	*/


	/* 左スティック(キーボード：WASD)で平行移動。
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.y += g_pad[0]->GetLStickYF();

	// 右スティック(キーボード：上下左右)で回転。
	m_rotation.AddRotationY(g_pad[0]->GetRStickXF() * 0.05f);
	m_rotation.AddRotationX(g_pad[0]->GetRStickYF() * 0.05f);*/

	// 上下左右キー(キーボード：2, 4, 6, 8)で拡大
	if (g_pad[3]->IsPress(enButtonUp)) {
		m_scale.y += 0.02f;
	}
	if (g_pad[3]->IsPress(enButtonDown)) {
		m_scale.y -= 0.02f;
	}
	if (g_pad[3]->IsPress(enButtonRight)) {
		m_scale.x += 0.02f;
	}
	if (g_pad[3]->IsPress(enButtonLeft)) {
		m_scale.x -= 0.02f;
	}

	/* アニメーションの切り替え。
	if (g_pad[0]->IsPress(enButtonA)) {
		m_player.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
	if (g_pad[0]->IsPress(enButtonB)) {
		m_player.PlayAnimation(enAnimClip_Run, 0.2f);
	}
	*/


	// 平行移動
	m_position.x += g_pad[3]->GetLStickXF();
	m_position.y += g_pad[3]->GetLStickYF();


	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_player4.SetScale(m_scale);
	m_player4.SetPosition(m_position);
	m_player4.SetRotation(m_rotation);
	m_player4.Update();
}

void Player4::AnimationState()
{
	/* アニメーションの切り替え。
	if (g_pad[0]->IsPress(enButtonA)) {
		m_player.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
	if (g_pad[0]->IsPress(enButtonB)) {
		m_player.PlayAnimation(enAnimClip_Run, 0.2f);
	}*/

	if (g_pad[3]->GetLStickXF() || g_pad[3]->GetLStickYF()) {
		m_player4.PlayAnimation(enAnimClip_Run, 0.2f);
	}

	else {
		m_player4.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
}

void Player4::Render(RenderContext& rc)
{
	m_player4.Draw(rc);
}
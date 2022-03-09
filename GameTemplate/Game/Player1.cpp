﻿#include "stdafx.h"
#include "Player1.h"
#include "Game.h"
#include "GameCamera.h"

bool Player1::Start()
{
	//アニメーションクリップをロードする。
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/purototype/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Guard].Load("Assets/purototype/guard.tka");
	m_animationClipArray[enAnimClip_Guard].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Punch].Load("Assets/purototype/punch.tka");
	m_animationClipArray[enAnimClip_Punch].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Jump].Load("Assets/purototype/jump.tka");
	m_animationClipArray[enAnimClip_Jump].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Hit].Load("Assets/purototype/hit.tka");
	m_animationClipArray[enAnimClip_Hit].SetLoopFlag(false);
	//モデルの読み込み
	m_player.Init("Assets/purototype/sushi.tkm", m_animationClipArray, enAnimClip_Num,enModelUpAxisY);
	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, {0.0f, 0.0f, 0.0f});
	
	m_rotation.SetRotationDegX(-90.0f);
	return true;
}

void Player1::Update()
{
	
	Move();
	AnimationState();
	ManageState();
	ManageJump();

	//m_player.Update();
}

void Player1::Move()
{
	
	//移動。横移動だけでいいので下はコメントにしている。
	moveSpeed.x = g_pad[0]->GetLStickXF() * 120.0f;
	//moveSpeed.z = g_pad[0]->GetLStickYF() * 120.0f;
	

	/*
	m_player.UpdateWorldMatrix(
		m_characterController.GetPosition(),
		m_rotation,
		g_vec3One
	);
	*/
	
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		m_playerState = 5;
	}
	
	
	/* 左スティック(キーボード：WASD)で平行移動。
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.y += g_pad[0]->GetLStickYF();
	
	// 右スティック(キーボード：上下左右)で回転。
	m_rotation.AddRotationY(g_pad[0]->GetRStickXF() * 0.05f);
	m_rotation.AddRotationX(g_pad[0]->GetRStickYF() * 0.05f);*/
	


	
	// 平行移動
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.y += g_pad[0]->GetLStickYF();
	

	m_position=m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_player.SetScale(m_scale);
	m_player.SetPosition(m_position);
	m_player.SetRotation(m_rotation);
	m_player.Update();				 
}

void Player1::AnimationState()
{
	
	if (m_playerState == 3) {

		m_timer += g_gameTime->GetFrameDeltaTime();
		if (m_timer >= 0.7f) {
			m_playerState = 0;
		}
	}

	else if (m_playerState == 4) {

		m_timer += g_gameTime->GetFrameDeltaTime();
		if (m_timer >= 1.5f) {
			m_playerState = 0;
		}
	}
	

	//通常攻撃
	if (g_pad[0]->IsTrigger(enButtonB)) {
		m_timer = 0.0f;
		m_playerState = 3;
	}


	if (m_playerState != 3 && m_playerState != 4) {

		if (g_pad[0]->IsPress(enButtonLB1) || g_pad[0]->IsPress(enButtonLB2)) {
			m_playerState = 2;
		}

		else if (g_pad[0]->IsTrigger(enButtonX)) {
			m_timer = 0.0f;
			m_playerState = 4;
		}

		else if (g_pad[0]->GetLStickXF() || g_pad[0]->GetLStickYF()) {
			m_playerState = 1;
		}

		else if(!g_pad[0]->IsPressAnyKey()) {
			m_playerState = 0;
		}
	}
}

void Player1::ManageState()
{
	switch (m_playerState)
	{
	case 0:
		m_player.PlayAnimation(enAnimClip_Idle, 0.2f);
		break;
	case 1:
		m_player.PlayAnimation(enAnimClip_Run, 0.2f);
		break;
	case 2:
		m_player.PlayAnimation(enAnimClip_Guard, 0.2f);
		break;
	case 3:
		m_player.PlayAnimation(enAnimClip_Punch, 0.2f);
		break;
	case 4:
		m_player.PlayAnimation(enAnimClip_Jump, 0.2f);
		break;
	case 5:
		m_player.PlayAnimation(enAnimClip_Hit, 0.2f);
		break;
	}
}

void Player1::ManageJump()
{
	//ジャンプの実装ゾーン
	if (g_pad[0]->IsTrigger(enButtonX)) {
		m_jumpState = 1;
		m_jumpTimer = 0.0f;
	}

	else {
		moveSpeed.y -= 80.0f;
		//80
	}

	if (m_jumpState == 1) {

		m_jumpTimer += g_gameTime->GetFrameDeltaTime();

		if (m_jumpTimer >= 0.48f) {
			m_jumpState = 2;
		}
	}

	if (m_jumpState == 2) {
		moveSpeed.y += 1200.0f;
		//1200
		m_jumpState = 0;
	}
}

void Player1::Render(RenderContext& rc)
{
	m_player.Draw(rc);
}
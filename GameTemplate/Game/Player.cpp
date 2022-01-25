#include "stdafx.h"
#include "Player.h"
#include "Game.h"

bool Player::Start()
{
	//アニメーションクリップをロードする。
	m_animationClipArray[enAnimClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/animData/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	//モデルの読み込み
	m_player.Init("Assets/modelData/unityChan.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisZ);
	return true;
}
void Player::Update()
{
	Move();
}
void Player::Move()
{
	// 左スティック(キーボード：WASD)で平行移動。
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.y += g_pad[0]->GetLStickYF();

	// 右スティック(キーボード：上下左右)で回転。
	m_rotation.AddRotationY(g_pad[0]->GetRStickXF() * 0.05f);
	m_rotation.AddRotationX(g_pad[0]->GetRStickYF() * 0.05f);
	// 上下左右キー(キーボード：2, 4, 6, 8)で拡大
	if (g_pad[0]->IsPress(enButtonUp)) {
		m_scale.y += 0.02f;
	}
	if (g_pad[0]->IsPress(enButtonDown)) {
		m_scale.y -= 0.02f;
	}
	if (g_pad[0]->IsPress(enButtonRight)) {
		m_scale.x += 0.02f;
	}
	if (g_pad[0]->IsPress(enButtonLeft)) {
		m_scale.x -= 0.02f;
	}

	// アニメーションの切り替え。
	if (g_pad[0]->IsPress(enButtonA)) {
		m_player.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
	if (g_pad[0]->IsPress(enButtonB)) {
		m_player.PlayAnimation(enAnimClip_Run, 0.2f);
	}
	// 回転
	m_rotation.AddRotationY(g_pad[0]->GetRStickXF() * 0.05f);

	// 平行移動
	m_position.x += g_pad[0]->GetLStickXF();
	m_position.y += g_pad[0]->GetLStickYF();

	m_player.SetScale(m_scale);
	m_player.SetPosition(m_position);
	m_player.SetRotation(m_rotation);
	m_player.Update();				 
}
void Player::Render(RenderContext& rc)
{
	m_player.Draw(rc);
}
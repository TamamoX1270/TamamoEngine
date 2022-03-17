#include "stdafx.h"
#include "Player2.h"
#include "Game.h"
#include "GameCamera.h"

bool Player2::Start()
{
	//アニメーションクリップをロードする。
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/purototype/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	//モデルの読み込み
	m_player2.Init("Assets/purototype/sushi.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);
	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, { 0.0f, 0.0f, 0.0f });
	m_rotation.SetRotationDegX(-90.0f);

	//m_player2.SetPosition(500.0f, 0.0f, 500.0f);
	//m_player2.Update();
	return true;
}

void Player2::Update()
{
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", m_hp);

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.5f);
	//黒色に設定
	m_fontRender.SetColor(g_vec4White);

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_attack");
	//配列をfor文で回す。
	for (auto collision : collisions)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			m_hp += 1;
		}

		
	}



	//m_player2.Update();
	Move();
	AnimationState();
}

void Player2::Move()
{

	Vector3 moveSpeed;
	moveSpeed.x = g_pad[1]->GetLStickXF() * 120.0f;
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
	if (g_pad[1]->IsPress(enButtonUp)) {
		m_scale.y += 0.02f;
	}
	if (g_pad[1]->IsPress(enButtonDown)) {
		m_scale.y -= 0.02f;
	}
	if (g_pad[1]->IsPress(enButtonRight)) {
		m_scale.x += 0.02f;
	}
	if (g_pad[1]->IsPress(enButtonLeft)) {
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
	m_position.x += g_pad[1]->GetLStickXF();
	m_position.y += g_pad[1]->GetLStickYF();


	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_player2.SetScale(m_scale);
	m_player2.SetPosition(m_position);
	m_player2.SetRotation(m_rotation);
	m_player2.Update();
}

void Player2::AnimationState()
{
	/* アニメーションの切り替え。
	if (g_pad[0]->IsPress(enButtonA)) {
		m_player.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
	if (g_pad[0]->IsPress(enButtonB)) {
		m_player.PlayAnimation(enAnimClip_Run, 0.2f);
	}*/

	if (g_pad[1]->GetLStickXF() || g_pad[1]->GetLStickYF()) {
		m_player2.PlayAnimation(enAnimClip_Run, 0.2f);
	}

	else {
		m_player2.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
}

void Player2::Render(RenderContext& rc)
{
	m_player2.Draw(rc);
	m_fontRender.Draw(rc);
}
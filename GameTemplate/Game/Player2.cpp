#include "stdafx.h"
#include "Player2.h"
#include "Game.h"

#include "Player1.h"

bool Player2::Start()
{
	//アニメーションクリップをロードする。
	m_animationClipArray[enAnimClip_Idle].Load("Assets/purototype/idle.tka");
	m_animationClipArray[enAnimClip_Idle].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Run].Load("Assets/purototype/walk.tka");
	m_animationClipArray[enAnimClip_Run].SetLoopFlag(true);
	m_animationClipArray[enAnimClip_Hit].Load("Assets/purototype/hit.tka");
	m_animationClipArray[enAnimClip_Hit].SetLoopFlag(false);
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
	if (shine == true) {
		AfterCatch();
		return;
	}


	int x;
	x = FindGO<Player1>("player1")->GetPlayer1State();
	if (x == 6) {
		//敵の攻撃用のコリジョンの配列を取得する。
		const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player_catch");
		//配列をfor文で回す。
		for (auto collision : collisions)
		{
			//コリジョンとキャラコンが衝突したら。
			if (collision->IsHit(m_characterController))
			{
				m_timer = 0.0f;
				shine = true;
			}
		}
	}


	Hit();
	Guard();

	//m_player2.Update();
	Move();
	AnimationState();
}

void Player2::Move()
{

	Vector3 moveSpeed;
	moveSpeed.x = g_pad[1]->GetLStickXF() * 120.0f;


	// 平行移動
	m_position.x += g_pad[1]->GetLStickXF();
	m_position.y += g_pad[1]->GetLStickYF();


	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_player2.SetScale(m_scale);
	m_player2.SetPosition(m_position);
	m_player2.SetRotation(m_rotation);
	m_player2.Update();
}

void Player2::Guard()
{

	if (!g_pad[1]->IsPress(enButtonLB1) && m_playerState == 0) {
		aaa = 0;
		return;
	}

	aaa = 1;

		//コリジョンオブジェクトを作成する。
		auto col = NewGO<CollisionObject>(0);

		Vector3 collisionPosition = m_position;
		//座標をプレイヤーの少し前に設定する。
		collisionPosition.y += 60.0f;

		//カプセル状のコリジョンを作成する。
		col->CreateCapsule(collisionPosition,
			Quaternion::Identity,
			35.0f,
			75.0f
		);

		col->SetName("P2_Guard");

}

void Player2::AnimationState()
{

	if (g_pad[1]->GetLStickXF() || g_pad[1]->GetLStickYF()) {
		m_player2.PlayAnimation(enAnimClip_Run, 0.2f);
	}
	else if (m_playerState == 1) {
		m_player2.PlayAnimation(enAnimClip_Hit, 0.2f);
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
	}

	else {
		m_player2.PlayAnimation(enAnimClip_Idle, 0.2f);
	}
}

void Player2::ManageState()
{
	switch (m_playerState)
	{
	case0:
		break;
	case1:
		break;
	case2:
		break;
	}
}

void Player2::Hit()
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
			if (aaa != 1) {
				m_hp += 1;
				m_playerState = 1;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player_attack2");
	//配列をfor文で回す。
	for (auto collision : collisions2)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (aaa != 1) {
				m_hp += 1;
				m_playerState = 1;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player_attack3");
	//配列をfor文で回す。
	for (auto collision : collisions3)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (aaa != 1) {
				m_hp += 1;
				m_playerState = 1;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions4)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{

			//HPを減らす。
			if (aaa != 1) {
				//m_hp += 1;
				m_playerState = 1;
			}
		}

	}
}

void Player2::AfterCatch()
{
	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions4)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			
			//HPを減らす。
			if (aaa != 1) {
				shine = false;
				m_hp += 1;
				m_playerState = 1;
			}
		}

	}

	m_timer += g_gameTime->GetFrameDeltaTime();
	if (m_timer >= 3.0f){
		shine = false;
	}
}

void Player2::Render(RenderContext& rc)
{
	m_player2.Draw(rc);
	m_fontRender.Draw(rc);
}
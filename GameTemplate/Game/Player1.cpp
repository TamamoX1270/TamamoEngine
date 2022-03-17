#include "stdafx.h"
#include "Player1.h"
#include "Game.h"

//CollisionObjectを使用したいため、ファイルをインクルードする。
#include "CollisionObject.h"

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
	m_characterController.Init(25.0f, 75.0f, m_position);

	//初期に右を向かせる。
	m_rotation.SetRotationDegX(-90.0f);
	m_rotation.AddRotationDegZ(180.0f);

	m_player.SetPosition(m_position);
	m_player.SetRotation(m_rotation);

	//アニメーションイベント用の関数を設定する。
	m_player.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);

		});

	//Sword」ボーンのID(番号)を取得する。
	m_handBoneId = m_player.FindBoneID(L"mixamorig:RightHandIndex1");

	return true;
}

void Player1::Update()
{	
	Move();
	Rotation();
	AnimationState();
	ManageState();
	ManageJump();

	MakeGuardCollision();

	MakeCollision();


	m_player.Update();
}

void Player1::Move()
{
	//ガード中なら。
	if (m_playerState == 2) {
		//動けない。
		return;
	}
	
	//移動。
	moveSpeed.x = g_pad[0]->GetLStickXF() * 120.0f;

	//キャラの当たり判定の更新。
	m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());

	m_player.SetScale(m_scale);
	m_player.SetPosition(m_position);			 
}

void Player1::Rotation()
{
	//ガード中なら。
	if (m_playerState == 2) {
		//向きを変えられない。
		return;
	}

	//スティックを左に倒すと。
	if (g_pad[0]->GetLStickXF() < 0) {
		m_charaRotState = 1;
	}

	//スティックを右に倒すと。
	else if (g_pad[0]->GetLStickXF() > 0) {
		m_charaRotState = 0;
	}

	//ステートによってキャラの向きを変える。
	switch (m_charaRotState) {
	case 0:
		m_rotation.SetRotationDegX(-90.0f);
		m_rotation.AddRotationDegZ(180.0f);
		break;
	case 1:
		m_rotation.SetRotationDegX(-90.0f);
		m_rotation.AddRotationDegZ(-180.0f);
		break;
	}

	m_player.SetRotation(m_rotation);
}

void Player1::AnimationState()
{
	//被ダメモーションの確認。
	if (g_pad[0]->IsTrigger(enButtonUp)) {
		m_playerState = 5;
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
	//ステートによるアニメーションの管理。
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
		if (m_player.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;

	case 4:
		m_player.PlayAnimation(enAnimClip_Jump, 0.2f);
		moveSpeed.y -= 80.0f;
		if (m_player.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
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

	/*else {
		moveSpeed.y -= 80.0f;
		//80
	}*/


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

void Player1::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
{
	//キーの名前が「attack_start」の時。
	if (wcscmp(eventName, L"Punch_Start") == 0)
	{
		//攻撃中にする。
		m_isUnderAttack = true;
	}
	//キーの名前が「attack_end」の時。
	else if (wcscmp(eventName, L"Punch_End") == 0)
	{
		//攻撃を終わる。
		m_isUnderAttack = false;
	}
}

void Player1::MakeCollision()
{

	if (m_isUnderAttack == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		Vector3 collisionPosition = m_position;
		//座標をプレイヤーの少し前に設定する。
		collisionPosition.y += 60.0f;
		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(collisionPosition,        //座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player_attack");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player.GetBone(m_handBoneId)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player1::MakeGuardCollision()
{
	if (m_playerState != 2) {
		return;
	}

	//コリジョンオブジェクトを作成する。
	auto collisionObject = NewGO<CollisionObject>(0);

	Vector3 collisionPosition = m_position;
	//座標をプレイヤーの少し前に設定する。
	collisionPosition.y +=  60.0f;

	//カプセル状のコリジョンを作成する。
	collisionObject->CreateCapsule(collisionPosition,
		Quaternion::Identity,
		35.0f,
		75.0f
	);

	collisionObject->SetName("P1_Guard");
}

void Player1::Render(RenderContext& rc)
{
	m_player.Draw(rc);
}
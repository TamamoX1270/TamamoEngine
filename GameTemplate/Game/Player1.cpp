#include "stdafx.h"
#include "Player1.h"
#include "Game.h"

#include "Player2.h"
#include "Player3.h"
#include "SoySauceBullet.h"

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
	m_animationClipArray[enAnimClip_Catch].Load("Assets/purototype/catch.tka");
	m_animationClipArray[enAnimClip_Catch].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Punch2].Load("Assets/purototype/punch2.tka");
	m_animationClipArray[enAnimClip_Punch2].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_Kick3].Load("Assets/purototype/kick3.tka");
	m_animationClipArray[enAnimClip_Kick3].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_CPunch].Load("Assets/purototype/cpunch.tka");
	m_animationClipArray[enAnimClip_CPunch].SetLoopFlag(false);

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
	m_handBoneIdCatch = m_player.FindBoneID(L"mixamorig:RightHandIndex1");
	m_handBoneId2 = m_player.FindBoneID(L"mixamorig:LeftHandIndex1");
	m_handBoneId3 = m_player.FindBoneID(L"mixamorig:RightToeBase");
	m_handBoneIdCPunch = m_player.FindBoneID(L"mixamorig:RightHandIndex1");
	

	return true;
}

void Player1::Update()
{
	if (shine == true) {
		AfterCatch();
		return;
	}

	p2_Catch = FindGO<Player2>("player2")->GetPlayer2State();
	//p3_Catch = FindGO<Player3>("player3")->GetPlayer3State();

	int soysoysoysoy = m_soysaucecount;
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", soysoysoysoy);

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-570.0f, -400.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.5f);
	//黒色に設定
	m_fontRender.SetColor(g_vec4White);

	if (p2_Catch != true|| p3_Catch != true) {
	Move();
	Rotation();
	}

	AnimationState();
	ManageState();
	ManageJump();

	Hit2();
	Hit3();
	MakeGuardCollision();
	MakeCatchCollision();

	MakeCollision();
	MakeCollision2();
	MakeCollision3();
	CatchAttackCollision();

	m_player.Update();
}

void Player1::Move()
{
	//ガード中なら。
	if (m_playerState == 2) {
		//動けない。
		return;
	}
	
	//攻撃中なら。
	if (m_playerState == 3 || m_playerState == 7 || m_playerState == 8) {
		//動けない。
		return;
	}

	//掴み中なら。
	if (m_playerState == 6) {
		//動けない。
		return;
	}
	
	//Yボタンが押された時に醤油のストックが１以上なら
	if (g_pad[0]->IsTrigger(enButtonY) && m_soysaucecount >= 1)
	{
		m_soysaucecount--;
		m_soysaucebullet = NewGO<SoySauceBullet>(0, "soysaucebullet");
		//bulletのムーブスピードにプレイヤーの前方向のベクトルを入れてやる。
		m_soysaucebullet->m_moveSpeed = m_forward;
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

	//攻撃中なら。
	if (m_playerState == 3 || m_playerState == 7 || m_playerState == 8) {
		//動けない。
		return;
	}

	//掴み中なら。
	if (m_playerState == 6) {
		//動けない。
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
		//プレイヤーの前方向のベクトルを設定する。
		m_forward = Vector3(0.0f, -1.0f, 0.0f);
		//ベクトルにクウォータニオンを適応してプレイヤーの向きに回転させる
		m_rotation.Apply(m_forward);
		break;
	case 1:
		m_rotation.SetRotationDegX(-90.0f);
		m_rotation.AddRotationDegZ(-180.0f);
		//プレイヤーの前方向のベクトルを設定する。
		m_forward = Vector3(0.0f, -1.0f, 0.0f);
		//ベクトルにクウォータニオンを適応してプレイヤーの向きに回転させる
		m_rotation.Apply(m_forward);
		break;
	}

	m_player.SetRotation(m_rotation);
}

void Player1::AnimationState()
{
	if (m_playerState == 4) {

		m_timer += g_gameTime->GetFrameDeltaTime();
		if (m_timer >= 1.5f) {
			m_playerState = 0;
		}
	}

	//掴み
	if (g_pad[0]->IsTrigger(enButtonRB1) || g_pad[0]->IsTrigger(enButtonRB2)) {
		m_playerState = 6;
	}
	
	//掴み攻撃
	if (p2_Catch == true||p3_Catch == true) {
		if (g_pad[0]->IsTrigger(enButtonB)) {
			m_playerState = 9;
		}
	}
	//通常攻撃
	else if (g_pad[0]->IsTrigger(enButtonB) && atkState == 2) {
		m_playerState = 8;
	}
	else if (g_pad[0]->IsTrigger(enButtonB) && atkState == 1) {
		m_playerState = 7;
	}
	else if (g_pad[0]->IsTrigger(enButtonB)) {
		m_timer = 0.0f;
		m_playerState = 3;
	}


	if (m_playerState != 3 && m_playerState != 4 && m_playerState != 5 && m_playerState != 6 && m_playerState != 7 && m_playerState != 8 && m_playerState != 9) {

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
		m_isUnderAttack = false;
		m_catch = false;
		m_2 = false;
		m_3 = false;
		break;

	case 1:
		m_player.PlayAnimation(enAnimClip_Run, 0.2f);
		break;

	case 2:
		m_player.PlayAnimation(enAnimClip_Guard, 0.2f);
		m_catch = false;
		break;

	case 3:
		m_player.PlayAnimation(enAnimClip_Punch, 0.2f);
		m_catch = false;
		if (m_player.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 4:
		m_player.PlayAnimation(enAnimClip_Jump, 0.2f);
		m_catch = false;
		moveSpeed.y -= 80.0f;
		if (m_player.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;

	case 5:
		m_player.PlayAnimation(enAnimClip_Hit, 0.2f);
		if (m_player.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		m_catch = false;
		break;

	case 6:
		m_player.PlayAnimation(enAnimClip_Catch, 0.2f);
		if (m_player.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;

	case 7:
		m_player.PlayAnimation(enAnimClip_Punch2, 0.2f);
		m_catch = false;
		if (m_player.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 8:
		m_player.PlayAnimation(enAnimClip_Kick3, 0.2f);
		m_catch = false;
		if (m_player.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 9:
		m_player.PlayAnimation(enAnimClip_CPunch, 0.2f);
		m_catch = false;
		if (m_player.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
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
		atkState = 1;
	}

	//キーの名前が「attack_start」の時。
	if (wcscmp(eventName, L"Catch_Start") == 0)
	{
		//攻撃中にする。
		m_catch = true;
	}
	//キーの名前が「attack_end」の時。
	else if (wcscmp(eventName, L"Catch_End") == 0)
	{
		//攻撃を終わる。
		m_catch = false;
	}

	if (wcscmp(eventName, L"Punch2_Start") == 0)
	{
		//攻撃中にする。
		m_2 = true;
	}
	//キーの名前が「attack_end」の時。
	else if (wcscmp(eventName, L"Punch2_End") == 0)
	{
		//攻撃を終わる。
		m_2 = false;
		atkState = 2;
	}

	if (wcscmp(eventName, L"Kick3_Start") == 0)
	{
		//攻撃中にする。
		m_3 = true;
	}
	//キーの名前が「attack_end」の時。
	else if (wcscmp(eventName, L"Kick3_End") == 0)
	{
		//攻撃を終わる。
		m_3 = false;
	}

	if (wcscmp(eventName, L"CPunch_Start") == 0)
	{
		//攻撃中にする。
		m_cpunch = true;
	}
	//キーの名前が「attack_end」の時。
	else if (wcscmp(eventName, L"CPunch_End") == 0)
	{
		//攻撃を終わる。
		m_cpunch = false;
	}
}

void Player1::MakeCollision()
{

	if (m_isUnderAttack == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player1_attack");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player.GetBone(m_handBoneId)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player1::MakeCollision2()
{

	if (m_2 == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player1_attack2");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player.GetBone(m_handBoneId2)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}


void Player1::MakeCollision3()
{

	if (m_3 == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player1_attack3");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player.GetBone(m_handBoneId3)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}


void Player1::MakeGuardCollision()
{
	if (m_playerState != 2 && m_playerState != 5) {
		guard = false;
		return;
	}
	guard = true;

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

void Player1::Hit2()
{
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", m_hp);

	//表示するテキストを設定。
	m_fontHPRender.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontHPRender.SetPosition(Vector3(-740.0f, -400.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontHPRender.SetScale(1.5f);
	//黒色に設定
	m_fontHPRender.SetColor(g_vec4White);

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player2_attack");
	//配列をfor文で回す。
	for (auto collision : collisions1)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player2_attack2");
	//配列をfor文で回す。
	for (auto collision : collisions2)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player2_attack3");
	//配列をfor文で回す。
	for (auto collision : collisions3)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player2_catch");
	//配列をfor文で回す。
	for (auto collision : collisions4)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			m_Catchtimer = 0.0f;
			shine = true;
		}
	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions5 = g_collisionObjectManager->FindCollisionObjects("player2_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions5)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{

			//HPを減らす。
			if (guard != true) {
				//m_hp += 1;
				////////////////////////////////////////////////////
				///ここが改善すべき点！！！
				//////////////////////////////////////////////////// 
				m_playerState = 5;
			}
		}

	}

	//醤油攻撃用のコリジョンの配列を取得する。
	const auto& collisions6 = g_collisionObjectManager->FindCollisionObjects("SoysauceAttack");
	//配列をfor文で回す。
	for (auto collision : collisions6)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}
}

void Player1::Hit3()
{

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player3_attack");
	//配列をfor文で回す。
	for (auto collision : collisions1)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player3_attack2");
	//配列をfor文で回す。
	for (auto collision : collisions2)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player3_attack3");
	//配列をfor文で回す。
	for (auto collision : collisions3)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player3_catch");
	//配列をfor文で回す。
	for (auto collision : collisions4)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			m_Catchtimer = 0.0f;
			shine = true;
		}
	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions5 = g_collisionObjectManager->FindCollisionObjects("player3_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions5)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{

			//HPを減らす。
			if (guard != true) {
				//m_hp += 1;
				////////////////////////////////////////////////////
				///ここが改善すべき点！！！
				//////////////////////////////////////////////////// 
				m_playerState = 5;
			}
		}

	}

}

void Player1::AfterCatch()
{
	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player2_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions2)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{

			//HPを減らす。
			if (guard != true) {
				shine = false;
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player3_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions3)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{

			//HPを減らす。
			if (guard != true) {
				shine = false;
				m_hp += 1;
				m_playerState = 5;
			}
		}

	}

	m_Catchtimer += g_gameTime->GetFrameDeltaTime();
	if (m_Catchtimer >= 3.0f) {
		shine = false;
	}
}

void Player1::MakeCatchCollision()
{
	if (m_catch == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player1_catch");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player.GetBone(m_handBoneIdCatch)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player1::CatchAttackCollision()
{
	if (m_cpunch == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player1_cpunch");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player.GetBone(m_handBoneIdCatch)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player1::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	m_fontHPRender.Draw(rc);
	m_player.Draw(rc);
}
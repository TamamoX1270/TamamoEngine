#include "stdafx.h"
#include "Player2.h"
#include "Game.h"
#include "GameUI.h"

#include "Player1.h"
#include "Player3.h"
#include "Player4.h"
#include "SoySauceBullet.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

//CollisionObjectを使用したいため、ファイルをインクルードする。
#include "CollisionObject.h"

//EffectEmitterを使用する時はファイルをインクルードする必要がある。
#include "graphics/effect/EffectEmitter.h"


bool Player2::Start()
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
	m_animationClipArray[enAnimClip_FlyAway].Load("Assets/purototype/hardhit.tka");
	m_animationClipArray[enAnimClip_FlyAway].SetLoopFlag(false);
	m_animationClipArray[enAnimClip_RiseUp].Load("Assets/purototype/riseup.tka");
	m_animationClipArray[enAnimClip_RiseUp].SetLoopFlag(false);

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/bigkome.efk");
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/smallkome.efk");

	//モデルの読み込み
	m_player2.Init("Assets/purototype/model3/tuna.tkm", m_animationClipArray, enAnimClip_Num, enModelUpAxisY);

	//キャラコンを初期化する。
	m_characterController.Init(25.0f, 75.0f, m_position);

	//初期に右を向かせる。
	m_rotation.SetRotationDegX(-90.0f);
	m_rotation.AddRotationDegZ(180.0f);

	m_player2.SetPosition(m_position);
	m_player2.SetRotation(m_rotation);

	//アニメーションイベント用の関数を設定する。
	m_player2.AddAnimationEvent([&](const wchar_t* clipName, const wchar_t* eventName) {
		OnAnimationEvent(clipName, eventName);

		});

	//Sword」ボーンのID(番号)を取得する。
	m_handBoneId = m_player2.FindBoneID(L"mixamorig:RightHandIndex1");
	m_handBoneIdCatch = m_player2.FindBoneID(L"mixamorig:RightHandIndex1");
	m_handBoneId2 = m_player2.FindBoneID(L"mixamorig:LeftHandIndex1");
	m_handBoneId3 = m_player2.FindBoneID(L"mixamorig:RightToeBase");
	m_handBoneIdCPunch = m_player2.FindBoneID(L"mixamorig:RightHandIndex1");

	//効果音を読み込む。
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/jump_2.wav");
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/punch_1.wav");
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/punch_2.wav");
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/punch_3.wav");
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/punch_suburi1.wav");
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/punch_suburi2.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/kick_suburi.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/syouyu_beam.wav");

	return true;
}

void Player2::Update()
{
	if (m_owaowari == true) {
		m_player2.PlayAnimation(enAnimClip_Idle, 0.2f);
		m_player2.Update();
		return;
	}
	m_owaowari = FindGO<GameUI>("gameui")->GetSokomade();

	if (shine == true) {
		AfterCatch();
		return;
	}

	p1_Catch = FindGO<Player1>("player1")->GetPlayer1State();
	p3_Catch = FindGO<Player3>("player3")->GetPlayer3State();
	p4_Catch = FindGO<Player4>("player4")->GetPlayer4State();

	int soysoysoysoy = m_soysaucecount;
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", soysoysoysoy);

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-100.0f, -400.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.5f);
	//黒色に設定
	m_fontRender.SetColor(g_vec4White);

	if (p1_Catch != true && p3_Catch != true) {
		Move();
		Rotation();
	}

	AnimationState();
	ManageState();

	Hit1();
	Hit3();
	Hit4();
	MakeGuardCollision();
	autoGuard();
	MakeCatchCollision();

	ManageJump();
	MakeCollision();
	MakeCollision2();
	MakeCollision3();
	CatchAttackCollision();

	RingOut();

	m_player2.Update();
}

void Player2::Move()
{
	/*
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

	//ダメージを食らっているなら。
	if (m_playerState == 5 || m_playerState == 10) {
		//動けない。
		return;
	}

	//起き上がっているなら。
	if (m_playerState == 11) {
		//動けない。
		return;
	}*/

	//Yボタンが押された時に醤油のストックが１以上なら
	if (g_pad[1]->IsTrigger(enButtonY) && m_soysaucecount >= 1)
	{
		m_soysaucecount--;
		m_soysaucebullet = NewGO<SoySauceBullet>(0, "soysaucebullet");
		//bulletのムーブスピードにプレイヤーの前方向のベクトルを入れてやる。
		m_soysaucebullet->m_moveSpeed = m_forward;
	}

	if (m_playerState == 0 || m_playerState == 1 || m_playerState == 4 || m_playerState == 9) {
		//移動。
		moveSpeed.x = g_pad[1]->GetLStickXF() * 120.0f;
	}

	//キャラがｚ軸方向にずれるのを防ぐコード
	if (m_position.z > 0.1f || m_position.z < -0.1f) {
		m_position.z = 0.0f;
	}

	if (m_playerState == 0 || m_playerState == 1 || m_playerState == 4 || m_playerState == 9) {
		//キャラの当たり判定の更新。
		m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
	}
	
	m_player2.SetScale(m_scale);
	m_player2.SetPosition(m_position);
}

void Player2::Rotation()
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

	//ダメージを食らっているなら。
	if (m_playerState == 5 || m_playerState == 10) {
		//動けない。
		return;
	}

	//起き上がっているなら。
	if (m_playerState == 11) {
		//動けない。
		return;
	}


	//スティックを左に倒すと。
	if (g_pad[1]->GetLStickXF() < 0) {
		m_charaRotState = 1;
	}

	//スティックを右に倒すと。
	else if (g_pad[1]->GetLStickXF() > 0) {
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

	m_player2.SetRotation(m_rotation);
}

void Player2::AnimationState()
{
	if (m_playerState == 4 || m_playerState == 5 || m_playerState == 10 || m_playerState == 11) {
		return;
	}

	//掴み
	if (g_pad[1]->IsTrigger(enButtonRB1) || g_pad[1]->IsTrigger(enButtonRB2)) {
		m_playerState = 6;
	}

	//掴み攻撃
	if (p1_Catch == true || p3_Catch == true || p4_Catch == true) {
		if (g_pad[1]->IsTrigger(enButtonB)) {
			m_playerState = 9;
		}
	}
	//通常攻撃
	else if (g_pad[1]->IsTrigger(enButtonB) && atkState == 2) {
		m_playerState = 8;
	}
	else if (g_pad[1]->IsTrigger(enButtonB) && atkState == 1) {
		m_playerState = 7;
	}
	else if (g_pad[1]->IsTrigger(enButtonB)) {
		m_playerState = 3;
	}


	if (m_playerState != 3 && m_playerState != 4 && m_playerState != 5 && m_playerState != 6 && m_playerState != 7 && m_playerState != 8 && m_playerState != 9) {

		if (g_pad[1]->IsPress(enButtonLB1) || g_pad[1]->IsPress(enButtonLB2)) {
			m_playerState = 2;
		}

		else if (g_pad[1]->IsTrigger(enButtonX)) {
			//効果音を再生する。
			SoundSource* P2se = NewGO<SoundSource>(3);
			P2se->Init(3);
			P2se->Play(false);
			m_playerState = 4;
		}

		else if (g_pad[1]->GetLStickXF() || g_pad[1]->GetLStickYF()) {
			m_playerState = 1;
		}

		else if (!g_pad[1]->IsPressAnyKey()) {
			m_playerState = 0;
		}
	}
}

void Player2::ManageState()
{
	//ステートによるアニメーションの管理。
	switch (m_playerState)
	{
	case 0:
		m_player2.PlayAnimation(enAnimClip_Idle, 0.2f);
		m_isUnderAttack = false;
		m_catch = false;
		m_2 = false;
		m_3 = false;
		break;

	case 1:
		m_player2.PlayAnimation(enAnimClip_Run, 0.2f);
		m_isUnderAttack = false;
		m_catch = false;
		m_2 = false;
		m_3 = false;
		break;

	case 2:
		m_player2.PlayAnimation(enAnimClip_Guard, 0.2f);
		m_catch = false;
		break;

	case 3:
		m_player2.PlayAnimation(enAnimClip_Punch, 0.2f);
		m_catch = false;
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 4:
		m_player2.PlayAnimation(enAnimClip_Jump, 0.2f);
		m_catch = false;
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;

	case 5:
		m_player2.PlayAnimation(enAnimClip_Hit, 0.2f);
		m_jumpState = false;
		atkState = 0;
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		m_catch = false;
		break;

	case 6:
		m_player2.PlayAnimation(enAnimClip_Catch, 0.2f);
		atkState = 0;
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;

	case 7:
		m_player2.PlayAnimation(enAnimClip_Punch2, 0.2f);
		m_catch = false;
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 8:
		m_player2.PlayAnimation(enAnimClip_Kick3, 0.2f);
		m_catch = false;
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 9:
		m_player2.PlayAnimation(enAnimClip_CPunch, 0.2f);
		m_catch = false;
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
			atkState = 0;
		}
		break;

	case 10:
		m_player2.PlayAnimation(enAnimClip_FlyAway, 0.2f);
		m_catch = false;
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 11;
			atkState = 0;
		}
		break;

	case 11:
		m_player2.PlayAnimation(enAnimClip_RiseUp, 0.2f);
		if (m_player2.IsPlayingAnimation() == false) {
			m_playerState = 0;
		}
		break;
	}

}

void Player2::ManageJump()
{
	//ジャンプ。
	if (m_jumpState == true) {
		moveSpeed.y = 450.0f;
	}
	//バグが起こらない重力。
	else if (m_position.y > 20.0f || m_position.y < -20.0f) {
		moveSpeed.y -= 80.0f;
	}
	else {
		moveSpeed.y = -250.0f;
	}
}

void Player2::OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName)
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

	if (wcscmp(eventName, L"Jump_Start") == 0)
	{
		//攻撃中にする。
		m_jumpState = true;
	}
	//キーの名前が「attack_end」の時。
	else if (wcscmp(eventName, L"Jump_End") == 0)
	{
		//攻撃を終わる。
		m_jumpState = false;
	}
}

void Player2::MakeCollision()
{

	if (m_isUnderAttack == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player2_attack");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player2.GetBone(m_handBoneId)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player2::MakeCollision2()
{

	if (m_2 == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player2_attack2");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player2.GetBone(m_handBoneId2)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}


void Player2::MakeCollision3()
{

	if (m_3 == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player2_attack3");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player2.GetBone(m_handBoneId3)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}


void Player2::MakeGuardCollision()
{
	if (m_playerState != 2) {
		guard = false;
		return;
	}
	guard = true;

	//コリジョンオブジェクトを作成する。
	auto collisionObject = NewGO<CollisionObject>(0);

	Vector3 collisionPosition = m_position;
	//座標をプレイヤーの少し前に設定する。
	collisionPosition.y += 60.0f;

	//カプセル状のコリジョンを作成する。
	collisionObject->CreateCapsule(collisionPosition,
		Quaternion::Identity,
		35.0f,
		75.0f
	);

	collisionObject->SetName("P2_Guard");

	//////////////////////////////////////////////////////////////////////////////////////////////

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player1_attack");
	//配列をfor文で回す。
	for (auto collision : collisions1)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(collisionObject))
		{
			FindGO<Player1>("player1")->SetPlayer1PlayerState11();
		}

	}

	/////////////////////////////////////////////////////////////////////////////////////////
}

void Player2::autoGuard()
{
	if (m_playerState != 5 && m_playerState != 10 && m_playerState != 11) {
		return;
	}
	guard = true;

	//コリジョンオブジェクトを作成する。
	auto collisionObject = NewGO<CollisionObject>(0);

	Vector3 collisionPosition = m_position;
	//座標をプレイヤーの少し前に設定する。
	collisionPosition.y += 60.0f;

	//カプセル状のコリジョンを作成する。
	collisionObject->CreateCapsule(collisionPosition,
		Quaternion::Identity,
		35.0f,
		75.0f
	);

	collisionObject->SetName("P2_autoGuard");
}

void Player2::Hit1()
{
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", m_hp);

	//表示するテキストを設定。
	m_fontHPRender.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontHPRender.SetPosition(Vector3(-260.0f, -400.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontHPRender.SetScale(1.5f);
	//黒色に設定
	m_fontHPRender.SetColor(g_vec4White);

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player1_attack");
	//配列をfor文で回す。
	for (auto collision : collisions1)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				//エフェクト。
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(1);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player1からplayer2を向くベクトルを求める。
				Vector3 a = m_position - FindGO<Player1>("player1")->GetPlayer1Position();
				a.Normalize();
				if (a.x > 0) {
					//体の向きを変える。
					m_charaRotState = 1;

					//少しノックバックする。
					moveSpeed.x += a.x * 200.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//少しノックバックする。
					moveSpeed.x += a.x * 200.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//効果音を再生する。
				SoundSource* P2se = NewGO<SoundSource>(4);
				P2se->Init(4);
				P2se->Play(false);

				//HPの減少。
				m_hp -= 2;

				//被ダメモーションの再生。
				m_playerState = 5;
			}
		}
	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player1_attack2");
	//配列をfor文で回す。
	for (auto collision : collisions2)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				//エフェクト。
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(1);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player1からplayer2を向くベクトルを求める。
				Vector3 a = m_position - FindGO<Player1>("player1")->GetPlayer1Position();
				a.Normalize();
				if (a.x > 0) {
					//体の向きを変える。
					m_charaRotState = 1;

					//少しノックバックする。
					moveSpeed.x += a.x * 500.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//少しノックバックする。
					moveSpeed.x += a.x * 500.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//効果音を再生する。
				SoundSource* P2se = NewGO<SoundSource>(5);
				P2se->Init(5);
				P2se->Play(false);

				m_hp -= 5;
				m_playerState = 5;
			}
		}
	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player1_attack3");
	//配列をfor文で回す。
	for (auto collision : collisions3)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				//エフェクト。
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(0);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player1からplayer2を向くベクトルを求める。
				Vector3 a = m_position - FindGO<Player1>("player1")->GetPlayer1Position();
				a.Normalize();
				if (a.x > 0) {
					//体の向きを変える。
					m_charaRotState = 1;

					//少しノックバックする。
					moveSpeed.x += a.x * 800.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//少しノックバックする。
					moveSpeed.x += a.x * 800.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//効果音を再生する。
				SoundSource* P2se = NewGO<SoundSource>(6);
				P2se->Init(6);
				P2se->Play(false);

				m_hp -= 8;
				m_playerState = 10;
			}
		}
	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player1_catch");
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
	const auto& collisions5 = g_collisionObjectManager->FindCollisionObjects("player1_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions5)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				//m_hp -= 1;
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
				m_hp -= 2;
				m_playerState = 5;
			}
		}
	}

	//HPの上限下限の設定。
	if (m_hp > m_max) {
		m_hp = m_max;
	}
	else if (m_hp < m_min) {
		m_hp = m_min;
	}
}

void Player2::Hit3()
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
				m_hp -= 1;
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
				m_hp -= 1;
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
				m_hp -= 1;
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
				//m_hp -= 1;
				////////////////////////////////////////////////////
				///ここが改善すべき点！！！
				//////////////////////////////////////////////////// 
				m_playerState = 5;
			}
		}
	}
}

void Player2::Hit4()
{
	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player4_attack");
	//配列をfor文で回す。
	for (auto collision : collisions1)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp -= 1;
				m_playerState = 5;
			}
		}
	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player4_attack2");
	//配列をfor文で回す。
	for (auto collision : collisions2)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp -= 1;
				m_playerState = 5;
			}
		}
	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions3 = g_collisionObjectManager->FindCollisionObjects("player4_attack3");
	//配列をfor文で回す。
	for (auto collision : collisions3)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				m_hp -= 1;
				m_playerState = 5;
			}
		}
	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player4_catch");
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
	const auto& collisions5 = g_collisionObjectManager->FindCollisionObjects("player4_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions5)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				//m_hp -= 1;
				////////////////////////////////////////////////////
				///ここが改善すべき点！！！
				//////////////////////////////////////////////////// 
				m_playerState = 5;
			}
		}
	}
}

void Player2::AfterCatch()
{
	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions1 = g_collisionObjectManager->FindCollisionObjects("player1_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions1)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				shine = false;

				//エフェクト。
				m_efpos1 = m_position;
				m_efpos1.y = 50.0f;
				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(0);
				effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
				effectEmitter->SetPosition(m_efpos1);
				effectEmitter->Play();

				//player1からplayer2を向くベクトルを求める。
				Vector3 a = m_position - FindGO<Player1>("player1")->GetPlayer1Position();
				a.Normalize();
				if (a.x > 0) {
					//体の向きを変える。
					m_charaRotState = 1;

					//少しノックバックする。
					moveSpeed.x += a.x * 2000.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}
				else if (a.x < 0) {
					m_charaRotState = 0;
					//少しノックバックする。
					moveSpeed.x += a.x * 2000.0f;
					m_position = m_characterController.Execute(moveSpeed, g_gameTime->GetFrameDeltaTime());
				}

				//効果音を再生する。
				SoundSource* P2se = NewGO<SoundSource>(10);
				P2se->Init(10);
				P2se->Play(false);

				m_hp -= 5;
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
				m_hp -= 1;
				m_playerState = 5;
			}
		}
	}

	//敵の攻撃用のコリジョンの配列を取得する。
	const auto& collisions4 = g_collisionObjectManager->FindCollisionObjects("player4_cpunch");
	//配列をfor文で回す。
	for (auto collision : collisions4)
	{
		//コリジョンとキャラコンが衝突したら。
		if (collision->IsHit(m_characterController))
		{
			//HPを減らす。
			if (guard != true) {
				shine = false;
				m_hp -= 1;
				m_playerState = 5;
			}
		}
	}

	m_Catchtimer += g_gameTime->GetFrameDeltaTime();

	if (m_Catchtimer >= 3.0f) {
		shine = false;
	}
}

void Player2::MakeCatchCollision()
{
	if (m_catch == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player2_catch");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player2.GetBone(m_handBoneIdCatch)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player2::CatchAttackCollision()
{
	if (m_cpunch == true) {

		//コリジョンオブジェクトを作成する。
		auto collisionObject = NewGO<CollisionObject>(0);

		//球状のコリジョンを作成する。
		collisionObject->CreateSphere(m_position,				//座標。
			Quaternion::Identity,                               //回転。
			10.0f                                               //半径。
		);

		collisionObject->SetName("player2_cpunch");

		//「Sword」ボーンのワールド行列を取得する。
		Matrix matrix = m_player2.GetBone(m_handBoneIdCatch)->GetWorldMatrix();
		//「Sword」ボーンのワールド行列をコリジョンに適用する。
		collisionObject->SetWorldMatrix(matrix);
	}
}

void Player2::RingOut()
{
	//左端。
	if (m_position.x < -1070.0f && m_position.y < -160.0f) {
		m_hp -= 5;
	}
	//右端。
	if (m_position.x > 1070.0f && m_position.y < -160.0f) {
		m_hp -= 5;
	}
}

void Player2::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	m_fontHPRender.Draw(rc);
	m_player2.Draw(rc);
}
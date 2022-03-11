#include "stdafx.h"
#include "GameCamera.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(0.0f, 180.0f, -300.0f);
	//0.0f, 125.0f, -250.0f
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player1>("player1");
	m_player2 = FindGO<Player2>("player2");
	m_player3 = FindGO<Player3>("player3");
	m_player4 = FindGO<Player4>("player4");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(60000.0f);

	return true;
}

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

void GameCamera::Update()
{
	//カメラを更新。
	//注視点を計算する。
	Vector3 target;
	//プレイヤー１～４の中間地点を注視点にする。
	target.x = (m_player->GetPlayer1Position().x + m_player2->GetPlayer2Position().x + m_player3->GetPlayer3Position().x + m_player4->GetPlayer4Position().x) / 4;
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 100.0f;

	target.z = fabsf(target.x) * -1.1f;
	if (target.z <= -5000.0f) {
		target.z = -49.0f;
	}
	else if (target.z >= 30.0f) {
		target.z = 29.0f;
	}

	Vector3 toCameraPosOld = m_toCameraPos;
	
	/*Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * x);
	qRot.Apply(m_toCameraPos);

	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * y);
	qRot.Apply(m_toCameraPos);*/

	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.2f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}

	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;
	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();
}
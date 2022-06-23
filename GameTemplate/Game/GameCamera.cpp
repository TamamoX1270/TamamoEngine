#include "stdafx.h"
#include "GameCamera.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"

namespace
{
	Vector3 TO_CAMERA_POS = { 0.0f,0.0f,-200.0f };
	float PLAYER_HEIGHT = 100.0f;
}

bool GameCamera::Start()
{
	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(TO_CAMERA_POS);

	//プレイヤーのインスタンスを探す。
	m_player1 = FindGO<Player1>("player1");
	m_player2 = FindGO<Player2>("player2");
	m_player3 = FindGO<Player3>("player3");
	m_player4 = FindGO<Player4>("player4");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(60000.0f);

	return true;
}

void GameCamera::Update()
{
	//4人のプレイヤーの位置を配列に入れる。
	//生きているプレイヤーを数える。
	float m_getPosition[4];
	int numActivePlayer = 0;
	if (m_player1->GetPlayerHP() >= 0) {
		m_getPosition[numActivePlayer] = m_player1->GetPlayer1Position().x;
		numActivePlayer++;
	}
	if (m_player2->GetPlayer2HP() >= 0) {
		m_getPosition[numActivePlayer] = m_player2->GetPlayer2Position().x;
		numActivePlayer++;
	}
	if (m_player3->GetPlayer3HP() >= 0) {
		m_getPosition[numActivePlayer] = m_player3->GetPlayer3Position().x;
		numActivePlayer++;
	}
	if (m_player4->GetPlayer4HP() >= 0) {
		m_getPosition[numActivePlayer] = m_player4->GetPlayer4Position().x;
		numActivePlayer++;
	}

	//一番右のplayerを探す。
	m_xPosMax = m_getPosition[0];

	for (int i = 0; i < numActivePlayer; i++) {
		if (m_xPosMax <= m_getPosition[i]) {
			m_xPosMax = m_getPosition[i];
		}
	}

	//一番左のpleyerを探す。
	m_xPosMin = m_getPosition[0];

	for (int i = 0; i < numActivePlayer; i++) {
		if (m_xPosMin >= m_getPosition[i]) {
			m_xPosMin = m_getPosition[i];
		}
	}

	//その中心を注視点にする。
	target.x = (m_xPosMax + m_xPosMin) / 2;


	//プレイヤーの頭上を注視点とする。
	//プレイヤーの距離に応じて少し上に上がる。
	target.y = (m_xPosMax - m_xPosMin) * 0.05f + PLAYER_HEIGHT;

	//一番左と一番右のプレイヤーの距離に応じてカメラを引く。
	target.z = (m_xPosMax - m_xPosMin) * -0.6f;

	//カメラの引きの上限。
	if (target.z <= -750.0f) {
		target.z = -749.0f;
	}

	//視点を計算する。
	Vector3 CameraPos = target + m_toCameraPos;

	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(CameraPos);

	//カメラの更新。
	g_camera3D->Update();
}
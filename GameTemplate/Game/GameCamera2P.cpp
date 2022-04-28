#include "stdafx.h"
#include "GameCamera2P.h"

#include "Player1.h"
#include "Player2.h"

bool GameCamera2P::Start()
{
	//注視点から視点までのベクトルを設定。
	//0.0f, 100.0f, -200.0f
	m_toCameraPos.Set(0.0f, 0.0f, -200.0f);

	//プレイヤーのインスタンスを探す。
	m_player1 = FindGO<Player1>("player1");
	m_player2 = FindGO<Player2>("player2");

	//カメラのニアクリップとファークリップを設定する。
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(60000.0f);

	return true;
}

GameCamera2P::GameCamera2P()
{

}

GameCamera2P::~GameCamera2P()
{

}

void GameCamera2P::Update()
{
	//カメラを更新。
	//注視点を計算する。
	Vector3 target;

	//2人のプレイヤーの位置を配列に入れる。	
	float m_getPosition[2];
	m_getPosition[0] = m_player1->GetPlayer1Position().x;
	m_getPosition[1] = m_player2->GetPlayer2Position().x;

	//一番右のやつを探す。
	m_max = m_getPosition[0];

	for (int i = 0; i < 2; i++) {
		if (m_max <= m_getPosition[i]) {
			m_max = m_getPosition[i];
		}
	}

	//一番左のやつを探す。
	m_min = m_getPosition[0];

	for (int i = 0; i < 2; i++) {
		if (m_min >= m_getPosition[i]) {
			m_min = m_getPosition[i];
		}
	}

	//その中心を注視点にする。
	target.x = (m_max + m_min) / 2;


	//プレイヤの足元からちょっと上を注視点とする。
	//プレイヤーの距離に応じて少し上に上がる。
	target.y = (m_max - m_min) * 0.05f + 100.0f;

	//一番左と一番右のプレイヤーの距離に応じてカメラを引く。
	target.z = (m_max - m_min) * -0.6f;

	//上限。
	if (target.z <= -750.0f) {
		target.z = -749.0f;
	}
	else if (target.z >= 30.0f) {
		target.z = 29.0f;
	}

	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;

	//メインカメラに注視点と視点を設定する。
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);

	//カメラの更新。
	g_camera3D->Update();
}
#include "stdafx.h"
#include "Game.h"
#include "GameUI.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "GameCamera2P.h"
#include "GameCamera3P.h"
#include "SoySauce.h"

bool Game::Start()
{
	//プレイヤーオブジェクトを作成する。
	m_player = NewGO<Player1>(0, "player1");
	m_player2 = NewGO<Player2>(0, "player2");
	//m_player3 = NewGO<Player3>(0, "player3");
	//m_player4 = NewGO<Player4>(0, "player4");

	//GameUIの生成
	m_gamingshigureui = NewGO<GameUI>(0, "gameui");
	//醤油オブジェクトを生成する。
	m_soysauce = NewGO<SoySauce>(0, "soysauce");
	//背景オブジェクトを作成する。
	m_backGround = NewGO<BackGround>(0, "background");

	//m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//m_gameCamera3 = NewGO<GameCamera3P>(0, "gamecamera3");
	m_gameCamera2 = NewGO<GameCamera2P>(0, "gamecamera2");

	return true;
}

Game::Game()
{
}

void Game::Update()
{
	int b = 4;
	wchar_t wcsbuf1[256];
	swprintf_s(wcsbuf1, 256, L"%d", b);

	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf1);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(1.5f);
	//黒色に設定
	m_fontRender.SetColor(g_vec4White);
	//(*･ω･)/ﾊｰｲ
	/*
	// 左スティック(キーボード：WASD)で平行移動。
	m_pointligpos.x += g_pad[0]->GetLStickXF();
	m_pointligpos.z += g_pad[0]->GetLStickYF();
	*/
	//m_pointligpos.y = 50.0f;
	m_pointligpos.x = 5000.0f;
	g_directionLig.SetPointPos(m_pointligpos);

	m_spPosition.y = 50.0f;
	m_spPosition.x = 5000.0f;
	//左のアナログスティックで動かす。
	//m_spPosition.x -= g_pad[0]->GetLStickXF();
	/*
	if (g_pad[0]->IsPress(enButtonB)) {
		//Bボタンが一緒に押されていたらY軸方向に動かす。
		m_spPosition.y += g_pad[0]->GetLStickYF();
	}
	else {
		//Z軸方向に動かす。
		m_spPosition.z -= g_pad[0]->GetLStickYF();
	}
	*/
	g_directionLig.SetSpotPos(m_spPosition);//スポットライトの位置を設定
	
	/*
	//初期方向は斜め下にする。
	m_spDirection.x = 1.0f;
	m_spDirection.y = -1.0f;
	m_spDirection.z = 1.0f;
	*/

	//ディレクションライトの当たる方向とカラーをセットできちゃいます
	//g_directionLig.SetLigDirection({ 0.0f,1.0f,-1.0f });


	/*if (g_pad[0]->IsPress(enButtonB))
	{
		m_directionligColor.x += 0.1f;
	}
	if (g_pad[0]->IsPress(enButtonA))
	{
		m_directionligColor.y += 0.1f;
		m_directionligColor.z += 0.1f;
	}
	g_directionLig.SetLigColor({ m_directionligColor });*/
	g_directionLig.SetLigColor({0.5f,0.5f,0.5f});
}

void Game::Render(RenderContext& rc)
{
	//m_fontRender.Draw(rc);
}
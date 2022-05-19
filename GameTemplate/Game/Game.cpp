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
#include "SoySauceBullet.h"
#include "SideWall.h"
#include "Title.h"
#include "Result.h"
#include "SpecialCamera.h"
#include "PlayerPoint.h"

bool Game::Start()
{
	//プレイヤーオブジェクトを作成する。
	m_player = NewGO<Player1>(0, "player1");
	m_player2 = NewGO<Player2>(0, "player2");
	//if (m_player3 != nullptr)
	//{
		m_player3 = NewGO<Player3>(0, "player3");
	//}
	//if (m_player4 != nullptr)
	//{
		m_player4 = NewGO<Player4>(0, "player4");
	//}

	//GameUIの生成
	m_gamingshigureui = NewGO<GameUI>(0, "gameui");
	//左右の壁オブジェクトを生成する。
	m_sidewall = NewGO<SideWall>(0, "sidewall");
	//背景オブジェクトを作成する。
	m_backGround = NewGO<BackGround>(0, "background");
	//プレイヤーの取得ポイントを保存するクラスを生成する。
	m_playerpoint = NewGO<PlayerPoint>(0, "playerpoint");
	sscamera = NewGO<SpecialCamera>(0, "specialcamera");

	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//m_gameCamera3 = NewGO<GameCamera3P>(0, "gamecamera3");
	//m_gameCamera2 = NewGO<GameCamera2P>(0, "gamecamera2");

	return true;
}

Game::Game()
{

}

Game::~Game()
{
	DeleteGO(m_gameCamera);
	//DeleteGO(m_gameCamera2);
	DeleteGO(sscamera);
	DeleteGO(m_backGround);
	DeleteGO(m_sidewall);
	DeleteGO(m_gamingshigureui);
}
void Game::Update()
{
	GameDelete();
	Camera();
	
	if (m_soysoucenewgotimer == false)
	{
		soysauce_timer += g_gameTime->GetFrameDeltaTime();
	}
	if (soysauce_timer >= 5.0f)
	{
		m_soysoucenewgotimer = true;
	}
	if (m_soysoucenewgotimer == true)
	{
		m_soysaucenewgo = true;
	}
	if (m_soysaucenewgo == true)
	{
		//醤油オブジェクトを生成する。
		m_soysauce = NewGO<SoySauce>(0, "soysauce");
		m_soysoucenewgotimer = false;
		m_soysaucenewgo = false;
		soysauce_timer = 0.0f;
	}
	//(*･ω･)/ﾊｰｲ
	/*
	// 左スティック(キーボード：WASD)で平行移動。
	m_pointligpos.x += g_pad[0]->GetLStickXF();
	m_pointligpos.z += g_pad[0]->GetLStickYF();
	*/
	//m_pointligpos.y = 50.0f;

	m_pointligpos.y = 0.0f;
	m_pointligpos.x = 20000.0f;
	g_directionLig.SetPointPos(m_pointligpos);

	m_spPosition.x = 0.0f;
	m_spPosition.y = 250.0f;
	m_spPosition.z = 100.0f;

	//m_spDirection = { 1.0f,0.0f,1.0f };
	//m_spDirection.Normalize();

	//g_directionLig.SetSpotAngle(100.0f);
	//g_directionLig.SetSpotRange(100.0f);
	//g_directionLig.SetSpotDir({ m_spDirection });
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
//	g_directionLig.SetLigColor({0.5f,0.5f,0.5f});

}

void Game::Camera()
{
		if (g_pad[0]->IsPress(enButtonUp)) {
			m_cameraState = 1;
		}
		else {
			m_cameraState = 0;
		}

		switch (m_cameraState) {
		case 0:
			m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
			break;
		case 1:
			sscamera = NewGO<SpecialCamera>(0, "specialcamera");
			break;
		}
}

void Game::GameDelete()
{
	//ゲームデリートステートがtrueの時
	if (m_gamedelete == true)
	{
		NewGO<Result>(0, "result");

		//PHPにプレイヤーのHPを格納する。
		int MaxPHP = 0;
		int PHP  = 0;
		int PHP2 = 0;
		int PHP3 = 0;
		int PHP4 = 0;
		PHP = m_player->GetPlayerHP();
		PHP2 = m_player2->GetPlayer2HP();
		//if (m_player3 != nullptr)
		//{
			PHP3 = m_player3->GetPlayer3HP();
		//}
		//if (m_player4 != nullptr)
		//{
			PHP4 = m_player4->GetPlayer4HP();
		//}

		//一番大きいHPの奴を格納する。
		if (MaxPHP < PHP)
		{
			MaxPHP = PHP;
			FindGO<Result>("result")->SetWinPlayer(0);
		}
		if (MaxPHP < PHP2)
		{
			MaxPHP = PHP2;
			FindGO<Result>("result")->SetWinPlayer(1);
		}
		//if (m_player3 != nullptr)
		//{
			if (MaxPHP < PHP3)
			{
				MaxPHP = PHP3;
				FindGO<Result>("result")->SetWinPlayer(2);
			}
		//}
		//if (m_player4 != nullptr)
		//{
			if (MaxPHP < PHP4)
			{
				MaxPHP = PHP4;
				FindGO<Result>("result")->SetWinPlayer(3);
			}
		//}

		//引き分け
		if (PHP == PHP2)
		{
			FindGO<Result>("result")->SetDrawFlag();
		}
		if (m_player3 != nullptr)
		{
			if (PHP==PHP3||
				PHP2==PHP3)
			{
				FindGO<Result>("result")->SetDrawFlag();
			}
		}
		if (m_player4 != nullptr)
		{
			if (PHP==PHP4||
				PHP2==PHP4||
				PHP3==PHP4
				)
			{
				FindGO<Result>("result")->SetDrawFlag();
			}
		}

		const auto& soysauces = FindGOs<SoySauce>("soysauce");
		//配列の個数を取得する
		int number = soysauces.size();
		for (int i = 0; i < number; i++)
		{
			DeleteGO(soysauces[i]);
		}
		const auto& soysaucebullets = FindGOs<SoySauceBullet>("soysaucebullet");
		//配列の個数を取得する
		int number2 = soysaucebullets.size();
		for (int s = 0; s < number2; s++)
		{
			DeleteGO(soysaucebullets[s]);
		}
		const auto& gamecamera = FindGOs<GameCamera>("gamecamera");
		//配列の個数を取得する
		int number3 = gamecamera.size();
		for (int c = 0; c < number3; c++)
		{
			DeleteGO(gamecamera[c]);
		}
		const auto& gamecamera2 = FindGOs<GameCamera2P>("gamecamera2");
		//配列の個数を取得する
		int number4 = gamecamera2.size();
		for (int c = 0; c < number4; c++)
		{
			DeleteGO(gamecamera2[c]);
		}
		const auto& gameSPcamera = FindGOs<SpecialCamera>("specialcamera");
		//配列の個数を取得する
		int number5 = gameSPcamera.size();
		for (int c = 0; c < number5; c++)
		{
			DeleteGO(gameSPcamera[c]);
		}
		DeleteGO(m_player);
		DeleteGO(m_player2);
		DeleteGO(m_player3);
		DeleteGO(m_player4);
		DeleteGO(this);
	}
	//ゲームデリートステートがtrueじゃない時
	else
	{
		if (m_player4 != nullptr)
		{
			if (m_player->GetPlayerHP() <= 0 &&
				m_player2->GetPlayer2HP() <= 0 &&
				m_player3->GetPlayer3HP() <= 0 ||
				m_player->GetPlayerHP() <= 0 &&
				m_player2->GetPlayer2HP() <= 0 &&
				m_player4->GetPlayer4HP() <= 0 ||
				m_player->GetPlayerHP() <= 0 &&
				m_player3->GetPlayer3HP() <= 0 &&
				m_player4->GetPlayer4HP() <= 0 ||
				m_player2->GetPlayer2HP() <= 0 &&
				m_player3->GetPlayer3HP() <= 0 &&
				m_player4->GetPlayer4HP() <= 0)
			{
				m_gamingshigureui->SetSokomade();
			}
		}
		else if (m_player3 != nullptr)
		{
			if (m_player->GetPlayerHP() <= 0 &&
				m_player2->GetPlayer2HP() <= 0 ||
				m_player->GetPlayerHP() <= 0 &&
				m_player3->GetPlayer3HP() <= 0 ||
				m_player2->GetPlayer2HP() <= 0 &&
				m_player3->GetPlayer3HP() <= 0)
			{
				m_gamingshigureui->SetSokomade();
			}
		}
		else
		{
			if (m_player->GetPlayerHP() <= 0 ||
				m_player2->GetPlayer2HP() <= 0)
			{
				m_gamingshigureui->SetSokomade();
			}
		}
	}
}
void Game::Render(RenderContext& rc)
{
}
#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"

bool Game::Start()
{
	//プレイヤーオブジェクトを作成する。
	m_player = NewGO<Player>(0, "player");
	//背景オブジェクトを作成する。
	m_backGround = NewGO<BackGround>(0, "background");

	return true;
}
void Game::Update()
{
	//ディレクションライトの当たる方向とカラーをセットできちゃいます
	g_directionLig.SetLigDirection({ 1.0f,-1.0f,-1.0f });
	g_directionLig.SetLigColor({0.5f,0.5f,0.5f});
}
void Game::Render(RenderContext& rc)
{
}
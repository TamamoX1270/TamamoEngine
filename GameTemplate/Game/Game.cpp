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

	//プレイヤーオブジェクトを作成する。
	m_player = NewGO<Player>(0, "player");

	return true;
}
void Game::Update()
{
<<<<<<< HEAD
	//くぁｗせｄｒｆｔｇｙふじこｌｐ
	
=======
	//上田は寿司ブレード楽しい。
	if (g_pad[0]->IsTrigger(enButtonDown)) {
		m_player = NewGO<Player>(0, "player");
	}

>>>>>>> 904b2db2eec969f6ca910db0da5f4e01da138348
	// 左スティック(キーボード：WASD)で平行移動。
	m_pointligpos.x += g_pad[0]->GetLStickXF();
	m_pointligpos.y += g_pad[0]->GetLStickYF();
	g_directionLig.SetPointPos(m_pointligpos);
	//ディレクションライトの当たる方向とカラーをセットできちゃいます
	g_directionLig.SetLigDirection({ 1.0f,-1.0f,-1.0f });
	g_directionLig.SetLigColor({0.5f,0.5f,0.5f});
}
void Game::Render(RenderContext& rc)
{
}
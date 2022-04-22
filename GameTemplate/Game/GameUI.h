#pragma once

#include "sound/SoundSource.h"

class Player1;
class Player2;
class Player3;
class Player4;

class GameUI : public IGameObject
{
public:
	GameUI() {};
	/// <summary>
	/// 開始の処理
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// ゲームのBGM
	void GameBGM();
	/// <summary>
	/// ゲームの残り時間
	void Timer();
	/// <summary>
	/// 醤油さしのプログラム
	/// </summary>
	void SoyCT();
	/// <summary>
	/// 寿司のHPバー
	/// </summary>
	void SushiHPBar();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;
	void GameHP();
private:
	Player1*		m_player1;
	Player2*		m_player2;
	Player3*		m_player3;
	Player4*		m_player4;

	SpriteRender	m_ui;
	SpriteRender	m_spriteRender;
	SpriteRender	m_spriteRender2;
	SpriteRender	m_spriteRender3;
	SpriteRender	m_spriteRender4;

	SpriteRender	m_soyct;
	SpriteRender	m_soyct2;
	SpriteRender	m_soyct3;
	SpriteRender	m_soyct4;

	SpriteRender	m_sushihpbar;
	SpriteRender	m_sushihpbarwaku;
	SpriteRender	m_sushihpbar2;
	SpriteRender	m_sushihpbarwaku2;
	SpriteRender	m_sushihpbar3;
	SpriteRender	m_sushihpbarwaku3;
	SpriteRender	m_sushihpbar4;
	SpriteRender	m_sushihpbarwaku4;

	SpriteRender	m_spriteRenderwakka;
	SpriteRender	m_spriteRenderwakka2;
	SpriteRender	m_spriteRenderwakka3;
	SpriteRender	m_spriteRenderwakka4;
	SpriteRender	m_spriteRendertime;

	FontRender		m_fontRender;
	float game_timer = 180.0f;

	SoundSource* gameBGM;

	int m_p1hp = 0;
	int m_p2hp = 0;
	int m_p3hp = 0;
	int m_p4hp = 0;

};


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
	~GameUI();
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
	void SoyCT();
	/// <summary>
	/// 寿司のHPバー
	/// </summary>
	void SushiHPBar();
	/// <summary>
	/// そこまで！をtrueにする。
	/// </summary>
	void SetSokomade()
	{
		m_sokomade = true;
	}/// <summary>
	/// そこまで！のtrueを受け取る。
	/// </summary>
	const int& GetSokomade()const
	{
		return m_sokomade;
	}
	const int& GetGameStart()const
	{
		return m_gamestart;
	}
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
	SpriteRender	m_sushihpbar2;
	SpriteRender	m_sushihpbar3;
	SpriteRender	m_sushihpbar4;

	SpriteRender	m_sushihpbar_kuro;
	SpriteRender	m_sushihpbar_kuro2;
	SpriteRender	m_sushihpbar_kuro3;
	SpriteRender	m_sushihpbar_kuro4;

	SpriteRender	m_sushihpbarwaku;
	SpriteRender	m_sushihpbarwaku2;
	SpriteRender	m_sushihpbarwaku3;
	SpriteRender	m_sushihpbarwaku4;

	SpriteRender	m_spriteRendersamonhuda;
	SpriteRender	m_spriteRendermagurohuda;
	SpriteRender	m_spriteRendertamagohuda;
	SpriteRender	m_spriteRenderebihuda;
	SpriteRender	m_spriteRendertime;

	SpriteRender	m_count1;
	SpriteRender	m_count2;
	SpriteRender	m_count3;
	SpriteRender	m_hajime;

	SpriteRender	m_spriteRendersokomade;

	FontRender		m_fontRender;
	//float game_timer = 120.0f;
	float game_timer = 20.0f;
	float gamestart_timer = 3.0f;
	float sokomade_timer = 0.0f;
	float hajime_timer = 0.0f;

	SoundSource* gameBGM;
	SoundSource* endSE;

	int m_p1hp = 0;
	int m_p2hp = 0;
	int m_p3hp = 0;
	int m_p4hp = 0;

	int m_sokomade = false;
	int m_gameendse = false;
	int m_gamestart = false;
	int m_countstate = false;
	int m_hajimestate = false;

};


#pragma once
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

	int m_hp=50;
};


#include "stdafx.h"
#include "GameUI.h"
#include "Game.h"

namespace
{
	//醤油さしの外側の透明度の設定
	Vector4 Transparent = { 1.0f, 1.0f, 1.0f, 0.5f };
	//最大HP。
	const int MAXIMUM_HP = 50;
}

bool GameUI::Start()
{
	//m_ui.Init("Assets/sprite/ComprehensiveUI.dds", 1600.0f, 900.0f);
	m_spriteRenderwakka.Init("Assets/sprite/wakka.dds", 210.0f, 210.0f);
	m_spriteRenderwakka2.Init("Assets/sprite/wakka.dds", 210.0f, 210.0f);
	m_spriteRenderwakka3.Init("Assets/sprite/wakka.dds", 210.0f, 210.0f);
	m_spriteRenderwakka4.Init("Assets/sprite/wakka.dds", 210.0f, 210.0f);
	m_spriteRendertime.Init("Assets/sprite/timer_UI2.dds", 520.0f, 300.0f);

	SoyCT();
	SushiHPBar();

	m_spriteRenderwakka.SetPosition(Vector3(-730.0f, -340.0f, 0.0f));
	m_spriteRenderwakka2.SetPosition(Vector3(-335.0f, -340.0f, 0.0f));
	m_spriteRenderwakka3.SetPosition(Vector3(65.0f, -340.0f, 0.0f));
	m_spriteRenderwakka4.SetPosition(Vector3(460.0f, -340.0f, 0.0f));
	m_spriteRendertime.SetPosition(Vector3(0.0f, 375.0f, 0.0f));

	m_spriteRender.Update();
	m_spriteRender2.Update();
	m_spriteRender3.Update();
	m_spriteRender4.Update();
	m_spriteRenderwakka.Update();
	m_spriteRenderwakka2.Update();
	m_spriteRenderwakka3.Update();
	m_spriteRenderwakka4.Update();
	m_spriteRendertime.Update();

	return true;
}

void GameUI::SoyCT()
{
	//醤油さし
	m_spriteRender.Init("Assets/sprite/soysaucecontainer_1P.dds", 200.0f, 200.0f);
	m_spriteRender.SetPosition({ -450.0f,-340.0f,0.0f });
	m_spriteRender2.Init("Assets/sprite/soysaucecontainer_2P.dds", 200.0f, 200.0f);
	m_spriteRender2.SetPosition({ -55.0f,-340.0f,0.0f });
	m_spriteRender3.Init("Assets/sprite/soysaucecontainer_3P.dds", 200.0f, 200.0f);
	m_spriteRender3.SetPosition({ 345.0f,-340.0f,0.0f });
	m_spriteRender4.Init("Assets/sprite/soysaucecontainer_4P.dds", 200.0f, 200.0f);
	m_spriteRender4.SetPosition({ 730.0f,-340.0f,0.0f });
	//醤油さしかばー
	m_soyct.Init("Assets/sprite/soysaucecontainercover.dds", 200.0f, 200.0f);
	m_soyct.SetPosition({ -450.0f,-340.0f,0.0f });
	m_soyct.SetMulColor({ Transparent });
	m_soyct2.Init("Assets/sprite/soysaucecontainercover.dds", 200.0f, 200.0f);
	m_soyct2.SetPosition({ -55.0f,-340.0f,0.0f });
	m_soyct2.SetMulColor({ Transparent });
	m_soyct3.Init("Assets/sprite/soysaucecontainercover.dds", 200.0f, 200.0f);
	m_soyct3.SetPosition({ 345.0f,-340.0f,0.0f });
	m_soyct3.SetMulColor({ Transparent });
	m_soyct4.Init("Assets/sprite/soysaucecontainercover.dds", 200.0f, 200.0f);
	m_soyct4.SetPosition({ 730.0f,-340.0f,0.0f });
	m_soyct4.SetMulColor({ Transparent });
	//更新処理
	m_soyct.Update();
	m_soyct2.Update();
	m_soyct3.Update();
	m_soyct4.Update();
}

void GameUI::SushiHPBar()
{
	m_sushihpbar.Init("Assets/sprite/hpbar.DDS", 170.0f, 90.0f);
	m_sushihpbarwaku.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	m_sushihpbar2.Init("Assets/sprite/hpbar.DDS", 170.0f, 90.0f);
	m_sushihpbarwaku2.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	m_sushihpbar3.Init("Assets/sprite/hpbar.DDS", 170.0f, 90.0f);
	m_sushihpbarwaku3.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	m_sushihpbar4.Init("Assets/sprite/hpbar.DDS", 170.0f, 90.0f);
	m_sushihpbarwaku4.Init("Assets/sprite/HPbar(1).DDS", 180.0f, 120.0f);
	//HPバーのピボットを設定。
	//m_sushihpbar.SetPivot(Vector2(0.5f, 0.5f));
	m_sushihpbar.SetPosition(Vector3(-669.0f, -363.0f, 0.0f));
	m_sushihpbarwaku.SetPosition(Vector3(-585.0f, -355.0f, 0.0f));
	m_sushihpbar2.SetPosition(Vector3(-180.0f, -363.0f, 0.0f));
	m_sushihpbarwaku2.SetPosition(Vector3(-185.0f, -355.0f, 0.0f));
	m_sushihpbar3.SetPosition(Vector3(217.0f, -363.0f, 0.0f));
	m_sushihpbarwaku3.SetPosition(Vector3(215.0f, -355.0f, 0.0f));
	m_sushihpbar4.SetPosition(Vector3(610.0f, -363.0f, 0.0f));
	m_sushihpbarwaku4.SetPosition(Vector3(605.0f, -355.0f, 0.0f));
	m_sushihpbar.Update();
	m_sushihpbarwaku.Update();
	m_sushihpbar2.Update();
	m_sushihpbarwaku2.Update();
	m_sushihpbar3.Update();
	m_sushihpbarwaku3.Update();
	m_sushihpbar4.Update();
	m_sushihpbarwaku4.Update();
}

void GameUI::GameHP()
{
	//Aボタンを押したら,体力回復。
	if (g_pad[0]->IsPress(enButtonA))
	{
		m_hp += 1;
	}
	//Bボタンを押したら、体力を減らす。
	else if (g_pad[0]->IsPress(enButtonB))
	{
		m_hp -= 1;
	}

	//HPが0より減っていたら。
	if (m_hp < 0)
	{
		//HPを0にする。
		m_hp = 0;
	}
	//HPが最大値を超えていたら。
	else if (m_hp > MAXIMUM_HP)
	{
		//HPを最大値にする。
		m_hp = MAXIMUM_HP;
	}

	Vector3 scale = Vector3::One;
	//現HP/最大HPをHPバーのスケールにする。
	//int型同士の計算だと、小数点以下切り捨てになるので。
	//float型に変換して計算を行う。
	scale.x = float(m_hp) / float(MAXIMUM_HP);
	//スケールを設定。
	m_sushihpbar.SetScale(scale);

	m_sushihpbar.SetPivot(Vector2(0.0f, 0.5f));
	//m_sushihpbar.SetLimitedX(0.5f);
	//m_sushihpbar.SetIsDisplayRestrictionLeftSide(0.5f);
	//更新処理。
	m_sushihpbar.Update();
}

void GameUI::Update()
{
	int b = m_hp;
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
	GameHP();
}

void GameUI::Render(RenderContext& rc)
{
	//m_ui.Draw(rc);

	//m_spriteRender99.Draw(rc);
	m_spriteRenderwakka.Draw(rc);
	m_spriteRenderwakka2.Draw(rc);
	m_spriteRenderwakka3.Draw(rc);
	m_spriteRenderwakka4.Draw(rc);
	m_spriteRender.Draw(rc);                 //描画
	m_spriteRender2.Draw(rc);
	m_spriteRender3.Draw(rc);
	m_spriteRender4.Draw(rc);
	m_spriteRendertime.Draw(rc);

	m_soyct.Draw(rc);
	m_soyct2.Draw(rc);
	m_soyct3.Draw(rc);
	m_soyct4.Draw(rc);

	m_sushihpbar.Draw(rc);
	m_sushihpbarwaku.Draw(rc);
	m_sushihpbar2.Draw(rc);
	m_sushihpbarwaku2.Draw(rc);
	m_sushihpbar3.Draw(rc);
	m_sushihpbarwaku3.Draw(rc);
	m_sushihpbar4.Draw(rc);
	m_sushihpbarwaku4.Draw(rc);
	m_fontRender.Draw(rc);
}
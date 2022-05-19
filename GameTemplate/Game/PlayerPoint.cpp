#include "stdafx.h"
#include "PlayerPoint.h"

void PlayerPoint::Update()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"1P%d点", int(m_1playerpoint));
	//表示するテキストを設定。
	m_fontRender.SetText(wcsbuf);
	//フォントの位置を設定。
	m_fontRender.SetPosition(Vector3(-200.0f, 200.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender.SetScale(2.0f);
	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"2P%d点", int(m_2playerpoint));
	//表示するテキストを設定。
	m_fontRender2.SetText(wcsbuf2);
	//フォントの位置を設定。
	m_fontRender2.SetPosition(Vector3(-95.0f, 200.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender2.SetScale(2.0f);
	wchar_t wcsbuf3[256];
	swprintf_s(wcsbuf3, 256, L"3P%d点", int(m_3playerpoint));
	//表示するテキストを設定。
	m_fontRender3.SetText(wcsbuf3);
	//フォントの位置を設定。
	m_fontRender3.SetPosition(Vector3(95.0f, 200.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender3.SetScale(2.0f);
	wchar_t wcsbuf4[256];
	swprintf_s(wcsbuf4, 256, L"4P%d点", int(m_4playerpoint));
	//表示するテキストを設定。
	m_fontRender4.SetText(wcsbuf4);
	//フォントの位置を設定。
	m_fontRender4.SetPosition(Vector3(200.0f, 200.0f, 0.0f));
	//フォントの大きさを設定。
	m_fontRender4.SetScale(2.0f);
}

void PlayerPoint::Render(RenderContext& rc)
{/*
	m_fontRender.Draw(rc);
	m_fontRender2.Draw(rc);
	m_fontRender3.Draw(rc);
	m_fontRender4.Draw(rc);*/
}
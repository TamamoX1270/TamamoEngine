#include "stdafx.h"
#include "PlayerPoint.h"

void PlayerPoint::Update()
{
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"1P%d�_", int(m_1playerpoint));
	//�\������e�L�X�g��ݒ�B
	m_fontRender.SetText(wcsbuf);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender.SetPosition(Vector3(-200.0f, 200.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender.SetScale(2.0f);
	wchar_t wcsbuf2[256];
	swprintf_s(wcsbuf2, 256, L"2P%d�_", int(m_2playerpoint));
	//�\������e�L�X�g��ݒ�B
	m_fontRender2.SetText(wcsbuf2);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender2.SetPosition(Vector3(-95.0f, 200.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender2.SetScale(2.0f);
	wchar_t wcsbuf3[256];
	swprintf_s(wcsbuf3, 256, L"3P%d�_", int(m_3playerpoint));
	//�\������e�L�X�g��ݒ�B
	m_fontRender3.SetText(wcsbuf3);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender3.SetPosition(Vector3(95.0f, 200.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender3.SetScale(2.0f);
	wchar_t wcsbuf4[256];
	swprintf_s(wcsbuf4, 256, L"4P%d�_", int(m_4playerpoint));
	//�\������e�L�X�g��ݒ�B
	m_fontRender4.SetText(wcsbuf4);
	//�t�H���g�̈ʒu��ݒ�B
	m_fontRender4.SetPosition(Vector3(200.0f, 200.0f, 0.0f));
	//�t�H���g�̑傫����ݒ�B
	m_fontRender4.SetScale(2.0f);
}

void PlayerPoint::Render(RenderContext& rc)
{/*
	m_fontRender.Draw(rc);
	m_fontRender2.Draw(rc);
	m_fontRender3.Draw(rc);
	m_fontRender4.Draw(rc);*/
}
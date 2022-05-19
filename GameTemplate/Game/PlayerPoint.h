#pragma once
class PlayerPoint : public IGameObject
{
public:
	void Update();
	void Render(RenderContext& rc);
	void Set1PPoint()
	{
		m_1playerpoint += 1;
	}
	void Set2PPoint()
	{
		m_2playerpoint += 1;
	}
	void Set3PPoint()
	{
		m_3playerpoint += 1;
	}
	void Set4PPoint()
	{
		m_4playerpoint += 1;
	}

private:
	FontRender		m_fontRender;
	FontRender		m_fontRender2;
	FontRender		m_fontRender3;
	FontRender		m_fontRender4;

	int m_1playerpoint = 0;
	int m_2playerpoint = 0;
	int m_3playerpoint = 0;
	int m_4playerpoint = 0;

};
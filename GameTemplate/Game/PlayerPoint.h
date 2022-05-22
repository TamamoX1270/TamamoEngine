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
	const int GetPoint1()
	{
		return m_1playerpoint;
	}
	const int GetPoint2()
	{
		return m_2playerpoint;
	}
	const int GetPoint3()
	{
		return m_3playerpoint;
	}
	const int GetPoint4()
	{
		return m_4playerpoint;
	}

	void SetPlayer1Point(const int& hp)
	{
		m_1playerpoint = hp;
	}
	void SetPlayer2Point(const int& hp)
	{
		m_2playerpoint = hp;
	}
	void SetPlayer3Point(const int& hp)
	{
		m_3playerpoint = hp;
	}
	void SetPlayer4Point(const int& hp)
	{
		m_4playerpoint = hp;
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
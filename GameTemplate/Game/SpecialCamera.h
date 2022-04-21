#pragma once

class Player1;
class Player2;

class SpecialCamera :public IGameObject
{
public:
	SpecialCamera();
	~SpecialCamera();
	bool Start();
	void Update();

public:


private:
	Player1* m_player1;	//プレイヤー。
	Player2* m_player2;	//プレイヤー。
	Vector3 m_toCameraPos;	//注視点から視点に向かうベクトル。

	float m_max;
	float m_min;
};
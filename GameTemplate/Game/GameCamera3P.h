#pragma once

class Player1;
class Player2;
class Player3;

class GameCamera3P :public IGameObject
{
public:
	GameCamera3P();
	~GameCamera3P();
	bool Start();
	void Update();

public:


private:
	Player1* m_player1;	//プレイヤー。
	Player2* m_player2;	//プレイヤー。
	Player3* m_player3;	//プレイヤー。
	Vector3 m_toCameraPos;	//注視点から視点に向かうベクトル。

	float m_max;
	float m_min;
};
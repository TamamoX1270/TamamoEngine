#pragma once

class Player1;
class Player2;
class Player3;
class Player4;

class GameCamera :public IGameObject
{
public:
	GameCamera() {};
	~GameCamera() {};
	bool Start();
	void Update();

private:
	Player1* m_player1;		//プレイヤー。
	Player2* m_player2;		//プレイヤー。
	Player3* m_player3;		//プレイヤー。
	Player4* m_player4;		//プレイヤー。

	Vector3 m_toCameraPos;	//注視点から視点に向かうベクトル。
	Vector3 target;			//注視点。

	float m_xPosMax;		//x座標の最大値。
	float m_xPosMin;		//x座標の最小値。
};
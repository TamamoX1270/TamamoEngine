#pragma once

class Player1;
class Player2;

class GameCamera2P :public IGameObject
{
public:
	GameCamera2P();
	~GameCamera2P();
	bool Start();
	void Update();

public:


private:
	Player1* m_player1;	//�v���C���[�B
	Player2* m_player2;	//�v���C���[�B
	Vector3 m_toCameraPos;	//�����_���王�_�Ɍ������x�N�g���B

	float m_max;
	float m_min;
};
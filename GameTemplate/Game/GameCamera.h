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
	Player1* m_player1;		//�v���C���[�B
	Player2* m_player2;		//�v���C���[�B
	Player3* m_player3;		//�v���C���[�B
	Player4* m_player4;		//�v���C���[�B

	Vector3 m_toCameraPos;	//�����_���王�_�Ɍ������x�N�g���B
	Vector3 target;			//�����_�B

	float m_xPosMax;		//x���W�̍ő�l�B
	float m_xPosMin;		//x���W�̍ŏ��l�B
};
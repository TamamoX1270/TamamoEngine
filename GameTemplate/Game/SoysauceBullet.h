#pragma once

class Player1;

class SoySauceBullet : public IGameObject
{
public:
	SoySauceBullet();
	~SoySauceBullet();
	//�ŏ��Ɉ�񂾂����s
	bool Start();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	FontRender m_fontRender;                       //�����̕`��
	FontRender m_fontRender1;                     //�����̕`��Q
	FontRender m_fontRender2;                    //�����̕`��R
	SphereCollider m_sphereCollider;		    //�~�^�̃R���C�_�[�B
	Vector3 m_playerposition;                  //�v���C���[�̈ʒu
	Vector3 m_enemyposition;                  //�G�̈ʒu
	Vector3 m_position;			              //���W�B
	Vector3 m_moveSpeed;					 //�ړ����x�B
	Vector3   m_bulletposition;             //�e�̈ʒu
	Quaternion m_rotation;                  //�N�E�H�[�^�j�I��
	ModelRender m_modelRender;             //���f�������_�[
	Player1* m_player1;
	CollisionObject* m_collisionObject;
	float m_deletetimer = 0.0f;
	int bulletdelete = 0;
};


#pragma once

class Player1;

class SoySauceBullet : public IGameObject
{
public:
	SoySauceBullet();
	~SoySauceBullet();
	//最初に一回だけ実行
	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	/// <summary>
	/// 醤油弾を撃つプレイヤーの数値を入れてやる。
	/// </summary>
	/// <param name="ngp"></param>
	void SetSoySauceNewGOPlayer(const int ngp)
	{
		m_soynewgoplayer = ngp;
	}
	void SetMoveSpeed(const Vector3& sms)
	{
		m_moveSpeed = sms;
	}
private:
	FontRender m_fontRender;                       //文字の描画
	FontRender m_fontRender1;                     //文字の描画２
	FontRender m_fontRender2;                    //文字の描画３
	SphereCollider m_sphereCollider;		    //円型のコライダー。
	Vector3 m_playerposition;                  //プレイヤーの位置
	Vector3 m_enemyposition;                  //敵の位置
	Vector3 m_position;			              //座標。
	Vector3 m_moveSpeed;					 //移動速度。
	Vector3   m_bulletposition;             //弾の位置
	Vector3	m_efpos1;						//エフェクト用のポジション
	Quaternion m_rotation;                  //クウォータニオン
	ModelRender m_modelRender;             //モデルレンダー
	Player1* m_player1;
	CollisionObject* m_collisionObject;
	float m_deletetimer = 0.0f;
	int bulletdelete = 0;

	int m_soynewgoplayer = 0;			//弾をNewGOしたプレイヤーの番号
};


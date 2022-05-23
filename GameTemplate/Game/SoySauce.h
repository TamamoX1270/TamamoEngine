#pragma once
#include "sound/SoundSource.h"

class Player1;
class Player2;
class Player3;
class Player4;

class SoySauce : public IGameObject
{
public:
	~SoySauce();
	/// <summary>
	/// 開始の処理
	/// </summary>
	/// <returns></returns>
	bool Start() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;

public:
	/// <summary>
	/// 醤油の座標を取得する。
	/// </summary>
	/// <returns>醤油の座標。</returns>
	const Vector3& GetSoySaucePosition() const
	{
		return m_position;
	}

	/// <summary>
	/// 醤油の座標を設定する。
	/// </summary>
	/// <param name="position">醤油の座標。</param>
	void SetSoySaucePosition(const Vector3& position)
	{
		m_position = position;
	}


private:

	Player1* m_player1 = nullptr;;								//プレイヤー１
	Player2* m_player2 = nullptr;;								//プレイヤー１
	Player3* m_player3 = nullptr;;								//プレイヤー１
	Player4* m_player4 = nullptr;;								//プレイヤー１

	SoundSource* Pse;											// プレイヤーの効果音

	ModelRender			m_soysauce;								//醤油
	Vector3				m_efpos;								//エフェクト用のポジション
	Vector3				m_position = Vector3::Zero;				// 座標
	Vector3				m_moveSpeed;							//移動速度。
	Quaternion			m_rotation = Quaternion::Identity;;		// 回転
	Vector3				m_scale = Vector3::One;					// 拡大率  
	EffectEmitter*		m_effectEmitter;						//エフェクト
	CollisionObject*	m_collisionObject;						//コリジョン
};


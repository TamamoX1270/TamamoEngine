#pragma once

class Player1;

class Player2 : public IGameObject
{
public:
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
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc) override;

public:
	/// <summary>
	/// プレイヤーの座標を取得する。
	/// </summary>
	/// <returns>プレイヤーの座標。</returns>
	const Vector3 & GetPlayer2Position() const
	{
		return m_position;
	}

	/// <summary>
	/// プレイヤーの座標を設定する。
	/// </summary>
	/// <param name="position">プレイヤーの座標。</param>
	void SetPlayer2Position(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// プレイヤーのステートを取得する。
	/// </summary>
	/// <returns>プレイヤーのステート。</returns>
	const float& GetPlayer2State() const
	{
		return shine;
	}

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// アニメーション管理
	/// </summary>
	void AnimationState();

	/// <summary>
	/// ステート管理
	/// </summary>
	void ManageState();

	/// <summary>
	/// ガード管理
	/// </summary>
	void Guard();

	/// <summary>
	/// 被ダメージモーション管理
	/// </summary>
	void Hit();

	/// <summary>
	/// 掴まれ後の管理
	/// </summary>
	void AfterCatch();
private:
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : 待機アニメーション、
		enAnimClip_Run,		// 1 : 走りアニメーション。
		enAnimClip_Hit,		// 2 : 被ダメージアニメーション。
		enAnimClip_Num,		// 3 :アニメーションクリップの数。
	};
	Model m_model;
	ModelRender m_player2;                             //プレイヤー
	Animation m_animation;	// アニメーション
	AnimationClip m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	CharacterController m_characterController;       //キャラクターコントローラー。
	Vector3 m_position = Vector3::Zero;				   // 座標
	Quaternion m_rotation = Quaternion::Identity;;     // 回転
	Vector3 m_scale = Vector3::One;	                   // 拡大率

	int m_hp = 0;
	FontRender      m_fontRender;					//フォントレンダー

	int aaa = 0;
	int m_playerState = 0;

	//掴み処理の関数
	float shine = false;
	float m_timer = 0.0f;
};
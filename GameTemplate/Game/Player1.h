#pragma once

class Player2;

class Player1 : public IGameObject
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
	const Vector3& GetPlayer1Position() const
	{
		return m_position;
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
	/// ジャンプ管理
	/// </summary>
	void ManageJump();

	// アニメーションイベント用の関数。
	//void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	/// <summary>
	/// 攻撃用のコリジョンを作成する。
	/// </summary>
	void MakeAttackCollision();

private:
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : 待機アニメーション、
		enAnimClip_Run,		// 1 : 走りアニメーション。
		enAnimClip_Guard,	// 2 : ガードアニメーション。
		enAnimClip_Punch,	// 3 : 攻撃アニメーション。
		enAnimClip_Jump,	// 4 : ジャンプアニメーション。
		enAnimClip_Hit,		// 5 : 被ダメージアニメーション。
		enAnimClip_Num,		// 6 : アニメーションクリップの数。
	};
	Model m_model;
	ModelRender m_player;								//プレイヤー
	Animation m_animation;								// アニメーション
	AnimationClip m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	CharacterController m_characterController;			//キャラクターコントローラー。
	Vector3 m_position= Vector3::Zero;					// 座標
	Quaternion m_rotation = Quaternion::Identity;;		// 回転
	Vector3 m_scale=Vector3::One;						// 拡大率

	Vector3 moveSpeed;	//プレイヤーの速さ。

	int m_playerState; //プレイヤーステート。
	float m_timer = 0.0f; //アニメーション用タイマー。

	int m_jumpState = 0;	//ジャンプ実装用ステート。
	float m_jumpTimer = 0.0f;	//ジャンプ実装用タイマー。

};
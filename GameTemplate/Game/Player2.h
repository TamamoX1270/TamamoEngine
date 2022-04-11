#pragma once

class SoySauceBullet;

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
	const Vector3& GetPlayer2Position() const
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
	/// プレイヤーの掴まれステートを取得する。
	/// </summary>
	/// <returns>プレイヤーのステート。</returns>
	const float& GetPlayer2State() const
	{
		return shine;
	}

	/// <summary>
	/// キャラクターコントローラーを取得。
	/// </summary>
	/// <returns>キャラクターコントローラー。</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	/// <summary>
	/// 醤油カウント+1
	/// </summary>
	void AddSoySauceCount()
	{
		m_soysaucecount++;
	}


private:
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation();

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
	void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);

	/// <summary>
	/// 攻撃１のコリジョンを作成する。
	/// </summary>
	void MakeCollision();

	/// <summary>
	/// 攻撃２のコリジョンを作成する。
	/// </summary>
	void MakeCollision2();

	/// <summary>
	/// 攻撃３のコリジョンを作成する。
	/// </summary>
	void MakeCollision3();

	/// <summary>
	/// 防御用のコリジョンを作成する。
	/// </summary>
	void MakeGuardCollision();

	/// <summary>
	/// プレイヤー1からの被ダメージモーション管理
	/// </summary>
	void Hit1();

	/// <summary>
	/// プレイヤー3からの被ダメージモーション管理
	/// </summary>
	void Hit3();

	/// <summary>
	/// 掴まれ後の管理
	/// </summary>
	void AfterCatch();

	/// <summary>
	/// 掴み用のコリジョンを作成する。
	/// </summary>
	void MakeCatchCollision();

	/// <summary>
	/// 掴み攻撃をするコリジョンを作成する。
	/// </summary>
	void CatchAttackCollision();

private:
	// アニメーションクリップの番号を表す列挙型。
	enum EnAnimationClip {
		enAnimClip_Idle,	// 0 : 待機アニメーション、
		enAnimClip_Run,		// 1 : 走りアニメーション。
		enAnimClip_Guard,	// 2 : ガードアニメーション。
		enAnimClip_Punch,	// 3 : 攻撃アニメーション。
		enAnimClip_Jump,	// 4 : ジャンプアニメーション。
		enAnimClip_Hit,		// 5 : 被ダメージアニメーション。
		enAnimClip_Catch,	// 6 : 掴みアニメーション。
		enAnimClip_Punch2,	// 7 : 攻撃２アニメーション。
		enAnimClip_Kick3,	// 8 : 攻撃３アニメーション。
		enAnimClip_CPunch,	// 9 : 掴み攻撃アニメーション。
		enAnimClip_Num,		// 10 : アニメーションクリップの数。
	};
	Model				m_model;
	ModelRender			m_player2;								//プレイヤー
	Animation			m_animation;							// アニメーション
	AnimationClip		m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	CharacterController m_characterController;					//キャラクターコントローラー。
	Vector3				m_position = Vector3::Zero;				// 座標
	Quaternion			m_rotation = Quaternion::Identity;;		// 回転
	Vector3				m_scale = Vector3::One;					// 拡大率

	//醤油弾の関数
	SoySauceBullet* m_soysaucebullet;   //醤油弾
	Vector3			m_forward;			//キャラクターの前方向のベクトル
	FontRender		m_fontRender;		//文字
	int m_soysaucecount = 0;			//醤油カウント

	//HPの仮表示
	int m_hp = 0;
	FontRender      m_fontHPRender;					//フォントレンダー

	Vector3		moveSpeed;				//プレイヤーの速さ。

	int			m_playerState;			//プレイヤーステート。
	float		m_timer = 0.0f;			//アニメーション用タイマー。

	int			m_jumpState = 0;		//ジャンプ実装用ステート。
	float		m_jumpTimer = 0.0f;		//ジャンプ実装用タイマー。

	int			m_charaRotState = 0;	//キャラの向きを変えるステート。


	float		m_isUnderAttack;		//1番目の攻撃。
	int			m_handBoneId = -1;		//「Hand」ボーンのID。  

	float		m_catch;					//掴み。
	int			m_handBoneIdCatch = -1;		//「Hand」ボーンのID。 

	float		m_2;					//2番目の攻撃。
	int			m_handBoneId2 = -1;		//「Hand」ボーンのID。  

	float		m_3;					//3番目の攻撃。
	int			m_handBoneId3 = -1;		//「Hand」ボーンのID。  

	float		m_cpunch;					//掴み攻撃。
	int			m_handBoneIdCPunch = -1;	//「Hand」ボーンのID。  

	int atkState = 0;					//連続攻撃のためのステート。

	float guard = false;				//ガードをしているかどうか。

	float p1_Catch;		//P1のshineステート。
	float p3_Catch;		//P3のshineステート。

	//掴み処理の関数
	float shine = false;		//掴まれているか。
	float m_Catchtimer = 0.0f;		//掴まれてからのタイマー。
};
#pragma once
#include "sound/SoundSource.h"

class SoySauceBullet;
class PlayerPoint;

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
	/// 自分が他のプレイヤーをつかんだことを取得する。
	/// </summary>
	void SetPlayer2Catch(const float& position)
	{
		tukami = position;
	}
	/// <summary>
	/// プレイヤーの前方向のベクトルの取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPlayerforward()const
	{
		return m_forward;
	}
	/// <summary>
	/// プレイヤーのHPの取得
	/// </summary>
	/// <returns></returns>
	const int& GetPlayer2HP()const
	{
		return m_hp;
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

	void SetPlayer2PlayerState15()
	{
		m_playerState = 15;
	}

	void AddSauce()
	{
		m_getsoyplayernumber++;
	}

	const int  GetSauce()
	{
		return m_getsoyplayernumber;
	}

	const int& GetSoySauceCount()
	{
		return m_soysaucecount;
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
	/// 被ダメ後の防御用のコリジョンを作成する。
	/// </summary>
	void autoGuard();

	/// <summary>
	/// プレイヤー1からの被ダメージモーション管理
	/// </summary>
	void Hit1();

	/// <summary>
	/// プレイヤー3からの被ダメージモーション管理
	/// </summary>
	void Hit3();

	/// <summary>
	/// プレイヤー4からの被ダメージモーション管理
	/// </summary>
	void Hit4();

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

	/// <summary>
	/// リングアウトした場合の処理。
	/// </summary>
	void RingOut();

	/// <summary>
	/// ガードの時のエフェクトの処理
	/// </summary>
	void Guard();

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
		enAnimClip_FlyAway,	// 10 : 吹っ飛びアニメーション。
		enAnimClip_RiseUp,	// 11 : 起き上がりアニメーション。
		enAnimClip_Death,	// 12 : 死ぬアニメーション。
		enAnimClip_RingOut,	// 13 : リングアウトアニメーション。
		enAnimClip_GrabHit,	// 14 : 掴まれるアニメーション。
		enAnimClip_Repel,	// 15 : 弾くアニメーション。
		enAnimClip_Num,		// 16 : アニメーションクリップの数。
	};
	Model				m_model;
	ModelRender			m_player2;								//プレイヤー
	Animation			m_animation;							// アニメーション
	AnimationClip		m_animationClipArray[enAnimClip_Num];	// アニメーションクリップ
	CharacterController m_characterController;					//キャラクターコントローラー。
	Vector3				m_position = Vector3::Zero;				// 座標
	Quaternion			m_rotation = Quaternion::Identity;;		// 回転
	Vector3				m_scale = Vector3::One;					// 拡大率
	Vector3				m_efpos1;								//エフェクト用のポジション
	Vector3				m_efpos2;								//エフェクト用のポジション
	PlayerPoint* m_playerpoint;							//プレイヤーのポイントを記録する

	//醤油弾の関数
	SoySauceBullet* m_soysaucebullet;   //醤油弾
	Vector3			m_forward;			//キャラクターの前方向のベクトル
	FontRender		m_fontRender;		//文字
	int m_soysaucecount = 5;			//醤油カウント

	//HPの表示
	int m_hp = 100;
	int m_max = 100;
	int m_min = 0;
	FontRender      m_fontHPRender;					//フォントレンダー

	Vector3		moveSpeed;				//プレイヤーの速さ。

	int			m_playerState;			//プレイヤーステート。

	float		m_jumpState = false;	//ジャンプ実装用ステート。

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

	Vector3 a;

	SoundSource* P2se;	//P2の効果音。

	//掴み処理の関数
	float shine = false;		//掴まれているか。
	float m_Catchtimer = 0.0f;		//掴まれてからのタイマー。
	float tukami = false;	//掴んでいるか。
	int c = 0;				//どのプレイヤーから殴られているか

	//ゲーム終了や負け処理の関数
	int m_owaowari; //そこまで！ステートを受け取る。
	float m_out = false;			//リングアウトしたかどうか。

	EffectEmitter* m_effectEmitter;						//エフェクト
	EffectEmitter* m_guardeffectEmitter;						//エフェクト
	int m_guardnewgo = false;

	int m_getsoyplayernumber = 0;								//取得したプレイヤーの番号
	int getsauce = 0;
};
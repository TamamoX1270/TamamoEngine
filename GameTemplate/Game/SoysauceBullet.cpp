#include "stdafx.h"
#include "SoySauceBullet.h"
#include "stdafx.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"

//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"
//EffectEmitterを使用する時はファイルをインクルードする必要がある。
#include "graphics/effect/EffectEmitter.h"

bool SoySauceBullet::Start()
{
	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(777, u"Assets/effect/syouyu.efk");
	switch (m_soynewgoplayer)
	{
	case 0:
		break;
	case 1:
		//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
		m_position = FindGO<Player1>("player1")->GetPlayer1Position();
		m_position.y += 70.0f;
		//プレイヤーが左を向いているなら左に、右を向いているなら右に弾を飛ばす
		if (FindGO<Player1>("player1")->GetPlayerforward().x < 0.0f)
		{
			m_position.x -= 60.0f;
		}
		else
		{
			m_position.x += 60.0f;
		}
		m_playerposition = FindGO<Player1>("player1")->GetPlayer1Position();
		break;
	case 2:
		//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
		m_position = FindGO<Player2>("player2")->GetPlayer2Position();
		m_position.y += 70.0f;
		//プレイヤーが左を向いているなら左に、右を向いているなら右に弾を飛ばす
		if (FindGO<Player2>("player2")->GetPlayerforward().x < 0.0f)
		{
			m_position.x -= 60.0f;
		}
		else
		{
			m_position.x += 60.0f;
		}
		m_playerposition = FindGO<Player2>("player2")->GetPlayer2Position();
		break;
	case 3:
		//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
		m_position = FindGO<Player3>("player3")->GetPlayer3Position();
		m_position.y += 70.0f;
		//プレイヤーが左を向いているなら左に、右を向いているなら右に弾を飛ばす
		if (FindGO<Player3>("player3")->GetPlayerforward().x < 0.0f)
		{
			m_position.x -= 60.0f;
		}
		else
		{
			m_position.x += 60.0f;
		}
		m_playerposition = FindGO<Player3>("player3")->GetPlayer3Position();
		break;
	case 4:
		//FindGOでPlayerクラスからm_position(プレイヤーの位置)を読み込む。
		m_position = FindGO<Player4>("player4")->GetPlayer4Position();
		m_position.y += 70.0f;
		//プレイヤーが左を向いているなら左に、右を向いているなら右に弾を飛ばす
		if (FindGO<Player4>("player4")->GetPlayerforward().x < 0.0f)
		{
			m_position.x -= 60.0f;
		}
		else
		{
			m_position.x += 60.0f;
		}
		m_playerposition = FindGO<Player4>("player4")->GetPlayer4Position();
		break;
	}
	//弾のモデルを読み込む。
	m_modelRender.Init("Assets/modelData/SoySauceBullet.tkm");
	m_modelRender.SetScale({ 0.5f,0.5f,0.5f });
	//FindGOで読み込んで入れたm_positionに弾を配置する。
	m_modelRender.SetPosition(m_position);
	m_modelRender.Update();
	//コライダーを初期化。
	m_sphereCollider.Create(48.0f);

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	//座標を敵の位置に設定する。
	collisionPosition = m_position;
	//球状のコリジョンを作成する。
	m_collisionObject->CreateSphere(collisionPosition,       //座標。
		Quaternion::Identity,                                   //回転。
		30.0f);                                                //球の大きさ(半径)。
		//名前を付ける。
	m_collisionObject->SetName("SoysauceAttack");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);
	return true;
}

SoySauceBullet::SoySauceBullet()
{

}

SoySauceBullet::~SoySauceBullet()
{
	DeleteGO(m_collisionObject);
}

void SoySauceBullet::Update() 
{
	Move();
	
	m_modelRender.Update();
}

void SoySauceBullet::Move()
{
	//弾の座標にmovespeedを+してやって、弾を動かす。
	m_position += m_moveSpeed * 15.0f;
	m_modelRender.SetPosition(m_position);
	//setpositionで動いた弾の当たり判定の反映
	m_collisionObject->SetPosition(m_position);
	//プレイヤーの座標と弾の距離のベクトルを求める。
	Vector3 diff = m_playerposition - m_position;

	//生成されてから5秒経過したら
	if (m_deletetimer >= 5.0f)
	{
		DeleteGO(this);
	}
	if (m_collisionObject->IsHit(FindGO<Player1>("player1")->GetCharacterController()) == true)
	{
		m_efpos1 = m_position;
		m_efpos1.y = 60.0f;
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(777);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->SetPosition(m_efpos1);
		effectEmitter->Play();
		DeleteGO(this);
	}
	if (m_collisionObject->IsHit(FindGO<Player2>("player2")->GetCharacterController()) == true)
	{
		m_efpos1 = m_position;
		m_efpos1.y = 60.0f;
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(777);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->SetPosition(m_efpos1);
		effectEmitter->Play();
		DeleteGO(this);
	}
	if (m_collisionObject->IsHit(FindGO<Player3>("player3")->GetCharacterController()) == true)
	{
		m_efpos1 = m_position;
		m_efpos1.y = 60.0f;
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(777);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->SetPosition(m_efpos1);
		effectEmitter->Play();
		DeleteGO(this);
	}
	if (m_collisionObject->IsHit(FindGO<Player4>("player4")->GetCharacterController()) == true)
	{
		m_efpos1 = m_position;
		m_efpos1.y = 60.0f;
		EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
		effectEmitter->Init(777);
		effectEmitter->SetScale({ 15.0f,15.0f,15.0f });
		effectEmitter->SetPosition(m_efpos1);
		effectEmitter->Play();
		DeleteGO(this);
	}

	m_deletetimer += g_gameTime->GetFrameDeltaTime();

}

void SoySauceBullet::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
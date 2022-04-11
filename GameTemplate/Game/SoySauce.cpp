#include "stdafx.h"
#include "SoySauce.h"
#include "Game.h"
#include "Player1.h"
//CollisionObjectを使用したいため、ファイルをインクルードする。
#include "CollisionObject.h"

bool SoySauce::Start()
{
	m_player1 = FindGO<Player1>("player1");
	//モデルの読み込み
	m_soysauce.Init("Assets/modelData/SoySauce.tkm");
	m_position.x = -150.0f;
	m_rotation.AddRotationDegY(180.0f);
	m_soysauce.SetScale(1.0, 1.0, 1.0);
	m_soysauce.SetPosition(m_position);
	m_soysauce.SetRotation(m_rotation);
	m_soysauce.Update();

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
	m_collisionObject->SetName("bullet_hit");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);
	return true;
}

SoySauce::~SoySauce()
{
	DeleteGO(m_collisionObject);
}

void SoySauce::Update()
{
	Move();
}

void SoySauce::Move()
{
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突していたら。(ここ仮で醤油側に実装してるけど後でプレイヤー側で判定取るようにした方がいいよ)
	if (m_collisionObject->IsHit(m_player1->GetCharacterController()) == true)
	{
		//醤油カウントを１増やす。
		m_player1->AddSoySauceCount();
		DeleteGO(this);
	}

}
void SoySauce::Render(RenderContext& rc)
{
	m_soysauce.Draw(rc);
}

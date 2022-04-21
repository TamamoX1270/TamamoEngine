#include "stdafx.h"
#include "SideWall.h"
#include "Player1.h"
#include "Player2.h"

//CollisionObjectを使用するために、ファイルをインクルードする。
#include "CollisionObject.h"

SideWall::SideWall()
{

}

SideWall::~SideWall()
{
	DeleteGO(m_collisionObject);
}
bool   SideWall::Start()
{
	m_sidewall.Init("Assets/modelData/SideWall.tkm");
	m_position.x = 950.0f;
	m_position.y = 0.0f;
	m_sidewall.SetPosition(m_position);
	m_sidewall.SetRotation(m_rotation);
	m_sidewall.SetScale(m_scale);
	m_sidewall.Update();

	//コリジョンオブジェクトを作成する。
	m_collisionObject = NewGO<CollisionObject>(0);
	Vector3 collisionPosition = m_position;
	//Box状のコリジョンを作成する。
	m_collisionObject->CreateBox(collisionPosition,       //座標。
		Quaternion::Identity,                             //回転。
		{ 100.0f,500.0f,100.0f });                                  //大きさ。

		//名前を付ける。
	m_collisionObject->SetName("player_touch");
	//自動で削除を無効にする(DeleteGOで削除する必要がある)。
	m_collisionObject->SetIsEnableAutoDelete(false);

	createstate = true;
	Create();

	return true;
}

void SideWall::GetCreate()
{

	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突していたら再生成しない。
	if (m_collisionObject->IsHit(FindGO<Player1>("player1")->GetCharacterController()) == true)
	{
		return;
	}

	//createstateがfalseで5.0fを越えていたら再生成する。
	if (createstate == false && m_timer >= 5.0f)
	{
		m_timer = 0.0f;
		createstate = true;
		Create();
	}
}

void SideWall::Create()
{
	if (createstate == true)
	{
		//PhysicsStaticObjectを初期化。
		m_physicsStaticObject.CreateFromModel(
			m_sidewall.GetModel(),
			m_sidewall.GetModel().GetWorldMatrix());
		m_wallhp = 1;
	}
}

void  SideWall::Break()
{
	if (m_wallhp <= 0)
	{
		//PhysicsStaticObjectをリリース
		m_physicsStaticObject.Release();
		createstate = false;
	}
	if (m_walldamagestate == true)
	{
		m_walltimer += g_gameTime->GetFrameDeltaTime();
	}
	if (m_walltimer >= 1.0f)
	{
		m_walldamagestate = false;
		m_walltimer = 0.0f;
	}
	//Playerが作成した、攻撃のヒット判定用のコリジョンの配列を取得。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player1_attack");
	//for文で配列を回す。
	for (auto collision : collisions)
	{
		//Playerの攻撃のコリジョンと壁のコリジョンが。
		//衝突していたら。
		if (collision->IsHit(m_collisionObject) == true)
		{
			if (m_walldamagestate == false)
			{
				if (m_walldamagestate == false)
				{
					m_wallhp--;
					m_walldamagestate = true;
				}
			}
		}
	}
	//Playerが作成した、攻撃のヒット判定用のコリジョン2の配列を取得。
	const auto& collisions2 = g_collisionObjectManager->FindCollisionObjects("player1_attack2");
	//for文で配列を回す。
	for (auto collision : collisions2)
	{
		//攻撃のコリジョンと壁のコリジョンが。
		//衝突していたら。
		if (collision->IsHit(m_collisionObject) == true)
		{
			if (m_walldamagestate == false)
			{
				if (m_walldamagestate == false)
				{
					m_wallhp--;
					m_walldamagestate = true;
				}
			}
		}
	}

	if (createstate == false)
	{
		m_timer += g_gameTime->GetFrameDeltaTime();
	}
}

void  SideWall::Update()
{
	Break();
	GetCreate();
	//モデルの更新処理。
	m_sidewall.Update();
}

void SideWall::Render(RenderContext& rc)
{
	if (createstate ==true)
	{
		m_sidewall.Draw(rc);    //モデルを描画する。
	}
}
#include "stdafx.h"
#include "SoySauce.h"
#include "Game.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
//CollisionObjectを使用したいため、ファイルをインクルードする。
#include "CollisionObject.h"
//乱数を使えるようにする
#include <random>

namespace
{
	//乱数を生成
	constexpr int MIN = -900;//乱数の範囲最低値
	constexpr int MAX = 900;//乱数の範囲最大値
	constexpr int RAND_NUMS_TO_GENERATE = 1;//乱数を生成する回数
}


bool SoySauce::Start()
{
	//敵の乱数。
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(MIN, MAX);
	int soypos = 0;
	for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
		m_position.x = distr(eng);
		break;
	}
	m_player1 = FindGO<Player1>("player1");
	m_player2 = FindGO<Player2>("player2");
	m_player3 = FindGO<Player3>("player3");
	m_player4 = FindGO<Player4>("player4");
	//モデルの読み込み
	m_soysauce.Init("Assets/modelData/SoySauce.tkm");
	//m_position.x = -150.0f;
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
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突していたら。(ここ仮で醤油側に実装してるけど後でプレイヤー側で判定取るようにした方がいいよ)
	if (m_collisionObject->IsHit(m_player2->GetCharacterController()) == true)
	{
		//醤油カウントを１増やす。
		m_player2->AddSoySauceCount();
		DeleteGO(this);
	}
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突していたら。(ここ仮で醤油側に実装してるけど後でプレイヤー側で判定取るようにした方がいいよ)
	if (m_collisionObject->IsHit(m_player3->GetCharacterController()) == true)
	{
		//醤油カウントを１増やす。
		m_player3->AddSoySauceCount();
		DeleteGO(this);
	}
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが。
	//衝突していたら。(ここ仮で醤油側に実装してるけど後でプレイヤー側で判定取るようにした方がいいよ)
	if (m_collisionObject->IsHit(m_player4->GetCharacterController()) == true)
	{
		//醤油カウントを１増やす。
		m_player4->AddSoySauceCount();
		DeleteGO(this);
	}

}
void SoySauce::Render(RenderContext& rc)
{
	m_soysauce.Draw(rc);
}

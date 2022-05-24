#include "stdafx.h"
#include "SoySauce.h"
#include "Game.h"
#include "Player1.h"
#include "Player2.h"
#include "Player3.h"
#include "Player4.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
//CollisionObjectを使用したいため、ファイルをインクルードする。
#include "CollisionObject.h"
//乱数を使えるようにする
#include <random>
//EffectEmitterを使用する時はファイルをインクルードする必要がある。
#include "graphics/effect/EffectEmitter.h"

namespace
{
	//乱数を生成
	constexpr int MIN = -600;//乱数の範囲最低値
	constexpr int MAX = 600;//乱数の範囲最大値
	constexpr int RAND_NUMS_TO_GENERATE = 1;//乱数を生成する回数
}


bool SoySauce::Start()
{
	m_position.y = 500.0f;
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
	EffectEngine::GetInstance()->ResistEffect(999, u"Assets/effect/Getsoysauce.efk");
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/syouyu_charge.wav");
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
	//コリジョンオブジェクトの削除
	DeleteGO(m_collisionObject);
}

void SoySauce::Update()
{
	Move();
	//プレイヤーが取得済みかつ再生が終わったら削除する。
	if (m_player1->GetSauce()== 1  ||
		m_player2->GetSauce() == 1 ||
		m_player3->GetSauce() == 1 ||
		m_player4->GetSauce() == 1)
	{
		DeleteGO(this);
	}
}

void SoySauce::Move()
{
	m_position.y -= 5.0f;
	
	if (m_position.y <= 0.0f)
	{
		m_position.y = 0.0f;
	}
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが触れた時実行。
	if (m_collisionObject->IsHit(m_player1->GetCharacterController()) == true)
	{

		//効果音をつける。
		SoundSource* Pse = NewGO<SoundSource>(14);
		Pse->Init(14);
		Pse->SetVolume(10.0f);
		Pse->Play(false);

		//醤油カウントを１増やす。
		m_player1->AddSoySauceCount();
		m_player1->AddSauce();
		//コリジョンオブジェクトを削除
		DeleteGO(m_collisionObject);
	}
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが触れた時実行。
	if (m_collisionObject->IsHit(m_player2->GetCharacterController()) == true)
	{

		//効果音をつける。
		SoundSource* Pse = NewGO<SoundSource>(14);
		Pse->Init(14);
		Pse->Play(false);

		//醤油カウントを１増やす。
		m_player2->AddSoySauceCount();
		m_player2->AddSauce();
		//コリジョンオブジェクトを削除
		DeleteGO(m_collisionObject);
	}
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが触れた時実行。
	if (m_collisionObject->IsHit(m_player3->GetCharacterController()) == true)
	{

		//効果音をつける。
		SoundSource* Pse = NewGO<SoundSource>(14);
		Pse->Init(14);
		Pse->Play(false);

		//醤油カウントを１増やす。
		m_player3->AddSoySauceCount();
		m_player3->AddSauce();
		//コリジョンオブジェクトを削除
		DeleteGO(m_collisionObject);
	}
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが触れた時実行。
	if (m_collisionObject->IsHit(m_player4->GetCharacterController()) == true)
	{

		//効果音をつける。
		SoundSource* Pse = NewGO<SoundSource>(14);
		Pse->Init(14);
		Pse->Play(false);

		//醤油カウントを１増やす。
		m_player4->AddSoySauceCount();
		m_player4->AddSauce();
		//コリジョンオブジェクトを削除
		DeleteGO(m_collisionObject);
	}
	
	m_soysauce.SetPosition(m_position);
	m_collisionObject->SetPosition(m_position);
	m_soysauce.Update();
}
void SoySauce::Render(RenderContext& rc)
{
	//取得していない時のみ醤油オブジェクトを描画する。
	if (m_player1->GetSauce() == 0 ||
		m_player2->GetSauce() == 0 ||
		m_player3->GetSauce() == 0 ||
		m_player4->GetSauce() == 0)
	{
		m_soysauce.Draw(rc);
	}
}

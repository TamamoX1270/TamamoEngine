#pragma once
class Player1;
class Player2;
class Player3;
class Player4;
class BackGround;
class GameUI;
class GameCamera;

class GameCamera2P;
class GameCamera3P;

class SpecialCamera;

class SoySauce;
class SideWall;
class Title;

class Game : public IGameObject
{
public:
	Game();
	~Game();
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

	/// <summary>
	/// ゲームを消す。
	/// </summary>
	/// <param name="kill">ゲーム削除。</param>
	void SetGameDelete(const int& kill)
	{
		m_gamedelete = kill;
	}

private:
	void Camera();
	//消すときに回す配列の為の関数
	void GameDelete();


private:
	BackGround*		m_backGround;					//背景。
	Title*			m_title;						//タイトル
	FontRender      m_fontRender;					//フォントレンダー
	ModelRender     m_modelRender;					//モデルレンダー
	Player1*        m_player;						//プレイヤー1
	Player2*		m_player2;						//プレイヤー2
	Player3*		m_player3;						//プレイヤー3
	Player4*		m_player4;						//プレイヤー4
	GameUI*			m_gamingshigureui;				//ゲーミングなういママ(GameUI)
	SoySauce*		m_soysauce;						//醤油さし
	SideWall*		m_sidewall;						//左右の壁
	Vector3         m_pointligpos;                  //ポイントライトの座標
	Vector3         m_directionligColor;		    //セットする色
	Vector3			m_spPosition;					//スポットライトのポジション
	Vector3			m_spDirection;                  //スポットライトの方向
	
	//HPバーの実装のための関数
	int m_hp = 0;

	//カメラのポインタ関数
	GameCamera* m_gameCamera;

	GameCamera2P* m_gameCamera2;
	GameCamera3P* m_gameCamera3;

	SpecialCamera* sscamera;
	int m_cameraState = 0;
	int m_gamedelete = false;							//ゲーム削除ステート
};


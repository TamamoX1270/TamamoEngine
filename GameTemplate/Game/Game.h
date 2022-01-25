#pragma once
class Player;
class DirectionLite;

class Game : public IGameObject
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
private:
	ModelRender     m_modelRender;  //モデルレンダー
	Player*         m_player;       //プレイヤー
	Vector3         m_directionligColor;     //セットする色
	
};


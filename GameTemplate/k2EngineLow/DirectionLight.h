#pragma once
namespace nsK2EngineLow {

	class DirectionLight
	{
	public:
		//ディレクションライト用の構造体を定義する。
		struct DirectionLightST {
			Vector3 ligDirection; //ライトの方向
			//HLSL側の定数バッファのfloat3型の変数は16の倍数のアドレスに配置されるため、C++側にはパディングを埋めておく。
			float pad;
			Vector3 ligColor;
		};

	public:
		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// ディレクションライトの方向を設定
		/// </summary>
		/// <param name="lig"></param>
		void SetLigDirection(const Vector3& lig)
		{
			m_directionLig.ligDirection = lig;
		}
		/// <summary>
		/// ディレクションライトの色を設定
		/// </summary>
		/// <param name="col"></param>
		void SetLigColor(const Vector3& col)
		{
			m_directionLig.ligColor = col;
		}
		DirectionLightST& GetDirectionLight()
		{
			return m_directionLig;
		}
	private:
		DirectionLightST            m_directionLig;				//ディレクションライトのデータを作成する。
	};

	//他の場所でも読み込めるようにグローバルにする。
	extern DirectionLight g_directionLig;
}
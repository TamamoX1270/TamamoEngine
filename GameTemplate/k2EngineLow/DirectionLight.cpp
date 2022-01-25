#include "k2EngineLowPreCompile.h"
#include "DirectionLight.h"

namespace nsK2EngineLow {
	//他の場所でも読み込めるようにグローバルにする。
	DirectionLight g_directionLig;
	DirectionLight::DirectionLight()
	{
		
		//ライトは斜め上から当たっている。
		m_directionLig.ligDirection.x = 1.0f;
		m_directionLig.ligDirection.y = -1.0f;
		m_directionLig.ligDirection.z = -1.0f;
		
		//正規化する。
		m_directionLig.ligDirection.Normalize();
		
		
		//ライトのカラーは灰⾊。
		
		m_directionLig.ligColor.x = 2.5f;
		m_directionLig.ligColor.y = 2.5f;
		m_directionLig.ligColor.z = 2.5f;
		
		
		
	}
	DirectionLight::~DirectionLight()
	{

	}
}
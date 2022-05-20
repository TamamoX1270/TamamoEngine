#pragma once

namespace nsK2EngineLow {

	class RenderingEngine :public Noncopyable
	{
	public:
		/// <summary>
		/// 描画オブジェクトを追加。
		/// </summary>
		/// <param name="renderObject"></param>
		void AddRenderObject(SpriteRender* renderObject)
		{
			m_Spriterenders.push_back(renderObject);
		}

		void AddUPRenderObject(SpriteRender* renderObject)
		{
			m_UPSpriterenders.push_back(renderObject);
		}
		
		void AddRenderObject(FontRender* renderObject)
		{
			m_Fontrenders.push_back(renderObject);
		}
		
		void SpriteRenderDraw(RenderContext& rc);
		void UPSpriteRenderDraw(RenderContext& rc);
		
		void FontRenderDraw(RenderContext& rc);
		

	private:
		std::vector<FontRender*> m_Fontrenders;
		std::vector<SpriteRender*> m_Spriterenders;
		std::vector<SpriteRender*> m_UPSpriterenders;
	};

	extern RenderingEngine g_renderingEngine;
}
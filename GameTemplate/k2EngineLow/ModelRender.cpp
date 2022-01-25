#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {

	//モデルを初期化するための情報を設定。
	ModelInitData m_initData;

	ModelRender::ModelRender()
	{
		//シェーダーファイルのファイルパスを指定する。
		m_initData.m_fxFilePath = "Assets/shader/model.fx";
		//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
		m_initData.m_vsEntryPointFunc = "VSMain";
		//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
		m_initData.m_vsSkinEntryPointFunc = "VSSkinMain";
		//スケルトンを指定する。
		m_initData.m_skeleton = &m_skeleton;
		//ディレクションライトの情報を定数バッファとしてディスクリプタヒープに登録するために
		//モデルの初期化情報として渡す。
	
		//モデルの上方向を指定する。
		//3dsMaxではデフォルトZアップになっているが、
		//ユニティちゃんはアニメーションでYアップに変更されている。
		m_initData.m_modelUpAxis = enModelUpAxisY;
	}
	ModelRender::~ModelRender()
	{

	}
	void ModelRender::Init(const char* filePath, AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		//tkmファイルのファイルパスを指定する。
		m_initData.m_tkmFilePath = filePath;
		// スケルトンを初期化。
		InitSkeleton(filePath);
		// アニメーションを初期化。
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);

		m_initData.m_expandConstantBuffer = &g_directionLig.GetDirectionLight();
		m_initData.m_expandConstantBufferSize = sizeof(g_directionLig.GetDirectionLight());

		//作成した初期化データをもとにモデルを初期化する。
		m_model.Init(m_initData);
	}
	void ModelRender::Update()
	{
		//スケルトンを更新。
		m_skeleton.Update(m_model.GetWorldMatrix());

		//アニメーションを進める。
		m_animation.Progress(g_gameTime->GetFrameDeltaTime());

		// ワールド行列を更新。
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	}
	void ModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンのデータを読み込み。
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skeleton,
				m_animationClips,
				numAnimationClips);
		}
	}
	void ModelRender::Draw(RenderContext& rc)
	{
		m_model.Draw(rc);
	}
}
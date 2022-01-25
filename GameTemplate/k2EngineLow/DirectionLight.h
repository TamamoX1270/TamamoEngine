#pragma once
namespace nsK2EngineLow {

	class DirectionLight
	{
	public:
		//�f�B���N�V�������C�g�p�̍\���̂��`����B
		struct DirectionLightST {
			Vector3 ligDirection; //���C�g�̕���
			//HLSL���̒萔�o�b�t�@��float3�^�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁AC++���ɂ̓p�f�B���O�𖄂߂Ă����B
			float pad;
			Vector3 ligColor;
		};

	public:
		DirectionLight();
		~DirectionLight();
		/// <summary>
		/// �f�B���N�V�������C�g�̕�����ݒ�
		/// </summary>
		/// <param name="lig"></param>
		void SetLigDirection(const Vector3& lig)
		{
			m_directionLig.ligDirection = lig;
		}
		/// <summary>
		/// �f�B���N�V�������C�g�̐F��ݒ�
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
		DirectionLightST            m_directionLig;				//�f�B���N�V�������C�g�̃f�[�^���쐬����B
	};

	//���̏ꏊ�ł��ǂݍ��߂�悤�ɃO���[�o���ɂ���B
	extern DirectionLight g_directionLig;
}
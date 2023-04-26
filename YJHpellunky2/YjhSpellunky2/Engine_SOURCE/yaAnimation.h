#pragma once
#include "yaEntity.h"
#include "yaTexture.h"

namespace ya
{
	using namespace ya::math;
	using namespace ya::graphics;
	
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;	// 좌측 상단 좌표
			Vector2 size;		// 좌측상단부터 잘라낼 가로 세로의 픽셀 길이
			Vector2 offset;		// 발 끝
			Vector2 atlasSize;  // 쪼개진 스프라이트의 크기
			float duration;		// 프레임 사이의 시간
			bool reverse;

			Sprite()
				: leftTop(0.0f, 0.0f)
				, size(0.0f, 0.0f)
				, offset(0.0f, 0.0f)
				, atlasSize(0.0f)
				, duration(0.1f)
				, reverse(false)
			{

			}
		};

		Animation();
		virtual ~Animation();

		UINT Update();
		void FixedUpdate();
		void Render();

		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas
			, Vector2 leftTop, Vector2 size, Vector2 offset
			, UINT spriteLegth, float duration , bool reverse);

		void Reset();

		void BindShader();
		void Clear();

		bool IsComplete() { return mbComplete; }
		std::wstring& AnimationName() { return mAnimationName; }

	private:
		std::shared_ptr<Texture> mAtlas;
		class Animator* mAnimator;
		
		std::wstring mAnimationName;
		std::vector<Sprite> mSpriteSheet; //하나씩 여러개 시트
		int mIndex;
		float mTime;
		bool mbComplete;

	};
}

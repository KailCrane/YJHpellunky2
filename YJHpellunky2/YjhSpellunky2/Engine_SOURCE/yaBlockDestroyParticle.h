#pragma once
#include "yaGameObject.h"
#include "yaScript.h"

namespace ya
{
	class BlockDestroyParticle : public Script
	{
	public:
		BlockDestroyParticle();
		~BlockDestroyParticle();

		virtual void Initialize()override;
		virtual void Render()override;

		void SetPoint(Vector3 _point) { point = _point; }
		void OnActive();
		void OffActive();

	private:

		Vector3 point;
	};
}


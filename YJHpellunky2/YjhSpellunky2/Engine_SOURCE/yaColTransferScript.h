#pragma once
#include "yaScript.h"
#include "yaGameObject.h"
#include "yaPlayerScript.h"
#include "yaCaveman.h"

namespace ya
{
	class ColTransferScript : public Script
	{
	public:

		ColTransferScript();
		virtual ~ColTransferScript();

		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;

		void SetReceiver(PlayerScript* obj) { receive_obj = obj; }
		void SetReceiver(Caveman* obj) { cave_receive_obj = obj; }

	private:
		PlayerScript* receive_obj;
		Caveman* cave_receive_obj;
	};
}


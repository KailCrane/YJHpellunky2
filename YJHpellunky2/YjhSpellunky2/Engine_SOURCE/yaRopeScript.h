#pragma once

#include "yaPlayerScript.h"
#include "yaGameObject.h"
#include "yaScript.h"
#include "yaRope.h"

namespace ya
{
	class RopeScript :public Script
	{
	public:
		RopeScript();
		~RopeScript();


		virtual void Initialize()override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void Render()override;

		virtual void OnCollisionEnter(Collider2D* collider) override;
		virtual void OnCollisionStay(Collider2D* collider) override;
		virtual void OnCollisionExit(Collider2D* collider) override;
		virtual void OnTriggerEnter(Collider2D* collider) override;

		//Start면
		//처음 시작한 곳에서 * Y만큼 올라가게
		//다 올라가면 Next에게 ]
		//첨은 갈퀴달린 돌돌이가 다 올라가면 다음 번호 ALLIVE
		// 이번엔 반대로 *Y만큼 내려가게 함
		// 일정 범위 내려갔으면 NEXT를 그자리에 ACTIVE();
		// 마지막에 도달하면 밧줄 풀리는 애니 재생 
		// 
		//불탐

		//내행동이 끝나면 다음에게 전달하기 위해서
		void SetNext(Rope* next){next_chain = next;}
		void SetPrev(Rope* prev){prev_chain = prev;}

		void Throw(Vector3 pos);

		enum State
		{
			Start,
			End,
			Middle
		};
		State state;

	private:
		Rope* prev_chain;
		Rope* next_chain;
		Vector3 start_pos;
		bool isThrow;
	};
};


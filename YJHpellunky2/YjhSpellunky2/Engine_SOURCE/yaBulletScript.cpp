#include "yaBulletScript.h"
#include "yaTime.h"

namespace ya
{
	
	BulletScript::BulletScript()
		:Script()
	{
	}
	BulletScript::~BulletScript()
	{
	}
	void BulletScript::Initialize()
	{
	}
	void BulletScript::Update()
	{
		Flow();
	}
	void BulletScript::FixedUpdate()
	{
	}
	void BulletScript::Render()
	{
	}
	void BulletScript::OnCollisionEnter(Collider2D* collider)
	{
	}
	void BulletScript::OnCollisionStay(Collider2D* collider)
	{
	}
	void BulletScript::OnCollisionExit(Collider2D* collider)
	{
	}
	void BulletScript::OnTriggerEnter(Collider2D* collider)
	{
	}

	void BulletScript::Flow()
	{
		Vector3 curr_pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Vector3 fixed_pos = Vector3(curr_pos.x += flow_dir.x * Time::DeltaTime(), curr_pos.y += flow_dir.y * Time::DeltaTime(), curr_pos.z);
		GetOwner()->GetComponent<Transform>()->SetPosition(fixed_pos);
	}
}


#include "yaMonster.h"

namespace ya
{
	Monster::Monster()
	{

	}
	Monster::~Monster()
	{

	}
	void Monster::Initialize()
	{
		GameObject::Initialize();
	}
	void Monster::Update()
	{
		GameObject::Update();
	}
	void Monster::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Monster::Render()
	{
		GameObject::Render();
	}
	void Monster::RemoveLife(int amount)
	{
		life -= amount;
		if (life < 0)
		{
			life = 0;
		}
	}

	void Monster::OnCollisionEnter(Collider2D col)
	{
	}

	void Monster::OnCollisionStay(Collider2D col)
	{
	}

	void Monster::OnCollisionExit(Collider2D col)
	{
	}
	
	void Monster::ChildOnCollisionEnter(Collider2D* col1, Collider2D* col2)
	{
		const std::vector<Script*>& scripts = GetScripts();

		for (Script* script : scripts)
		{
			script->ChildOnCollisionEnter(col1, col2);
		}
	}

	void Monster::ChildOnCollisionStay(Collider2D* Col1, Collider2D* col2)
	{

	}
	void Monster::ChildOnCollisionExit(Collider2D* Col1, Collider2D* col2)
	{

	}
}
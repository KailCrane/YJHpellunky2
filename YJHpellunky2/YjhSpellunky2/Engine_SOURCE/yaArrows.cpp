#include "yaArrows.h"
#include "yaCollider2D.h"

namespace ya
{
	Arrows::Arrows()
	{
	}
	Arrows::~Arrows()
	{
	}
	void Arrows::Initialize()
	{

	}
	void Arrows::Update()
	{
	}
	void Arrows::FixedUpdate()
	{
	}
	void Arrows::Render()
	{
	}


	void Arrows::OnCollisionEnter(Collider2D* col)
	{
		switch (col->GetOwner()->GetLayerType())
		{
		case eLayerType::Tile:
			//if (col->GetOwner()->GetComponent<Collider2D>()->GetPosition().x)

			break;
		}

	}
	void Arrows::OnCollisionStay(Collider2D* collider)
	{
	}
	void Arrows::OnCollisionExit(Collider2D* collider)
	{
	}

}
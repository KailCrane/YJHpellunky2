#include "yaDetector.h"


namespace ya
{
	Detector::Detector()
		:Script(),
		monster(nullptr)
	{

	}
	Detector::~Detector()
	{
	}
	void Detector::Initialize()
	{
	}

	void Detector::Update()
	{
		if(col == nullptr)
			col = GetOwner()->GetComponent<Collider2D>();

	}

	void Detector::FixedUpdate()
	{

	}

	void Detector::Render()
	{
	}
	void Detector::OnCollisionEnter(Collider2D* collider)
	{
		if (col != nullptr)
		{
			if (col->GetName() ==L"BodyCollider")
			{
				int a = 0;
			}
			if (sender != nullptr)
			{
				sender->ChildOnCollisionEnter(col,collider);
			}
		}
	}
	void Detector::OnCollisionStay(Collider2D* collider)
	{
		if (col != nullptr)
			if(sender != nullptr)
				sender->ChildOnCollisionStay(col, collider);
	}
	void Detector::OnCollisionExit(Collider2D* collider)
	{
		if (col != nullptr)
			if(sender != nullptr)
				sender->ChildOnCollisionExit(col, collider);
	}
}
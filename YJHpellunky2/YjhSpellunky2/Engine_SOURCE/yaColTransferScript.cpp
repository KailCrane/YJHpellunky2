#include "yaColTransferScript.h"
#include "yaPlayerScript.h"

namespace ya
{
	ColTransferScript::ColTransferScript()
		:Script(),
		receive_obj(nullptr),
		cave_receive_obj(nullptr)
	{
	}
	ColTransferScript::~ColTransferScript()
	{
	}
	void ColTransferScript::Initialize()
	{
	}
	void ColTransferScript::Update()
	{

	}
	void ColTransferScript::FixedUpdate()
	{
	}
	void ColTransferScript::Render()
	{
	}
	void ColTransferScript::OnCollisionEnter(Collider2D* collider)
	{
		
			eLayerType sLayer = this->GetOwner()->GetLayerType();
			eLayerType colLayer = collider->GetOwner()->GetLayerType();

			if (receive_obj != nullptr)
				receive_obj->ReciveColEnter(sLayer, collider);
			if (cave_receive_obj != nullptr)
				cave_receive_obj->ReciveColEnter(sLayer, collider);
	}
	void ColTransferScript::OnCollisionStay(Collider2D* collider)
	{
		eLayerType sLayer = this->GetOwner()->GetLayerType();
		if (receive_obj != nullptr)
			receive_obj->ReciveColStay(sLayer, collider);
		if (cave_receive_obj != nullptr)
			cave_receive_obj->ReciveColStay(sLayer, collider);
	}
	void ColTransferScript::OnCollisionExit(Collider2D* collider)
	{
		eLayerType sLayer = this->GetOwner()->GetLayerType();
		if (receive_obj != nullptr)
			receive_obj->ReciveColExit(sLayer, collider);
		if (cave_receive_obj != nullptr)
			cave_receive_obj->ReciveColExit(sLayer, collider);
	}
	void ColTransferScript::OnTriggerEnter(Collider2D* collider)
	{
		//receiver->Reiceive(this->GetOwner()->GetLayerType(),collider->GetOwner()->GetLayerType())
	}
}
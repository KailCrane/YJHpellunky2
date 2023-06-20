#include "yaSkeleton.h"
#include "yaObject.h"
#include "yaTime.h"
#include "yaResources.h"
#include "yaSpriteRenderer.h"

namespace ya
{
	Skeleton::Skeleton()
	{
	}

	Skeleton::~Skeleton()
	{
		
	}


	void Skeleton::Initialize()
	{
		tr = GetOwner()->GetComponent<Transform>();
		tr->SetPosition(Vector3(1.0f, 3.0f, 1.1f));
		animator = GetOwner()->AddComponent<Animator>();
		SetName(L"Skeleton");
		SpriteRenderer* mr = GetOwner()->AddComponent<SpriteRenderer>();
		std::shared_ptr<Material> material = Resources::Find<Material>(L"PlayerMaterial");
		mr->SetMaterial(material);
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
		mr->SetMesh(mesh);

		SetAnimation();
		
		Collider2D* coll = GetOwner()->AddComponent<Collider2D>();
		coll->SetType(eColliderType::Rect);
		coll->SetSize(Vector2(1, 1));
		coll->SetName(L"Monster");
		
		/*{
			head_obj = object::Instantiate<GameObject>(eLayerType::MonsterHead, scene);
			head_obj->SetName(L"MonsterHead");
			head_obj->SetLayerType(eLayerType::Door);
			Transform* head_tr = head_obj->GetComponent<Transform>();
			head_tr->SetPosition(Vector3(head_tr->GetPosition()));
			head_tr->SetScale(Vector3(1, 1, 1));
			head_tr->GetScale();
			head_obj ->AddComponent<Detector>();
			int a = 0;
			SpriteRenderer* mr = head_obj->AddComponent<SpriteRenderer>();
			std::shared_ptr<Material> material = Resources::Find<Material>(L"PlayerMaterial");
			mr->SetMaterial(material);
			std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"RectMesh");
			mr->SetMesh(mesh);
		}*/
			

			/*head = object::Instantiate<GameObject>(eLayerType::MonsterHead, scene);
			Transform* head_tr = head->GetComponent<Transform>();
			
			mr->SetMesh(mesh);


			Collider2D* head_col = head->AddComponent<Collider2D>();

			head_col->SetType(eColliderType::Rect);
			head_col->SetSize(Vector2(1, 1));*/
			//body = object::Instantiate<GameObject>(eLayerType::MonsterBody, scene);
			//Collider2D* body_col = body->AddComponent<Collider2D>();
		//Detector* head_detector = head->AddComponent<Detector>();
		//Detector* body_detector = body->AddComponent<Detector>();
		//Detector* eye_detector = detect_col->AddComponent<Detector>();
		
		//head_detector->SetMonster(this);
		//body_detector->SetMonster(this); 

		//detect_col = object::Instantiate<GameObject>(eLayerType::Detector, scene);

		//eye_detector->SetMonster(this);
	}

	void Skeleton::Update()
	{

		//머리의 좌표값 바디의 좌표값 수정
		//플레이어 감지

		// 만약 플레이어가 자신 보다 왼쪽에 있다면 오른쪽에 있다면


	}

	void Skeleton::FixedUpdate()
	{
	}

	void Skeleton::Render()
	{
	}


	void Skeleton::SetAnimation()
	{
		std::shared_ptr<Texture> texture_L = Resources::Load<Texture>(L"LSkeleton", L"Monster//monstersbasic01L.png");
		std::shared_ptr<Texture> texture_R = Resources::Load<Texture>(L"RSkeleton", L"Monster//monstersbasic01R.png");

		animator->Create(L"LeftIdle", texture_L, Vector2(1920.0f, 0.0f), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
		animator->Create(L"RightIdle", texture_R, Vector2(0.0f, 138.0f * 2), Vector2(128.0f, 128.0f), Vector2::Zero, 1, 0.05f, false);
		animator->Create(L"RightJumpOut", texture_R, Vector2(0.0f, 128.0f * 2), Vector2(128.0f, 128.0f), Vector2::Zero, 6, 0.05f, false);
		animator->Play(L"RightJumpOut",true);
	}

	void Skeleton::SetPlayer()
	{
		std::vector<GameObject*> gameobjcets = scene->GetGameObjects(eLayerType::Player);
		player = gameobjcets[0]->GetScript<Player>();
	}

	void Skeleton::Camouflage()
	{
		animator->Play(L"Camouflage",false);
		Vector3 head_pos(head_obj->GetComponent<Transform>()->GetPosition());
		head_obj->GetComponent<Transform>()->SetPosition(Vector3(head_pos.x,head_pos.y -0.2f,head_pos.z));
		Vector3 body_pos(body->GetComponent<Transform>()->GetPosition());
	}

	void Skeleton::JumpOut()
	{
		
		//튀어나오기 애니메이션 재생과 콜라이더 변경
		const int num = jumpout_sequence;
		//애니메이션 카모폴라쥬 재생과 콜라이더 변경
		switch (num)
		{
		case 0:
			animator->Play(L"JumpOut0");//재생 1
			break;
		case 1:
			animator->Play(L"JumpOut1");
			break;
		case 2:
			animator->Play(L"JumpOut2");//여기까지가 3
			break;
		case 3:
			animator->Play(L"JumpOut3");
			break;
		case 4:
			animator->Play(L"JumpOut4");
			Vector3 head_pos(head_obj->GetComponent<Transform>()->GetPosition());
			head_obj->GetComponent<Transform>()->SetPosition(Vector3(head_pos.x, head_pos.y + 0.2f, head_pos.z));
			Vector3 body_pos(body->GetComponent<Transform>()->GetPosition());
			break; //여기까지가 끝
		}
		jumpout_sequence += 1;
	}

	void Skeleton::PlayerChase()
	{
		Transform* player_tr = player->GetComponent<Transform>();
		if (player_tr->GetPosition().x <= tr->GetPosition().x)
		{
		    Vector3	mPosition = tr->GetPosition();
			tr->SetPosition(Vector3(mPosition.x -= Time::DeltaTime() * move_speed , mPosition.y, mPosition.z));
		}
		else
		{
			Vector3	mPosition = tr->GetPosition();
			tr->SetPosition(Vector3(mPosition.x += Time::DeltaTime() * move_speed, mPosition.y, mPosition.z));
		}
	}

	void Skeleton::Dead()
	{
		//이펙트 전송
		//collider 끄기
	}
	void Skeleton::OnCollisionEnter(Collider2D col)
	{
	}
	void Skeleton::OnCollisionStay(Collider2D col)
	{
	}
	void Skeleton::OnCollisionExit(Collider2D col)
	{
	}
	void Skeleton::ChildOnCollisionEnter(Collider2D* Col1, Collider2D* col2)
	{
	}
	void Skeleton::ChildOnCollisionStay(Collider2D* Col1, Collider2D* col2)
	{
	}
	void Skeleton::ChildOnCollisionExit(Collider2D* Col1, Collider2D* col2)
	{
	}
}
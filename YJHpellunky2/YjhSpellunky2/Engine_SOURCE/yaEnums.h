#pragma once

namespace ya::enums
{
	enum class eSceneType
	{
		Tilte,
		CharacterSelect,
		Play,
		End,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Bg,
		Door,
		Block,
		Ground,
		Ceiling,
		Map,
		MonsterLeftDetect,
		MonsterRightDetect,
		Feet,
		MonsterFeet,
		Head,
		MonsterHead,
		MonsterLeftbody,
		Leftbody,
		MonsterRightBody,
		RightBody,
		Rope,
		Whip,
		Monster,
		Player,
		Arrow,
		ShotGun,
		Bullet,
		ExitDoor,
		UI,

		End = 32,
	};


	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Gravity, // 낙하를 위한 중력
		Camera,
		Mesh,
		Animator,
		Light,
		MeshRenerer,
		SpriteRenderer,
		Collider,
		UI,
		Script,
		End,
	};

	enum class eResourceType
	{
		Mesh,
		Texture,
		Material,
		Sound,
		/*Font,*/
		Prefab,
		MeshData,
		GraphicShader,
		ComputeShader,
		Script,
		End,
	};

	enum class eColliderType
	{
		None,
		Rect,
		Circle,
		Box,
		Sphere,
		End,
	};


	enum class eAnimationType
	{
		None,
		SecondDimension,
		ThirdDimession,
		End
	};

	enum class eItemType
	{
		AlienCompass,
		Ankh,
		ArrowofLight,
		Arrows,
		BearTrap,
		Bomb,
		BombBag,
		BombBox,
		BrokenSword,
		CameraItem,
		Cape,
		Chest,
		ClimbingGloves,
		CloneGun,
		Compass,
		CookedTurkey,
		Crate,
		Crossbow,
		Crown,
		CursePot,
		EggplantCrown,
		Elixir,
		Excalibur,
		FourLeafClover,
		FreezeRay,
		GoldKey,
		Hedjet,
		HouYiBow,
		HoverPack,
		Idol,
		Jetpack,
		Kapala,
		Key,
		Landmine,
		LockedChest,
		Machete,
		Mattock,
		MetalShield,
		Parachute,
		Paste,
		PitcherMitt,
		PlasmaCannon,
		PlayerBag,
		PotofGold,
		PowerPack,
		Present,
		PunishBall,
		Rope,
		RopeBox,
		RopeBag,
		RoyalJelly,
		Scepter,
		Scrap,
		Shotgun,
		Spectacles,
		SpikesShoes,
		SpringShoes,
		TabletofDestiny,
		TekePack,
		TelePoter,
		TheTrueCrown,
		TheTuskIdol,
		Thrownables, 
		Torch,
		UdjatEyes,
		Ushabti,
		vladCape,
		Webgun,
		WoodenShield
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	//struct Ray
	//{
	//	Vector3 origin;
	//	Vector3 dest;
	//};

}
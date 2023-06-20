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

	enum class eTreasureType
	{
		eGoldBar,
		ePileOfGoldBar,
		eSmallGoldNugget,
		eLargeGoldNugget,
		eSmallEmerald,
		eLargeEmerald,
		eSmallSapphire,
		eLargeSapphire,
		eSmallRuby,
		eLargeRuby,
	};

	enum class eLayerType
	{
		None = 0,
		Camera,
		Grid,
		Bg,
		Door,
		Ground,
		Ceiling,
		LeftSide,
		RightSide,
		Map,
		MonsterLeftDetect,
		MonsterRightDetect,
		Head,
		Body,
		Feet,
		Tile,
		MonsterFeet,
		MonsterHead,
		MonsterBody,
		MonsterLeftbody,
		MonsterRightBody,
		Rope,
		Whip,
		Detector,
		Monster,
		ExitDoor,
		Player,
		Arrow,
		ShotGun,
		Bullet,
		Item,
		Particle,
		UI,

		End = 64,
	};


	enum class eComponentType
	{
		None,
		Transform, // 위치 데이터 수정하는 컴포넌트
		Gravity, // 낙하를 위한 중력
		Camera,
		Mesh,
		Animator,
		ParticleSystem,
		Light,
		SpriteRenderer,
		MeshRenerer,
		UI,
		Collider,
		Script,
		End,
	};

	enum class eMonsterType
	{
		eSkeleton,
		eBat,
		eSpider,
		eCaveman,
		eSnake,
		eHornlizard,
		eMerchant,
		eQuillback
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
		None,
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
		Goods,
		Hedjet,
		HouYiBow,
		HoverPack,
		Idol,
		Jetpack,
		Kapala,
		Key,
		SkeletonKey,
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

	enum class eBlockType
	{
		Dirt,
		Wood,
		Stone
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
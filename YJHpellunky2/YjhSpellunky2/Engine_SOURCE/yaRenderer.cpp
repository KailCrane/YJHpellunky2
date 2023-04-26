#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSceneManager.h"

namespace ya::renderer
{
	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};
	
	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;

	void LoadMesh()
	{
		//RECT
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Rect Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes;
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		//
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Debug Rect Mesh
		std::shared_ptr<Mesh> debugmesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugmesh);
		debugmesh->CreateVertexBuffer(vertexes, 4);
		debugmesh->CreateIndexBuffer(indexes.data(), indexes.size());

		//Circle Mesh
		std::vector<Vertex> circleVertexes;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, 0.0f,1.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2::Zero;

		circleVertexes.push_back(center);

		int iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		// 삼각함수를 이용한 백터회전
		for (size_t i = 0; i < iSlice; i++)
		{
			Vertex vtx = {};
			vtx.pos = Vector4
			(
				fRadius * cosf(fTheta * (float)i)
				,fRadius * sinf(fTheta * (float)i)
				, -0.00001f, 1.0f
			);
			vtx.color = center.color;

			circleVertexes.push_back(vtx);
		}
		indexes.clear();

		for (size_t i = 0; i < iSlice - 2; i++)
		{

			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		// Crate Circle Mesh
		std::shared_ptr<Mesh> circleMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"CircleMesh", circleMesh);
		circleMesh->CreateVertexBuffer(circleVertexes.data(), indexes.size());
		circleMesh->CreateIndexBuffer(indexes.data(),indexes.size());

	}

	void SetUpState()
	{
#pragma region Input layout
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;


		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, shader->GetVSBlobBufferPointer()
			, shader->GetVSBlobBufferSize()
			, shader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, debugShader->GetVSBlobBufferPointer()
			, debugShader->GetVSBlobBufferSize()
			, debugShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, uiShader->GetVSBlobBufferPointer()
			, uiShader->GetVSBlobBufferSize()
			, uiShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, gridShader->GetVSBlobBufferPointer()
			, gridShader->GetVSBlobBufferSize()
			, gridShader->GetInputLayoutAddressOf());


#pragma endregion
#pragma region sampler state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		//D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
		//D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,
		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;


		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Point].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState
		(
			&samplerDesc
			, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf()
		);

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point
			, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear
			, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());

		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic
			, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer state
		D3D11_RASTERIZER_DESC rsDesc = {};
		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GetDevice()->CreateRasterizerState(&rsDesc
			, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());


#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;
		
		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&dsDesc
			, depthstencilStates[(UINT)eDSType::None].GetAddressOf());
		
#pragma endregion
#pragma region Blend State

		blendStates[(UINT)eBSType::Default] = nullptr;

		D3D11_BLEND_DESC bsDesc = {};
		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;

		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());

#pragma endregion
	}

	void LoadBuffer()
	{
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));
	}

	void LoadShader()
	{
		// Default
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");

		Resources::Insert<Shader>(L"RectShader", shader);

		// Sprite
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"SpriteShader", spriteShader);

		// UI
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");

		Resources::Insert<Shader>(L"UIShader", uiShader);

		// Grid Shader
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);

		Resources::Insert<Shader>(L"GridShader", gridShader);

		//Debug Shader
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::NoWrite);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Resources::Insert<Shader>(L"DebugShader", debugShader);


		// Player Shader
		std::shared_ptr<Shader> playerShader = std::make_shared<Shader>();
		playerShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		playerShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");

		Resources::Insert<Shader>(L"PlayerShader", playerShader);
	}

	void LoadTexture()
	{
		Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
		Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
		Resources::Load<Texture>(L"PlayerSprite", L"Player\\Player.png");
		Resources::Load<Texture>(L"MenuTitleTexture", L"UI\\BackGround\\MenuTitle.png");
		Resources::Load<Texture>(L"MenuTitlegalTexture", L"UI\\BackGround\\MenuTitlegal.png");
		Resources::Load<Texture>(L"PlayerTexture", L"Player\\Anna_Walk\\AnnaWalk_2.png");

		Resources::Load<Texture>(L"PlayerTexture", L"Player\\Anna_Walk\\AnnaWalk_2.png");
		Resources::Load<Texture>(L"ChrSelTexture", L"UI\\ChrSel\\Menu_Charsel.png");
		Resources::Load<Texture>(L"CaveBgTexture", L"UI\\Level1\\Level1Bg.png");
		Resources::Load<Texture>(L"level1_floorTexture", L"UI\\Level1\\Level1Floor.png");
		Resources::Load<Texture>(L"deco_basecamp_entranceTexture", L"UI\\Level1\\deco_basecamp_01.png");
		Resources::Load<Texture>(L"deco_basecamp_uroborosTexture", L"UI\\Level1\\deco_basecamp_04.png");

		Resources::Load<Texture>(L"StoneDiskTexture", L"TitleMenu\\StoneDisk.png");
		Resources::Load<Texture>(L"SplitDisk_L_Texture", L"TitleMenu\\SplitDiskLeft.png");
		Resources::Load<Texture>(L"SplitDisk_R_Texture", L"TitleMenu\\SplitDiskRight.png");

		Resources::Load<Texture>(L"StoneHeadTexture", L"TitleMenu\\StoneHead.png");
		Resources::Load<Texture>(L"SnakeHeadTexture", L"TitleMenu\\SnakeHead.png");

		Resources::Load<Texture>(L"main_fore_2L_Texture", L"TitleMenu\\main_fore_2L.png");
		Resources::Load<Texture>(L"main_fore_2R_Texture", L"TitleMenu\\main_fore_2R.png");
		Resources::Load<Texture>(L"main_foreL_Texture", L"TitleMenu\\main_foreL.png");
		Resources::Load<Texture>(L"main_foreR_Texture", L"TitleMenu\\main_foreR.png");
		Resources::Load<Texture>(L"main_doorframe_Texture", L"TitleMenu\\main_doorframe.png");
		Resources::Load<Texture>(L"main_doorback_Texture", L"TitleMenu\\main_doorback.png");
		Resources::Load<Texture>(L"main_dirt_Texture", L"TitleMenu\\main_dirt.png");

		Resources::Load<Texture>(L"SelectBarL_Texture", L"TitleMenu\\SelectBarL.png");
		Resources::Load<Texture>(L"SelectBarR_Texture", L"TitleMenu\\SelectBarR.png");

		Resources::Load<Texture>(L"OptionBar_Texture", L"TitleMenu\\OptionBar.png");
		Resources::Load<Texture>(L"PlayBar_Texture", L"TitleMenu\\PlayBar.png");
		Resources::Load<Texture>(L"PlayerProfileBar_Texture", L"TitleMenu\\PlayerProfileBar.png");
		Resources::Load<Texture>(L"RankBar_Texture", L"TitleMenu\\RankBar.png");

		Resources::Load<Texture>(L"RankBar_Texture", L"TitleMenu\\RankBar.png");
		Resources::Load<Texture>(L"RankBar_Texture", L"TitleMenu\\RankBar.png");
		Resources::Load<Texture>(L"RankBar_Texture", L"TitleMenu\\RankBar.png");

		Resources::Load<Texture>(L"CharDoor_Texture", L"CharSel\\menu_chardoor_01.png");
		Resources::Load<Texture>(L"CharDoorBlocked_Texture", L"CharSel\\menu_chardoor_02.png");
		Resources::Load<Texture>(L"CharDoorFrame_Texture", L"CharSel\\menu_chardoor_03.png");
		Resources::Load<Texture>(L"CharDoorSpace_Texture", L"CharSel\\menu_chardoor_04.png");
		Resources::Load<Texture>(L"MenuCharsel_Texture", L"CharSel\\menu_charsel.png");

		Resources::Load<Texture>(L"RopeMidlle_Texture", L"CharSel\\Rope_Middle.png");

		Resources::Load<Texture>(L"Scroll_Texture", L"CharSel\\Scroll.png");
		Resources::Load<Texture>(L"ScrollMiddle_Texture", L"CharSel\\ScrollMiddle.png");

		Resources::Load<Texture>(L"Char_Select_Upboard_Texture", L"CharSel\\char_select_upboard.png");
		Resources::Load<Texture>(L"Char_Select_Downboard_Texture", L"CharSel\\char_select_downboard.png");

		Resources::Load<Texture>(L"Z_Button_Texture", L"CharSel\\z_button.png");

		Resources::Load<Texture>(L"LeftArrow_Texture", L"CharSel\\LeftArrow.png");
		Resources::Load<Texture>(L"RightArrow_Texture", L"CharSel\\RightArrow.png");

	}

	void LoadMaterial()
	{

		// Default
		std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"SmileTexture");
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(texture);
		Resources::Insert<Material>(L"RectMaterial", material);

		// Sprite
		std::shared_ptr <Texture> spriteTexture = Resources::Find<Texture>(L"DefaultSprite");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(spriteShader);
		spriteMaterial->SetTexture(spriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);

		//Player_Default
		std::shared_ptr <Texture> player_Texture = Resources::Find<Texture>(L"PlayerTexture");
		std::shared_ptr<Shader> player_Shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> Player_Material = std::make_shared<Material>();
		Player_Material->SetRenderingMode(eRenderingMode::Transparent);
		Player_Material->SetShader(player_Shader);
		Player_Material->SetTexture(player_Texture);
		Resources::Insert<Material>(L"PlayerMaterial", Player_Material);

		// UI
		std::shared_ptr <Texture> Menu_uiTexture = Resources::Find<Texture>(L"MenuTitleTexture");
		std::shared_ptr<Shader> Menu_uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> Menu_uiMaterial = std::make_shared<Material>();
		Menu_uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		Menu_uiMaterial->SetShader(Menu_uiShader);
		Menu_uiMaterial->SetTexture(Menu_uiTexture);
		Resources::Insert<Material>(L"MenuTitleMaterial", Menu_uiMaterial);

		std::shared_ptr <Texture> MenuTitlegal_uiTexture = Resources::Find<Texture>(L"MenuTitlegalTexture");
		std::shared_ptr<Shader> MenuTitlegal_uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> MenuTitlegal_uiMaterial = std::make_shared<Material>();
		MenuTitlegal_uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		MenuTitlegal_uiMaterial->SetShader(MenuTitlegal_uiShader);
		MenuTitlegal_uiMaterial->SetTexture(MenuTitlegal_uiTexture);
		Resources::Insert<Material>(L"MenuTitlegalMaterial", MenuTitlegal_uiMaterial);

		std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"HPBarTexture");
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
		uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		uiMaterial->SetShader(uiShader);
		uiMaterial->SetTexture(uiTexture);
		Resources::Insert<Material>(L"UIMaterial", uiMaterial);

#pragma region TitleStone


		std::shared_ptr <Texture> stonediskTexture = Resources::Find<Texture>(L"StoneDiskTexture");
		std::shared_ptr<Shader> stonediskShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> stonediskMaterial = std::make_shared<Material>();
		stonediskMaterial->SetRenderingMode(eRenderingMode::Transparent);
		stonediskMaterial->SetShader(stonediskShader);
		stonediskMaterial->SetTexture(stonediskTexture);
		Resources::Insert<Material>(L"StoneDiskMaterial", stonediskMaterial);

		std::shared_ptr <Texture> stoneheadTexture = Resources::Find<Texture>(L"StoneHeadTexture");
		std::shared_ptr<Shader> stoneheadShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> stoneheadMaterial = std::make_shared<Material>();
		stoneheadMaterial->SetRenderingMode(eRenderingMode::Transparent);
		stoneheadMaterial->SetShader(stoneheadShader);
		stoneheadMaterial->SetTexture(stoneheadTexture);
		Resources::Insert<Material>(L"StoneHeadMaterial", stoneheadMaterial);

		std::shared_ptr <Texture> snakeheadTexture = Resources::Find<Texture>(L"SnakeHeadTexture");
		std::shared_ptr<Shader> snakeheadShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> snakeheadMaterial = std::make_shared<Material>();
		snakeheadMaterial->SetRenderingMode(eRenderingMode::Transparent);
		snakeheadMaterial->SetShader(snakeheadShader);
		snakeheadMaterial->SetTexture(snakeheadTexture);
		Resources::Insert<Material>(L"SnakeHeadMaterial", snakeheadMaterial);


		//split_disk
		std::shared_ptr <Texture> split_disk_L_Texture = Resources::Find<Texture>(L"SplitDisk_L_Texture");
		std::shared_ptr<Shader> split_disk_L_Shader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> split_disk_L_Material = std::make_shared<Material>();
		split_disk_L_Material->SetRenderingMode(eRenderingMode::Transparent);
		split_disk_L_Material->SetShader(split_disk_L_Shader);
		split_disk_L_Material->SetTexture(split_disk_L_Texture);
		Resources::Insert<Material>(L"SplitDisk_L_Material", split_disk_L_Material);

		std::shared_ptr <Texture> split_disk_R_Texture = Resources::Find<Texture>(L"SplitDisk_R_Texture");
		std::shared_ptr<Shader> split_disk_R_Shader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> split_disk_R_Material = std::make_shared<Material>();
		split_disk_R_Material->SetRenderingMode(eRenderingMode::Transparent);
		split_disk_R_Material->SetShader(split_disk_R_Shader);
		split_disk_R_Material->SetTexture(split_disk_R_Texture);
		Resources::Insert<Material>(L"SplitDisk_R_Material", split_disk_R_Material);

#pragma endregion

#pragma region MenuBg
		{
			std::shared_ptr <Texture>main_fore_2L_Texture = Resources::Find<Texture>(L"main_fore_2L_Texture");
			std::shared_ptr<Shader> main_fore_2L_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_fore_2L_Material = std::make_shared<Material>();
			main_fore_2L_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_fore_2L_Material->SetShader(main_fore_2L_Shader);
			main_fore_2L_Material->SetTexture(main_fore_2L_Texture);
			Resources::Insert<Material>(L"main_fore_2L_Material", main_fore_2L_Material);
		}

		{
			std::shared_ptr <Texture>main_fore_2R_Texture = Resources::Find<Texture>(L"main_fore_2R_Texture");
			std::shared_ptr<Shader> main_fore_2R_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_fore_2R_Material = std::make_shared<Material>();
			main_fore_2R_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_fore_2R_Material->SetShader(main_fore_2R_Shader);
			main_fore_2R_Material->SetTexture(main_fore_2R_Texture);
			Resources::Insert<Material>(L"main_fore_2R_Material", main_fore_2R_Material);
		}

		{
			std::shared_ptr <Texture>main_foreL_Texture = Resources::Find<Texture>(L"main_foreL_Texture");
			std::shared_ptr<Shader> main_foreL_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_foreL_Material = std::make_shared<Material>();
			main_foreL_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_foreL_Material->SetShader(main_foreL_Shader);
			main_foreL_Material->SetTexture(main_foreL_Texture);
			Resources::Insert<Material>(L"main_foreL_Material", main_foreL_Material);
		}

		{
			std::shared_ptr <Texture>main_foreR_Texture = Resources::Find<Texture>(L"main_foreR_Texture");
			std::shared_ptr<Shader> main_foreR_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_foreR_Material = std::make_shared<Material>();
			main_foreR_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_foreR_Material->SetShader(main_foreR_Shader);
			main_foreR_Material->SetTexture(main_foreR_Texture);
			Resources::Insert<Material>(L"main_foreR_Material", main_foreR_Material);
		}
		{
			std::shared_ptr <Texture>main_doorframe_Texture = Resources::Find<Texture>(L"main_doorframe_Texture");
			std::shared_ptr<Shader> main_doorframe_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_doorframe_Material = std::make_shared<Material>();
			main_doorframe_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_doorframe_Material->SetShader(main_doorframe_Shader);
			main_doorframe_Material->SetTexture(main_doorframe_Texture);
			Resources::Insert<Material>(L"main_doorframe_Material", main_doorframe_Material);
		}
		{
			std::shared_ptr <Texture>main_doorback_Texture = Resources::Find<Texture>(L"main_doorback_Texture");
			std::shared_ptr<Shader> main_doorback_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_doorback_Material = std::make_shared<Material>();
			main_doorback_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_doorback_Material->SetShader(main_doorback_Shader);
			main_doorback_Material->SetTexture(main_doorback_Texture);
			Resources::Insert<Material>(L"main_doorback_Material", main_doorback_Material);
		}
		{
			std::shared_ptr <Texture>main_dirt_Texture = Resources::Find<Texture>(L"main_dirt_Texture");
			std::shared_ptr<Shader> main_dirt_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_dirt_Material = std::make_shared<Material>();
			main_dirt_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_dirt_Material->SetShader(main_dirt_Shader);
			main_dirt_Material->SetTexture(main_dirt_Texture);
			Resources::Insert<Material>(L"main_dirt_Material", main_dirt_Material);
		}

		{
			std::shared_ptr <Texture>selectBarL_Texture = Resources::Find<Texture>(L"SelectBarL_Texture");
			std::shared_ptr<Shader> selectBarL_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> selectBarL_Material = std::make_shared<Material>();
			selectBarL_Material->SetRenderingMode(eRenderingMode::Transparent);
			selectBarL_Material->SetShader(selectBarL_Shader);
			selectBarL_Material->SetTexture(selectBarL_Texture);
			Resources::Insert<Material>(L"selectBarL_Material", selectBarL_Material);
		}

		{
			std::shared_ptr <Texture>selectBarR_Texture = Resources::Find<Texture>(L"SelectBarR_Texture");
			std::shared_ptr<Shader> selectBarR_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> selectBarR_Material = std::make_shared<Material>();
			selectBarR_Material->SetRenderingMode(eRenderingMode::Transparent);
			selectBarR_Material->SetShader(selectBarR_Shader);
			selectBarR_Material->SetTexture(selectBarR_Texture);
			Resources::Insert<Material>(L"SelectBarR_Material", selectBarR_Material);
		}

		{
			std::shared_ptr <Texture>optionBar_Texture = Resources::Find<Texture>(L"OptionBar_Texture");
			std::shared_ptr<Shader> optionBar_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> optionBar_Material = std::make_shared<Material>();
			optionBar_Material->SetRenderingMode(eRenderingMode::Transparent);
			optionBar_Material->SetShader(optionBar_Shader);
			optionBar_Material->SetTexture(optionBar_Texture);
			Resources::Insert<Material>(L"OptionBar_Material", optionBar_Material);
		}

		{
			std::shared_ptr <Texture>playBar_Texture = Resources::Find<Texture>(L"PlayBar_Texture");
			std::shared_ptr<Shader> playBar_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> playBar_Material = std::make_shared<Material>();
			playBar_Material->SetRenderingMode(eRenderingMode::Transparent);
			playBar_Material->SetShader(playBar_Shader);
			playBar_Material->SetTexture(playBar_Texture);
			Resources::Insert<Material>(L"PlayBar_Material", playBar_Material);
		}

		{
			std::shared_ptr <Texture>playerProfileBar_Texture = Resources::Find<Texture>(L"PlayerProfileBar_Texture");
			std::shared_ptr<Shader> playerProfileBar_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> playerProfileBar_Material = std::make_shared<Material>();
			playerProfileBar_Material->SetRenderingMode(eRenderingMode::Transparent);
			playerProfileBar_Material->SetShader(playerProfileBar_Shader);
			playerProfileBar_Material->SetTexture(playerProfileBar_Texture);
			Resources::Insert<Material>(L"PlayerProfileBar_Material", playerProfileBar_Material);
		}

		{
			std::shared_ptr <Texture>rankBar_Texture = Resources::Find<Texture>(L"RankBar_Texture");
			std::shared_ptr<Shader> rankBar_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> rankBar_Material = std::make_shared<Material>();
			rankBar_Material->SetRenderingMode(eRenderingMode::Transparent);
			rankBar_Material->SetShader(rankBar_Shader);
			rankBar_Material->SetTexture(rankBar_Texture);
			Resources::Insert<Material>(L"RankBar_Material", rankBar_Material);
		}

		{
			std::shared_ptr <Texture>charDoor_Texture = Resources::Find<Texture>(L"CharDoor_Texture");
			std::shared_ptr<Shader> charDoor_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> charDoor_Material = std::make_shared<Material>();
			charDoor_Material->SetRenderingMode(eRenderingMode::Transparent);
			charDoor_Material->SetShader(charDoor_Shader);
			charDoor_Material->SetTexture(charDoor_Texture);
			Resources::Insert<Material>(L"CharDoor_Material", charDoor_Material);
		}

		{
			std::shared_ptr <Texture>charDoorBlocked_Texture = Resources::Find<Texture>(L"CharDoorBlocked_Texture");
			std::shared_ptr<Shader> charDoorBlocked_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> charDoorBlocked_Material = std::make_shared<Material>();
			charDoorBlocked_Material->SetRenderingMode(eRenderingMode::Transparent);
			charDoorBlocked_Material->SetShader(charDoorBlocked_Shader);
			charDoorBlocked_Material->SetTexture(charDoorBlocked_Texture);
			Resources::Insert<Material>(L"CharDoorBlocked_Material", charDoorBlocked_Material);
		}

		{
			std::shared_ptr <Texture>charDoorFrame_Texture = Resources::Find<Texture>(L"CharDoorFrame_Texture");
			std::shared_ptr<Shader> charDoorFrame_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> charDoorFrame_Material = std::make_shared<Material>();
			charDoorFrame_Material->SetRenderingMode(eRenderingMode::Transparent);
			charDoorFrame_Material->SetShader(charDoorFrame_Shader);
			charDoorFrame_Material->SetTexture(charDoorFrame_Texture);
			Resources::Insert<Material>(L"CharDoorFrame_Material", charDoorFrame_Material);
		}
		{
			std::shared_ptr <Texture>charDoorSpace_Texture = Resources::Find<Texture>(L"CharDoorSpace_Texture");
			std::shared_ptr<Shader> charDoorSpace_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> charDoorSpace_Material = std::make_shared<Material>();
			charDoorSpace_Material->SetRenderingMode(eRenderingMode::Transparent);
			charDoorSpace_Material->SetShader(charDoorSpace_Shader);
			charDoorSpace_Material->SetTexture(charDoorSpace_Texture);
			Resources::Insert<Material>(L"CharDoorSpace_Material", charDoorSpace_Material);
		}
		{
			std::shared_ptr <Texture>menucharsel_Texture = Resources::Find<Texture>(L"MenuCharsel_Texture");
			std::shared_ptr<Shader> menucharsel_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> menucharsel_Material = std::make_shared<Material>();
			menucharsel_Material->SetRenderingMode(eRenderingMode::Transparent);
			menucharsel_Material->SetShader(menucharsel_Shader);
			menucharsel_Material->SetTexture(menucharsel_Texture);
			Resources::Insert<Material>(L"MenuCharsel_Material", menucharsel_Material);
		}

		{
			std::shared_ptr <Texture>ropeMiddle_Texture = Resources::Find<Texture>(L"RopeMidlle_Texture");
			std::shared_ptr<Shader> ropeMiddle_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>ropeMiddle_Material = std::make_shared<Material>();
			ropeMiddle_Material->SetRenderingMode(eRenderingMode::Transparent);
			ropeMiddle_Material->SetShader(ropeMiddle_Shader);
			ropeMiddle_Material->SetTexture(ropeMiddle_Texture);
			Resources::Insert<Material>(L"RopeMiddle_Material", ropeMiddle_Material);
		}

		{
			std::shared_ptr <Texture>scroll_Texture = Resources::Find<Texture>(L"Scroll_Texture");
			std::shared_ptr<Shader> scroll_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>scroll_Material = std::make_shared<Material>();
			scroll_Material->SetRenderingMode(eRenderingMode::Transparent);
			scroll_Material->SetShader(scroll_Shader);
			scroll_Material->SetTexture(scroll_Texture);
			Resources::Insert<Material>(L"Scroll_Material", scroll_Material);
		}

		{
			std::shared_ptr <Texture>scrollMiddle_Texture = Resources::Find<Texture>(L"ScrollMiddle_Texture");
			std::shared_ptr<Shader> scrollMiddle_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>scrollMiddle_Material = std::make_shared<Material>();
			scrollMiddle_Material->SetRenderingMode(eRenderingMode::Transparent);
			scrollMiddle_Material->SetShader(scrollMiddle_Shader);
			scrollMiddle_Material->SetTexture(scrollMiddle_Texture);
			Resources::Insert<Material>(L"ScrollMiddle_Material", scrollMiddle_Material);
		}
		{
			std::shared_ptr <Texture>char_Select_Upboard_Texture = Resources::Find<Texture>(L"Char_Select_Upboard_Texture");
			std::shared_ptr<Shader> char_Select_Upboard_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>char_Select_Upboard_Material = std::make_shared<Material>();
			char_Select_Upboard_Material->SetRenderingMode(eRenderingMode::Transparent);
			char_Select_Upboard_Material->SetShader(char_Select_Upboard_Shader);
			char_Select_Upboard_Material->SetTexture(char_Select_Upboard_Texture);
			Resources::Insert<Material>(L"Char_Select_Upboard_Material", char_Select_Upboard_Material);
		}
		{
			std::shared_ptr <Texture>char_Select_Downboard_Texture = Resources::Find<Texture>(L"Char_Select_Downboard_Texture");
			std::shared_ptr<Shader> char_Select_Downboard_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>char_Select_Downboard_Material = std::make_shared<Material>();
			char_Select_Downboard_Material->SetRenderingMode(eRenderingMode::Transparent);
			char_Select_Downboard_Material->SetShader(char_Select_Downboard_Shader);
			char_Select_Downboard_Material->SetTexture(char_Select_Downboard_Texture);
			Resources::Insert<Material>(L"Char_Select_Downboard_Material", char_Select_Downboard_Material);
		}

		{
			std::shared_ptr <Texture>z_button_Texture = Resources::Find<Texture>(L"Z_Button_Texture");
			std::shared_ptr<Shader> z_button_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>z_button_Material = std::make_shared<Material>();
			z_button_Material->SetRenderingMode(eRenderingMode::Transparent);
			z_button_Material->SetShader(z_button_Shader);
			z_button_Material->SetTexture(z_button_Texture);
			Resources::Insert<Material>(L"Z_Button_Material", z_button_Material);
		}

		{
			std::shared_ptr <Texture>leftarrow_Texture = Resources::Find<Texture>(L"LeftArrow_Texture");
			std::shared_ptr<Shader> leftarrow_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>leftarrow_Material = std::make_shared<Material>();
			leftarrow_Material->SetRenderingMode(eRenderingMode::Transparent);
			leftarrow_Material->SetShader(leftarrow_Shader);
			leftarrow_Material->SetTexture(leftarrow_Texture);
			Resources::Insert<Material>(L"LeftArrow_Material", leftarrow_Material);
		}

		{
			std::shared_ptr <Texture>rightarrow_Texture = Resources::Find<Texture>(L"RightArrow_Texture");
			std::shared_ptr<Shader> rightarrow_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>rightarrow_Material = std::make_shared<Material>();
			rightarrow_Material->SetRenderingMode(eRenderingMode::Transparent);
			rightarrow_Material->SetShader(rightarrow_Shader);
			rightarrow_Material->SetTexture(rightarrow_Texture);
			Resources::Insert<Material>(L"RightArrow_Material", rightarrow_Material);


			//Bg
			std::shared_ptr <Texture> chrseltexture = Resources::Find<Texture>(L"ChrSelTexture");
			std::shared_ptr<Shader> chrselshader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> chrselmaterial = std::make_shared<Material>();
			chrselmaterial->SetShader(chrselshader);
			chrselmaterial->SetTexture(chrseltexture);
			Resources::Insert<Material>(L"ChrSelMaterial", chrselmaterial);

			std::shared_ptr <Texture> cavebgtexture = Resources::Find<Texture>(L"CaveBgTexture");
			std::shared_ptr<Shader> cavebgshader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> cavebgmaterial = std::make_shared<Material>();
			cavebgmaterial->SetShader(cavebgshader);
			cavebgmaterial->SetTexture(cavebgtexture);
			Resources::Insert<Material>(L"CaveBgMaterial", cavebgmaterial);

			std::shared_ptr <Texture> level1_floortexture = Resources::Find<Texture>(L"level1_floorTexture");
			std::shared_ptr<Shader> level1_floorshader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> level1_floormaterial = std::make_shared<Material>();
			level1_floormaterial->SetShader(level1_floorshader);
			level1_floormaterial->SetTexture(level1_floortexture);
			Resources::Insert<Material>(L"level1_floorMaterial", level1_floormaterial);

			std::shared_ptr <Texture> deco_basecamp_entrance_texture = Resources::Find<Texture>(L"deco_basecamp_entranceTexture");
			std::shared_ptr<Shader> deco_basecamp_entrance_shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> deco_basecamp_entrance_material = std::make_shared<Material>();
			deco_basecamp_entrance_material->SetShader(deco_basecamp_entrance_shader);
			deco_basecamp_entrance_material->SetTexture(deco_basecamp_entrance_texture);
			Resources::Insert<Material>(L"deco_basecamp_entranceMaterial", deco_basecamp_entrance_material);

			std::shared_ptr <Texture> deco_basecamp_uroboros_texture = Resources::Find<Texture>(L"deco_basecamp_uroborosTexture");
			std::shared_ptr<Shader> deco_basecamp_uroboros_shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> deco_basecamp_uroboros_material = std::make_shared<Material>();
			deco_basecamp_uroboros_material->SetShader(deco_basecamp_uroboros_shader);
			deco_basecamp_uroboros_material->SetTexture(deco_basecamp_uroboros_texture);
			Resources::Insert<Material>(L"deco_basecamp_uroborosMaterial", deco_basecamp_uroboros_material);




			// Grid
			std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
			std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
			gridMaterial->SetShader(gridShader);
			Resources::Insert<Material>(L"GridMaterial", gridMaterial);

			// Debug
			std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
			std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
			debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
			debugMaterial->SetShader(debugShader);
			Resources::Insert<Material>(L"DebugMaterial", debugMaterial);

			// Player
			/*std::shared_ptr<Texture> playerTexture = Resources::Find<Texture>(L"PlayerSprite");
			std::shared_ptr<Shader> playerShader = Resources::Find<Shader>(L"PlayerShader");*/

		}
	}
	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; i++)
		{
			delete constantBuffers[i]; 
			constantBuffers[i] = nullptr;
		}
	}

	void Render()
	{
		//std::vector<Camera*> cameras[(UINT)eSceneType::End];
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();
	}
}
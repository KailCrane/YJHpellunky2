#include "yaRenderer.h"
#include "yaResources.h"
#include "yaMaterial.h"
#include "yaSceneManager.h"
#include "yaPaintShader.h"
#include "yaParticleShader.h"

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
	std::vector<LightAttribute> lights;
	StructedBuffer* lightsBuffer = nullptr;



	void LoadMesh()
	{
		#pragma region POINT MESH
		Vertex v = {};
		std::shared_ptr<Mesh> pointMesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"PointMesh", pointMesh);
		pointMesh->CreateVertexBuffer(&v, 1);
		UINT pointIndex = 0;
		pointMesh->CreateIndexBuffer(&pointIndex, 1);
		#pragma endregion
		#pragma region RECT MESH
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

		// Crate Mesh
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
#pragma endregion
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

#pragma endregion
#pragma region DEBUG RECTMESH
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.f, 0.f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Crate Mesh
		std::shared_ptr<Mesh> debugmesh = std::make_shared<Mesh>();
		Resources::Insert<Mesh>(L"DebugRectMesh", debugmesh);
		debugmesh->CreateVertexBuffer(vertexes, 4);
		debugmesh->CreateIndexBuffer(indexes.data(), indexes.size());

#pragma endregion


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

	void LoadShader()
	{
		
		// Default
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		shader->SetBSState(eBSType::AlphaBlend);
		shader->SetRSState(eRSType::SolidNone);
		Resources::Insert<Shader>(L"RectShader", shader);
#pragma region SPRITE SHADER
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		spriteShader->SetRSState(eRSType::SolidNone);
		Resources::Insert<Shader>(L"SpriteShader", spriteShader);

		std::shared_ptr<Shader> bossShader = std::make_shared<Shader>();
		bossShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		bossShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		bossShader->SetRSState(eRSType::SolidNone);
		Resources::Insert<Shader>(L"BossShader", bossShader);

#pragma endregion
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

		// PaintShader
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		Resources::Insert<PaintShader>(L"PaintShader", paintShader);


#pragma region DEBUG SHADER
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetRSState(eRSType::SolidNone);
		debugShader->SetDSState(eDSType::NoWrite);
		debugShader->SetBSState(eBSType::AlphaBlend);
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		Resources::Insert<Shader>(L"DebugShader", debugShader);
#pragma endregion

		// Particle Shader
		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		Resources::Insert<Shader>(L"ParticleShader", particleShader);

		std::shared_ptr<ParticleShader> particleCS = std::make_shared<ParticleShader>();
		Resources::Insert<ParticleShader>(L"ParticleCS", particleCS);
		particleCS->Create(L"ParticleCS.hlsl", "main");

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

		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, particleShader->GetVSBlobBufferPointer()
			, particleShader->GetVSBlobBufferSize()
			, particleShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, spriteShader->GetVSBlobBufferPointer()
			, spriteShader->GetVSBlobBufferSize()
			, spriteShader->GetInputLayoutAddressOf());

		std::shared_ptr<Shader> bossShader = Resources::Find<Shader>(L"BossShader");
		GetDevice()->CreateInputLayout(arrLayoutDesc, 3
			, bossShader->GetVSBlobBufferPointer()
			, bossShader->GetVSBlobBufferSize()
			, bossShader->GetInputLayoutAddressOf());


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

		constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
		constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

		constantBuffers[(UINT)eCBType::Texture] = new ConstantBuffer(eCBType::Texture);
		constantBuffers[(UINT)eCBType::Texture]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::ParticleSystem] = new ConstantBuffer(eCBType::ParticleSystem);
		constantBuffers[(UINT)eCBType::ParticleSystem]->Create(sizeof(ParticleSystemCB));

		constantBuffers[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffers[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));


		//Structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 128, eSRVType::SRV, nullptr , true);
	}

	void LoadTexture()
	{
		Resources::Load<Texture>(L"SmileTexture", L"Smile.png");
		Resources::Load<Texture>(L"DefaultSprite", L"Light.png");
		Resources::Load<Texture>(L"HPBarTexture", L"HPBar.png");
		Resources::Load<Texture>(L"PlayerSprite", L"Player\\Player.png");
		Resources::Load<Texture>(L"MenuTitleTexture", L"UI\\BackGround\\MenuTitle.png");
		Resources::Load<Texture>(L"MenuTitlegalTexture", L"UI\\BackGround\\MenuTitlegal.png");
		Resources::Load<Texture>(L"PlayerTexture", L"Player\\AnnaDefualt.png");

		//Create
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE
			| D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert<Texture>(L"PaintTexture", uavTexture);

		Resources::Load<Texture>(L"noise_01", L"noise\\noise_01.png");
		Resources::Load<Texture>(L"noise_02", L"noise\\noise_02.png");
		//Resources::Load<Texture>(L"noise_03", L"noise\\noise_03.png");

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

		Resources::Load<Texture>(L"EntranceDoor_Texture", L"FloorCave\\EntranceDoor.png");
		Resources::Load<Texture>(L"ExitDoor_Texture", L"FloorCave\\ExitDoor.png");
#pragma region CaveDirtTexture
		Resources::Load<Texture>(L"DirtTexture1", L"FloorCave\\Tile1.png");
		Resources::Load<Texture>(L"DirtTexture2", L"FloorCave\\Tile2.png");
		Resources::Load<Texture>(L"DirtTexture3", L"FloorCave\\Tile3.png");
		Resources::Load<Texture>(L"DirtTexture4", L"FloorCave\\Tile4.png");
		Resources::Load<Texture>(L"DirtTexture5", L"FloorCave\\Tile5.png");
		Resources::Load<Texture>(L"DirtTexture6", L"FloorCave\\Tile6.png");
		Resources::Load<Texture>(L"DirtTexture7", L"FloorCave\\Tile7.png");
		Resources::Load<Texture>(L"DirtTexture8", L"FloorCave\\Tile8.png");
		Resources::Load<Texture>(L"DirtTexture9", L"FloorCave\\Tile9.png");
		Resources::Load<Texture>(L"DirtTexture10", L"FloorCave\\Tile10.png");
		Resources::Load<Texture>(L"DirtTexture11", L"FloorCave\\Tile11.png");
		Resources::Load<Texture>(L"DirtTexture12", L"FloorCave\\Tile12.png");
		Resources::Load<Texture>(L"DirtTexture13", L"FloorCave\\Tile13.png");
		Resources::Load<Texture>(L"DirtTexture14", L"FloorCave\\Tile14.png");
		Resources::Load<Texture>(L"DirtTexture15", L"FloorCave\\Tile15.png");
		Resources::Load<Texture>(L"DirtTexture16", L"FloorCave\\Tile16.png");
		Resources::Load<Texture>(L"DirtTexture17", L"FloorCave\\Tile17.png");
		Resources::Load<Texture>(L"DirtTexture18", L"FloorCave\\Tile18.png");
		Resources::Load<Texture>(L"DirtTexture19", L"FloorCave\\Tile19.png");
		Resources::Load<Texture>(L"DirtTexture20", L"FloorCave\\Tile20.png");
		Resources::Load<Texture>(L"DirtTexture21", L"FloorCave\\Tile21.png");
		Resources::Load<Texture>(L"DirtTexture22", L"FloorCave\\Tile22.png");
		Resources::Load<Texture>(L"DirtTexture23", L"FloorCave\\Tile23.png");
		Resources::Load<Texture>(L"DirtTexture24", L"FloorCave\\Tile24.png");
		Resources::Load<Texture>(L"DirtTexture25", L"FloorCave\\Tile25.png");
		Resources::Load<Texture>(L"DirtTexture26", L"FloorCave\\Tile26.png");
		Resources::Load<Texture>(L"DirtTexture27", L"FloorCave\\Tile27.png");
		Resources::Load<Texture>(L"DirtTexture28", L"FloorCave\\Tile28.png");


		Resources::Load<Texture>(L"ObsidianTexture", L"Obsidian.png");


		Resources::Load<Texture>(L"DirtUpperTexture", L"DirtBorder\\DirtUpper.png");
		Resources::Load<Texture>(L"DirtBelowTexture", L"DirtBorder\\DirtBelow.png");
		Resources::Load<Texture>(L"DirtLeftEdgeTexture", L"DirtBorder\\DirtLeftEdge.png");
		Resources::Load<Texture>(L"DirtLeftSideTexture", L"DirtBorder\\DirtLeftSide.png");
		Resources::Load<Texture>(L"DirtRightEdgeTexture", L"DirtBorder\\DirtLeftSide.png");
		Resources::Load<Texture>(L"DirtRightSideTexture", L"DirtBorder\\DirtLeftSide.png");


#pragma endregion

#pragma region CaveWooldFloor

		Resources::Load<Texture>(L"WoodTileTexture1", L"FloorstyledWood\\Tile1.png");
		Resources::Load<Texture>(L"WoodTileTexture2", L"FloorstyledWood\\Tile2.png");
		Resources::Load<Texture>(L"WoodTileTexture3", L"FloorstyledWood\\Tile3.png");
		Resources::Load<Texture>(L"WoodTileTexture4", L"FloorstyledWood\\Tile4.png");
		Resources::Load<Texture>(L"WoodTileTexture5", L"FloorstyledWood\\Tile5.png");
		Resources::Load<Texture>(L"WoodTileTexture6", L"FloorstyledWood\\Tile6.png");
		Resources::Load<Texture>(L"WoodTileTexture7", L"FloorstyledWood\\Tile7.png");
		Resources::Load<Texture>(L"WoodTileTexture8", L"FloorstyledWood\\Tile8.png");
		Resources::Load<Texture>(L"WoodTileTexture9", L"FloorstyledWood\\Tile9.png");
		Resources::Load<Texture>(L"WoodTileTexture10", L"FloorstyledWood\\Tile10.png");
		Resources::Load<Texture>(L"WoodTileTexture11", L"FloorstyledWood\\Tile11.png");
		Resources::Load<Texture>(L"WoodTileTexture12", L"FloorstyledWood\\Tile12.png");
		Resources::Load<Texture>(L"WoodTileTexture13", L"FloorstyledWood\\Tile13.png");
		Resources::Load<Texture>(L"WoodTileTexture14", L"FloorstyledWood\\Tile14.png");
		Resources::Load<Texture>(L"WoodTileTexture15", L"FloorstyledWood\\Tile15.png");
		Resources::Load<Texture>(L"WoodTileTexture16", L"FloorstyledWood\\Tile16.png");
		Resources::Load<Texture>(L"WoodTileTexture17", L"FloorstyledWood\\Tile17.png");
		Resources::Load<Texture>(L"WoodTileTexture18", L"FloorstyledWood\\Tile18.png");
		Resources::Load<Texture>(L"WoodTileTexture19", L"FloorstyledWood\\Tile19.png");
		Resources::Load<Texture>(L"WoodTileTexture20", L"FloorstyledWood\\Tile20.png");
		Resources::Load<Texture>(L"WoodTileTexture21", L"FloorstyledWood\\Tile21.png");
		Resources::Load<Texture>(L"WoodTileTexture22", L"FloorstyledWood\\Tile22.png");
		Resources::Load<Texture>(L"WoodTileTexture23", L"FloorstyledWood\\Tile23.png");
		Resources::Load<Texture>(L"WoodTileTexture24", L"FloorstyledWood\\Tile24.png");
		Resources::Load<Texture>(L"WoodTileTexture25", L"FloorstyledWood\\Tile25.png");
		Resources::Load<Texture>(L"WoodTileTexture26", L"FloorstyledWood\\Tile26.png");
		Resources::Load<Texture>(L"WoodTileTexture27", L"FloorstyledWood\\Tile27.png");
		Resources::Load<Texture>(L"WoodTileTexture28", L"FloorstyledWood\\Tile28.png");
		Resources::Load<Texture>(L"WoodTileTexture29", L"FloorstyledWood\\Tile29.png");
		Resources::Load<Texture>(L"WoodTileTexture30", L"FloorstyledWood\\Tile30.png");
		Resources::Load<Texture>(L"WoodTileTexture31", L"FloorstyledWood\\Tile31.png");
		Resources::Load<Texture>(L"WoodTileTexture32", L"FloorstyledWood\\Tile32.png");
		Resources::Load<Texture>(L"WoodTileTexture33", L"FloorstyledWood\\Tile33.png");
		Resources::Load<Texture>(L"WoodTileTexture34", L"FloorstyledWood\\Tile34.png");
		Resources::Load<Texture>(L"WoodTileTexture35", L"FloorstyledWood\\Tile35.png");
		Resources::Load<Texture>(L"WoodTileTexture36", L"FloorstyledWood\\Tile36.png");
		Resources::Load<Texture>(L"WoodTileTexture37", L"FloorstyledWood\\Tile37.png");
		Resources::Load<Texture>(L"WoodTileTexture38", L"FloorstyledWood\\Tile38.png");
		Resources::Load<Texture>(L"WoodTileTexture39", L"FloorstyledWood\\Tile39.png");
		Resources::Load<Texture>(L"WoodTileTexture40", L"FloorstyledWood\\Tile40.png");
		Resources::Load<Texture>(L"WoodTileTexture41", L"FloorstyledWood\\Tile41.png");
		Resources::Load<Texture>(L"WoodTileTexture42", L"FloorstyledWood\\Tile42.png");
		Resources::Load<Texture>(L"WoodTileTexture43", L"FloorstyledWood\\Tile43.png");
		Resources::Load<Texture>(L"WoodTileTexture44", L"FloorstyledWood\\Tile44.png");
		Resources::Load<Texture>(L"WoodTileTexture45", L"FloorstyledWood\\Tile45.png");
		Resources::Load<Texture>(L"WoodTileTexture46", L"FloorstyledWood\\Tile46.png");
		Resources::Load<Texture>(L"WoodTileTexture47", L"FloorstyledWood\\Tile47.png");
		
		
		Resources::Load<Texture>(L"WoolBackTileTexture1", L"FloorstyledWood\\WoolBackTile1.png");
		Resources::Load<Texture>(L"WoolBackTileTexture2", L"FloorstyledWood\\WoolBackTile2.png");
		Resources::Load<Texture>(L"WoolBackTileTexture3", L"FloorstyledWood\\WoolBackTile3.png");
		Resources::Load<Texture>(L"WoolBackTileTexture4", L"FloorstyledWood\\WoolBackTile4.png");
		Resources::Load<Texture>(L"WoolBackTileTexture5", L"FloorstyledWood\\WoolBackTile5.png");
		Resources::Load<Texture>(L"WoolBackTileTexture6", L"FloorstyledWood\\WoolBackTile6.png");
		








#pragma endregion


#pragma region  "GameHud"
		Resources::Load<Texture>(L"LifeIcon", L"GameHud\\LifeIcon.png");
		Resources::Load<Texture>(L"BombIcon", L"GameHud\\BombIcon.png");
		Resources::Load<Texture>(L"RopeIcon", L"GameHud\\RopeIcon.png");
		Resources::Load<Texture>(L"NoneIcon", L"GameHud\\NoneIcon.png");
		Resources::Load<Texture>(L"ClimbingGlovesIcon", L"GameHud\\ClimbingGlovesIcon.png");
		Resources::Load<Texture>(L"SkeletonKeyIcon", L"GameHud\\SkeletonKeyIcon.png");
		Resources::Load<Texture>(L"MoneyHud", L"GameHud\\MoneyHud.png");
		Resources::Load<Texture>(L"LocateIcon", L"GameHud\\LocateIcon.png");
		Resources::Load<Texture>(L"TimerIcon", L"GameHud\\TimerIcon.png");

		Resources::Load<Texture>(L"SampleNum_0", L"GameHud\\SampleNum_0.png");
		Resources::Load<Texture>(L"SampleNum_1", L"GameHud\\SampleNum_1.png");
		Resources::Load<Texture>(L"SampleNum_2", L"GameHud\\SampleNum_2.png");
		Resources::Load<Texture>(L"SampleNum_3", L"GameHud\\SampleNum_3.png");
		Resources::Load<Texture>(L"SampleNum_4", L"GameHud\\SampleNum_4.png");
		Resources::Load<Texture>(L"SampleNum_5", L"GameHud\\SampleNum_5.png");
		Resources::Load<Texture>(L"SampleNum_6", L"GameHud\\SampleNum_6.png");
		Resources::Load<Texture>(L"SampleNum_7", L"GameHud\\SampleNum_7.png");
		Resources::Load<Texture>(L"SampleNum_8", L"GameHud\\SampleNum_8.png");
		Resources::Load<Texture>(L"SampleNum_9", L"GameHud\\SampleNum_9.png");

		Resources::Load<Texture>(L"DeadIcon", L"GameHud\\DeadIcon.png");
		Resources::Load<Texture>(L"ButtonUI", L"GameHud\\ButtonUI.png");
		Resources::Load<Texture>(L"ButtonAUI", L"GameHud\\ButtonAUI.png");
		
#pragma endregion

#pragma region "Monster"
		Resources::Load<Texture>(L"QuillbackTexture", L"Monster\\Quillback.png");
		Resources::Load<Texture>(L"SpiderTexture", L"Monster\\Spider.png");

#pragma endregion

#pragma region "Item"

		Resources::Load<Texture>(L"GoldBarTexture", L"Item\\GoldBar.png");
		Resources::Load<Texture>(L"PileOfGoldBarTexture", L"Item\\PileOfGoldBar.png");
		Resources::Load<Texture>(L"SmallGoldNuggetTexture", L"Item\\SmallGoldNugget.png");
		Resources::Load<Texture>(L"LargeGoldNuggetTexture", L"Item\\LargeGoldNugget.png");
		Resources::Load<Texture>(L"SmallEmeraldTexture", L"Item\\SmallEmerald.png");
		Resources::Load<Texture>(L"LargeEmeraldTexture", L"Item\\LargeEmerald.png");
		Resources::Load<Texture>(L"SmallSapphireTexture", L"Item\\SmallSapphire.png");
		Resources::Load<Texture>(L"LargeSapphireTexture", L"Item\\LargeSapphire.png");
		Resources::Load<Texture>(L"SmallRubyTexture", L"Item\\SmallRuby.png");
		Resources::Load<Texture>(L"LargeRubyTexture", L"Item\\LargeRuby.png");
		Resources::Load<Texture>(L"BombTexture", L"Item\\BombDefault.png");

#pragma endregion

#pragma region "Particle"
		Resources::Load<Texture>(L"BounceRingTexture", L"Particles\\BounceRing.png");
		Resources::Load<Texture>(L"BounceStarTexture", L"Particles\\BounceStar.png");
		Resources::Load<Texture>(L"BloodTexture", L"Particles\\Blood.png");
		Resources::Load<Texture>(L"BloodTexture", L"Particles\\Flint.png");

#pragma endregion

#pragma region "ResultUI"
		Resources::Load<Texture>(L"DarkBoardUITexture", L"UI\\LevelEnd\\DarkBoardUI.png");
		Resources::Load<Texture>(L"LevelBoardUITexture", L"UI\\LevelEnd\\LevelBoardUI.png");
		Resources::Load<Texture>(L"PapyrusUITexture", L"UI\\LevelEnd\\PapyrusUI.png");
		Resources::Load<Texture>(L"PlankBardUITexture", L"UI\\LevelEnd\\PlankBardUI.png");
		Resources::Load<Texture>(L"RollUITexture", L"UI\\LevelEnd\\RollUI.png");
		Resources::Load<Texture>(L"WoodBoardUITexture", L"UI\\LevelEnd\\WoodBoardUI.png");
#pragma endregion

		

	}

	void LoadMaterial()
	{

		// Default
		std::shared_ptr <Texture> texture = Resources::Find<Texture>(L"SmileTexture");
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(eTextureSlot::T0, texture);
		Resources::Insert<Material>(L"RectMaterial", material);

		// Sprite
		std::shared_ptr <Texture> spriteTexture = Resources::Find<Texture>(L"DefaultSprite");
		std::shared_ptr<Shader> spriteShader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		spriteMaterial->SetShader(spriteShader);
		spriteMaterial->SetTexture(eTextureSlot::T0,spriteTexture);
		Resources::Insert<Material>(L"SpriteMaterial", spriteMaterial);

		//Player_Default
		std::shared_ptr <Texture> player_Texture = Resources::Find<Texture>(L"PlayerTexture");
		std::shared_ptr<Shader> player_Shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> Player_Material = std::make_shared<Material>();
		Player_Material->SetRenderingMode(eRenderingMode::Transparent);
		Player_Material->SetShader(player_Shader);
		Player_Material->SetTexture(eTextureSlot::T0, player_Texture);
		Resources::Insert<Material>(L"PlayerMaterial", Player_Material);

		// UI
		std::shared_ptr <Texture> Menu_uiTexture = Resources::Find<Texture>(L"MenuTitleTexture");
		std::shared_ptr<Shader> Menu_uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> Menu_uiMaterial = std::make_shared<Material>();
		Menu_uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		Menu_uiMaterial->SetShader(Menu_uiShader);
		Menu_uiMaterial->SetTexture(eTextureSlot::T0, Menu_uiTexture);
		Resources::Insert<Material>(L"MenuTitleMaterial", Menu_uiMaterial);

		std::shared_ptr <Texture> MenuTitlegal_uiTexture = Resources::Find<Texture>(L"MenuTitlegalTexture");
		std::shared_ptr<Shader> MenuTitlegal_uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> MenuTitlegal_uiMaterial = std::make_shared<Material>();
		MenuTitlegal_uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		MenuTitlegal_uiMaterial->SetShader(MenuTitlegal_uiShader);
		MenuTitlegal_uiMaterial->SetTexture(eTextureSlot::T0, MenuTitlegal_uiTexture);
		Resources::Insert<Material>(L"MenuTitlegalMaterial", MenuTitlegal_uiMaterial);

		std::shared_ptr <Texture> uiTexture = Resources::Find<Texture>(L"HPBarTexture");
		std::shared_ptr<Shader> uiShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
		uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		uiMaterial->SetShader(uiShader);
		uiMaterial->SetTexture(eTextureSlot::T0, uiTexture);
		Resources::Insert<Material>(L"UIMaterial", uiMaterial);

		std::shared_ptr<Shader> particleShader = Resources::Find<Shader>(L"ParticleShader");
		std::shared_ptr<Material> particleMaterial = std::make_shared<Material>();
		particleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		particleMaterial->SetShader(particleShader);
		Resources::Insert<Material>(L"ParticleMaterial", particleMaterial);

#pragma region TitleStone


		std::shared_ptr <Texture> stonediskTexture = Resources::Find<Texture>(L"StoneDiskTexture");
		std::shared_ptr<Shader> stonediskShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> stonediskMaterial = std::make_shared<Material>();
		stonediskMaterial->SetRenderingMode(eRenderingMode::Transparent);
		stonediskMaterial->SetShader(stonediskShader);
		stonediskMaterial->SetTexture(eTextureSlot::T0, stonediskTexture);
		Resources::Insert<Material>(L"StoneDiskMaterial", stonediskMaterial);

		std::shared_ptr <Texture> stoneheadTexture = Resources::Find<Texture>(L"StoneHeadTexture");
		std::shared_ptr<Shader> stoneheadShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> stoneheadMaterial = std::make_shared<Material>();
		stoneheadMaterial->SetRenderingMode(eRenderingMode::Transparent);
		stoneheadMaterial->SetShader(stoneheadShader);
		stoneheadMaterial->SetTexture(eTextureSlot::T0, stoneheadTexture);
		Resources::Insert<Material>(L"StoneHeadMaterial", stoneheadMaterial);

		std::shared_ptr <Texture> snakeheadTexture = Resources::Find<Texture>(L"SnakeHeadTexture");
		std::shared_ptr<Shader> snakeheadShader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> snakeheadMaterial = std::make_shared<Material>();
		snakeheadMaterial->SetRenderingMode(eRenderingMode::Transparent);
		snakeheadMaterial->SetShader(snakeheadShader);
		snakeheadMaterial->SetTexture(eTextureSlot::T0, snakeheadTexture);
		Resources::Insert<Material>(L"SnakeHeadMaterial", snakeheadMaterial);


		//split_disk
		std::shared_ptr <Texture> split_disk_L_Texture = Resources::Find<Texture>(L"SplitDisk_L_Texture");
		std::shared_ptr<Shader> split_disk_L_Shader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> split_disk_L_Material = std::make_shared<Material>();
		split_disk_L_Material->SetRenderingMode(eRenderingMode::Transparent);
		split_disk_L_Material->SetShader(split_disk_L_Shader);
		split_disk_L_Material->SetTexture(eTextureSlot::T0, split_disk_L_Texture);
		Resources::Insert<Material>(L"SplitDisk_L_Material", split_disk_L_Material);

		std::shared_ptr <Texture> split_disk_R_Texture = Resources::Find<Texture>(L"SplitDisk_R_Texture");
		std::shared_ptr<Shader> split_disk_R_Shader = Resources::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> split_disk_R_Material = std::make_shared<Material>();
		split_disk_R_Material->SetRenderingMode(eRenderingMode::Transparent);
		split_disk_R_Material->SetShader(split_disk_R_Shader);
		split_disk_R_Material->SetTexture(eTextureSlot::T0, split_disk_R_Texture);
		Resources::Insert<Material>(L"SplitDisk_R_Material", split_disk_R_Material);

#pragma endregion

#pragma region MenuBg
		{
			std::shared_ptr <Texture>main_fore_2L_Texture = Resources::Find<Texture>(L"main_fore_2L_Texture");
			std::shared_ptr<Shader> main_fore_2L_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_fore_2L_Material = std::make_shared<Material>();
			main_fore_2L_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_fore_2L_Material->SetShader(main_fore_2L_Shader);
			main_fore_2L_Material->SetTexture(eTextureSlot::T0, main_fore_2L_Texture);
			Resources::Insert<Material>(L"main_fore_2L_Material", main_fore_2L_Material);
		}

		{
			std::shared_ptr <Texture>main_fore_2R_Texture = Resources::Find<Texture>(L"main_fore_2R_Texture");
			std::shared_ptr<Shader> main_fore_2R_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_fore_2R_Material = std::make_shared<Material>();
			main_fore_2R_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_fore_2R_Material->SetShader(main_fore_2R_Shader);
			main_fore_2R_Material->SetTexture(eTextureSlot::T0, main_fore_2R_Texture);
			Resources::Insert<Material>(L"main_fore_2R_Material", main_fore_2R_Material);
		}

		{
			std::shared_ptr <Texture>main_foreL_Texture = Resources::Find<Texture>(L"main_foreL_Texture");
			std::shared_ptr<Shader> main_foreL_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_foreL_Material = std::make_shared<Material>();
			main_foreL_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_foreL_Material->SetShader(main_foreL_Shader);
			main_foreL_Material->SetTexture(eTextureSlot::T0, main_foreL_Texture);
			Resources::Insert<Material>(L"main_foreL_Material", main_foreL_Material);
		}

		{
			std::shared_ptr <Texture>main_foreR_Texture = Resources::Find<Texture>(L"main_foreR_Texture");
			std::shared_ptr<Shader> main_foreR_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_foreR_Material = std::make_shared<Material>();
			main_foreR_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_foreR_Material->SetShader(main_foreR_Shader);
			main_foreR_Material->SetTexture(eTextureSlot::T0, main_foreR_Texture);
			Resources::Insert<Material>(L"main_foreR_Material", main_foreR_Material);
		}
		{
			std::shared_ptr <Texture>main_doorframe_Texture = Resources::Find<Texture>(L"main_doorframe_Texture");
			std::shared_ptr<Shader> main_doorframe_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_doorframe_Material = std::make_shared<Material>();
			main_doorframe_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_doorframe_Material->SetShader(main_doorframe_Shader);
			main_doorframe_Material->SetTexture(eTextureSlot::T0, main_doorframe_Texture);
			Resources::Insert<Material>(L"main_doorframe_Material", main_doorframe_Material);
		}
		{
			std::shared_ptr <Texture>main_doorback_Texture = Resources::Find<Texture>(L"main_doorback_Texture");
			std::shared_ptr<Shader> main_doorback_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_doorback_Material = std::make_shared<Material>();
			main_doorback_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_doorback_Material->SetShader(main_doorback_Shader);
			main_doorback_Material->SetTexture(eTextureSlot::T0, main_doorback_Texture);
			Resources::Insert<Material>(L"main_doorback_Material", main_doorback_Material);
		}
		{
			std::shared_ptr <Texture>main_dirt_Texture = Resources::Find<Texture>(L"main_dirt_Texture");
			std::shared_ptr<Shader> main_dirt_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> main_dirt_Material = std::make_shared<Material>();
			main_dirt_Material->SetRenderingMode(eRenderingMode::Transparent);
			main_dirt_Material->SetShader(main_dirt_Shader);
			main_dirt_Material->SetTexture(eTextureSlot::T0, main_dirt_Texture);
			Resources::Insert<Material>(L"main_dirt_Material", main_dirt_Material);
		}

		{
			std::shared_ptr <Texture>selectBarL_Texture = Resources::Find<Texture>(L"SelectBarL_Texture");
			std::shared_ptr<Shader> selectBarL_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> selectBarL_Material = std::make_shared<Material>();
			selectBarL_Material->SetRenderingMode(eRenderingMode::Transparent);
			selectBarL_Material->SetShader(selectBarL_Shader);
			selectBarL_Material->SetTexture(eTextureSlot::T0, selectBarL_Texture);
			Resources::Insert<Material>(L"selectBarL_Material", selectBarL_Material);
		}

		{
			std::shared_ptr <Texture>selectBarR_Texture = Resources::Find<Texture>(L"SelectBarR_Texture");
			std::shared_ptr<Shader> selectBarR_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> selectBarR_Material = std::make_shared<Material>();
			selectBarR_Material->SetRenderingMode(eRenderingMode::Transparent);
			selectBarR_Material->SetShader(selectBarR_Shader);
			selectBarR_Material->SetTexture(eTextureSlot::T0, selectBarR_Texture);
			Resources::Insert<Material>(L"SelectBarR_Material", selectBarR_Material);
		}

		{
			std::shared_ptr <Texture>optionBar_Texture = Resources::Find<Texture>(L"OptionBar_Texture");
			std::shared_ptr<Shader> optionBar_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> optionBar_Material = std::make_shared<Material>();
			optionBar_Material->SetRenderingMode(eRenderingMode::Transparent);
			optionBar_Material->SetShader(optionBar_Shader);
			optionBar_Material->SetTexture(eTextureSlot::T0, optionBar_Texture);
			Resources::Insert<Material>(L"OptionBar_Material", optionBar_Material);
		}

		{
			std::shared_ptr <Texture>playBar_Texture = Resources::Find<Texture>(L"PlayBar_Texture");
			std::shared_ptr<Shader> playBar_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> playBar_Material = std::make_shared<Material>();
			playBar_Material->SetRenderingMode(eRenderingMode::Transparent);
			playBar_Material->SetShader(playBar_Shader);
			playBar_Material->SetTexture(eTextureSlot::T0, playBar_Texture);
			Resources::Insert<Material>(L"PlayBar_Material", playBar_Material);
		}

		{
			std::shared_ptr <Texture>playerProfileBar_Texture = Resources::Find<Texture>(L"PlayerProfileBar_Texture");
			std::shared_ptr<Shader> playerProfileBar_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> playerProfileBar_Material = std::make_shared<Material>();
			playerProfileBar_Material->SetRenderingMode(eRenderingMode::Transparent);
			playerProfileBar_Material->SetShader(playerProfileBar_Shader);
			playerProfileBar_Material->SetTexture(eTextureSlot::T0, playerProfileBar_Texture);
			Resources::Insert<Material>(L"PlayerProfileBar_Material", playerProfileBar_Material);
		}

		{
			std::shared_ptr <Texture>rankBar_Texture = Resources::Find<Texture>(L"RankBar_Texture");
			std::shared_ptr<Shader> rankBar_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> rankBar_Material = std::make_shared<Material>();
			rankBar_Material->SetRenderingMode(eRenderingMode::Transparent);
			rankBar_Material->SetShader(rankBar_Shader);
			rankBar_Material->SetTexture(eTextureSlot::T0, rankBar_Texture);
			Resources::Insert<Material>(L"RankBar_Material", rankBar_Material);
		}

		{
			std::shared_ptr <Texture>charDoor_Texture = Resources::Find<Texture>(L"CharDoor_Texture");
			std::shared_ptr<Shader> charDoor_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> charDoor_Material = std::make_shared<Material>();
			charDoor_Material->SetRenderingMode(eRenderingMode::Transparent);
			charDoor_Material->SetShader(charDoor_Shader);
			charDoor_Material->SetTexture(eTextureSlot::T0, charDoor_Texture);
			Resources::Insert<Material>(L"CharDoor_Material", charDoor_Material);
		}

		{
			std::shared_ptr <Texture>charDoorBlocked_Texture = Resources::Find<Texture>(L"CharDoorBlocked_Texture");
			std::shared_ptr<Shader> charDoorBlocked_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> charDoorBlocked_Material = std::make_shared<Material>();
			charDoorBlocked_Material->SetRenderingMode(eRenderingMode::Transparent);
			charDoorBlocked_Material->SetShader(charDoorBlocked_Shader);
			charDoorBlocked_Material->SetTexture(eTextureSlot::T0, charDoorBlocked_Texture);
			Resources::Insert<Material>(L"CharDoorBlocked_Material", charDoorBlocked_Material);
		}

		{
			std::shared_ptr <Texture>charDoorFrame_Texture = Resources::Find<Texture>(L"CharDoorFrame_Texture");
			std::shared_ptr<Shader> charDoorFrame_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> charDoorFrame_Material = std::make_shared<Material>();
			charDoorFrame_Material->SetRenderingMode(eRenderingMode::Transparent);
			charDoorFrame_Material->SetShader(charDoorFrame_Shader);
			charDoorFrame_Material->SetTexture(eTextureSlot::T0, charDoorFrame_Texture);
			Resources::Insert<Material>(L"CharDoorFrame_Material", charDoorFrame_Material);
		}
		{
			std::shared_ptr <Texture>charDoorSpace_Texture = Resources::Find<Texture>(L"CharDoorSpace_Texture");
			std::shared_ptr<Shader> charDoorSpace_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> charDoorSpace_Material = std::make_shared<Material>();
			charDoorSpace_Material->SetRenderingMode(eRenderingMode::Transparent);
			charDoorSpace_Material->SetShader(charDoorSpace_Shader);
			charDoorSpace_Material->SetTexture(eTextureSlot::T0, charDoorSpace_Texture);
			Resources::Insert<Material>(L"CharDoorSpace_Material", charDoorSpace_Material);
		}
		{
			std::shared_ptr <Texture>menucharsel_Texture = Resources::Find<Texture>(L"MenuCharsel_Texture");
			std::shared_ptr<Shader> menucharsel_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material> menucharsel_Material = std::make_shared<Material>();
			menucharsel_Material->SetRenderingMode(eRenderingMode::Transparent);
			menucharsel_Material->SetShader(menucharsel_Shader);
			menucharsel_Material->SetTexture(eTextureSlot::T0, menucharsel_Texture);
			Resources::Insert<Material>(L"MenuCharsel_Material", menucharsel_Material);
		}

		{
			std::shared_ptr <Texture>ropeMiddle_Texture = Resources::Find<Texture>(L"RopeMidlle_Texture");
			std::shared_ptr<Shader> ropeMiddle_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>ropeMiddle_Material = std::make_shared<Material>();
			ropeMiddle_Material->SetRenderingMode(eRenderingMode::Transparent);
			ropeMiddle_Material->SetShader(ropeMiddle_Shader);
			ropeMiddle_Material->SetTexture(eTextureSlot::T0, ropeMiddle_Texture);
			Resources::Insert<Material>(L"RopeMiddle_Material", ropeMiddle_Material);
		}

		{
			std::shared_ptr <Texture>scroll_Texture = Resources::Find<Texture>(L"Scroll_Texture");
			std::shared_ptr<Shader> scroll_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>scroll_Material = std::make_shared<Material>();
			scroll_Material->SetRenderingMode(eRenderingMode::Transparent);
			scroll_Material->SetShader(scroll_Shader);
			scroll_Material->SetTexture(eTextureSlot::T0, scroll_Texture);
			Resources::Insert<Material>(L"Scroll_Material", scroll_Material);
		}

		{
			std::shared_ptr <Texture>scrollMiddle_Texture = Resources::Find<Texture>(L"ScrollMiddle_Texture");
			std::shared_ptr<Shader> scrollMiddle_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>scrollMiddle_Material = std::make_shared<Material>();
			scrollMiddle_Material->SetRenderingMode(eRenderingMode::Transparent);
			scrollMiddle_Material->SetShader(scrollMiddle_Shader);
			scrollMiddle_Material->SetTexture(eTextureSlot::T0, scrollMiddle_Texture);
			Resources::Insert<Material>(L"ScrollMiddle_Material", scrollMiddle_Material);
		}
		{
			std::shared_ptr <Texture>char_Select_Upboard_Texture = Resources::Find<Texture>(L"Char_Select_Upboard_Texture");
			std::shared_ptr<Shader> char_Select_Upboard_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>char_Select_Upboard_Material = std::make_shared<Material>();
			char_Select_Upboard_Material->SetRenderingMode(eRenderingMode::Transparent);
			char_Select_Upboard_Material->SetShader(char_Select_Upboard_Shader);
			char_Select_Upboard_Material->SetTexture(eTextureSlot::T0, char_Select_Upboard_Texture);
			Resources::Insert<Material>(L"Char_Select_Upboard_Material", char_Select_Upboard_Material);
		}
		{
			std::shared_ptr <Texture>char_Select_Downboard_Texture = Resources::Find<Texture>(L"Char_Select_Downboard_Texture");
			std::shared_ptr<Shader> char_Select_Downboard_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>char_Select_Downboard_Material = std::make_shared<Material>();
			char_Select_Downboard_Material->SetRenderingMode(eRenderingMode::Transparent);
			char_Select_Downboard_Material->SetShader(char_Select_Downboard_Shader);
			char_Select_Downboard_Material->SetTexture(eTextureSlot::T0, char_Select_Downboard_Texture);
			Resources::Insert<Material>(L"Char_Select_Downboard_Material", char_Select_Downboard_Material);
		}

		{
			std::shared_ptr <Texture>z_button_Texture = Resources::Find<Texture>(L"Z_Button_Texture");
			std::shared_ptr<Shader> z_button_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>z_button_Material = std::make_shared<Material>();
			z_button_Material->SetRenderingMode(eRenderingMode::Transparent);
			z_button_Material->SetShader(z_button_Shader);
			z_button_Material->SetTexture(eTextureSlot::T0, z_button_Texture);
			Resources::Insert<Material>(L"Z_Button_Material", z_button_Material);
		}

		{
			std::shared_ptr <Texture>leftarrow_Texture = Resources::Find<Texture>(L"LeftArrow_Texture");
			std::shared_ptr<Shader> leftarrow_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>leftarrow_Material = std::make_shared<Material>();
			leftarrow_Material->SetRenderingMode(eRenderingMode::Transparent);
			leftarrow_Material->SetShader(leftarrow_Shader);
			leftarrow_Material->SetTexture(eTextureSlot::T0, leftarrow_Texture);
			Resources::Insert<Material>(L"LeftArrow_Material", leftarrow_Material);
		}

		{
			std::shared_ptr <Texture>rightarrow_Texture = Resources::Find<Texture>(L"RightArrow_Texture");
			std::shared_ptr<Shader> rightarrow_Shader = Resources::Find<Shader>(L"UIShader");
			std::shared_ptr<Material>rightarrow_Material = std::make_shared<Material>();
			rightarrow_Material->SetRenderingMode(eRenderingMode::Transparent);
			rightarrow_Material->SetShader(rightarrow_Shader);
			rightarrow_Material->SetTexture(eTextureSlot::T0, rightarrow_Texture);
			Resources::Insert<Material>(L"RightArrow_Material", rightarrow_Material);


			//Bg
			std::shared_ptr <Texture> chrseltexture = Resources::Find<Texture>(L"ChrSelTexture");
			std::shared_ptr<Shader> chrselshader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> chrselmaterial = std::make_shared<Material>();
			chrselmaterial->SetShader(chrselshader);
			chrselmaterial->SetTexture(eTextureSlot::T0, chrseltexture);
			Resources::Insert<Material>(L"ChrSelMaterial", chrselmaterial);

			std::shared_ptr <Texture> cavebgtexture = Resources::Find<Texture>(L"CaveBgTexture");
			std::shared_ptr<Shader> cavebgshader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> cavebgmaterial = std::make_shared<Material>();
			cavebgmaterial->SetShader(cavebgshader);
			cavebgmaterial->SetTexture(eTextureSlot::T0, cavebgtexture);
			Resources::Insert<Material>(L"CaveBgMaterial", cavebgmaterial);

			std::shared_ptr <Texture> spidertexture = Resources::Find<Texture>(L"SpiderTexture");
			std::shared_ptr<Shader> spidershader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> spidermaterial = std::make_shared<Material>();
			spidermaterial->SetShader(spidershader);
			spidermaterial->SetTexture(eTextureSlot::T0, spidertexture);
			Resources::Insert<Material>(L"SpiderMaterial", spidermaterial);

			std::shared_ptr <Texture> quillbacktexture = Resources::Find<Texture>(L"QuillbackTexture");
			std::shared_ptr<Shader> quillbackshader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> quillbackmaterial = std::make_shared<Material>();
			quillbackmaterial->SetShader(quillbackshader);
			quillbackmaterial->SetTexture(eTextureSlot::T0, quillbacktexture);
			Resources::Insert<Material>(L"QuillbackMaterial", quillbackmaterial);

			

			std::shared_ptr <Texture> level1_floortexture = Resources::Find<Texture>(L"level1_floorTexture");
			std::shared_ptr<Shader> level1_floorshader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> level1_floormaterial = std::make_shared<Material>();
			level1_floormaterial->SetShader(level1_floorshader);
			level1_floormaterial->SetTexture(eTextureSlot::T0, level1_floortexture);
			Resources::Insert<Material>(L"level1_floorMaterial", level1_floormaterial);

			std::shared_ptr <Texture> deco_basecamp_entrance_texture = Resources::Find<Texture>(L"deco_basecamp_entranceTexture");
			std::shared_ptr<Shader> deco_basecamp_entrance_shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> deco_basecamp_entrance_material = std::make_shared<Material>();
			deco_basecamp_entrance_material->SetShader(deco_basecamp_entrance_shader);
			deco_basecamp_entrance_material->SetTexture(eTextureSlot::T0, deco_basecamp_entrance_texture);
			Resources::Insert<Material>(L"deco_basecamp_entranceMaterial", deco_basecamp_entrance_material);

			std::shared_ptr <Texture> deco_basecamp_uroboros_texture = Resources::Find<Texture>(L"deco_basecamp_uroborosTexture");
			std::shared_ptr<Shader> deco_basecamp_uroboros_shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> deco_basecamp_uroboros_material = std::make_shared<Material>();
			deco_basecamp_uroboros_material->SetShader(deco_basecamp_uroboros_shader);
			deco_basecamp_uroboros_material->SetTexture(eTextureSlot::T0, deco_basecamp_uroboros_texture);
			Resources::Insert<Material>(L"deco_basecamp_uroborosMaterial", deco_basecamp_uroboros_material);
#pragma endregion

#pragma region DirtBlock
			for (int i = 1; i < 29; i++)
			{
				std::shared_ptr <Texture> dirtTexture = Resources::Find<Texture>(L"DirtTexture" + std::to_wstring(i));
				std::shared_ptr<Shader> dirtShader = Resources::Find<Shader>(L"RectShader");
				std::shared_ptr<Material> dirtMaterial = std::make_shared<Material>();
				dirtMaterial->SetRenderingMode(eRenderingMode::Transparent);
				dirtMaterial->SetShader(dirtShader);
				dirtMaterial->SetTexture(eTextureSlot::T0, dirtTexture);
				Resources::Insert<Material>(L"DirtMaterial" + std::to_wstring(i), dirtMaterial);
			}

#pragma endregion

#pragma region WoodFloor
			for (int i = 1; i < 46; i++)
			{
				std::shared_ptr <Texture> woodTileTexture = Resources::Find<Texture>(L"WoodTileTexture" + std::to_wstring(i));
				std::shared_ptr<Shader> woodTileShader = Resources::Find<Shader>(L"RectShader");
				std::shared_ptr<Material> woodTileMaterial = std::make_shared<Material>();
				woodTileMaterial->SetRenderingMode(eRenderingMode::Transparent);
				woodTileMaterial->SetShader(woodTileShader);
				woodTileMaterial->SetTexture(eTextureSlot::T0, woodTileTexture);
				Resources::Insert<Material>(L"WoodTileMaterial"+std::to_wstring(i), woodTileMaterial);
			}
#pragma endregion

			std::shared_ptr <Texture> dirtUpperTexture = Resources::Find<Texture>(L"DirtUpperTexture");
			std::shared_ptr<Shader> dirtUpperShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> dirtUpperMaterial = std::make_shared<Material>();
			dirtUpperMaterial->SetRenderingMode(eRenderingMode::Transparent);
			dirtUpperMaterial->SetShader(dirtUpperShader);
			dirtUpperMaterial->SetTexture(eTextureSlot::T0, dirtUpperTexture);
			Resources::Insert<Material>(L"DirtUpperMaterial", dirtUpperMaterial);

			std::shared_ptr <Texture> dirtBelowTexture = Resources::Find<Texture>(L"DirtBelowTexture");
			std::shared_ptr<Shader> dirtBelowShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> dirtBelowMaterial = std::make_shared<Material>();
			dirtBelowMaterial->SetRenderingMode(eRenderingMode::Transparent);
			dirtBelowMaterial->SetShader(dirtBelowShader);
			dirtBelowMaterial->SetTexture(eTextureSlot::T0, dirtBelowTexture);
			Resources::Insert<Material>(L"DirtBelowMaterial", dirtBelowMaterial);

			std::shared_ptr <Texture> dirtLeftEdgeTexture = Resources::Find<Texture>(L"DirtLeftEdgeTexture");
			std::shared_ptr<Shader> dirtLeftEdgeShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> dirtLeftEdgeMaterial = std::make_shared<Material>();
			dirtLeftEdgeMaterial->SetRenderingMode(eRenderingMode::Transparent);
			dirtLeftEdgeMaterial->SetShader(dirtLeftEdgeShader);
			dirtLeftEdgeMaterial->SetTexture(eTextureSlot::T0, dirtLeftEdgeTexture);
			Resources::Insert<Material>(L"DirtLeftEdgeMaterial", dirtLeftEdgeMaterial);

			std::shared_ptr <Texture> dirtLeftSideTexture = Resources::Find<Texture>(L"DirtLeftSideTexture");
			std::shared_ptr<Shader> dirtLeftSideShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> dirtLeftSideMaterial = std::make_shared<Material>();
			dirtLeftSideMaterial->SetRenderingMode(eRenderingMode::Transparent);
			dirtLeftSideMaterial->SetShader(dirtLeftSideShader);
			dirtLeftSideMaterial->SetTexture(eTextureSlot::T0, dirtLeftSideTexture);
			Resources::Insert<Material>(L"DirtLeftSideMaterial", dirtLeftSideMaterial);

			std::shared_ptr <Texture> dirtRightSideTexture = Resources::Find<Texture>(L"DirtRightSideTexture");
			std::shared_ptr<Shader> dirtRightSideShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> dirtRightSideMaterial = std::make_shared<Material>();
			dirtRightSideMaterial->SetRenderingMode(eRenderingMode::Transparent);
			dirtRightSideMaterial->SetShader(dirtRightSideShader);
			dirtRightSideMaterial->SetTexture(eTextureSlot::T0, dirtRightSideTexture);
			Resources::Insert<Material>(L"DirtRightSideMaterial", dirtRightSideMaterial);

			std::shared_ptr <Texture> dirtRightEdgeTexture = Resources::Find<Texture>(L"DirtLeftSideTexture");
			std::shared_ptr<Shader> dirtRightEdgeShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> dirtRightEdgeMaterial = std::make_shared<Material>();
			dirtRightEdgeMaterial->SetRenderingMode(eRenderingMode::Transparent);
			dirtRightEdgeMaterial->SetShader(dirtRightEdgeShader);
			dirtRightEdgeMaterial->SetTexture(eTextureSlot::T0, dirtRightEdgeTexture);
			Resources::Insert<Material>(L"DirtRightEdgeMaterial", dirtRightEdgeMaterial);
			/*std::shared_ptr <Texture> entrance_texture = Resources::Find<Texture>(L"Entrance_Texture");
			std::shared_ptr<Shader> entrance_shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> entrance_material = std::make_shared<Material>();
			entrance_material->SetShader(entrance_shader);
			entrance_material->SetTexture(entrance_texture);
			Resources::Insert<Material>(L"entrance_Material", entrance_material);
			*/

			std::shared_ptr <Texture> exit_texture = Resources::Find<Texture>(L"ExitDoor_Texture");
			std::shared_ptr<Shader> exit_shader = Resources::Find<Shader>
			(L"RectShader");
			std::shared_ptr<Material> exit_material = std::make_shared<Material>();
			exit_material->SetShader(exit_shader);
			exit_material->SetTexture(eTextureSlot::T0, exit_texture);
			Resources::Insert<Material>(L"ExitDoorMaterial", exit_material);

			CreateMaterial(L"EntranceDoor_Texture",L"RectShader", eTextureSlot::T0,L"EntranceDoorMaterial");


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

#pragma region "GameHud"
			std::shared_ptr <Texture> lifeIconTexture = Resources::Find<Texture>(L"LifeIcon");
			std::shared_ptr<Shader> lifeIconShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> lifeIconMaterial = std::make_shared<Material>();
			lifeIconMaterial->SetShader(lifeIconShader);
			lifeIconMaterial->SetTexture(eTextureSlot::T0, lifeIconTexture);
			Resources::Insert<Material>(L"LifeIconMaterial", lifeIconMaterial);


			std::shared_ptr <Texture> bombIconTexture = Resources::Find<Texture>(L"BombIcon");
			std::shared_ptr<Shader> bombIconShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> bombIconMaterial = std::make_shared<Material>();
			bombIconMaterial->SetShader(bombIconShader);
			bombIconMaterial->SetTexture(eTextureSlot::T0, bombIconTexture);
			Resources::Insert<Material>(L"BombIconMaterial", bombIconMaterial);

			std::shared_ptr <Texture> ropeIconTexture = Resources::Find<Texture>(L"RopeIcon");
			std::shared_ptr<Shader> ropeIconShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> ropeIconMaterial = std::make_shared<Material>();
			ropeIconMaterial->SetShader(ropeIconShader);
			ropeIconMaterial->SetTexture(eTextureSlot::T0, ropeIconTexture);
			Resources::Insert<Material>(L"RopeIconMaterial", ropeIconMaterial);

			std::shared_ptr <Texture> noneIconTexture = Resources::Find<Texture>(L"NoneIcon");
			std::shared_ptr<Shader> noneIconShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> noneIconMaterial = std::make_shared<Material>();
			noneIconMaterial->SetShader(noneIconShader);
			noneIconMaterial->SetTexture(eTextureSlot::T0, noneIconTexture);
			Resources::Insert<Material>(L"NoneIconMaterial", noneIconMaterial);

			std::shared_ptr <Texture> climingGlovesIconTexture = Resources::Find<Texture>(L"ClimbingGlovesIcon");
			std::shared_ptr<Shader>  climingGlovesIconShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material>  climingGlovesIconMaterial = std::make_shared<Material>();
			climingGlovesIconMaterial->SetShader(climingGlovesIconShader);
			climingGlovesIconMaterial->SetTexture(eTextureSlot::T0, climingGlovesIconTexture);
			Resources::Insert<Material>(L"ClimbingGlovesMaterial", climingGlovesIconMaterial);

			std::shared_ptr <Texture> skeletonKeyIconTexture = Resources::Find<Texture>(L"SkeletonKeyIcon");
			std::shared_ptr<Shader>  skeletonKeyIconShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> skeletonKeyIconMaterial = std::make_shared<Material>();
			skeletonKeyIconMaterial->SetShader(skeletonKeyIconShader);
			skeletonKeyIconMaterial->SetTexture(eTextureSlot::T0, skeletonKeyIconTexture);
			Resources::Insert<Material>(L"SkeletonKeyIconMaterial", skeletonKeyIconMaterial);

			std::shared_ptr <Texture> locateIconTexture = Resources::Find<Texture>(L"LocateIcon");
			std::shared_ptr<Shader>  locateIconShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> locateIconMaterial = std::make_shared<Material>();
			locateIconMaterial->SetShader(locateIconShader);
			locateIconMaterial->SetTexture(eTextureSlot::T0, locateIconTexture);
			Resources::Insert<Material>(L"LocateIconMaterial", locateIconMaterial);

			std::shared_ptr <Texture> timerIconTexture = Resources::Find<Texture>(L"TimerIcon");
			std::shared_ptr<Shader>  timerIconShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> timerIconMaterial = std::make_shared<Material>();
			timerIconMaterial->SetShader(timerIconShader);
			timerIconMaterial->SetTexture(eTextureSlot::T0, timerIconTexture);
			Resources::Insert<Material>(L"TimerIconMaterial", timerIconMaterial);
			
			std::shared_ptr <Texture> moneyHudTexture = Resources::Find<Texture>(L"MoneyHud");
			std::shared_ptr<Shader>  moneyHudShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> moneyHudMaterial = std::make_shared<Material>();
			moneyHudMaterial->SetShader(moneyHudShader);
			moneyHudMaterial->SetTexture(eTextureSlot::T0, moneyHudTexture);
			Resources::Insert<Material>(L"MoneyHudMaterial", moneyHudMaterial);


#pragma region SampleNumber

			std::shared_ptr <Texture> number_texture = Resources::Find<Texture>(L"SampleNum_0");
			std::shared_ptr<Shader>  number_Shader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material>number_Material = std::make_shared<Material>();
			number_Material->SetShader(number_Shader);
			number_Material->SetTexture(eTextureSlot::T0, number_texture);
			Resources::Insert<Material>(L"NumberMaterial", number_Material);


			std::shared_ptr <Texture> sampleNum_0_Texture = Resources::Find<Texture>(L"SampleNum_0");
			std::shared_ptr<Shader>  sampleNum_0_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_0_Material = std::make_shared<Material>();
			sampleNum_0_Material->SetShader(sampleNum_0_Shader);
			sampleNum_0_Material->SetTexture(eTextureSlot::T0, sampleNum_0_Texture);
			Resources::Insert<Material>(L"SampleNum_0_Material", sampleNum_0_Material);

			std::shared_ptr <Texture> sampleNum_1_Texture = Resources::Find<Texture>(L"SampleNum_1");
			std::shared_ptr<Shader>  sampleNum_1_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_1_Material = std::make_shared<Material>();
			sampleNum_1_Material->SetShader(sampleNum_1_Shader);
			sampleNum_1_Material->SetTexture(eTextureSlot::T0, sampleNum_1_Texture);
			Resources::Insert<Material>(L"SampleNum_1_Material", sampleNum_1_Material);

			std::shared_ptr <Texture> sampleNum_2_Texture = Resources::Find<Texture>(L"SampleNum_2");
			std::shared_ptr<Shader>  sampleNum_2_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_2_Material = std::make_shared<Material>();
			sampleNum_2_Material->SetShader(sampleNum_2_Shader);
			sampleNum_2_Material->SetTexture(eTextureSlot::T0, sampleNum_2_Texture);
			Resources::Insert<Material>(L"SampleNum_2_Material", sampleNum_2_Material);

			std::shared_ptr <Texture> sampleNum_3_Texture = Resources::Find<Texture>(L"SampleNum_3");
			std::shared_ptr<Shader>  sampleNum_3_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_3_Material = std::make_shared<Material>();
			sampleNum_3_Material->SetShader(sampleNum_3_Shader);
			sampleNum_3_Material->SetTexture(eTextureSlot::T0, sampleNum_3_Texture);
			Resources::Insert<Material>(L"SampleNum_3_Material", sampleNum_3_Material);

			std::shared_ptr <Texture> sampleNum_4_Texture = Resources::Find<Texture>(L"SampleNum_4");
			std::shared_ptr<Shader>  sampleNum_4_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_4_Material = std::make_shared<Material>();
			sampleNum_4_Material->SetShader(sampleNum_4_Shader);
			sampleNum_4_Material->SetTexture(eTextureSlot::T0, sampleNum_4_Texture);
			Resources::Insert<Material>(L"SampleNum_4_Material", sampleNum_4_Material);

			std::shared_ptr <Texture> sampleNum_5_Texture = Resources::Find<Texture>(L"SampleNum_5");
			std::shared_ptr<Shader>  sampleNum_5_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_5_Material = std::make_shared<Material>();
			sampleNum_5_Material->SetShader(sampleNum_5_Shader);
			sampleNum_5_Material->SetTexture(eTextureSlot::T0, sampleNum_5_Texture);
			Resources::Insert<Material>(L"SampleNum_5_Material", sampleNum_5_Material);

			std::shared_ptr <Texture> sampleNum_6_Texture = Resources::Find<Texture>(L"SampleNum_6");
			std::shared_ptr<Shader>   sampleNum_6_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_6_Material = std::make_shared<Material>();
			sampleNum_6_Material->SetShader(sampleNum_6_Shader);
			sampleNum_6_Material->SetTexture(eTextureSlot::T0, sampleNum_6_Texture);
			Resources::Insert<Material>(L"SampleNum_0_Material", sampleNum_6_Material);

			std::shared_ptr <Texture> sampleNum_7_Texture = Resources::Find<Texture>(L"SampleNum_7");
			std::shared_ptr<Shader>   sampleNum_7_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_7_Material = std::make_shared<Material>();
			sampleNum_7_Material->SetShader(sampleNum_7_Shader);
			sampleNum_7_Material->SetTexture(eTextureSlot::T0, sampleNum_7_Texture);
			Resources::Insert<Material>(L"SampleNum_0_Material", sampleNum_7_Material);

			std::shared_ptr <Texture> sampleNum_8_Texture = Resources::Find<Texture>(L"SampleNum_8");
			std::shared_ptr<Shader>   sampleNum_8_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_8_Material = std::make_shared<Material>();
			sampleNum_8_Material->SetShader(sampleNum_8_Shader);
			sampleNum_8_Material->SetTexture(eTextureSlot::T0, sampleNum_8_Texture);
			Resources::Insert<Material>(L"SampleNum_0_Material", sampleNum_8_Material);

			std::shared_ptr <Texture> sampleNum_9_Texture = Resources::Find<Texture>(L"SampleNum_9");
			std::shared_ptr<Shader>   sampleNum_9_Shader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> sampleNum_9_Material = std::make_shared<Material>();
			sampleNum_9_Material->SetShader(sampleNum_9_Shader);
			sampleNum_9_Material->SetTexture(eTextureSlot::T0, sampleNum_9_Texture);
			Resources::Insert<Material>(L"SampleNum_0_Material", sampleNum_9_Material);
#pragma endregion

			std::shared_ptr <Texture> deadIconTexture = Resources::Find<Texture>(L"DeadIcon");
			std::shared_ptr<Shader>   deadIconShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> deadIconMaterial = std::make_shared<Material>();
			deadIconMaterial->SetShader( deadIconShader);
			deadIconMaterial->SetTexture(eTextureSlot::T0, deadIconTexture);
			Resources::Insert<Material>(L"DeadIconMaterial", deadIconMaterial);

			std::shared_ptr <Texture> buttonHudTexture = Resources::Find<Texture>(L"ButtonUI");
			std::shared_ptr<Shader>   buttonHudShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> buttonHudMaterial = std::make_shared<Material>();
			buttonHudMaterial->SetShader(buttonHudShader);
			buttonHudMaterial->SetTexture(eTextureSlot::T0, buttonHudTexture);
			Resources::Insert<Material>(L"ButtonHudMaterial", buttonHudMaterial);

			std::shared_ptr <Texture> buttonAHudTexture = Resources::Find<Texture>(L"ButtonAUI");
			std::shared_ptr<Shader>   buttonAHudShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> buttonAHudMaterial = std::make_shared<Material>();
			buttonAHudMaterial->SetShader(buttonAHudShader);
			buttonAHudMaterial->SetTexture(eTextureSlot::T0, buttonAHudTexture);
			Resources::Insert<Material>(L"ButtonAHudMaterial", buttonAHudMaterial);


#pragma endregion


#pragma region "Item"

			std::shared_ptr <Texture> bombTexture = Resources::Find<Texture>(L"BombTexture");
			std::shared_ptr<Shader>  bombShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> bombMaterial = std::make_shared<Material>();
			bombMaterial->SetShader(bombShader);
			bombMaterial->SetTexture(eTextureSlot::T0, bombTexture);
			Resources::Insert<Material>(L"BombMaterial", bombMaterial);
			

			std::shared_ptr <Texture> goldBarTexture = Resources::Find<Texture>(L"GoldBarTexture");
			std::shared_ptr<Shader>  goldBarShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> goldBarMaterial = std::make_shared<Material>();
			goldBarMaterial->SetShader(goldBarShader);
			goldBarMaterial->SetTexture(eTextureSlot::T0, goldBarTexture);
			Resources::Insert<Material>(L"GoldBarMaterial", goldBarMaterial);


			std::shared_ptr <Texture> pileOfGoldBarTexture = Resources::Find<Texture>(L"PileOfGoldBarTexture");
			std::shared_ptr<Shader>  pileOfGoldBarShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> pileOfGoldBarMaterial = std::make_shared<Material>();
			pileOfGoldBarMaterial->SetShader(pileOfGoldBarShader);
			pileOfGoldBarMaterial->SetTexture(eTextureSlot::T0, pileOfGoldBarTexture);
			Resources::Insert<Material>(L"PileOfGoldBarMaterial", pileOfGoldBarMaterial);

			std::shared_ptr <Texture> smallGoldNuggetTexture = Resources::Find<Texture>(L"SmallGoldNuggetTexture");
			std::shared_ptr<Shader>  smallGoldNuggetShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> smallGoldNuggetMaterial = std::make_shared<Material>();
			smallGoldNuggetMaterial->SetShader(smallGoldNuggetShader);
			smallGoldNuggetMaterial->SetTexture(eTextureSlot::T0, smallGoldNuggetTexture);
			Resources::Insert<Material>(L"SmallGoldNuggetMaterial", smallGoldNuggetMaterial);

			std::shared_ptr <Texture> largeGoldNuggetTexture = Resources::Find<Texture>(L"LargeGoldNuggetTexture");
			std::shared_ptr<Shader>  largeGoldNuggetShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> largeGoldNuggetMaterial = std::make_shared<Material>();
			largeGoldNuggetMaterial->SetShader(largeGoldNuggetShader);
			largeGoldNuggetMaterial->SetTexture(eTextureSlot::T0, largeGoldNuggetTexture);
			Resources::Insert<Material>(L"LargeGoldNuggetMaterial", largeGoldNuggetMaterial);

			std::shared_ptr <Texture> SmallEmeraldTexture = Resources::Find<Texture>(L"SmallEmeraldTexture");
			std::shared_ptr<Shader>  SmallEmeraldShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> SmallEmeraldMaterial = std::make_shared<Material>();
			SmallEmeraldMaterial->SetShader(SmallEmeraldShader);
			SmallEmeraldMaterial->SetTexture(eTextureSlot::T0, SmallEmeraldTexture);
			Resources::Insert<Material>(L"SmallEmeraldMaterial", SmallEmeraldMaterial);

			std::shared_ptr <Texture> largeEmeraldTexture = Resources::Find<Texture>(L"LargeEmeraldTexture");
			std::shared_ptr<Shader>   largeEmeraldShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material>  largeEmeraldMaterial = std::make_shared<Material>();
			largeEmeraldMaterial->SetShader(largeEmeraldShader);
			largeEmeraldMaterial->SetTexture(eTextureSlot::T0, largeEmeraldTexture);
			Resources::Insert<Material>(L"LargeEmeraldMaterial", largeEmeraldMaterial);

			std::shared_ptr <Texture> smallSapphireTexture = Resources::Find<Texture>(L"SmallSapphireTexture");
			std::shared_ptr<Shader>  smallSapphireShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material>  smallSapphireMaterial = std::make_shared<Material>();
			smallSapphireMaterial->SetShader(smallSapphireShader);
			smallSapphireMaterial->SetTexture(eTextureSlot::T0, smallSapphireTexture);
			Resources::Insert<Material>(L"SmallSapphireMaterial", smallSapphireMaterial);

			std::shared_ptr <Texture> largeSapphireTexture = Resources::Find<Texture>(L"LargeSapphireTexture");
			std::shared_ptr<Shader>  largeSapphireShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material>  largeSapphireMaterial = std::make_shared<Material>();
			largeSapphireMaterial->SetShader(largeSapphireShader);
			largeSapphireMaterial->SetTexture(eTextureSlot::T0, largeSapphireTexture);
			Resources::Insert<Material>(L"LargeSapphireMaterial", largeSapphireMaterial);

			std::shared_ptr <Texture> smallRubyTexture = Resources::Find<Texture>(L"SmallRubyTexture");
			std::shared_ptr<Shader> smallRubyShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material>  smallRubyMaterial = std::make_shared<Material>();
			smallRubyMaterial->SetShader(smallRubyShader);
			smallRubyMaterial->SetTexture(eTextureSlot::T0, smallRubyTexture);
			Resources::Insert<Material>(L"SmallRubyMaterial", smallRubyMaterial);

			std::shared_ptr <Texture> largeRubyTexture = Resources::Find<Texture>(L"LargeRubyTexture");
			std::shared_ptr<Shader> largeRubyShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material>  largeRubyMaterial = std::make_shared<Material>();
			largeRubyMaterial->SetShader(largeRubyShader);
			largeRubyMaterial->SetTexture(eTextureSlot::T0, largeRubyTexture);
			Resources::Insert<Material>(L"LargeRubyMaterial", largeRubyMaterial);

#pragma endregion

#pragma region "Particle"

			std::shared_ptr <Texture> bounceRingTexture = Resources::Find<Texture>(L"BounceRingTexture");
			std::shared_ptr<Shader> bounceRingShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> bounceRingMaterial = std::make_shared<Material>();
			bounceRingMaterial->SetShader(bounceRingShader);
			bounceRingMaterial->SetTexture(eTextureSlot::T0, bounceRingTexture);
			Resources::Insert<Material>(L"BounceRingMaterial", bounceRingMaterial);


			std::shared_ptr <Texture> bounceStarTexture = Resources::Find<Texture>(L"BounceStarTexture");
			std::shared_ptr<Shader> bounceStarShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> bounceStarMaterial = std::make_shared<Material>();
			bounceStarMaterial->SetShader(bounceRingShader);
			bounceStarMaterial->SetTexture(eTextureSlot::T0, bounceStarTexture);
			Resources::Insert<Material>(L"BounceStarMaterial", bounceStarMaterial);

			std::shared_ptr <Texture> bloodTexture = Resources::Find<Texture>(L"BloodTexture");
			std::shared_ptr<Shader> bloodShader = Resources::Find<Shader>(L"RectShader");
			std::shared_ptr<Material> bloodMaterial = std::make_shared<Material>();
			bloodMaterial->SetShader(bloodShader);
			bloodMaterial->SetTexture(eTextureSlot::T0, bloodTexture);
			Resources::Insert<Material>(L"BloodMaterial", bloodMaterial);

			std::shared_ptr <Texture> flintTexture = Resources::Find<Texture>(L"FlintTexture");
			std::shared_ptr<Shader> flintShader = Resources::Find<Shader>(L"SpriteShader");
			std::shared_ptr<Material> flintMaterial = std::make_shared<Material>();
			flintMaterial->SetShader(flintShader);
			flintMaterial->SetTexture(eTextureSlot::T0, flintTexture);
			Resources::Insert<Material>(L"FlintMaterial", flintMaterial);


			CreateMaterial(L"DarkBoardUITexture", L"RectShader",eTextureSlot::T0, L"DarkBoardUIMaterial");
			CreateMaterial(L"LevelBoardUITexture", L"RectShader", eTextureSlot::T0, L"LevelBoardUIMaterial");
			CreateMaterial(L"PapyrusUITexture", L"RectShader", eTextureSlot::T0, L"PapyrusUIMaterial");
			CreateMaterial(L"PlankBardUITexture", L"RectShader", eTextureSlot::T0, L"PlankBardUIMaterial");
			CreateMaterial(L"RollUITexture", L"RectShader", eTextureSlot::T0, L"RollUIMaterial");
			CreateMaterial(L"WoodBoardUITexture", L"RectShader", eTextureSlot::T0, L"WoodBoardUIMaterial");

			CreateMaterial(L"ObsidianTexture", L"RectShader", eTextureSlot::T0, L"ObsidianMaterial");
			
			CreateMaterial(L"WoolBackTileTexture1", L"RectShader",eTextureSlot::T0,L"WoolBackTileMaterial1");
			CreateMaterial(L"WoolBackTileTexture2", L"RectShader",eTextureSlot::T0,L"WoolBackTileMaterial2");
			CreateMaterial(L"WoolBackTileTexture3", L"RectShader",eTextureSlot::T0,L"WoolBackTileMaterial3");
			CreateMaterial(L"WoolBackTileTexture4", L"RectShader",eTextureSlot::T0,L"WoolBackTileMaterial4");
			CreateMaterial(L"WoolBackTileTexture5", L"RectShader",eTextureSlot::T0,L"WoolBackTileMaterial5");
			CreateMaterial(L"WoolBackTileTexture6", L"RectShader",eTextureSlot::T0,L"WoolBackTileMaterial6");

#pragma endregion

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

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}

	void CreateMaterial(const std::wstring& texture_name, const std::wstring& shader_name, eTextureSlot slot, const std::wstring& key_mame)
	{
		std::shared_ptr <Texture> texture = Resources::Find<Texture>(texture_name);
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(shader_name);
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(slot, texture);
		Resources::Insert<Material>(key_mame, material);
	}

	void Render()
	{
		BindLights();

		//std::vector<Camera*> cameras[(UINT)eSceneType::End];
		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();
		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras[(UINT)type].clear();

		renderer::lights.clear();
	}
	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{
		lightsBuffer->SetData(lights.data(), lights.size());
		lightsBuffer->BindSRV(eShaderStage::VS, 13);
		lightsBuffer->BindSRV(eShaderStage::PS, 13);

		renderer::LightCB trCb = {};
		trCb.numberOfLight = lights.size();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		cb->SetData(&trCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> noise = Resources::Find<Texture>(L"noise_01");
		noise->BindShaderResource(eShaderStage::VS, 16);
		noise->BindShaderResource(eShaderStage::HS, 16);
		noise->BindShaderResource(eShaderStage::DS, 16);
		noise->BindShaderResource(eShaderStage::GS, 16);
		noise->BindShaderResource(eShaderStage::PS, 16);
		noise->BindShaderResource(eShaderStage::CS, 16);

		NoiseCB info = {};
		info.noiseSize.x = noise->GetWidth();
		info.noiseSize.y = noise->GetHeight();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Noise];
		cb->SetData(&info);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}

}
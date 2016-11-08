#include "ResourceManager.h"
#include "DDSTextureLoader.h"
#include "../FAST_FBX_LOADER/FASTFBXLoader.h"
#include "BindPose.h"
ResourceManager::ResourceManager()
{
	m_deviceResources = new DeviceResources();
	
}

ResourceManager::~ResourceManager()
{
	m_deviceResources->Shutdown();
	delete m_deviceResources;
	delete m_renderer;
}

void ResourceManager::Init(int screenWidth, int screenHeight, bool vsync, HWND hwnd, bool fullscreen,
	float screenDepth, float screenNear)
{
	m_deviceResources->Initialize(screenWidth, screenHeight, vsync, hwnd, fullscreen, screenDepth, screenNear);
	m_renderer = new Renderer(m_deviceResources->GetDevice(), m_deviceResources->GetDeviceContext());
	std::vector<FullVertex> vertices;
	std::vector<unsigned short> indeces;

	Model* model;
	FullVertex topright, topleft, bottomright, bottomleft;
	topright.pos = XMFLOAT3(10, 0, 10);
	topleft.pos = XMFLOAT3(-10, 0, 10);
	bottomright.pos = XMFLOAT3(10, 0, -10);
	bottomleft.pos = XMFLOAT3(-10, 0, -10);


	topright.norm = XMFLOAT3(0.0f, 1.0f, 0.0f);
	topleft.norm = XMFLOAT3(0.0f, 1.0f, 0.0f);
	bottomright.norm = XMFLOAT3(0.0f, 1.0f, 0.0f);
	bottomleft.norm = XMFLOAT3(0.0f, 1.0f, 0.0f);


	topright.bIndices = XMFLOAT4(0, 0, 0, 0);
	topleft.bIndices = XMFLOAT4(0, 0, 0, 0);
	bottomright.bIndices = XMFLOAT4(0, 0, 0, 0);
	bottomleft.bIndices = XMFLOAT4(0, 0, 0, 0);

	topright.bWeights = XMFLOAT4(0, 0, 0, 0);
	topleft.bWeights = XMFLOAT4(0, 0, 0, 0);
	bottomright.bWeights = XMFLOAT4(0, 0, 0, 0);
	bottomleft.bWeights = XMFLOAT4(0, 0, 0, 0);










	vertices.clear();
	vertices.push_back(topleft);
	vertices.push_back(topright);
	vertices.push_back(bottomleft);
	vertices.push_back(bottomright);

	//1, 2, 4

	indeces.clear();
	indeces.push_back(0);
	indeces.push_back(1);
	indeces.push_back(2);

	//2, 4, 3
	indeces.push_back(1);
	indeces.push_back(3);
	indeces.push_back(2);




	model = new Model(m_deviceResources->GetDevice(), vertices, indeces);
	m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);


	{
		bool noerror = true;
		noerror = FASTFBXLoader::Init();
		noerror = FASTFBXLoader::Load("../FAST_RTA_SOLUTION/Teddy_Idle.fbx");
		noerror = FASTFBXLoader::Export("../FAST_RTA_SOLUTION/model.bin");
		Model* animmodel;
		std::vector<FullVertex> vertices;
		//std::vector<unsigned short>* pindeces;
		std::vector<unsigned short> indeces;
		
		animmodel = new Model(m_deviceResources->GetDevice(), vertices, indeces);
		animmodel->hasAnimation = true;//true;
		
		animmodel->LoadAnimation("../FAST_RTA_SOLUTION/model.bin", m_deviceResources->GetDevice());
		animmodel->Update(XMMatrixScaling(.01, .01, .01));
		m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, animmodel);
		FASTFBXLoader::Clean();

		//make spheres for bones
		//unsigned int numBones = animmodel->GetAnimationSet().GetDefaultAnimation()->GetNumBones();
		//vertices.clear();
		//indeces.clear();
		//loadOBJ("../FAST_RTA_SOLUTION/Sphere.obj", 0, m_deviceResources->GetDevice(), vertices, indeces);
		//for (unsigned int i = 0; i < numBones; i++)
		//{
		//	model = new Model(m_deviceResources->GetDevice(), vertices, indeces);
		//	animmodel->GetAnimationSet().GetDefaultAnimation()->GetFrame(0)->m_bones[i].m_world;
		//	model->Update(XMMatrixMultiply(XMLoadFloat4x4(&animmodel->GetAnimationSet().GetDefaultAnimation()->GetFrame(0)->m_bones[i].m_world), animmodel->GetWorldMat()));
		//	
		//
		//
		//	m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
		//
		//
		//
		//}







	}




	//
	//char* myFilename = "Cube.obj";
	//wchar_t*temp = L"cubeskybox.dds";
	//
	//loadOBJ(myFilename, temp, m_deviceResources->GetDevice(), XMFLOAT3(), vertices, indeces);
	//
	//Model* model = new Model(m_deviceResources->GetDevice(), vertices, indeces);
	//HRESULT hr;
	//if (temp != NULL)
	//{
	//	hr = CreateDDSTextureFromFile(m_deviceResources->GetDevice(),
	//		temp, NULL,
	//		&model->shaderview);
	//}
	//
	//
	//
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//

	
	//std::vector<unsigned short> backward;
	//backward.resize(indeces.size());
	//for (int i = 0; i < indeces.size(); i++)
	//{
	//	backward[i] = indeces[indeces.size() - 1 - i];
	//}
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, -1, 0, 1);
	//}
	//
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, backward);
	//
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//
	//
	//
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, 1, 0, 1);
	//}
	//
	//
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, indeces);
	//XMMATRIX trans = XMMatrixTranslation(0, 3, 0);
	//model->Update(trans);
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, -1, 0, 1);
	//}
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, backward);
	//trans = XMMatrixTranslation(0, 3, 0);
	//model->Update(trans);
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, 1, 0, 1);
	//}
	//
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, indeces);
	//trans = XMMatrixTranslation(0, -3, 0);
	//model->Update(trans);
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	//
	//for (size_t i = 0; i < vertices.size(); i++)
	//{
	//	vertices[i].norm = XMFLOAT4(0, -1, 0, 1);
	//}
	//
	//model = new Model(m_deviceResources->GetDevice(), vertices, backward);
	//trans = XMMatrixTranslation(0, -3, 0);
	//model->Update(trans);
	//m_renderer->AddModel(m_deviceResources->GetDevice(), hwnd, model);
	////cube code
	//Vertex T1, T2, T3, T4, B1, B2, B3, B4;
	//float left, right, up, down, top, bottom;
	//left = down = bottom = -2;
	//up = right = top = 2;
	//T1.pos = XMFLOAT4(left, bottom, up, 1.0f);
	//T2.pos = XMFLOAT4(right, bottom, up, 1.0f);
	//T3.pos = XMFLOAT4(left, bottom, down, 1.0f);
	//T4.pos = XMFLOAT4(right, bottom, down, 1.0f);
	//B1.pos = XMFLOAT4(left, bottom, up, 1.0f);
	//B2.pos = XMFLOAT4(right, bottom, up, 1.0f);
	//B3.pos = XMFLOAT4(left, bottom, down, 1.0f);
	//B4.pos = XMFLOAT4(right, bottom, down, 1.0f);




}

void ResourceManager::loadOBJ(char* filename, wchar_t* texturename, ID3D11Device* device,
	std::vector<FullVertex> &_vertices, std::vector<unsigned short> &_indeces)
{
	if (filename)
	{
		std::vector<FullVertex> Iverts;
		std::vector<unsigned int> Iindeces;
		std::vector<XMFLOAT3> verts, normals;
		std::vector<XMFLOAT2> uvs;
		std::vector<unsigned int> vi, uvi, ni;
		FILE* file;
		fopen_s(&file, filename, "r");
		if (file != NULL)
		{

			int i = 0;
			while (true)
			{

				char header[128];
				int res = fscanf_s(file, "%s", header, 128);
				if (res == EOF)
				{
					break;
				}
				if (strcmp(header, "v") == 0)
				{
					XMFLOAT3 vert;
					fscanf_s(file, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
					vert.x;
					vert.y;
					vert.z;
					verts.push_back((vert));
				}
				else if (strcmp(header, "vt") == 0)
				{
					XMFLOAT2 uv;
					fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
					uv.y = 1 - uv.y;
					uvs.push_back(uv);
				}
				else if (strcmp(header, "vn") == 0)
				{
					XMFLOAT3 norm;
					fscanf_s(file, "%f %f %f\n", &norm.x, &norm.y, &norm.z);
					normals.push_back(norm);
				}
				else if (strcmp(header, "f") == 0)
				{

					unsigned int indeces[9];
					int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
						&indeces[0], &indeces[1], &indeces[2], &indeces[3],
						&indeces[4], &indeces[5], &indeces[6], &indeces[7],
						&indeces[8]);

					vi.push_back(indeces[0] - 1);
					vi.push_back(indeces[6] - 1);
					vi.push_back(indeces[3] - 1);

					uvi.push_back(indeces[1] - 1);
					uvi.push_back(indeces[7] - 1);
					uvi.push_back(indeces[4] - 1);

					ni.push_back(indeces[2] - 1);
					ni.push_back(indeces[8] - 1);
					ni.push_back(indeces[5] - 1);


				}
				else
				{
					continue;
				}

			}

		}


		std::vector<FullVertex> vertices;
		std::vector<unsigned short> indeces;

		for (size_t i = 0; i < vi.size(); i++)
		{
			FullVertex temp;
			temp.pos = XMFLOAT3(verts[vi[i]].x, verts[vi[i]].y, verts[vi[i]].z);
			temp.norm = XMFLOAT3(verts[vi[i]].x, verts[vi[i]].y, verts[vi[i]].z);
			temp.bIndices = XMFLOAT4(0, 0, 0, 0);
			temp.bWeights = XMFLOAT4(0, 0, 0, 0);
			Iverts.push_back(temp);
			Iindeces.push_back((unsigned int)i);
		}
		_vertices = Iverts;
		_indeces.clear();
		for (int i = 0; i < Iindeces.size(); i++)
		{
			_indeces.push_back(Iindeces[i]);
		}




	}
}

void ResourceManager::Update(bool* keys, float dt)
{
	m_renderer->Update(keys, dt);
}

void ResourceManager::Render()
{
	m_deviceResources->GetProjectionMatrix(m_proj);
	m_deviceResources->BeginScene(.5, .5, .5, 1);
	m_renderer->Render(m_deviceResources->GetDeviceContext(), m_proj);
	m_deviceResources->EndScene();
}

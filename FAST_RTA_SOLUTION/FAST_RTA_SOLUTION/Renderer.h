#pragma once
#pragma comment(lib, "d3d11.lib")
#include "Model.h"
#include "Light.h"
#include "PolyShader.h"
#include "Camera.h"
class Renderer
{
private:
	std::vector<Model*> m_objects;
	Light* m_light;
	//temp shaders
	ID3D11VertexShader* vs;
	ID3D11PixelShader* ps;
	ID3D11Buffer* cameraPos;
	Camera* m_camera;
	Model* m_dragDrop;
	Blender *m_dragDropBlend;
	ID3D11Device *m_device;
	Renderer();
public:
	PolyShader* m_polyShader;

	Renderer(ID3D11Device* device, ID3D11DeviceContext* context);
	~Renderer();

	void Update(bool* keys, float dt, Blender* blender, HWND hwnd);
	void Render(ID3D11DeviceContext* deviceContext, XMMATRIX proj, Blender* blender);
	void AddModel(ID3D11Device* device, HWND hwnd, Model* key);
};


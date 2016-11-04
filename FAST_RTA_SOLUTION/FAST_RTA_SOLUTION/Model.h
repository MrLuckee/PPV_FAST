#pragma once
#include "Mesh.h"
#include "StructsEnumsDefines.h"

class Model
{
private:
	std::vector<Model*> m_children;
	DirectX::XMMATRIX m_local;
	DirectX::XMMATRIX m_world;
	Mesh* m_Mesh;
	Model();
public:
	ID3D11ShaderResourceView* shaderview;
	Model(ID3D11Device* device, std::vector<FullVertex> _vertices, std::vector<unsigned short> _indices);
	~Model();
	void Update(float dt);
	void Update(DirectX::XMMATRIX& _matrix);
	const DirectX::XMMATRIX& GetWorldMat();
	unsigned int AddChild(Model& _mod);
	void RemoveChild(unsigned int _index);
	size_t GetChildCount() const;
	//giving compile errors TODO
	Model& GetChild(unsigned int _index) const;
	//Model& const GetChild(unsigned int) const;
	unsigned short GetNumIndeces();
	ID3D11Buffer** GetVertBuffer();
	ID3D11Buffer** GetIndexBuffer();
	bool hasAnimation;


};


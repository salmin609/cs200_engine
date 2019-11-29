#pragma once
#include <DirectXMath.h>
#include "Vertex_Buffer.h"
#include "Index_Buffer.h"
#include "Constant_Buffer_Types.h"
#include "Vertex.h"
#include "matrix3.hpp"
#include "Constant_Buffer.h"
#include "matrix4.hpp"
using namespace DirectX;

//#include <minwindef.h>

#ifndef _WINDEF_
typedef unsigned long DWORD;
#endif

class Object
{
public:
    
    enum Shape
    {
        None = -1,
        Triangle = 0,
        Rectangle = 1,
        Line = 2,
        Circle = 3,
    	Rect = 4
    };
    Object()
    {
        
    }
    Object(Shape shape);

    matrix3<float>& Get_Transform()
    {
        return transform;
    }
    vector2<float>& Get_Scale()
    {
        return scale;
    }
	vector2<float>& Get_Translation()
    {
        return translation;
    }
    DirectX::XMFLOAT2& Get_Rotation()
    {
        return rotation;
    }
    Shape Get_Shape() const
    {
        return shape;
    }
    void Set_Shape(Shape shape)
    {
        this->shape = shape;
    }
    int Get_Vertex_Count() const
    {
        return vertex_count;
    }
    Vertex* Get_Vertex_Pointer() const
    {
        return v;
    }
    DWORD* Get_Indices_Pointer() const
    {
        return indices;
    }
    int Get_Indices_Index_Count() const
    {
        return indices_index_count;
    }
    void Update();

    bool Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context, ID3D11ShaderResourceView * texture ,ConstantBuffer<Constant_VS_vertex_shader>& constant_vertexshader);
    void Set_Texture(ID3D11ShaderResourceView* texture);
    void Draw(const matrix4<float>& view_projection_matrix);
    //bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * texture, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader);

    void Set_Name(std::string name)
    {
        this->name = name;
    }

private:
    void Update_World_Matrix();

    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* device_context = nullptr;
    ConstantBuffer<Constant_VS_vertex_shader>* constant_buffer_vertex_shader = nullptr;
    ID3D11ShaderResourceView* texture = nullptr;

    VertexBuffer<Vertex> vertex_buffer;
    IndexBuffer index_buffer;

    //DirectX::XMMATRIX world_transform;
	matrix4<float> world_transform;
    //MATRIX3 transform;
    matrix3<float> transform;
    vector2<float> scale;
    vector2<float> translation;
    DirectX::XMFLOAT2 rotation;
    Shape shape;
    DWORD* indices;
    Vertex* v;
    int indices_index_count;
    int vertex_count;
    std::string name;
	float angle;
    
};

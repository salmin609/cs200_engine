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

    virtual bool Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context, ID3D11ShaderResourceView * texture ,ConstantBuffer<Constant_VS_vertex_shader>& constant_vertexshader, float z = -0.5f);
    void Set_Texture(ID3D11ShaderResourceView* texture);
	virtual void Draw(const matrix4<float>& view_projection_matrix);
    //bool Initialize(ID3D11Device * device, ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * texture, ConstantBuffer<CB_VS_vertexshader> & cb_vs_vertexshader);

    void Set_Name(std::string name)
    {
        this->name = name;
    }
	void Set_Left_Leg(Object* left_leg)
    {
		Hierachy_left_leg = left_leg;
		Hierachy_left_leg->Get_Translation().x = this->translation.x - 1.f;
		Hierachy_left_leg->Get_Translation().y = this->translation.y - 1.3f;
    }
	void Set_Right_Leg(Object* right_leg)
	{
		Hierachy_right_leg = right_leg;
		Hierachy_right_leg->Get_Translation().x = this->translation.x + 1.f;
		Hierachy_right_leg->Get_Translation().y = this->translation.y - 1.3f;
	}
	void Set_Left_Arm(Object* left_arm)
	{
		Hierachy_left_arm = left_arm;
		Hierachy_left_arm->Get_Translation().x = this->translation.x - 1.f;
		Hierachy_left_arm->Get_Translation().y = this->translation.y - 0.3f;
	}
	void Set_Right_Arm(Object* right_arm)
	{
		Hierachy_right_arm = right_arm;
		Hierachy_right_arm->Get_Translation().x = this->translation.x + 1.f;
		Hierachy_right_arm->Get_Translation().y = this->translation.y - 0.3f;
	}
	void Set_Last(Object* last)
	{
		Hierachy_last = last;
	}
	float& Get_Angle()
    {
		return angle;
    }

protected:
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

	Object* Hierachy_left_leg = nullptr;
	Object* Hierachy_right_leg = nullptr;
	Object* Hierachy_left_arm = nullptr;
	Object* Hierachy_right_arm = nullptr;
	Object* Hierachy_last = nullptr;
    
};

#include "Object.h"
#include "Input.h"
#include "Object_Manager.h"
#include "angles.hpp"

static int indices_count = 0;

Object::Object(Shape shape) :transform(MATRIX3::build_identity<float>()), scale(1, 1), translation(0, 0), rotation(0, 0), shape(shape)
{
    if(shape == Rectangle)
    {
        v = new Vertex[4];
        v[0].pos = { -0.5f, -0.5f, 0.0f};
        v[0].tex_coord = { 0.0f, 1.0f };
        v[1].pos = { -0.5f, 0.5f, 0.0f };
        v[1].tex_coord = { 0.0f, 0.0f };
        v[2].pos = { 0.5f,  0.5f, 0.0f };
        v[2].tex_coord = { 1.0f, 0.0f };
        v[3].pos = { 0.5f,  -0.5f, 0.0f };
        v[3].tex_coord = { 1.0f, 1.0f };

        vertex_count = 4;
        indices = new DWORD[6];
        indices[0] = indices_count;
        indices[1] = indices_count + 1;
        indices[2] = indices_count + 2;
        indices[3] = indices_count;
        indices[4] = indices_count + 2;
        indices[5] = indices_count + 3;

        indices_index_count = 6;

        indices_count += vertex_count;

    }
    else if(shape == Triangle)
    {
        v = new Vertex[3];
        v[0].pos = { 2.0f, 0.5f,0.0f };
        v[0].tex_coord = { 0.5f, 0.0f };
        v[1].pos = { 1.5f,-0.5f, 0.0f };
        v[1].tex_coord = { 0.0f,1.0f };
        v[2].pos = { 2.5f, -0.5f, 0.0f };
        v[2].tex_coord = { 1.0f,1.0f };
        vertex_count = 3;

        indices = new DWORD[3];

        indices[0] = indices_count;
        indices[1] = indices_count + 1;
        indices[2] = indices_count + 2;

        indices_index_count = 3;
        
        indices_count += vertex_count;
    }
        
}

void Object::Update()
{
    if(this->shape == Rectangle)
    {
        if(input.Is_Key_Pressed(Keyboard::W))
        {
            this->translation.y += 0.01;
            Update_World_Matrix();
        }
        if (input.Is_Key_Pressed(Keyboard::A))
        {
            this->translation.x -= 0.01;
            Update_World_Matrix();
        }
        if (input.Is_Key_Pressed(Keyboard::S))
        {
            this->translation.y -= 0.01;
            Update_World_Matrix();
        }
        if (input.Is_Key_Pressed(Keyboard::D))
        {
            this->translation.x += 0.01;
            Update_World_Matrix();
        }
        if(input.Is_Key_Pressed(Keyboard::NUM_1))
        {
            this->scale.x += 0.01;
            Update_World_Matrix();
        }
        if(input.Is_Key_Pressed(Keyboard::NUM_2))
        {
            this->scale.x -= 0.01;
            Update_World_Matrix();
        }
        if (input.Is_Key_Pressed(Keyboard::NUM_3))
        {
            this->scale.y -= 0.01;
            Update_World_Matrix();
        }
        if (input.Is_Key_Pressed(Keyboard::NUM_4))
        {
            this->scale.y += 0.01;
            Update_World_Matrix();
        }
        if(input.Is_Key_Pressed(Keyboard::K))
        {
            this->rotation.x += 0.01;
            this->rotation.y += 0.01;
            Update_World_Matrix();
        }
    }
}

bool Object::Initialize(ID3D11Device* device, ID3D11DeviceContext* device_context,
    ID3D11ShaderResourceView * texture ,ConstantBuffer<Constant_VS_vertex_shader>& constant_vertexshader)
{
    this->device = device;
    this->device_context = device_context;
    this->texture = texture;
    this->constant_buffer_vertex_shader = &constant_vertexshader;
    this->scale = { 1,1 };
    if(this->name == "rectangle")
    {
        this->shape = Rectangle;
        Vertex v[] =
        {
                Vertex(-0.5f,  -0.5f, -0.5f, 0.0f, 1.0f), //FRONT Bottom Left   - [0]
                Vertex(-0.5f,   0.5f, -0.5f, 0.0f, 0.0f), //FRONT Top Left      - [1]
                Vertex(0.5f,   0.5f, -0.5f, 1.0f, 0.0f), //FRONT Top Right     - [2]
                Vertex(0.5f,  -0.5f, -0.5f, 1.0f, 1.0f)
        };

        HRESULT hr = this->vertex_buffer.Initialize(this->device, v, ARRAYSIZE(v));

        DWORD indices[] =
        {
            0,1,2,
            0,2,3,
        };
        hr = this->index_buffer.Initialize(this->device, indices, ARRAYSIZE(indices));
    }

    if (this->name == "triangle")
    {
        this->shape = Triangle;


        Vertex v[] =
        {
                Vertex(2.0,  0.5f, 0.0f, 0.5f, 0.0f), //FRONT Bottom Left   - [0]
                Vertex(1.5f,   -0.5f, 0.0f, 0.0f, 1.0f), //FRONT Top Left      - [1]
                Vertex(2.5f,   -0.5f, 0.0f, 1.0f, 1.0f), //FRONT Top Right     - [2]
        };

        HRESULT hr = this->vertex_buffer.Initialize(this->device, v, ARRAYSIZE(v));

        DWORD indices[] =
        {
            0,1,2,
        };
        hr = this->index_buffer.Initialize(this->device, indices, ARRAYSIZE(indices));
    }

    if(this->name == "circle")
    {
        this->shape = Circle;

        Vertex* v = new Vertex[31];
        v[0] = { 0,0,0 };

        float theta;

        for(int i = 1; i < 30; i++)
        {
            theta = (TWO_PI * i) / static_cast<float>(30);
            v[i] = { 1 * cosf(theta), 1 * sinf(theta), 0,1,0 };
        }


        HRESULT hr = this->vertex_buffer.Initialize(this->device, v, 31);

        DWORD* indices = new DWORD[90];

        int incre_1 = 1;
        int incre_2 = 2;

        for(int i = 0; i < 84; i += 3)
        {
            indices[i] = 0;
            indices[i + 1] = incre_1;
            indices[i + 2] = incre_2;
            incre_1++;
            incre_2++;
        }
        indices[84] = 0;
        indices[85] = 29;
        indices[86] = 1;

        hr = this->index_buffer.Initialize(this->device, indices, 87);
    }

    this->Update_World_Matrix();
    return true;
}

void Object::Set_Texture(ID3D11ShaderResourceView* texture)
{
    this->texture = texture;
}

void Object::Draw(const XMMATRIX& view_projection_matrix)
{
    Update_World_Matrix();
    this->constant_buffer_vertex_shader->data.mat = this->world_transform * view_projection_matrix;
    this->constant_buffer_vertex_shader->data.mat = XMMatrixTranspose(this->constant_buffer_vertex_shader->data.mat);
    this->constant_buffer_vertex_shader->ApplyChange();
    this->device_context->VSSetConstantBuffers(0, 1, this->constant_buffer_vertex_shader->GetAddressOf());
    this->device_context->PSSetShaderResources(0, 1, &this->texture);
    this->device_context->IASetIndexBuffer(this->index_buffer.Get(), DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
    UINT offset = 0;
    this->device_context->IASetVertexBuffers(0, 1, this->vertex_buffer.Get_Address(), this->vertex_buffer.Stride_Ptr(), &offset);
    this->device_context->DrawIndexed(this->index_buffer.Buffer_Size(), 0, 0);
}

void Object::Update_World_Matrix()
{
    this->world_transform = DirectX::XMMatrixIdentity();
    this->world_transform *= DirectX::XMMatrixTranslation(translation.x, translation.y, 0) * DirectX::XMMatrixRotationRollPitchYawFromVector({rotation.x, rotation.y}) * DirectX::XMMatrixScaling(scale.x, scale.y, 0);
    
}

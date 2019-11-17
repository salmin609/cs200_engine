#pragma once
#include <DirectXMath.h>
using namespace DirectX;

class Camera
{
public:
    Camera();

    void Set_Projection_Value(float fov_degrees, float aspect_ratio, float near_z, float far_z);

    const XMMATRIX& Get_View_Matrix() const;
    const XMMATRIX& Get_Projection_Matrix() const;

    const XMVECTOR& Get_Position_Vector() const;
    const XMFLOAT3& Get_Position_Float3() const;
    const XMVECTOR& Get_Rotation_Vector() const;
    const XMFLOAT3& Get_Rotation_Float3() const;

    void Set_Position(const XMVECTOR& pos);
    void Set_Position(float x, float y, float z);
    void Adjust_Position(const XMVECTOR& pos);
    void Adjust_Position(float x, float y, float z);
    void Set_Rotation(const XMVECTOR& rot);
    void Set_Rotation(float x, float y, float z);
    void Adjust_Rotation(const XMVECTOR& rot);
    void Adjust_Rotation(float x, float y, float z);
    void Set_Lookat_Pos(XMFLOAT3 look_at_pos);

private:
    void Update_View_Matrix();
    XMVECTOR pos_vector;
    XMVECTOR rot_vector;
    XMFLOAT3 pos;
    XMFLOAT3 rot;
    XMMATRIX view_matrix;
    XMMATRIX projection_matrix;

    const XMVECTOR default_forward_vector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
    const XMVECTOR default_up_vector = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);


};
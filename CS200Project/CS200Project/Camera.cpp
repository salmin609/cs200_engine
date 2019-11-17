#include "Camera.h"

Camera::Camera()
{
    this->pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
    this->pos_vector = XMLoadFloat3(&this->pos);
    this->rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
    this->rot_vector = XMLoadFloat3(&this->rot);
    Update_View_Matrix();
}

void Camera::Set_Projection_Value(float fov_degrees, float aspect_ratio, float near_z, float far_z)
{
    float fov_radians = (fov_degrees / 360.f) * XM_2PI;
    this->projection_matrix = XMMatrixPerspectiveFovLH(fov_radians, aspect_ratio, near_z, far_z);
}

const XMMATRIX& Camera::Get_View_Matrix() const
{
    return this->view_matrix;
}

const XMMATRIX& Camera::Get_Projection_Matrix() const
{
    return this->projection_matrix;
}

const XMVECTOR& Camera::Get_Position_Vector() const
{
    return this->pos_vector;
}

const XMFLOAT3& Camera::Get_Position_Float3() const
{
    return this->pos;
}

const XMVECTOR& Camera::Get_Rotation_Vector() const
{
    return this->rot_vector;
}

const XMFLOAT3& Camera::Get_Rotation_Float3() const
{
    return this->rot;
}

void Camera::Set_Position(const XMVECTOR& pos)
{
    XMStoreFloat3(&this->pos, pos);
    this->pos_vector = pos;
    this->Update_View_Matrix();
}

void Camera::Set_Position(float x, float y, float z)
{
    this->pos = XMFLOAT3(x, y, z);
    this->pos_vector = XMLoadFloat3(&this->pos);
    this->Update_View_Matrix();
}

void Camera::Adjust_Position(const XMVECTOR& pos)
{
    this->pos_vector += pos;
    XMStoreFloat3(&this->pos, this->pos_vector);
    this->Update_View_Matrix();
}

void Camera::Adjust_Position(float x, float y, float z)
{
    this->pos.x += x;
    this->pos.y += y;
    this->pos.z += z;
    this->pos_vector = XMLoadFloat3(&this->pos);
    this->Update_View_Matrix();
}

void Camera::Set_Rotation(const XMVECTOR& rot)
{
    this->rot_vector = rot;
    XMStoreFloat3(&this->rot, rot);
    this->Update_View_Matrix();
}

void Camera::Set_Rotation(float x, float y, float z)
{
    this->rot = XMFLOAT3(x, y, z);
    this->rot_vector = XMLoadFloat3(&this->rot);
    this->Update_View_Matrix();
}

void Camera::Adjust_Rotation(const XMVECTOR& rot)
{
    this->rot_vector += rot;
    XMStoreFloat3(&this->rot, this->rot_vector);
    this->Update_View_Matrix();
}

void Camera::Adjust_Rotation(float x, float y, float z)
{
    this->rot.x += x;
    this->rot.y += y;
    this->rot.z += z;
    this->rot_vector = XMLoadFloat3(&this->rot);
    this->Update_View_Matrix();
}

void Camera::Set_Lookat_Pos(XMFLOAT3 look_at_pos)
{
    if(look_at_pos.x == this->pos.x && look_at_pos.y == this->pos.y && look_at_pos.z == this->pos.z)
    {
        return;
    }
    look_at_pos.x = this->pos.x - look_at_pos.x;
    look_at_pos.y = this->pos.y - look_at_pos.y;
    look_at_pos.z = this->pos.z - look_at_pos.z;

    float pitch = 0.0f;
    if (look_at_pos.y != 0.0f)
    {
        const float distance = sqrt(look_at_pos.x * look_at_pos.x + look_at_pos.z * look_at_pos.z);
        pitch = atan(look_at_pos.y / distance);
    }

    this->Set_Rotation(pitch, 0.0f, 0.0f);
}

void Camera::Update_View_Matrix()
{
    XMMATRIX cam_rotation_matrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);

    XMVECTOR cam_target = XMVector3TransformCoord(this->default_forward_vector, cam_rotation_matrix);

    cam_target += this->pos_vector;

    XMVECTOR up_dir = XMVector3TransformCoord(this->default_up_vector, cam_rotation_matrix);

    this->view_matrix = XMMatrixLookAtLH(this->pos_vector, cam_target, up_dir);

}




#pragma once

class Camera
{
public:
	
	Camera()
	{
		zoom = 0.2f;
		cam_trans.x = 0.0f;
		cam_trans.y = 0.0f;
		cam_angle = 0.0f;
	}

	vector2<float>& Get_Cam_Trans()
	{
		return cam_trans;
	}
	float& Get_Zoom()
	{
		return zoom;
	}
	float& Get_Angle()
	{
		return cam_angle;
	}

	matrix4<float> Get_Cam_Matrix()
	{
		matrix4<float> result = MATRIX4::build_identity <float>();
		result *= MATRIX4::build_translation<float>(cam_trans.x, cam_trans.y);
		result *= MATRIX4::build_rotation<float>(cam_angle);
		result *= MATRIX4::build_scale<float>(zoom);
		result = MATRIX4::transpose(result);
		return result;
	}
	

	
private:
	vector2<float> cam_trans;
	float zoom;
	float cam_angle;
	matrix4<float> cam_mat;
	
};
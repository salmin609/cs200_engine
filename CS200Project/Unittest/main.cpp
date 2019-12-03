
#define CATCH_CONFIG_MAIN
#include "Catch2.h"
#include "matrix3.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix4.hpp"

TEST_CASE("Matrix Constructor")
{
	matrix3<float> mat_ctor_test1;
	REQUIRE(mat_ctor_test1.column0.x == 0.f);
	REQUIRE(mat_ctor_test1.column1.x == 0.f);
	REQUIRE(mat_ctor_test1.column2.x == 0.f);
						 
	REQUIRE(mat_ctor_test1.column0.y == 0.f);
	REQUIRE(mat_ctor_test1.column1.y == 0.f);
	REQUIRE(mat_ctor_test1.column2.y == 0.f);
						 
	REQUIRE(mat_ctor_test1.column0.z == 0.f);
	REQUIRE(mat_ctor_test1.column1.z == 0.f);
	REQUIRE(mat_ctor_test1.column2.z == 0.f);

	vector3<float> first = {1.f,2.f,3.f};
	vector3<float> second = { 4.f,5.f,6.f };
	vector3<float> third = { 7.f,8.f,9.f };
	matrix3<float> mat_ctor_test2(first, second, third);

	REQUIRE(mat_ctor_test2.column0.x == 1.f);
	REQUIRE(mat_ctor_test2.column0.y == 2.f);
	REQUIRE(mat_ctor_test2.column0.z == 3.f);

	REQUIRE(mat_ctor_test2.column1.x == 4.f);
	REQUIRE(mat_ctor_test2.column1.y == 5.f);
	REQUIRE(mat_ctor_test2.column1.z == 6.f);

	REQUIRE(mat_ctor_test2.column2.x == 7.f);
	REQUIRE(mat_ctor_test2.column2.y == 8.f);
	REQUIRE(mat_ctor_test2.column2.z == 9.f);

	matrix3<float> mat_ctor_test3(1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f);
	
	REQUIRE(mat_ctor_test3.column0.x == 1.f);
	REQUIRE(mat_ctor_test3.column0.y == 2.f);
	REQUIRE(mat_ctor_test3.column0.z == 3.f);
						 
	REQUIRE(mat_ctor_test3.column1.x == 4.f);
	REQUIRE(mat_ctor_test3.column1.y == 5.f);
	REQUIRE(mat_ctor_test3.column1.z == 6.f);
						 
	REQUIRE(mat_ctor_test3.column2.x == 7.f);
	REQUIRE(mat_ctor_test3.column2.y == 8.f);
	REQUIRE(mat_ctor_test3.column2.z == 9.f);
}

TEST_CASE("operator()")
{
	
	matrix3<float> mat_test(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);

	
	REQUIRE(mat_test(0, 0) == 1.f);
	REQUIRE(mat_test(0, 1) == 2.f);
	REQUIRE(mat_test(0, 2) == 3.f);
	REQUIRE(mat_test(1, 0) == 4.f);
	REQUIRE(mat_test(1, 1) == 5.f);
	REQUIRE(mat_test(1, 2) == 6.f);
	REQUIRE(mat_test(2, 0) == 7.f);
	REQUIRE(mat_test(2, 1) == 8.f);
	REQUIRE(mat_test(2, 2) == 9.f);

	
}

TEST_CASE("matrix3 operator*")
{
	matrix3<float> first_mat_test(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	matrix3<float> first_mat_test2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	matrix3<float> first_result = first_mat_test * first_mat_test2;
	
	matrix3<float> real_result(30.f, 36.f, 42.f, 66.f, 81.f, 96.f, 102.f, 126.f, 150.f);

	REQUIRE(first_result(0, 0) == real_result(0, 0));
	REQUIRE(first_result(0, 1) == real_result(0, 1));
	REQUIRE(first_result(0, 2) == real_result(0, 2));
	REQUIRE(first_result(1, 0) == real_result(1, 0));
	REQUIRE(first_result(1, 1) == real_result(1, 1));
	REQUIRE(first_result(1, 2) == real_result(1, 2));
	REQUIRE(first_result(2, 0) == real_result(2, 0));
	REQUIRE(first_result(2, 1) == real_result(2, 1));
	REQUIRE(first_result(2, 2) == real_result(2, 2));

	matrix3<float> second_mat_test(1.f, 0.f, 3.f, -56.f, 88.f, -6.f, -14.f, 463.f, 9.f);
	matrix3<float> second_mat_test2(1.f, 0.f, -60.f, -4.f, 0.f, 0.f, 0.f, 73.f, 9.f);
	matrix3<float> second_result = second_mat_test * second_mat_test2;

	matrix3<float> second_real_result(841.f, -27780.f, -537.f, -4.f, 0.f, -12.f, -4214.f, 10591.f, -357.f);
	
	REQUIRE(second_result(0, 0) == second_real_result(0, 0));
	REQUIRE(second_result(0, 1) == second_real_result(0, 1));
	REQUIRE(second_result(0, 2) == second_real_result(0, 2));
	REQUIRE(second_result(1, 0) == second_real_result(1, 0));
	REQUIRE(second_result(1, 1) == second_real_result(1, 1));
	REQUIRE(second_result(1, 2) == second_real_result(1, 2));
	REQUIRE(second_result(2, 0) == second_real_result(2, 0));
	REQUIRE(second_result(2, 1) == second_real_result(2, 1));
	REQUIRE(second_result(2, 2) == second_real_result(2, 2));
	
}

TEST_CASE("matrix3 operator*=")
{
	matrix3<float> first_mat_test(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	matrix3<float> first_mat_test2(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	first_mat_test *= first_mat_test2;
	
	matrix3<float> real_result(30.f, 36.f, 42.f, 66.f, 81.f, 96.f, 102.f, 126.f, 150.f);
	
	REQUIRE(first_mat_test(0, 0) == real_result(0, 0));
	REQUIRE(first_mat_test(0, 1) == real_result(0, 1));
	REQUIRE(first_mat_test(0, 2) == real_result(0, 2));
	REQUIRE(first_mat_test(1, 0) == real_result(1, 0));
	REQUIRE(first_mat_test(1, 1) == real_result(1, 1));
	REQUIRE(first_mat_test(1, 2) == real_result(1, 2));
	REQUIRE(first_mat_test(2, 0) == real_result(2, 0));
	REQUIRE(first_mat_test(2, 1) == real_result(2, 1));
	REQUIRE(first_mat_test(2, 2) == real_result(2, 2));

	matrix3<float> second_mat_test(1.f, 0.f, 3.f, -56.f, 88.f, -6.f, -14.f, 463.f, 9.f);
	matrix3<float> second_mat_test2(1.f, 0.f, -60.f, -4.f, 0.f, 0.f, 0.f, 73.f, 9.f);
	second_mat_test *= second_mat_test2;

	matrix3<float> second_real_result(841.f, -27780.f, -537.f, -4.f, 0.f, -12.f, -4214.f, 10591.f, -357.f);

	REQUIRE(second_mat_test(0, 0) == second_real_result(0, 0));
	REQUIRE(second_mat_test(0, 1) == second_real_result(0, 1));
	REQUIRE(second_mat_test(0, 2) == second_real_result(0, 2));
	REQUIRE(second_mat_test(1, 0) == second_real_result(1, 0));
	REQUIRE(second_mat_test(1, 1) == second_real_result(1, 1));
	REQUIRE(second_mat_test(1, 2) == second_real_result(1, 2));
	REQUIRE(second_mat_test(2, 0) == second_real_result(2, 0));
	REQUIRE(second_mat_test(2, 1) == second_real_result(2, 1));
	REQUIRE(second_mat_test(2, 2) == second_real_result(2, 2));

}

TEST_CASE("matrix3 operator* with vec")
{
	matrix3<float> first_mat_test(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	vector3<float> vec_test(1.f, 2.f, 3.f);
	vector3<float> result = first_mat_test * vec_test;

	vector3<float> real_result = { 30.f, 36.f, 42.f };

	REQUIRE(result.x == real_result.x);
	REQUIRE(result.y == real_result.y);
	REQUIRE(result.z == real_result.z);


	matrix3<float> second_mat_test(-30.f, 12.f, 0.f, -20.f, 593.f, 0.f, 0.f, 23.f, 23.f);
	vector3<float> vec_test2(0.f, -12.f, 23.f);
	vector3<float> result2 = second_mat_test * vec_test2;

	vector3<float> real_result2(240.f, -6587.f, 529.f);

	REQUIRE(result2.x == real_result2.x);
	REQUIRE(result2.y == real_result2.y);
	REQUIRE(result2.z == real_result2.z);
}

TEST_CASE("matrix3 transpose")
{
	matrix3<float> mat_test(1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f, 8.f, 9.f);
	matrix3<float> result(1.f, 4.f, 7.f, 2.f, 5.f, 8.f, 3.f, 6.f, 9.f);
	mat_test = MATRIX3::transpose(mat_test);

	REQUIRE(mat_test(0, 0) == result(0, 0));
	REQUIRE(mat_test(0, 1) == result(0, 1));
	REQUIRE(mat_test(0, 2) == result(0, 2));
	REQUIRE(mat_test(1, 0) == result(1, 0));
	REQUIRE(mat_test(1, 1) == result(1, 1));
	REQUIRE(mat_test(1, 2) == result(1, 2));
	REQUIRE(mat_test(2, 0) == result(2, 0));
	REQUIRE(mat_test(2, 1) == result(2, 1));
	REQUIRE(mat_test(2, 2) == result(2, 2));
}

TEST_CASE("matrix3 rotation")
{
	matrix3<float> test = MATRIX3::build_rotation<float>(30.f);;
	
	matrix3<float> result(cos(30.f), sin(30.f), 0.f, -sin(30.f), cos(30.f), 0.f, 0.f, 0.f, 1.f);
	
	REQUIRE(test(0, 0) == result(0, 0));
	REQUIRE(test(0, 1) == result(0, 1));
	REQUIRE(test(0, 2) == result(0, 2));
	REQUIRE(test(1, 0) == result(1, 0));
	REQUIRE(test(1, 1) == result(1, 1));
	REQUIRE(test(1, 2) == result(1, 2));
	REQUIRE(test(2, 0) == result(2, 0));
	REQUIRE(test(2, 1) == result(2, 1));
	REQUIRE(test(2, 2) == result(2, 2));
}

TEST_CASE("matrix3 identity")
{
	matrix3<float> test = MATRIX3::build_identity<float>();

	matrix3<float> result(1.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,1.f);

	REQUIRE(test(0, 0) == result(0, 0));
	REQUIRE(test(0, 1) == result(0, 1));
	REQUIRE(test(0, 2) == result(0, 2));
	REQUIRE(test(1, 0) == result(1, 0));
	REQUIRE(test(1, 1) == result(1, 1));
	REQUIRE(test(1, 2) == result(1, 2));
	REQUIRE(test(2, 0) == result(2, 0));
	REQUIRE(test(2, 1) == result(2, 1));
	REQUIRE(test(2, 2) == result(2, 2));
}

TEST_CASE("matrix3 scale_2float")
{
	matrix3<float> test = MATRIX3::build_scale<float>(10.f,20.f);

	matrix3<float> result(10.f, 0.f, 0.f, 0.f, 20.f, 0.f, 0.f, 0.f, 1.f);

	REQUIRE(test(0, 0) == result(0, 0));
	REQUIRE(test(0, 1) == result(0, 1));
	REQUIRE(test(0, 2) == result(0, 2));
	REQUIRE(test(1, 0) == result(1, 0));
	REQUIRE(test(1, 1) == result(1, 1));
	REQUIRE(test(1, 2) == result(1, 2));
	REQUIRE(test(2, 0) == result(2, 0));
	REQUIRE(test(2, 1) == result(2, 1));
	REQUIRE(test(2, 2) == result(2, 2));
}

TEST_CASE("matrix3 scale_1float")
{
	matrix3<float> test = MATRIX3::build_scale<float>(10.f);

	matrix3<float> result(10.f, 0.f, 0.f, 0.f, 10.f, 0.f, 0.f, 0.f, 1.f);

	REQUIRE(test(0, 0) == result(0, 0));
	REQUIRE(test(0, 1) == result(0, 1));
	REQUIRE(test(0, 2) == result(0, 2));
	REQUIRE(test(1, 0) == result(1, 0));
	REQUIRE(test(1, 1) == result(1, 1));
	REQUIRE(test(1, 2) == result(1, 2));
	REQUIRE(test(2, 0) == result(2, 0));
	REQUIRE(test(2, 1) == result(2, 1));
	REQUIRE(test(2, 2) == result(2, 2));
}

TEST_CASE("matrix3 scale_vector")
{
	matrix3<float> test = MATRIX3::build_scale<float>({10.f,20.f});

	matrix3<float> result(10.f, 0.f, 0.f, 0.f, 20.f, 0.f, 0.f, 0.f, 1.f);

	REQUIRE(test(0, 0) == result(0, 0));
	REQUIRE(test(0, 1) == result(0, 1));
	REQUIRE(test(0, 2) == result(0, 2));
	REQUIRE(test(1, 0) == result(1, 0));
	REQUIRE(test(1, 1) == result(1, 1));
	REQUIRE(test(1, 2) == result(1, 2));
	REQUIRE(test(2, 0) == result(2, 0));
	REQUIRE(test(2, 1) == result(2, 1));
	REQUIRE(test(2, 2) == result(2, 2));
}

TEST_CASE("matrix3 translation_2float")
{
	matrix3<float> test = MATRIX3::build_translation<float>(10.f,25.f);

	matrix3<float> result(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 10.f, 25.f, 1.f);

	REQUIRE(test(0, 0) == result(0, 0));
	REQUIRE(test(0, 1) == result(0, 1));
	REQUIRE(test(0, 2) == result(0, 2));
	REQUIRE(test(1, 0) == result(1, 0));
	REQUIRE(test(1, 1) == result(1, 1));
	REQUIRE(test(1, 2) == result(1, 2));
	REQUIRE(test(2, 0) == result(2, 0));
	REQUIRE(test(2, 1) == result(2, 1));
	REQUIRE(test(2, 2) == result(2, 2));
}


TEST_CASE("matrix3 translation_vector")
{
	matrix3<float> test = MATRIX3::build_translation<float>({ 10.f, 25.f });

	matrix3<float> result(1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 10.f, 25.f, 1.f);

	REQUIRE(test(0, 0) == result(0, 0));
	REQUIRE(test(0, 1) == result(0, 1));
	REQUIRE(test(0, 2) == result(0, 2));
	REQUIRE(test(1, 0) == result(1, 0));
	REQUIRE(test(1, 1) == result(1, 1));
	REQUIRE(test(1, 2) == result(1, 2));
	REQUIRE(test(2, 0) == result(2, 0));
	REQUIRE(test(2, 1) == result(2, 1));
	REQUIRE(test(2, 2) == result(2, 2));
}

TEST_CASE("matrix4 constructor")
{
	matrix4<float> test;

	REQUIRE(test.column0.x == 0.f);
	REQUIRE(test.column0.y == 0.f);
	REQUIRE(test.column0.z == 0.f);
	REQUIRE(test.column0.w == 0.f);
	REQUIRE(test.column1.x == 0.f);
	REQUIRE(test.column1.y == 0.f);
	REQUIRE(test.column1.z == 0.f);
	REQUIRE(test.column1.w == 0.f);
	REQUIRE(test.column2.x == 0.f);
	REQUIRE(test.column2.y == 0.f);
	REQUIRE(test.column2.z == 0.f);
	REQUIRE(test.column2.w == 0.f);
	REQUIRE(test.column3.x == 0.f);
	REQUIRE(test.column3.y == 0.f);
	REQUIRE(test.column3.z == 0.f);
	REQUIRE(test.column3.w == 0.f);
}

TEST_CASE("matrix4 operator()")
{
	matrix4<float> test;

	REQUIRE(test(0, 0) == 0.f);
	REQUIRE(test(0, 1) == 0.f);
	REQUIRE(test(0, 2) == 0.f);
	REQUIRE(test(0, 3) == 0.f);
	REQUIRE(test(1, 0) == 0.f);
	REQUIRE(test(1, 1) == 0.f);
	REQUIRE(test(1, 2) == 0.f);
	REQUIRE(test(1, 3) == 0.f);
	REQUIRE(test(2, 0) == 0.f);
	REQUIRE(test(2, 1) == 0.f);
	REQUIRE(test(2, 2) == 0.f);
	REQUIRE(test(2, 3) == 0.f);
	REQUIRE(test(3, 0) == 0.f);
	REQUIRE(test(3, 1) == 0.f);
	REQUIRE(test(3, 2) == 0.f);
	REQUIRE(test(3, 3) == 0.f);
}

TEST_CASE("matrix4 build translation")
{
	matrix4<float> test = MATRIX4::build_translation<float>(3.f,3.f);

	REQUIRE(test(0, 0) == 1.f);
	REQUIRE(test(0, 1) == 0.f);
	REQUIRE(test(0, 2) == 0.f);
	REQUIRE(test(0, 3) == 0.f);
	REQUIRE(test(1, 0) == 0.f);
	REQUIRE(test(1, 1) == 1.f);
	REQUIRE(test(1, 2) == 0.f);
	REQUIRE(test(1, 3) == 0.f);
	REQUIRE(test(2, 0) == 0.f);
	REQUIRE(test(2, 1) == 0.f);
	REQUIRE(test(2, 2) == 1.f);
	REQUIRE(test(2, 3) == 0.f);
	REQUIRE(test(3, 0) == 3.f);
	REQUIRE(test(3, 1) == 3.f);
	REQUIRE(test(3, 2) == 0.f);
	REQUIRE(test(3, 3) == 1.f);
}

TEST_CASE("matrix4 build scale vec")
{
	matrix4<float> test = MATRIX4::build_scale<float>({3.f,3.f});

	REQUIRE(test(0, 0) == 3.f);
	REQUIRE(test(0, 1) == 0.f);
	REQUIRE(test(0, 2) == 0.f);
	REQUIRE(test(0, 3) == 0.f);
	REQUIRE(test(1, 0) == 0.f);
	REQUIRE(test(1, 1) == 3.f);
	REQUIRE(test(1, 2) == 0.f);
	REQUIRE(test(1, 3) == 0.f);
	REQUIRE(test(2, 0) == 0.f);
	REQUIRE(test(2, 1) == 0.f);
	REQUIRE(test(2, 2) == 0.f);
	REQUIRE(test(2, 3) == 0.f);
	REQUIRE(test(3, 0) == 0.f);
	REQUIRE(test(3, 1) == 0.f);
	REQUIRE(test(3, 2) == 0.f);
	REQUIRE(test(3, 3) == 1.f);
}


TEST_CASE("matrix4 build scale float")
{
	matrix4<float> test = MATRIX4::build_scale<float>(5.f);

	REQUIRE(test(0, 0) == 5.f);
	REQUIRE(test(0, 1) == 0.f);
	REQUIRE(test(0, 2) == 0.f);
	REQUIRE(test(0, 3) == 0.f);
	REQUIRE(test(1, 0) == 0.f);
	REQUIRE(test(1, 1) == 5.f);
	REQUIRE(test(1, 2) == 0.f);
	REQUIRE(test(1, 3) == 0.f);
	REQUIRE(test(2, 0) == 0.f);
	REQUIRE(test(2, 1) == 0.f);
	REQUIRE(test(2, 2) == 0.f);
	REQUIRE(test(2, 3) == 0.f);
	REQUIRE(test(3, 0) == 0.f);
	REQUIRE(test(3, 1) == 0.f);
	REQUIRE(test(3, 2) == 0.f);
	REQUIRE(test(3, 3) == 1.f);
}

TEST_CASE("matrix4 build scale 2float")
{
	matrix4<float> test = MATRIX4::build_scale<float>(5.f, 10.f);

	REQUIRE(test(0, 0) == 5.f);
	REQUIRE(test(0, 1) == 0.f);
	REQUIRE(test(0, 2) == 0.f);
	REQUIRE(test(0, 3) == 0.f);
	REQUIRE(test(1, 0) == 0.f);
	REQUIRE(test(1, 1) == 10.f);
	REQUIRE(test(1, 2) == 0.f);
	REQUIRE(test(1, 3) == 0.f);
	REQUIRE(test(2, 0) == 0.f);
	REQUIRE(test(2, 1) == 0.f);
	REQUIRE(test(2, 2) == 0.f);
	REQUIRE(test(2, 3) == 0.f);
	REQUIRE(test(3, 0) == 0.f);
	REQUIRE(test(3, 1) == 0.f);
	REQUIRE(test(3, 2) == 0.f);
	REQUIRE(test(3, 3) == 1.f);
}

TEST_CASE("matrix4 build identity")
{
	matrix4<float> test = MATRIX4::build_identity<float>();

	REQUIRE(test(0, 0) == 1.f);
	REQUIRE(test(0, 1) == 0.f);
	REQUIRE(test(0, 2) == 0.f);
	REQUIRE(test(0, 3) == 0.f);
	REQUIRE(test(1, 0) == 0.f);
	REQUIRE(test(1, 1) == 1.f);
	REQUIRE(test(1, 2) == 0.f);
	REQUIRE(test(1, 3) == 0.f);
	REQUIRE(test(2, 0) == 0.f);
	REQUIRE(test(2, 1) == 0.f);
	REQUIRE(test(2, 2) == 1.f);
	REQUIRE(test(2, 3) == 0.f);
	REQUIRE(test(3, 0) == 0.f);
	REQUIRE(test(3, 1) == 0.f);
	REQUIRE(test(3, 2) == 0.f);
	REQUIRE(test(3, 3) == 1.f);
}

TEST_CASE("matrix4 build rotation")
{
	matrix4<float> test = MATRIX4::build_rotation<float>(30.f);

	REQUIRE(test(0, 0) == cos(30.f));
	REQUIRE(test(0, 1) == sin(30.f));
	REQUIRE(test(0, 2) == 0.f);
	REQUIRE(test(0, 3) == 0.f);
	REQUIRE(test(1, 0) == -sin(30.f));
	REQUIRE(test(1, 1) == cos(30.f));
	REQUIRE(test(1, 2) == 0.f);
	REQUIRE(test(1, 3) == 0.f);
	REQUIRE(test(2, 0) == 0.f);
	REQUIRE(test(2, 1) == 0.f);
	REQUIRE(test(2, 2) == 1.f);
	REQUIRE(test(2, 3) == 0.f);
	REQUIRE(test(3, 0) == 0.f);
	REQUIRE(test(3, 1) == 0.f);
	REQUIRE(test(3, 2) == 0.f);
	REQUIRE(test(3, 3) == 1.f);
}

TEST_CASE("matrix4 build transpose")
{
	matrix4<float> test = MATRIX4::build_translation<float>(30.f, 20.f);
	test = MATRIX4::transpose<float>(test);

	REQUIRE(test(0, 0) == 1.f);
	REQUIRE(test(0, 1) == 0.f);
	REQUIRE(test(0, 2) == 0.f);
	REQUIRE(test(0, 3) == 30.f);
	REQUIRE(test(1, 0) == 0.f);
	REQUIRE(test(1, 1) == 1.f);
	REQUIRE(test(1, 2) == 0.f);
	REQUIRE(test(1, 3) == 20.f);
	REQUIRE(test(2, 0) == 0.f);
	REQUIRE(test(2, 1) == 0.f);
	REQUIRE(test(2, 2) == 1.f);
	REQUIRE(test(2, 3) == 0.f);
	REQUIRE(test(3, 0) == 0.f);
	REQUIRE(test(3, 1) == 0.f);
	REQUIRE(test(3, 2) == 0.f);
	REQUIRE(test(3, 3) == 1.f);
}

TEST_CASE("matrix4 operator*=")
{
	matrix4<float> test = MATRIX4::build_translation<float>(30.f, 20.f);
	matrix4<float> test2 = MATRIX4::build_translation<float>(60.f, 50.f);
	test *= test2;

	matrix4<float> result = MATRIX4::build_translation<float>(90.f, 70.f);
	
	REQUIRE(test(0, 0) == result(0, 0));
	REQUIRE(test(0, 1) == result(0, 1));
	REQUIRE(test(0, 2) == result(0, 2));
	REQUIRE(test(0, 3) == result(0, 3));
	REQUIRE(test(1, 0) == result(1, 0));
	REQUIRE(test(1, 1) == result(1, 1));
	REQUIRE(test(1, 2) == result(1, 2));
	REQUIRE(test(1, 3) == result(1, 3));
	REQUIRE(test(2, 0) == result(2, 0));
	REQUIRE(test(2, 1) == result(2, 1));
	REQUIRE(test(2, 2) == result(2, 2));
	REQUIRE(test(2, 3) == result(2, 3));
	REQUIRE(test(3, 0) == result(3, 0));
	REQUIRE(test(3, 1) == result(3, 1));
	REQUIRE(test(3, 2) == result(3, 2));
	REQUIRE(test(3, 3) == result(3, 3));
}

TEST_CASE("matrix4 operator*")
{
	matrix4<float> test = MATRIX4::build_translation<float>(30.f, 20.f);
	matrix4<float> test2 = MATRIX4::build_translation<float>(60.f, 50.f);
	matrix4<float> tset_result = test * test2;

	matrix4<float> result = MATRIX4::build_translation<float>(90.f, 70.f);

	REQUIRE(tset_result(0, 0) == result(0, 0));
	REQUIRE(tset_result(0, 1) == result(0, 1));
	REQUIRE(tset_result(0, 2) == result(0, 2));
	REQUIRE(tset_result(0, 3) == result(0, 3));
	REQUIRE(tset_result(1, 0) == result(1, 0));
	REQUIRE(tset_result(1, 1) == result(1, 1));
	REQUIRE(tset_result(1, 2) == result(1, 2));
	REQUIRE(tset_result(1, 3) == result(1, 3));
	REQUIRE(tset_result(2, 0) == result(2, 0));
	REQUIRE(tset_result(2, 1) == result(2, 1));
	REQUIRE(tset_result(2, 2) == result(2, 2));
	REQUIRE(tset_result(2, 3) == result(2, 3));
	REQUIRE(tset_result(3, 0) == result(3, 0));
	REQUIRE(tset_result(3, 1) == result(3, 1));
	REQUIRE(tset_result(3, 2) == result(3, 2));
	REQUIRE(tset_result(3, 3) == result(3, 3));
}
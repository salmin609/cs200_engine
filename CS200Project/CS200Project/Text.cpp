///************************************************
// *NAME              : sangmin.kim
// *ASSIGNMENT NUMBER : 7
// *COURSE NAME       : CS230
// *TERM              : Spring 2019
// ************************************************/
//#include "BitmapFont.hpp"
//#include "Text.hpp"
//
//Text::Text(std::wstring text_string, const BitmapFont& text_font) noexcept
//{
//	font = &text_font;
//	string = text_string;
//	InitializeWithEmptyVertices();
//}
//
//std::vector<std::pair<const Vertices*, const Texture*>> Text::GetVerticesWithMatchingTextures() const noexcept
//{
//	if (needNewMeshes)
//	{
//		BuildNewMeshesIfNeeded();
//	}
//	else if (!needNewMeshes)
//	{
//		std::vector<std::pair<const Vertices*, const Texture*>> my_vec;
//
//		for (int i = 0; i < font->GetInformation().pagesCount; i++)
//		{
//			if (vertices.at(i).GetVerticesCount() == 0)
//			{
//				continue;
//			}
//
//			std::pair temp_pair(&vertices.at(i), &font->GetTexture(i));
//			my_vec.emplace_back(temp_pair);
//		}
//		return my_vec;
//	}
//	return {};
//}
//
//std::wstring Text::GetString() const noexcept
//{
//	return string;
//}
//
//void Text::SetString(const std::wstring& text_string) noexcept
//{
//	if (text_string != string)
//	{
//		needNewMeshes = true;
//		string = text_string;
//	}
//}
//
//const BitmapFont* Text::GetFont() const noexcept
//{
//	return font;
//}
//
//void Text::SetFont(const BitmapFont& text_font) noexcept
//{
//	vertices.clear();
//	if (&text_font != font)
//	{
//		needNewMeshes = true;
//		font = &text_font;
//	}
//	InitializeWithEmptyVertices();
//}
//
//
//void Text::InitializeWithEmptyVertices() const noexcept
//{
//	vertices.clear();
//	for (int i = 0; i < font->GetInformation().pagesCount; i++)
//	{
//		Vertices tmp;
//		Mesh new_mesh;
//		new_mesh.Clear();
//		tmp.InitializeWithMeshAndLayout(new_mesh, SHADER::textured_vertex_layout());
//		vertices.insert_or_assign(i, std::move(tmp));
//	}
//}
//void Helper_Set_Mesh(float left_pos, float right_pos, float up_pos, float down_pos, float left_u, float right_u, float up_v, float down_v, Mesh* mesh)
//{
//	mesh->AddPoint({ left_pos, up_pos });
//	mesh->AddPoint({ left_pos, down_pos });
//	mesh->AddPoint({ right_pos, up_pos });
//	mesh->AddPoint({ right_pos, up_pos });
//	mesh->AddPoint({ left_pos, down_pos });
//	mesh->AddPoint({ right_pos, down_pos });
//
//	mesh->AddTextureCoordinate({ left_u, up_v });
//	mesh->AddTextureCoordinate({ left_u, down_v });
//	mesh->AddTextureCoordinate({ right_u, up_v });
//	mesh->AddTextureCoordinate({ right_u, up_v });
//	mesh->AddTextureCoordinate({ left_u, down_v });
//	mesh->AddTextureCoordinate({ right_u, down_v });
//}
//
//void Text::BuildNewMeshesIfNeeded() const noexcept
//{
//	if (needNewMeshes)
//	{
//		BitmapFont::character this_character;
//		float left_pos, right_pos, up_pos, down_pos;
//		float left_texel, right_texel, up_texel, down_texel;
//		float left_u, right_u, down_v, up_v;
//		Mesh new_mesh_first;
//		Mesh new_mesh_second;
//		Mesh new_mesh_third;
//		new_mesh_first.SetPointListType(PointListPattern::Triangles);
//		new_mesh_second.SetPointListType(PointListPattern::Triangles);
//		new_mesh_third.SetPointListType(PointListPattern::Triangles);
//		short cursor_x = 0;
//		short cursor_y = 0;
//
//		for (int i = 0; i < string.size(); i++)
//		{
//			this_character = font->GetCharacter(string.at(i));
//			if (string.at(i) == ' ')
//			{
//				cursor_x += this_character.xAdvance;
//				continue;
//			}
//			if (string.at(i) == '\t')
//			{
//				cursor_x += this_character.xAdvance * 4;
//				continue;
//			}
//			if (string.at(i) == '\n')
//			{
//				cursor_y -= font->GetInformation().lineHeight;
//				cursor_x = 0;
//				continue;
//			}
//			left_pos = static_cast<float>(this_character.xOffset + cursor_x);
//			right_pos = static_cast<float>(left_pos + this_character.width);
//			down_pos = static_cast<float>((this_character.yOffset + this_character.height) * -1 + font->GetInformation().lineHeight + cursor_y);
//			up_pos = static_cast<float>(down_pos + this_character.height);
//
//			left_texel = this_character.x;
//			left_u = left_texel / font->GetInformation().imageWidth;
//			right_texel = left_texel + this_character.width;
//			right_u = right_texel / font->GetInformation().imageWidth;
//			up_texel = this_character.y;
//			up_v = up_texel / font->GetInformation().imageHeight;
//			down_texel = up_texel + this_character.height;
//			down_v = down_texel / font->GetInformation().imageHeight;
//
//			if (this_character.page == 0)
//			{
//				Helper_Set_Mesh(left_pos, right_pos, up_pos, down_pos, left_u, right_u, up_v, down_v, &new_mesh_first);
//				vertices[0].InitializeWithMeshAndLayout(new_mesh_first, SHADER::textured_vertex_layout());
//			}
//			else if (this_character.page == 1)
//			{
//				Helper_Set_Mesh(left_pos, right_pos, up_pos, down_pos, left_u, right_u, up_v, down_v, &new_mesh_second);
//				vertices[1].InitializeWithMeshAndLayout(new_mesh_second, SHADER::textured_vertex_layout());
//			}
//			else if (this_character.page == 2)
//			{
//				Helper_Set_Mesh(left_pos, right_pos, up_pos, down_pos, left_u, right_u, up_v, down_v, &new_mesh_third);
//				vertices[2].InitializeWithMeshAndLayout(new_mesh_third, SHADER::textured_vertex_layout());
//			}
//			cursor_x += this_character.xAdvance;
//		}
//		needNewMeshes = false;
//	}
//}

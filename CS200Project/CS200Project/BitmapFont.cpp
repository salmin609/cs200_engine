/************************************************
 *NAME              : sangmin.kim
 *ASSIGNMENT NUMBER : 7
 *COURSE NAME       : CS230
 *TERM              : Spring 2019
 ************************************************/
#include "BitmapFont.hpp"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <sstream>

bool BitmapFont::LoadFromFile(const std::filesystem::path& filename)
{
	bool is_success_parse = CanParseFile(filename);

	if (is_success_parse)
	{
		for (int i = 0; i < details.pagesCount; i++)
		{
			std::wstring temp_string = filename.parent_path();
			temp_string += '/';
			temp_string += details.pageNames[i].substr(1, details.pageNames[i].size() - 2);

			pageTextures.emplace_back();
			pageTextures[i].LoadFromPNG(temp_string);
		}
		return true;
	}
	return false;
}

bool BitmapFont::LoadDefinition(const std::wstring& font_definition, std::vector<Texture> page_textures)
{
	std::wistringstream stream(font_definition);
	if (!CanParseStream(stream))
		return false;
	pageTextures = std::move(page_textures);
	return pageTextures.size() == details.pagesCount;
}

const BitmapFont::information& BitmapFont::GetInformation() const noexcept
{
	return details;
}

BitmapFont::character BitmapFont::GetCharacter(wchar_t character_id) const noexcept
{
	const auto this_character = characters.find(character_id);

	if (this_character != characters.end())
	{
		return this_character->second;
	}
	if (this_character == characters.end())
	{
		return characters.begin()->second;
	}
	return character{};
}

unsigned short BitmapFont::GetLineHeight() const noexcept
{
	return details.lineHeight;
}

const Texture& BitmapFont::GetTexture(int page_index) const noexcept
{
	assert(page_index >= 0 && page_index < details.pagesCount);
	assert(!pageTextures.empty());

	return pageTextures.at(page_index);
}

bool BitmapFont::HasCharacter(wchar_t character_id) const noexcept
{
	const auto this_character = characters.find(character_id);

	return this_character != characters.end();
}

bool BitmapFont::CanParseFile(const std::filesystem::path& filename)
{
	std::wifstream stream(filename);
	if (stream)
	{
		return CanParseStream(stream);
	}
	return false;
}

bool BitmapFont::CanParseStream(std::wistream& stream)
{
	std::wstring line;
	std::wstring read, key, value;
	std::size_t i = 0;
	unsigned short char_id = 0;



	while (!stream.eof())
	{
		std::wstringstream line_stream;
		std::getline(stream, line);
		line_stream << line;
		line_stream >> read;
		if (read == L"common")
		{
			while (!line_stream.eof())
			{
				std::wstringstream converter;

				line_stream >> read;
				i = read.find(L'=');
				key = read.substr(0, i);
				value = read.substr(i + 1);

				converter << value;
				if (key == L"lineHeight")
				{
					converter >> details.lineHeight;
				}
				else if (key == L"scaleW")
				{
					converter >> details.imageWidth;
				}
				else if (key == L"scaleH")
				{
					converter >> details.imageHeight;
				}
				else if (key == L"pages")
				{
					converter >> details.pagesCount;
				}
			}
		}
		else if (read == L"info")
		{
			while (!line_stream.eof())
			{
				std::wstringstream converter;

				line_stream >> read;
				i = read.find(L'=');
				key = read.substr(0, i);
				value = read.substr(i + 1);

				converter << value;
				if (key == L"face")
				{
					converter >> details.fontName;
				}
				else if (key == L"size")
				{
					converter >> details.fontSize;
				}
			}
		}
		else if (read == L"page")
		{
			while (!line_stream.eof())
			{
				std::wstringstream converter;
				line_stream >> read;
				i = read.find(L'=');
				key = read.substr(0, i);
				value = read.substr(i + 1);
				converter << value;

				if (key == L"file")
				{
					details.pageNames.push_back(value);
				}
			}
		}
		else if (read == L"char")
		{
			while (!line_stream.eof())
			{
				std::wstringstream converter;
				line_stream >> read;
				i = read.find('=');
				key = read.substr(0, i);
				value = read.substr(i + 1);
				converter << value;

				if (key == L"id")
				{
					converter >> char_id;
					characters[char_id].id = char_id;
				}
				else if (key == L"x")
				{
					converter >> characters[char_id].x;
				}
				else if (key == L"y")
				{
					converter >> characters[char_id].y;
				}
				else if (key == L"width")
				{
					converter >> characters[char_id].width;
				}
				else if (key == L"height")
				{
					converter >> characters[char_id].height;
				}
				else if (key == L"xoffset")
				{
					converter >> characters[char_id].xOffset;
				}
				else if (key == L"yoffset")
				{
					converter >> characters[char_id].yOffset;
				}
				else if (key == L"xadvance")
				{
					converter >> characters[char_id].xAdvance;
				}
				else if (key == L"page")
				{
					converter >> reinterpret_cast<unsigned short&>(characters[char_id].page);
				}
			}
		}
	}
	return true;
}




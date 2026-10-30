#include "Map.h"

#include "DxLib.h"
#include <sstream>
#include <functional>

bool Map::LoadMapData(const std::string& mapName)
{
	std::function<bool(const std::string&)> Error = [&](const std::string& message)
	{
		MessageBoxA(NULL, message.c_str(), "Fatal Error", MB_OK | MB_ICONERROR);
		return false;
	};




	int fileHandle = FileRead_open((mapName).c_str());
	if (fileHandle == 0)
	{
		return Error(mapName + "ファイルを開くことに失敗しました。");
	}

	int result;

	for (int y = 0; y < MAP_SIZE_Y; y++)
	{
		char line[256];
		result = FileRead_gets(line, sizeof(line), fileHandle);
		if (result == -1)
		{
			result = FileRead_close(fileHandle);
			if (result == -1)
			{
				return Error(mapName + "ファイルを閉じることに失敗しました。");
			}
			return Error(mapName + "ファイルを読み込むことに失敗しました。");
		}

		std::stringstream ss(line);
		std::string cell;

		for (int x = 0; x < MAP_SIZE_X; x++)
		{
			std::getline(ss, cell, ',');

			try
			{
				m_Map[y][x] = static_cast<int>(std::stoi(cell));
			}
			catch (const std::invalid_argument&)
			{
				return Error(mapName + "に数値以外の値が含まれています。" + cell);
			}
			catch (const std::out_of_range&)
			{
				return Error(mapName + "に範囲外の値が含まれています。" + cell);
			}
		}
	}

	result = FileRead_close(fileHandle);
	if (result == -1)
	{
		return Error(mapName + "ファイルを閉じることに失敗しました。");
	}

	return true;
}
#include <fstream>
#include <sstream>
#include <SDL_rect.h>

#include "managers/TextureManager.h"
#include "Core/Sprite.h"

#include "R-Type/Map/Map.h"

#include "Managers/EnemyManager.h"
#include "R-Type/Map/Tile.h"
#include "R-Type/Map/Camera.h"

Map::Map(const char* textureMapPath, const char* tileSheetPath, const int columns, const int rows)
{
	m_MapSheet = std::make_unique<Sprite>(tileSheetPath, columns, rows);

	CreateTiles(textureMapPath);
}

Map::~Map()
{
	m_CanRender = false;
	RemoveTiles();
	m_MapSheet.reset();
}

void Map::CreateTiles(const char* textureMapPath)
{
	bool hasReachedWhile = false;

	//Create temporary files for handling strings
	std::ifstream file;
	std::string line;
	std::string final;

	//Open Texture Map
	file.open(textureMapPath);


	//Create string with all numbers

	while (std::getline(file, line))
	{
		final.append(line);
		final.append(",");
	}

	int type;
	std::string temp;
	int itX = 0;
	int itY = 0;
	std::istringstream str_buf {final};

	//Loop over all numbers and create tiles based on it.
	while (str_buf >> type)
	{
		hasReachedWhile = true;

		m_MapTiles[itY][itX] = new Tile(type);

		if (itX < (m_MapColumns - 1))
		{
			itX++;
		}
		else
		{
			itX = 0;
			if (itY < m_MapRows)
			{
				itY++;
			}
		}

		if ((str_buf >> std::ws).peek() == ',')
			str_buf.ignore();
	}

	file.close();

	//Temporary safeguard to guarantee it has at least tried to make objects
	if (hasReachedWhile)
	{
		m_CanRender = true;
	}
}

void Map::CreateEnemies(const char* EnemyMapPath, EnemyManager& enemyManager)
{
	//Create temporary files for handling strings
	std::ifstream file;
	std::string line;
	std::string final;

	//Open Texture Map
	file.open(EnemyMapPath);


	//Create string with all numbers

	while (std::getline(file, line))
	{
		final.append(line);
		final.append(",");
	}

	int type;
	std::string temp;
	int itX = 0;
	int itY = 0;
	std::istringstream str_buf {final};

	//Loop over all numbers and create tiles based on it.
	while (str_buf >> type)
	{
		switch (type)
		{
			case 1:
				enemyManager.AddEntity(m_EnemyType::PataPata,itX,itY);
				break;
		}

		if (itX < (m_MapColumns - 1))
		{
			itX++;
		}
		else
		{
			itX = 0;
			if (itY < m_MapRows)
			{
				itY++;
			}
		}

		if ((str_buf >> std::ws).peek() == ',')
			str_buf.ignore();
	}

	file.close();
}

void Map::DrawMap(Camera& cam) const
{
	if (!m_CanRender)
		return;

	for (int i = 0; i < m_MapRows; ++i)
	{
		for (int j = 0; j < m_MapColumns; ++j)
		{
			int id = m_MapTiles[i][j]->GetID();
			float posX = (static_cast<float>(m_MapSheet->GetWidth() * j)) - cam.GetPosX();
			float PosY = static_cast<float>(m_MapSheet->GetHeight() * i) - cam.GetPosY();
			RenderSprite(id,posX,PosY);
		}
	}
}

void Map::RemoveTiles() const
{
	for (int i = 0; i < m_MapRows; ++i)
	{
		for (int j = 0; j < m_MapColumns; ++j)
		{
			if(m_MapTiles[i][j] != nullptr)
			{
				delete m_MapTiles[i][j];
			}
		}
	}
}

bool Map::HasTileCollision(int posX, int posX2, int posY, int posY2) const
{
	if (GetTile(posY, posX)->CanCollide())
	{
		return true;
	}
	if (GetTile(posY, posX2)->CanCollide())
	{
		return true;
	}
	if (GetTile(posY2, posX)->CanCollide())
	{
		return true;
	}
	if (GetTile(posY2, posX2)->CanCollide())
	{
		return true;
	}

	return false;
}

Tile* Map::GetTile(int row, int column) const
{
	return m_MapTiles[row][column];
}

void Map::RenderSprite(int frameID, float posX, float posY) const
{
	if (m_MapSheet != nullptr)
	{
		m_MapSheet->SetFrame(frameID);

		//Create Variable for the position of the sprite
		const SDL_Rect tempRec(static_cast<int>(posX), static_cast<int>(posY), m_MapSheet->GetWidth(), m_MapSheet->GetHeight());

		//Create temp variable to get the position / size that needs to be rendered
		SDL_Rect tempSource;
		m_MapSheet->GetSourceRec(tempSource);

		TextureManager::RenderTexture(m_MapSheet->GetTexture(), &tempSource, &tempRec);
	}
}

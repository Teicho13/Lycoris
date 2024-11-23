#include "R-Type/Map/Tile.h"

Tile::Tile(const int id)
{
	m_TileID = id;
}

int Tile::GetID() const
{
	return m_TileID;
}

//Check if current tile can be hit (not a background tile)
bool Tile::CanCollide() const
{
	if (m_TileID != 17 && m_TileID != 126 && m_TileID != 127 && m_TileID != 208)
	{
		return true;
	}

	return false;
}

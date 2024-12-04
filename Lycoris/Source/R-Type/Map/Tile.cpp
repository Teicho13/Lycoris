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
	if (m_TileID != 28 && m_TileID != 104 && m_TileID != 105 && m_TileID != 280 && m_TileID != 369 && m_TileID != 1474
		&& m_TileID != 1475 && m_TileID != 1298 && m_TileID != 1211 && m_TileID != 184
		&& m_TileID != 185 && m_TileID != 1142 && m_TileID != 1143 && m_TileID != 230
		&& m_TileID != 276 && m_TileID != 322 && m_TileID != 249 && m_TileID != 207
		&& m_TileID != 165 && m_TileID != 122 && m_TileID != 123 && m_TileID != 872
		&& m_TileID != 873 && m_TileID != 830 && m_TileID != 788 && m_TileID != 746)
	{
		return true;
	}

	return false;
}

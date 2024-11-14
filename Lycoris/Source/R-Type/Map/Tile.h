#pragma once
class Tile
{
public:
	Tile(const int id);

	int GetID() const;
	bool CanCollide() const;

private:
	int m_TileID = 0;
};

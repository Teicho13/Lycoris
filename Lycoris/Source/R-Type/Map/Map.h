#pragma once
#include <memory>

class EnemyManager;
class Tile;
class Sprite;
class Camera;

class Map
{
public:

	Map(const char* textureMapPath, const char* tileSheetPath, const int columns, const int rows);
	~Map();

	void CreateTiles(const char* textureMapPath);
	void CreateEnemies(const char* EnemyMapPath, EnemyManager& enemyManager);
	void DrawMap(Camera& cam) const;
	void RemoveTiles() const;

	bool HasTileCollision(int posX, int posX2, int posY, int posY2) const;

	Tile* GetTile(int row, int column) const;

	static constexpr int m_MapRows = 12;
	static constexpr int m_MapColumns = 268;
private:

	void RenderSprite(int frameID, float posX, float posY) const;

	std::unique_ptr<Sprite> m_MapSheet = nullptr;
	Tile* m_MapTiles[m_MapRows][m_MapColumns];

	bool m_CanRender = false;
};

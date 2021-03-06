#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"



class TileMap
{
private:
	/**** DATA MEMBERS ****/

	/* Storage */
	std::vector<std::vector<std::vector<std::vector<Tile*> > > > tileMap;

	/* Tile Textures */
	sf::Texture tileTextureSheet;
	sf::IntRect* textureSelector;

	/* Enemy Spawner Textures */
	sf::Texture enemyTextures[3];
	std::string textureFileNames[3];

	/* Deferred Render */
	std::stack<Tile*> deferredRenderStack;

	/* Dimensions */
	float maxSizeX;
	float maxSizeY;
	float maxLayers;
	float maxTiles;
	float gridSizeF;

	/* Map Updates */
	int tileType;
	bool collisionEnabled;
	int collisionType;
	
	/* Enemy Specific */
	bool enemySpawnerEnabled;
	int enemyType;

	/* Key Timer */
	float keyTimer;
	float keyTimerMax;
	

	/**** METHODS(Private) ****/
	void initTextures();

	void clearMap();
	void initTileMap(std::string texture_sheet_file = "");
	void initVars();


protected:

public:
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	TileMap(float max_size_x, float max_size_y, float max_layers, float grid_size_f);
	~TileMap();

	/**** ACCESSORS ****/
	const bool& getCollision() const;
	const bool& getEnemySpawner() const;
	const int& getEnemyType() const;
	const int& getTileType() const;
	const int& getCollisionType() const;
	const sf::Vector2f& getTileMapMaxSize();

	/**** MUTATORS ****/
	void toggleCollision();
	void toggleType();
	void toggleEnemySpawner();
	void toggleEnemyType();
	void toggleCollistionType();

	/**** METHODS ****/

	void saveTileMap(std::string filename);
	void loadTileMap(std::string filename);

	/*** Updates ***/
	void Update();

	bool addTile(const unsigned int& pos_x, const unsigned int& pos_y, const float& layer, 
		sf::Texture& tile_texture_sheet, sf::IntRect& texture_selector, 
		bool collision = false, int collision_type = CollisionType::COVER,
		int tile_type = 0);
	bool removeTile(const float& pos_x, const float& pos_y, const float& layer);
	void clearCurrentMap();

	void checkTileCollision(const float& dt, Entity* entity = NULL);
	void getCollisionOffset();
	void checkEnemySpawners(const float& dt, std::vector<Enemy*>* game_enemies, Entity* entity);

	/*** Renders ***/
	void Render(sf::RenderTarget& target, const sf::Sprite* entity = NULL, sf::View* mainView = NULL);
	void deferredRender(sf::RenderTarget& target);
};



#endif
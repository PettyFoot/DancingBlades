#pragma once


#include "Weapon.h"
#include "HitboxComponent.h"

enum SwordAttack{ DEFAULT = 0, STAB, CRUSH, SLASH, GYRATE };

class Sword :
    public Weapon
{

private:
	/**** DATA MEMBERS ****/

	/* Sword Texture Rect */
	sf::FloatRect textureRect;

	/* Sword Hitbox */
	HitboxComponent* swordHitboxComponent;

	/* Sword State */
	int swordAttack;
	sf::Vector2f swingVelocity;
	bool combat;
	
	float attackTime;

	float attackX;
	float attackY;

	
	/* Sword Range */
	sf::FloatRect entityBounds;
	sf::FloatRect swordBounds;

	sf::Vector2i mousePosWindow;

	/* Sword Controls */
	bool isEquipped;
	float attackTimer;
	float attackTimerReset;

	/**** METHODS(Private) ****/
	void initTexture(float scale);
	void initVars();
	void initHitboxComponent();

protected:

public:

	bool isAttacking;
	/**** CONSTRUCTOR | DESTRUCTOR ****/
	Sword(std::string item_name, unsigned int item_level, unsigned int item_value, unsigned int item_weight, 
		bool item_wieldable, bool item_consumable, 
		sf::Texture& item_texture, float scale = 1);
	virtual ~Sword();

	/**** ACCESSORS ****/
	const bool& getSwordEquipped() const; 
	const bool& getSwordState() const;
	const bool& getAttackTimer();

	const sf::FloatRect getSwordHitBox() const;


	void toggleEquip();
	void toggleAttacking();

	/**** METHODS ****/

	/*** Updates ***/
	void Update(const float& dt, sf::Vector2i mouse_pos_window);
	void updateMousePos(sf::Vector2i mouse_pos_window);
	void updateAttackTimer(const float& dt);
	void updateSwordRanges(sf::FloatRect playerBounds);
	void updateHitbox(float rotation = -1);

	void animateSword(sf::FloatRect playerBounds);
	void rotateSword(sf::FloatRect playerBounds);
	void floatSword();
	void attack();
	void resetSword();

	/*** Renders ***/
	void Render(sf::RenderTarget& target);

};


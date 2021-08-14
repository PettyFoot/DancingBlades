#include "stdafx.h"
#include "Player.h"

void Player::initSounds()
{
	if (!this->buffer.loadFromFile("Resources/Sound/running.wav"))
	{
		throw "ERROR::InitSounds()::PLAYER could not load player running footsteps sound ";
	}
	
	this->footSteps.setBuffer(this->buffer);
}

void Player::initSword()
{
	if (!this->swordTexture.loadFromFile("Resources/Images/Sprites/Weapons/Sword/sword.png"))
	{
		throw "ERROR::PLAYER::InitSword() could not load sword texture file";
	}
	else
	{
		/* "Sword", 3, 25, 4, true, false, &this->swordTexture, &this->entity */
		this->sword = new Sword("Sword", 3, 25, 4, true, false, this->swordTexture);
	}
	
}

Player::Player(float x, float y, sf::Texture& texture)
{
	this->initSounds();
	this->setTexture(texture);
	this->setPosition(x, y);

	this->createMovementComponent(200.f, 1100.f, 750.f);
	this->createAnimationComponent(texture);
	this->createHitBoxComponent(this->entity, 0.f, 0.f, 32.f, 45.f);

	this->initSword();

	this->animationComponent->addAnimation("WALK_DOWN", 5.f, 0, 0, 3, 0, 32, 48);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 3, 1, 32, 48);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 2, 3, 2, 32, 48);
	this->animationComponent->addAnimation("WALK_UP", 5.f, 0, 3, 3, 3, 32, 48);

	
}

Player::~Player()
{
	delete this->sword;
}

const int& Player::getMovementState() const
{
	if (this->movementComponent->getState(MOVING_LEFT)) //Left
	{
		return 1;
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) //Right
	{
		return 2;
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		return 3;
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		return 4;
	}
	else if (this->movementComponent->getState(IDLE))
	{
		return 0;
	}
}

void Player::toggleSwordEquip()
{
	this->sword->toggleEquip();
}

void Player::toggleAttacking()
{
	this->sword->toggleAttacking();
}



void Player::Update(const float& dt, int sword_attack_style)
{
	this->movementComponent->Update(dt); //Applies physics to velocity (deceleration) and moves the sprite that represents the player
	this->updateAnimation(dt); //check for movement and play animation sequence in accordance
	this->updateSounds(); //Check for sound queues based off player/world actions
	this->hitboxComponent->update(); //Updates the players hitbox based off player's sprite position
	
	/* If sword is equipped update its position and attack style */
	if (this->sword->getSwordEquipped())
	{
		this->updateSword(dt, sword_attack_style);
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(MOVING_LEFT)) //Left
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x,
		this->movementComponent->getMaxVelocity(), false);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) //Right
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x,
		this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().x,
			this->movementComponent->getMaxVelocity());
		
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().x,
			this->movementComponent->getMaxVelocity());
	}
}

void Player::updateSounds()
{
	/* Footsteps */
	if (this->footSteps.getStatus() != sf::Sound::Playing)
	{
		this->footSteps.setLoop(true);
		this->footSteps.play();
	}
	if (this->movementComponent->getState(IDLE))
	{
		this->footSteps.stop();
	}
}

void Player::updateSword(const float& dt, int sword_attack_style)
{
	this->sword->Update(dt);
	this->sword->updateSwordRanges(this->getEntityGlobalBounds());
	this->sword->updateSwordAttack(sword_attack_style);
	this->sword->animateSword(this->getEntityGlobalBounds());
}

void Player::Render(sf::RenderTarget& target)
{
	/* If a sword is equipped draw it*/
	if (this->sword->getSwordEquipped())
	{
		this->sword->Render(target);
	}

	this->hitboxComponent->render(target);
	target.draw(this->entity);
}

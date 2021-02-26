#pragma once

#include <SFML/Graphics.hpp> 
#include "Animation.h"

class Player
{
public:
	enum class PlayerAnimationState { walk, run, jump, idle }; 
	PlayerAnimationState animationState = PlayerAnimationState::idle;
	Animation animations[5];
	AnimationSheet animSheet;
	sf::Sprite& spriteSheet;
	int robotWalkingSpeed = 1;
	int robotRunningSpeed = 3;

	Player(sf::Sprite& spheet) : spriteSheet(spheet) 
	{ }

	void InitAnimationData() 
	{
		animations[int(PlayerAnimationState::walk)] = { 8, 36,5,true };
		animations[int(PlayerAnimationState::run)] = { 3,24,3,true };
		animations[int(PlayerAnimationState::jump)] = { 3,1,20,false };
		animations[int(PlayerAnimationState::idle)] = { 1,0,80,true };
		animationState = PlayerAnimationState::idle;
		animSheet.Init(spriteSheet.getGlobalBounds().width, spriteSheet.getGlobalBounds().height, 5, 9);
		spriteSheet.setPosition(160, 500);
		spriteSheet.setOrigin(50, 48);


	}

	void startAnimaton(PlayerAnimationState _animationState) 
	{ 
		animationState = _animationState;
		animSheet.StartAnimation(animations[int(animationState)]);
	}

	void Draw(sf::RenderWindow& win) 
	{ 
		animSheet.nextFrame();
		spriteSheet.setTextureRect(animSheet.GetFrame());
		win.draw(spriteSheet); 
	}

	void Update(sf::Time t_deltaTime)
	{
		if (animationState == PlayerAnimationState::walk) 
		{
			robotWalking();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
				{ 
					animationState = PlayerAnimationState::jump;
					startAnimaton(animationState);
				} 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
				{ 
					animationState = PlayerAnimationState::run; 
					startAnimaton(animationState); 
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				animationState = PlayerAnimationState::idle;
				startAnimaton(animationState);
			}
		}
		else if (animationState == PlayerAnimationState::run) 
		{ 
			robotRunning();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
				{ 
					animationState = PlayerAnimationState::jump;
					startAnimaton(animationState);
				} 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
				{ 
					animationState = PlayerAnimationState::walk;
					startAnimaton(animationState); 
				} 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					animationState = PlayerAnimationState::idle;
					startAnimaton(animationState);
				}
			}
		else if (animationState == PlayerAnimationState::jump) 
			{ 
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
					{ 
						animationState = PlayerAnimationState::walk;
						startAnimaton(animationState);
					} 
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
				{
					animationState = PlayerAnimationState::idle;
					startAnimaton(animationState);
				}
			}
		else if (animationState == PlayerAnimationState::idle) 
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
					{
						animationState = PlayerAnimationState::walk;
						startAnimaton(animationState);
					}
			}
	}

	void robotWalking()
	{
		if (spriteSheet.getPosition().x >= 1350)
		{
			robotWalkingSpeed = -robotWalkingSpeed;
			//spriteSheet.move(robotWalkingSpeed, 0);
			spriteSheet.setScale(-1, 1);
		}

		//spriteSheet.move(robotWalkingSpeed, 0);

		if (spriteSheet.getPosition().x < 50)
		{
			robotWalkingSpeed = -robotWalkingSpeed;
			spriteSheet.setScale(1, 1);
		}
	}

	void robotRunning()
	{
		if (spriteSheet.getPosition().x >= 1350)
		{
			robotRunningSpeed = -robotRunningSpeed;
			//spriteSheet.move(robotRunningSpeed, 0);
			spriteSheet.setScale(-1,1);
		}

		//spriteSheet.move(robotRunningSpeed, 0);

		if (spriteSheet.getPosition().x < 50)
		{
			robotRunningSpeed = -robotRunningSpeed;
			spriteSheet.setScale(1,1);
		}
	}
	
};


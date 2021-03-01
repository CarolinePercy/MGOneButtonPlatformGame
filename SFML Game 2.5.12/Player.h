#pragma once

#include <SFML/Graphics.hpp> 
#include "Animation.h"

enum class PlayerAnimationState { run, jump };

class Player
{
public:
	PlayerAnimationState animationState = PlayerAnimationState::run;
	Animation animations[5];
	AnimationSheet animSheet;
	sf::Sprite& spriteSheet;
	int robotWalkingSpeed = 1;
	int robotRunningSpeed = 3;

	Player(sf::Sprite& spheet) : spriteSheet(spheet) 
	{ }

	void InitAnimationData() 
	{
		animations[int(PlayerAnimationState::run)] = { 3,24,3,true };
		animations[int(PlayerAnimationState::jump)] = { 3,1,20,false };
		animationState = PlayerAnimationState::run;
		animSheet.Init(spriteSheet.getGlobalBounds().width, spriteSheet.getGlobalBounds().height, 5, 9);
		spriteSheet.setPosition(160, 500);

		spriteSheet.setScale(0.4, 0.4);


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

		if (animationState == PlayerAnimationState::run) 
		{ 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
				{ 
					animationState = PlayerAnimationState::jump;
					startAnimaton(animationState);
				} 			
			}		
				
	}

	void playerHitGround()
	{
		if (animationState == PlayerAnimationState::jump)
		{
			startAnimaton(PlayerAnimationState::run);
		}
	}
	
};


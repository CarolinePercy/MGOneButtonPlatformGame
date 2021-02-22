#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Animation
{
public:
	int numframes;
	int startOffset;
	int speed;
	bool loop;
};

class AnimationSheet 
{
public: 
	int frameCounter; 
	sf::Vector2i frameSize{ }; 
	int numRows = 0;
	int numCols = 0;
	Animation curAnimation;
	int curFrameOffset = 0;

	void Init(int _pixelWidth, int _pixelHeight, int _numRows, int _numCols)
	{
		numCols = _numCols;
		numRows = _numRows;
		frameSize.x = _pixelWidth / numCols;
		frameSize.y = _pixelHeight / numRows; 
		curFrameOffset = 0;
	}

	sf::IntRect GetFrame() 
	{ 
		int row = curFrameOffset / numCols;
		int col = curFrameOffset % numCols;
		sf::IntRect frameRectangle;
		frameRectangle.left = col * frameSize.x;
		frameRectangle.top = row * frameSize.y;
		frameRectangle.width = frameSize.x;
		frameRectangle.height = frameSize.y;
		return frameRectangle;
	} 

	void StartAnimation(Animation curAnimation) 
	{ 
		this->curAnimation = curAnimation;
		frameCounter = 0;
		curFrameOffset = curAnimation.startOffset;
	} 

	void nextFrame() 
	{ 
		if (frameCounter > curAnimation.speed) 
			{ 
				frameCounter = 0;
				if (curFrameOffset >= curAnimation.startOffset + curAnimation.numframes - 1)
					{ 
						if (curAnimation.loop == true) 
							{ 
								curFrameOffset = curAnimation.startOffset;
							} 
						else 
							{ 
								curFrameOffset = curAnimation.startOffset + curAnimation.numframes - 1;
							}
							}
						else 
							{ 
								std::cout << curFrameOffset << std::endl;
								curFrameOffset++;
							} 
				} else 
					{ 
						frameCounter++;
					} 
		}

};


// Noel O' Hara
//first simple game. 

//Group Project : https://instituteoftechnol663-my.sharepoint.com/:f:/g/personal/c00248791_itcarlow_ie/ErOw-dZHWh9Ejr-qmJL3aG0B4Fkfe80gcEovs1G4qBorNQ?e=htt1ea

//Caroline Percy
//Eoin Galavan
//Masih Shafieian 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include"Trigonometry.hpp"
#include"VectorAlgebra2D.h" 
#include "Player.h"

static double const MS_PER_UPDATE = 10.0;

class Game
{

public:


	Player player;
	sf::Texture playerTextureSheet;
	sf::Sprite playerSpriteSheet;

	sf::Texture coinTexture;
	sf::Sprite coinSprite;
	Animation coinAnimation = { 5, 0, 2, true };
	AnimationSheet coinSheet;
	

	//create Window 
	sf::RenderWindow window;
	sf::View view;
	float randomNum;
	//sf::RectangleShape playerShape;
	float pixelsPerMeter = 5;
	sf::Vector2f jumpPushOff{ 0, -2.4 * pixelsPerMeter };
	//sf::Vector2f gravity{ 0.0f, 9.8f * pixelsPerMeter };
	float gravity = 9.8f * pixelsPerMeter;
	sf::Vector2f velocity = { 0,0 };
	sf::Vector2f position{ 160, 500 };

	sf::Color gameColours[5] = {sf::Color(152, 107, 219), sf::Color(), sf::Color(), sf::Color(), sf::Color()};

	sf::Text gameText;
	sf::Font gameFont;

	bool gameEnd = false;
	sf::Text endGameText;
	sf::Font endGameFont;


	static const int numRows = 57;
	static const int numCols = 20;

	int score = 0;

	int levelData[numRows][numCols] =
	{
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,1,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,1,1,1,0,0 },
		{ 0,0,0,1,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,0,0,0,0,5,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0,0,0,0,5,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,0,0,0,0,5,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,1,0,4,0,0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0 },
		{ 0,0,1,1,1,1,1,0,0,0,0,0,0,0,6,0,0,0,0,0 },
		{ 0,0,1,1,1,1,1,0,0,0,0,0,0,0,6,0,0,0,0,0 }


	};

	sf::RectangleShape level[numRows][numCols];

	Game():
		player(playerSpriteSheet)
	{
		window.create(sf::VideoMode(800, 600), "Endless Runner Game");

		if (!playerTextureSheet.loadFromFile("ASSETS\\IMAGES\\character_robot_sheet.png"))
		{
			// error... player texture
		}

		if (!coinTexture.loadFromFile("ASSETS\\IMAGES\\MonedaD.png"))
		{
			// error... player texture
		}

		playerSpriteSheet.setTexture(playerTextureSheet);
		window.setVerticalSyncEnabled(true);
		//starField.Init(m_window);
		player.InitAnimationData();
		player.startAnimaton(PlayerAnimationState::run);
		window.setVerticalSyncEnabled(true);

		coinSprite.setTexture(coinTexture);
		coinSprite.setScale(2, 2);
		coinSheet.Init(coinSprite.getGlobalBounds().width, coinSprite.getGlobalBounds().height, 1, 10);
		coinSheet.StartAnimation(coinAnimation);
	
		if (!gameFont.loadFromFile("ASSETS/FONTS/ariblk.ttf"))
		{
			std::cout << "error loading font";
		}
		gameText.setFont(gameFont);
		gameText.setCharacterSize(30);

		if (!endGameFont.loadFromFile("ASSETS/FONTS/ariblk.ttf"))
		{
			std::cout << "error loading font";
		}
		endGameText.setFont(gameFont);
		endGameText.setCharacterSize(100);
		endGameText.setString("Game Over!");
		endGameText.setPosition(90, 100);
	}
	void init()
	{
		view = window.getDefaultView();
		//playerShape.setSize(sf::Vector2f(20, 20));
		playerSpriteSheet.setPosition(160, 500);
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (levelData[row][col] == 1)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color(255,19,3));
				}
				if (levelData[row][col] == 0)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Black);
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Color(28,112,255));
				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Color(39,255,13));
				}
				if (levelData[row][col] == 4)
				{
					level[row][col].setSize(sf::Vector2f(30, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Color(255,252,28));
				}
				if (levelData[row][col] == 5)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Color(126, 21, 255));
				}
				if (levelData[row][col] == 6)
				{
					level[row][col].setSize(sf::Vector2f(70, 70));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Color(155,255,10));
				}
			}
			std::cout << std::endl;
		}
	}
	void run()
	{

		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		sf::Clock clock;
		clock.restart();
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			timeSinceLastUpdate += clock.restart();
			if (timeSinceLastUpdate > timePerFrame)
			{
				float timeChange = (float)timeSinceLastUpdate.asSeconds();
				update(timePerFrame); //60 fps

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						level[row][col].move(-3.7, 0);
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocity.y == 0)
				{
					//velocity.y = -11.8;
					velocity.y = jumpPushOff.y;
					position = position + velocity * timeChange;
				}
				velocity.y = velocity.y + gravity;
				playerSpriteSheet.move(0, velocity.y);
				gravity = 0.6;

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (velocity.y > 0)
						{
							if (levelData[row][col] == 5)
							{
								if (playerSpriteSheet.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerSpriteSheet.getPosition().y < level[row][col].getPosition().y)
									{
										gravity = 0;
										velocity.y = 0;
										playerSpriteSheet.setPosition(playerSpriteSheet.getPosition().x, level[row][col].getPosition().y);
										playerSpriteSheet.move(7, -playerSpriteSheet.getGlobalBounds().height);
										player.playerHitGround();
										break;
									}
								}
							}
							if (levelData[row][col] == 4)
							{
								if (playerSpriteSheet.getGlobalBounds().intersects(level[row][col].getGlobalBounds())
									&& level[row][col].getFillColor() != sf::Color::Black)
								{
									level[row][col].setFillColor(sf::Color::Black);
									score++;
								}
							}
							if (levelData[row][col] == 3)
							{
								if (playerSpriteSheet.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerSpriteSheet.getPosition().y < level[row][col].getPosition().y)
									{
										gravity = -4;
										velocity.y = 0;
										playerSpriteSheet.setPosition(playerSpriteSheet.getPosition().x, level[row][col].getPosition().y);
										playerSpriteSheet.move(0, -playerSpriteSheet.getGlobalBounds().height);
										player.playerHitGround();
										break;
									}
								}
							}
							if (levelData[row][col] == 1)
							{
								if (playerSpriteSheet.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerSpriteSheet.getPosition().y  < level[row][col].getPosition().y)
									{
										gravity = 0;
										velocity.y = 0;
										playerSpriteSheet.setPosition(playerSpriteSheet.getPosition().x, level[row][col].getPosition().y);
										playerSpriteSheet.move(0, -playerSpriteSheet.getGlobalBounds().height);
										player.playerHitGround();
										break;
									}
									else
									{
										init();
									}
								}
							}
						}
						if (velocity.y <= 0)
						{
							if (levelData[row][col] == 1)
							{
								if (playerSpriteSheet.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();
								}
							}
						}
						if (levelData[row][col] == 2)
						{
							if (playerSpriteSheet.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								init();
							}
						}
						if (levelData[row][col] == 3)
						{
							if (playerSpriteSheet.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								init();
							}
						}
						if (levelData[row][col] == 6)
						{
							if (playerSpriteSheet.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								gameEnd = true;
							}
						}

					}
				}
				if (playerSpriteSheet.getPosition().y > 600)
				{
					init();
				}
				

				coinSheet.nextFrame();
				coinSprite.setTextureRect(coinSheet.GetFrame());
				window.clear();
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (levelData[row][col] == 4 && level[row][col].getFillColor() != sf::Color::Black)
						{
							coinSprite.setPosition(level[row][col].getPosition());
							window.draw(coinSprite);
						}
						else
						{
							window.draw(level[row][col]);
						}
					}
				}
				//window.draw(playerSpriteSheet);
				player.Draw(window);

				gameText.setString("Score: " + std::to_string(score));
				window.draw(gameText);
				if (gameEnd)
				{
					window.clear();
					window.draw(endGameText);
					gameText.setPosition(300, 300);
					gameText.setCharacterSize(70);
					window.draw(gameText);
				}
				window.display();
				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}

	void update(sf::Time t_deltaTime)
	{	
		player.Update(t_deltaTime);
	}

	
};

int main()
{
	Game game;
	game.init();
	game.run();
	return 0;
}
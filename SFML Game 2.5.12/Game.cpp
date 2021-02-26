// Noel O' Hara
//first simple game. 

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

	//create Window 
	sf::RenderWindow window;
	sf::View view;
	float randomNum;
	sf::RectangleShape playerShape;
	float pixelsPerMeter = 5;
	sf::Vector2f jumpPushOff{ 0, -2.4 * pixelsPerMeter };
	//sf::Vector2f gravity{ 0.0f, 9.8f * pixelsPerMeter };
	float gravity = 9.8f * pixelsPerMeter;
	sf::Vector2f velocity = { 0,0 };
	sf::Vector2f position{ 160, 500 };


	sf::Text gameText;
	sf::Font gameFont;

	static const int numRows = 45;
	static const int numCols = 20;

	int score = 0;

	int levelData[numRows][numCols] =
	{
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
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,1,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,1,1,1,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0,0,0,4,5,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,1,1,1,0,5,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0 },
		{ 0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 }

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

		playerSpriteSheet.setTexture(playerTextureSheet);
		window.setVerticalSyncEnabled(true);
		//starField.Init(m_window);
		player.InitAnimationData();
		player.startAnimaton(Player::PlayerAnimationState::idle);
		window.setVerticalSyncEnabled(true);
	
		if (!gameFont.loadFromFile("ASSETS/FONTS/ariblk.ttf"))
		{
			std::cout << "error loading font";
		}
		gameText.setFont(gameFont);
	}
	void init()
	{
		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(position);
		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{
				if (levelData[row][col] == 1)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Red);
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
					level[row][col].setFillColor(sf::Color::Blue);
				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Green);
				}
				if (levelData[row][col] == 4)
				{
					level[row][col].setSize(sf::Vector2f(30, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Yellow);
				}
				if (levelData[row][col] == 5)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color::Cyan);
				}
			}
			gameText.setCharacterSize(30);
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
				playerShape.move(0, velocity.y);
				gravity = 0.6;

				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						if (velocity.y >= 0)
						{
							if (levelData[row][col] == 5)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{
										gravity = 0;
										velocity.y = 0;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(7, -playerShape.getGlobalBounds().height);
										break;
									}
								}
							}
							if (levelData[row][col] == 4)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()) 
									&& level[row][col].getFillColor() != sf::Color::Black)
								{
									level[row][col].setFillColor(sf::Color::Black);
									score++;
								}
							}
							if (levelData[row][col] == 3)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{
										gravity = -4;
										velocity.y = 0;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);
										break;
									}
								}
							}
							if (levelData[row][col] == 1)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{
										gravity = 0;
										velocity.y = 0;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);
										break;
									}
									else
									{
										init();
									}
								}
							}
						}
						if (velocity.y < 0)
						{
							if (levelData[row][col] == 1)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();
								}
							}
						}
						if (levelData[row][col] == 2)
						{
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								init();
							}
						}
						if (levelData[row][col] == 3)
						{
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								init();
							}
						}

					}
				}
				if (playerShape.getPosition().y > 600)
				{
					init();
				}
				window.clear();
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						window.draw(level[row][col]);
					}
				}
				window.draw(playerShape);
				player.Draw(window);

				gameText.setString("Score: " + std::to_string(score));
				window.draw(gameText);

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
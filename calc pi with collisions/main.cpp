#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "block.h"
#include "constants.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pi calculation", sf::Style::Close);
	{
		window.setVerticalSyncEnabled(true);
		//commit test
		//counter for the number of collisions between either 
		//both blocks or the smaller block and the wall
		int counter{ 0 };

		int desiredDigits{ 5 };

		//increase accuracy
		const int timeStep{ 10000 };

		//load font, arial
		sf::Font font;
		if (!font.loadFromFile("arial.ttf"))
		{
			return 1;
		}

		//create text for displaying total collisions
		sf::Text count;
		count.setFont(font);
		count.setCharacterSize(35);
		count.setFillColor(sf::Color::Green);

		Block blockOne(blockOneSize, initialVelocity / timeStep);
		blockOne.setMass(pow(100, desiredDigits - 1));
		blockOne.setPosition(sf::Vector2f(windowWidth / 1.5, 405));

		Block blockTwo(blockTwoSize, 0);
		blockTwo.setMass(1);
		blockTwo.setPosition(sf::Vector2f(windowWidth / 4, 455));

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					break;
				}
			}


			for (int i = 0; i < timeStep; i++)
			{
				blockOne.move(blockOne.getVelocity());
				blockTwo.move(blockTwo.getVelocity());

				if (blockOne.getShape().getPosition().x - blockOneSize / 2 <=
					blockTwo.getShape().getPosition().x + blockTwoSize / 2)
				{
					double newVOne = blockOne.bounceBlock(blockTwo);
					double newVTwo = blockTwo.bounceBlock(blockOne);
					blockOne.setVelocity(newVOne);
					blockTwo.setVelocity(newVTwo);

					counter++;
					count.setString(std::to_string(counter));
				}

				if (blockTwo.getShape().getPosition().x - blockTwoSize / 2 <= 0)
				{
					blockTwo.bounceWall();

					counter++;
					count.setString(std::to_string(counter));
				}
			}

			//log console info
			system("cls");
			std::cout << "Block one velocity: " << blockOne.getVelocity() * timeStep << std::endl;
			std::cout << "Block one position: (" << blockOne.getShape().getPosition().x <<
				"," << blockOne.getShape().getPosition().y << ")" << std::endl;
			std::cout << "Block two velocity: " << blockTwo.getVelocity() * timeStep << std::endl;
			std::cout << "Block two position: (" << blockTwo.getShape().getPosition().x <<
				"," << blockTwo.getShape().getPosition().y << ")" << std::endl;

			//clear window w/ black color
			window.clear(sf::Color::Black);

			//choose items to draw - window.draw(...)
			window.draw(blockOne.getShape());
			window.draw(blockTwo.getShape());
			window.draw(count);
			
			//actually draw the items
			window.display();
		}
	}

	return 0;
}
#include <SFML/Graphics.hpp>
#include "block.h"

Block::Block(int size, double v)
{
	block.setSize(sf::Vector2f(size, size));
	block.setOrigin(sf::Vector2f(size / 2, size / 2));
	block.setFillColor(sf::Color::Green);

	velocity = v;
}

sf::RectangleShape Block::getShape()
{
	return block;
}

void Block::move(double velocity)
{
	block.move(sf::Vector2f(velocity, 0));
}

void Block::bounceWall()
{
	//reverses velocity for perfect elastic collisioin
	velocity = -velocity;
}

double Block::bounceBlock(Block otherBlock)
{
	double sumMass{ mass + otherBlock.getMass() };
	//perfect elastic collision formula to calculate new velocity
	double newVelocity{ (((mass - otherBlock.getMass()) / sumMass) * velocity) +
		(((2 * otherBlock.getMass()) / sumMass) * otherBlock.getVelocity()) };

	return newVelocity;
}

void Block::setMass(double m)
{
	mass = m;
}

double Block::getVelocity()
{
	return velocity;
}

void Block::setPosition(sf::Vector2f position)
{
	block.setPosition(position);
}

void Block::setVelocity(double v)
{
	velocity = v;
}

double Block::getMass()
{
	return mass;
}
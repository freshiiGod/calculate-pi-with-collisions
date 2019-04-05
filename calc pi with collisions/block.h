#pragma once
#ifndef BLOCK_H
#define BLOCK_H

class Block
{
public:
	Block(int blockSize, double velocity);

	//returns the shape too draw in main
	sf::RectangleShape getShape();

	//set variables
	void setMass(double mass);
	void setPosition(sf::Vector2f position);
	void setVelocity(double velocity);

	//get variables
	double getVelocity();
	double getMass();

	//movement
	void move(double velocity);
	void bounceWall();
	double bounceBlock(Block otherBlock);

private:
	sf::RectangleShape block;
	double velocity;
	double mass;
};

#endif
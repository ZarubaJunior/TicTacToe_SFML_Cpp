#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Card.h"

class Game
{
public:
	Game();
	virtual ~Game();

	const bool isRunning() const;
	void updateEvents(float deltaTime);
	void update();
	void render();
private:
	void initWindow();
	void initVars();
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Clock clock;
	float deltaTime;
	std::vector <Card> cards;
	Card card;
	MapGUI map;;
};


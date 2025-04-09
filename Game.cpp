#include "Game.h"
void Game::initWindow()
{
	this->videoMode.height = 480;
	this->videoMode.width = 960;

	this->window = new sf::RenderWindow(this->videoMode, "TicTacToe");
	this->window->setFramerateLimit(60);
}

void Game::initVars() {
	this->window = nullptr;
	map.initSprites();
}

Game::Game()
{
	this->initVars();
	this->initWindow();

}

Game::~Game() { delete this->window; }

const bool Game::isRunning() const { return this->window && this->window->isOpen(); }

void Game::updateEvents(float deltaTime)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
	while (this->window && this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::MouseButtonPressed:
			if (this->ev.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i mousePixelPos = sf::Mouse::getPosition(*this->window);
				sf::Vector2f mouseWorldPos = this->window->mapPixelToCoords(mousePixelPos);
				map.HandleClick(mouseWorldPos);
			}
			break;
		}
	}

}

void Game::update()
{
	deltaTime = clock.restart().asSeconds();
	updateEvents(deltaTime);
}


void Game::render()
{
	if (this->window) {
		this->window->clear(sf::Color(24, 28, 46));
		map.drawMapGUI(*window);
		this->window->display();
	}
}

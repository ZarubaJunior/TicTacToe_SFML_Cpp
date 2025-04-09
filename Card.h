#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <random>
#include <SFML/Graphics.hpp>
using namespace std;

enum class CardType {
	None,
	Cross,
	Circle
};

struct CardsParametres {
	int id;
};
inline CardsParametres getCardsParametres(CardType type) {
	switch (type)
	{
	case CardType::None:
		return { 0 };
		break;
	case CardType::Cross:
		return { 1 };
		break;
	case CardType::Circle:
		break;
		return { 2 };
	}
}

inline CardType getCardTypeFromID(int id) {
	switch (id) {
	case 1: return CardType::Cross;
	case 0: return CardType::Circle;
	default:
		return CardType::None;
	}
}
class Card
{
	std::vector<CardType> cards;
};

class Map
{
	
public:
	int width = 3, height = 3;
	void SetMapSize(int x, int y);
	void SetMap();
	std::vector<std::vector<CardType>> GetMap();
	int ConsoleMapCreator(CardType type); 
	std::vector<std::vector<CardType>> tiles;
	bool checkForEmtySlotes();

	CardType getCardType(int x, int y);
	void setCardType(int x, int y, CardType type);

};
class MapGUI {
public:
	std::vector < std::vector<sf::Sprite>> cardSprites;
	std::vector < std::vector<sf::Texture>> cardTextures;
	std::vector < std::vector<sf::RectangleShape>> cardRect;
	std::string getTexture(CardType type);
	void initSprites();
	Map map;
	void drawMapGUI(sf::RenderWindow& window);
	int width = 3, height = 3;
	float scaleX = 5, scaleY = 5;
	void HandleClick(const sf::Vector2f& worldPos);
	
	CardType previousCardClicked =CardType::None;
	bool isFirstPlayer = true;
	bool isWinner(CardType type);
	bool isWin = false;
	void resetGame();
	sf::RectangleShape resetButton;
	sf::RectangleShape okButton;
	sf::Text okText;
	void initText();
	sf::Font font;
	sf::Text Player1Text;
	sf::Text Player2Text;
	sf::Text DrawCounterText;
	sf::Text EndGameText;
	sf::Text resetText;
	int player1Score = 0, player2Score =0, drawCounter=0;
	int winId;
};
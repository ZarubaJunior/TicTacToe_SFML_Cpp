#include "Card.h"

void Map::SetMapSize(int x, int y)
{
    width = x;
    height = y;
}

void Map::SetMap()
{
    tiles.resize(height);
    for (int y = 0; y < height; ++y) 
        tiles[y].resize(width, CardType::None);
    for (int y = 0; y < height; ++y)
        for (int x = 0; x < width; ++x)
            tiles[x][y] = CardType::None;
}

std::vector<std::vector<CardType>> Map::GetMap()
{
    return tiles;
}
int Map::ConsoleMapCreator(CardType type)
{
    return getCardsParametres(type).id;
}

bool Map::checkForEmtySlotes()
{
    bool isEmpty = false;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (tiles[y][x] == CardType::None) {
                isEmpty = true;
                break;
            }
        }
    }
    return isEmpty;
}

CardType Map::getCardType(int x, int y)
{
    return (tiles[y][x]);
}

void Map::setCardType(int x, int y, CardType type )
{
    tiles[y][x] = type;
}

std::string MapGUI::getTexture(CardType type)
{
    switch (type)
    {
    case CardType::None:
        return "Res//Textures//None.png";
    case CardType::Cross:
        return "Res//Textures//Cross_2.png";
    case CardType::Circle:
        return "Res//Textures//Circle_2.png";
    }
}

void MapGUI::initSprites()
{
    initText();
    map.SetMapSize(width, height);
    map.SetMap();

    cardSprites.resize(width, std::vector<sf::Sprite>(height));
    cardTextures.resize(width, std::vector<sf::Texture>(height));
    cardRect.resize(width, std::vector<sf::RectangleShape>(height));
  
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                        
            if (!cardTextures[x][y].loadFromFile(getTexture(map.getCardType(x,y))))
                std::cout << "TEXTURE ERROR \n";
            cardSprites[x][y].setTexture(cardTextures[x][y]);
            cardSprites[x][y].setPosition(sf::Vector2f(32.f * x * scaleX, 32.f * y * scaleY));
            cardSprites[x][y].setScale(scaleX, scaleY);

            cardRect[x][y].setPosition(sf::Vector2f(32.f * x * scaleX, 32.f * y * scaleY));
            cardRect[x][y].setSize(sf::Vector2f(32 * scaleX, 32 * scaleX));                   
        }
    }

        resetButton.setPosition(500, 480 - 32 * scaleX);
        resetButton.setSize(sf::Vector2f(32 * scaleX, 32 * scaleX));
        resetButton.setFillColor(sf::Color(173, 3, 49));

        okButton.setPosition(500 + 10 + 32 * scaleX, 480 - 32 * scaleX);
        okButton.setSize(sf::Vector2f(32 * scaleX, 32 * scaleX));
        okButton.setFillColor(sf::Color(26, 163, 56));
}

void MapGUI::HandleClick(const sf::Vector2f& worldPos)
{
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            if (cardRect[x][y].getGlobalBounds().contains(worldPos)) {
                CardType playerType;
                if (map.getCardType(x, y) == CardType::None && !isWin) {                    
                    if (isFirstPlayer) {
                        if (!cardTextures[x][y].loadFromFile(getTexture(CardType::Cross)))
                            std::cout << "TEXTURE ERROR \n";
                        isFirstPlayer = false;
                        playerType = CardType::Cross;
                    }                        
                    else {
                        isFirstPlayer = true;
                         if (!cardTextures[x][y].loadFromFile(getTexture(CardType::Circle)))
                            std::cout << "TEXTURE ERROR \n";
                         playerType = CardType::Circle;
                    }
                    map.setCardType(x, y, playerType);
                    if (isWinner(playerType)) {
                        std::cout << "WINNER!!!";
                        if (playerType == CardType::Cross)
                            player1Score++;
                        else 
                            player2Score++;
                    }                       
                    if (!map.checkForEmtySlotes() && !isWin) {
                        drawCounter++;
                        isWin = true;
                        winId = 0;
                        std::cout << "DRAW";
                    }                     
                    cardSprites[x][y].setTexture(cardTextures[x][y]);  
                }   
            }         
    if (resetButton.getGlobalBounds().contains(worldPos))
        resetGame();
    if (okButton.getGlobalBounds().contains(worldPos) && isWin)
        resetGame();
}


bool MapGUI::isWinner(CardType type)
{
    for (int y = 0; y < width; ++y) {
        for (int x = 0; x < width; ++x) {

            if (map.getCardType(0, y) == type && map.getCardType(1, y) == type && map.getCardType(2, y) == type)
                isWin = true;
            else if (map.getCardType(x, 0) == type && map.getCardType(x, 1) == type && map.getCardType(x, 2) == type)
                isWin = true;
            else if (map.getCardType(0, 0) == type && map.getCardType(1, 1) == type && map.getCardType(2, 2) == type)
                isWin = true;
            else if (map.getCardType(2, 0) == type && map.getCardType(1, 1) == type && map.getCardType(0, 2) == type)
                isWin = true;
        }
    }

    if (type == CardType::Cross && isWin)
        winId = 1;
    else if (type == CardType::Circle && isWin)
        winId = 2;
    else
        winId = 3;

    return isWin;
}

void MapGUI::resetGame()
{
    isWin = false;
    map.SetMap();
    initSprites();
    
    std::string player1ScoreString = std::to_string(player1Score);
    std::string player2ScoreString = std::to_string(player2Score);
    std::string drawCounterString = std::to_string(drawCounter);

    Player1Text.setString("Player 1 Score: " + player1ScoreString);
    Player2Text.setString("Player 2 Score: " + player2ScoreString);
    DrawCounterText.setString("Draw Score: " + drawCounterString);
}

void MapGUI::initText()
{
    if (!font.loadFromFile("Minecraft.ttf"))
        std::cout << "TEXTURE ERROR \n";

    Player1Text.setFont(font);
    Player1Text.setString("Player 1 Score: 0");
    Player1Text.setCharacterSize(10 * scaleX);
    Player1Text.setPosition(500, 0);
    Player1Text.setFillColor(sf::Color(197, 143, 217));
    Player1Text.setStyle(sf::Text::Bold);

    Player2Text.setFont(font);
    Player2Text.setString("Player 2 Score: 0");
    Player2Text.setCharacterSize(10 * scaleX);
    Player2Text.setPosition(500, 10 * scaleX);
    Player2Text.setFillColor(sf::Color(197, 143, 217));
    Player2Text.setStyle(sf::Text::Bold);

    DrawCounterText.setFont(font);
    DrawCounterText.setString("Draw Score: 0");
    DrawCounterText.setCharacterSize(10 * scaleX);
    DrawCounterText.setPosition(500, 10 * scaleX *2);
    DrawCounterText.setFillColor(sf::Color(197, 143, 217));
    DrawCounterText.setStyle(sf::Text::Bold);

    okText.setFont(font);
    okText.setString("OK");
    okText.setOrigin(10 * scaleX, 10 * scaleX);
    okText.setCharacterSize(10 * scaleX);
    okText.setPosition(500 + 10 + 32 * scaleX + 16 * scaleX, 480 - 32 * scaleX + 20 * scaleX);
    okText.setFillColor(sf::Color(176, 207, 182));
    okText.setStyle(sf::Text::Bold);

    resetText.setFont(font);
    resetText.setString("RESET");
    resetText.setOrigin(10 * scaleX, 10 * scaleX);
    resetText.setCharacterSize(9 * scaleX);
    resetText.setPosition(500 + 10 * scaleX, 480 - 32 * scaleX + 20 * scaleX);
    resetText.setFillColor(sf::Color(196, 116, 136));
    resetText.setStyle(sf::Text::Bold);

    EndGameText.setFont(font);
    EndGameText.setString("Won");
    EndGameText.setCharacterSize(12 * scaleX);
    EndGameText.setOutlineThickness(1 * scaleX);
    EndGameText.setPosition(500, 10 * scaleX * 3);
    EndGameText.setStyle(sf::Text::Bold);

}
void MapGUI::drawMapGUI(sf::RenderWindow& window)
{
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            window.draw(cardSprites[x][y]);
    
    window.draw(resetButton);
    window.draw(Player1Text);
    window.draw(Player2Text);
    window.draw(DrawCounterText);
    window.draw(resetText);
    if (isWin) {
        window.draw(okButton);
        window.draw(okText);
        if (winId == 1) {
            EndGameText.setFillColor(sf::Color(29, 141, 58));
            EndGameText.setOutlineColor(sf::Color(7, 36, 14));
            EndGameText.setString("Player 1 Won");
        }
           
        else if (winId == 2) {
           
            EndGameText.setFillColor(sf::Color(141, 29, 132));
            EndGameText.setOutlineColor(sf::Color(54, 11, 50));
            EndGameText.setString("Player 2 Won");
        }
          
        else {
            EndGameText.setOutlineColor(sf::Color(71, 48, 79));
            EndGameText.setFillColor(sf::Color(197, 143, 217));
            EndGameText.setString("Draw");
        }
           
        window.draw(EndGameText);
    }
}
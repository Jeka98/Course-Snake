#include "main.h"
#include "Utilities.h"
#include <fstream>
#include <sstream>
#include <string>
#include <Windows.h>
#include "shellapi.h"
#include "DirectoryHelper.h"
//---------------------------

void browser(void);

//Open website, where you can find explanatory note
void browser()
{
	ShellExecute(NULL, "open", "D:\\БГУИР\\КПрог\\Курсач_сдача\\Snake\\x64\\Release\\Website v2.0\\index.html", NULL, NULL, SW_SHOWNORMAL);
}

Menu::Menu()
{
	//Load background, fonts
	m_background.loadFromFile(DirectoryHelper::GetImage("snakemain"));
	m_sprite.setTexture(m_background);
	m_fontSnakeMix.loadFromFile(DirectoryHelper::GetFont("Snake Mix"));
	m_fontEarth2073.loadFromFile(DirectoryHelper::GetFont("Earth 2073"));

	m_text[0].setFont(m_fontSnakeMix);
	m_text[0].setFillColor(sf::Color(0, 110, 0, 255));
	m_text[0].setString("Snake!");
	m_text[0].setCharacterSize(70);
	m_text[0].setPosition(WIDTH / 2 - m_text[0].getLocalBounds().width / 2, 0);

	//Set position of buttons
	for (int i = 1; i < MAX_NUM_OF_ITEMS; i++)
	{
		m_text[i].setFont(m_fontEarth2073);
		m_text[i].setFillColor(sf::Color(0, 110, 0, 255));
		m_text[i].setCharacterSize(25);
		m_text[i].setPosition(50, (HEIGHT / 3) *(i - (i - 1)* 0.5) + (MAX_NUM_OF_ITEMS - i) * 10);
	}

	m_text[1].setString("Play");
	m_text[2].setString("High Score");
	m_text[3].setString("Help & Note");
	m_text[4].setString("Exit");
}
//---------------------------
void Menu::input(sf::RenderWindow & window, int highScore)
{
	sf::Event event;

	while (window.waitEvent(event))
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//button ...Play...
				if (m_text[1].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					return;
				//button ...High Score...
				if (m_text[2].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					handleHighScore(window, event, highScore);
				
				//button ...HELP...
				if (m_text[3].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
						browser();
				//button ...Exit...	
				else if (m_text[4].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					window.close();
			}
		}
}
//---------------------------
void Menu::handleHighScore(sf::RenderWindow & window, sf::Event & event, int highScore)
{
	//Window of high score
	m_textHighScore.setFont(m_fontEarth2073);
	m_textClose.setFont(m_fontEarth2073);
	m_textClose.setString("Close");
	m_textClose.setPosition(20, 300);
	m_textClose.setFillColor(sf::Color(0, 110, 0, 255));

	std::stringstream _string;
	_string << "High Score: " << highScore;
	std::string newString = _string.str();
	m_textHighScore.setString(newString);
	m_textHighScore.setPosition(WIDTH / 36 - m_textHighScore.getLocalBounds().width / 36, HEIGHT / 4);
	m_textHighScore.setFillColor(sf::Color(0, 110, 0, 255));
	drawHighScore(window);

	while (window.waitEvent(event))
		if (m_textClose.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
		{
			drawMenu(window);
			return;
		}
}
//---------------------------
void Menu::drawMenu(sf::RenderWindow & window) const
{
	window.clear();
	window.draw(m_sprite);

	for (int i = 0; i < MAX_NUM_OF_ITEMS; ++i)
		window.draw(m_text[i]);

	window.display();
}
//---------------------------
void Menu::drawHighScore(sf::RenderWindow & window) const
{
	window.clear();
	window.draw(m_sprite);
	window.draw(m_textClose);
	window.draw(m_textHighScore);
	window.display();
}
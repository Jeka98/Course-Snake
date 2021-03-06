#pragma once

#include <SFML/Audio.hpp>

#include "Controller.h"
#include "Fruit.h"
#include "Snake.h"
#include <thread>
#include <sstream>
#include <string>
#include <iostream>
#include "DirectoryHelper.h"

//---------------------------

Controller::Controller()
{
	m_window.create(sf::VideoMode(WIDTH, HEIGHT), "Snake", sf::Style::Close);
	//*****************************************************************
	//sound in game
	m_soundBuffer1.loadFromFile(DirectoryHelper::GetSound("OldMcDonaldHadAFarm"));
	m_gameSound.setBuffer(m_soundBuffer1);
	m_gameSound.play();
	m_gameSound.setLoop(true);
	//*****************************************************************
	// Set
	m_sprite.setTexture(Resources::Images.Background);
	m_spriteReset.setTexture(Resources::Images.Reset);
	m_spritePower.setTexture(Resources::Images.Power);
	m_spriteReset.setPosition(WIDTH_RESET, MARGIN_TOP);
	m_spritePower.setPosition(WIDTH_POWER, MARGIN_TOP);

	initText(m_text, std::string(""), 15);

	m_snake = Snake(ImageResources::Texture);
	m_fruit.update(m_snake);
	m_fruit = Fruit(Resources::Images.Texture, m_fruit.get());
	
	m_file.open(DirectoryHelper::ResolvePath("High_Score.txt"), std::fstream::in);
	if (!m_file)
		throw std::exception("Failed to open file 'High_Score.txt'!");
	
	std::string score;
	m_file >> score;
	std::string::size_type sz;
	m_highScore = stoi(score, &sz);
	m_file.close();
}
//---------------------------
void Controller::run()
{
	m_menu.drawMenu(m_window);
	m_menu.input(m_window, m_highScore);

	while (m_window.isOpen())
	{
		while (m_window.isOpen() && !m_gameOver)
		{
			draw();
			input();
			logic();
		}

		sf::Text text, text2;

		initText(text, std::string("GAME OVER"), 40);
		text.setPosition(WIDTH / 2 - text.getGlobalBounds().width / 2, 200);

		std::stringstream _string;
		if (m_score > m_highScore)
		{
			_string << "New Record : " << m_score;
			m_file.open("High_Score.txt", std::fstream::out);
			m_file << m_score;
			m_file.close();
		}
		else
			_string << "Score: " << m_score;

		std::string newString = _string.str();

		initText(text2, newString, 30);
		text2.setPosition(WIDTH / 2 - text2.getGlobalBounds().width / 2, text.getGlobalBounds().left + 160);

		draw();
		m_window.draw(text);
		m_window.draw(text2);
		m_window.draw(m_spriteReset);
		m_window.draw(m_spritePower);
		m_window.display();

		sf::Event event;
		while (m_window.waitEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
				return;
			}
			if (m_spriteReset.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
			{
				clean();
				break;
			}
			if (m_spritePower.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
			{
				clean();
				m_menu.drawMenu(m_window);
				m_menu.input(m_window, m_highScore);
				break;
			}
		}
	}
}
//---------------------------
//Moving buttons
void Controller::input()
{
	sf::Event event;

	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	if (m_window.pollEvent(event))

		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;

		case sf::Event::KeyPressed:

			switch (event.key.code)
			{
			case sf::Keyboard::Down:
				if (m_direction == UP)
					break;
				m_direction = DOWN;
				break;

			case sf::Keyboard::Left:
				if (m_direction == RIGHT)
					break;
				m_direction = LEFT;
				break;

			case sf::Keyboard::Right:
				if (m_direction == LEFT)
					break;
				m_direction = RIGHT;
				break;

			case sf::Keyboard::Up:
				if (m_direction == DOWN)
					break;
				m_direction = UP;
				break;
			}
		}
}

//---------------------------

// status value : 0 = Game Over, 1 = Succeded move, 2 = Succeed move + ate fruit
void Controller::logic()
{
	int status = 1;

	switch (m_direction)
	{
	case LEFT:
		status = m_snake.move(m_fruit, sf::Vector2f(-(float)PIC_SIZE, 0), m_direction);
		break;

	case RIGHT:
		status = m_snake.move(m_fruit, sf::Vector2f((float)PIC_SIZE, 0), m_direction);
		break;

	case UP:
		status = m_snake.move(m_fruit, sf::Vector2f(0, -(float)PIC_SIZE), m_direction);
		break;

	case DOWN:
		status = m_snake.move(m_fruit, sf::Vector2f(0, (float)PIC_SIZE), m_direction);
		break;
	}

	if (status == 0)
		m_gameOver = true;
	else if (status == 1)
		updateScore(0);
	else
		updateScore(SCORE_UP);
}
//---------------------------
void Controller::draw()
{
	m_window.clear();

	m_window.draw(m_sprite);
	m_snake.draw(m_window);
	m_fruit.draw(m_window);
	m_window.draw(m_text);

	m_window.display();
}
//---------------------------
void Controller::updateScore(int i)
{
	m_score += i;
	std::stringstream _string;
	
	_string << "SCORE: " << m_score;
	std::string newString = _string.str();
	m_text.setString(newString);
}
//---------------------------
void Controller::clean()
{
	m_snake = Snake(Resources::Images.Texture);
	m_fruit.update(m_snake);
	m_fruit = Fruit(Resources::Images.Texture, m_fruit.get());
	m_direction = STOP;
	m_score = 0;
	m_gameOver = false;
}
//---------------------------
void Controller::initText(sf::Text & text, std::string & string, unsigned int size)
{
	text.setFont(Resources::Font);
	text.setString(string);
	text.setCharacterSize(size);
}
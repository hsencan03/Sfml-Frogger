#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "GameObject.hpp"

class Frog : public GameObject {
public:
	Frog(std::string path, sf::Vector2f position)
	{
		if (!m_texture.loadFromFile(path))
		{
			std::cout << path << " don't exsist" << '\n';
		}
		else
		{
			m_sprite.setTexture(m_texture);
			m_maiPos = position;
		}

		Reset();
	}

	virtual void Update(sf::RenderWindow& window, float dt)
	{
		m_sprite.setPosition(getPosition());
	}

	virtual void HandleEvent(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::W: // UP
					move(0, -m_sprite.getGlobalBounds().height);
					break;
				case sf::Keyboard::S: // DOWN
					move(0, m_sprite.getGlobalBounds().height);
					break;
				case sf::Keyboard::A: //LEFT
					move(-m_sprite.getLocalBounds().width, 0);
					break;
				case sf::Keyboard::D: //RIGHT
					move(m_sprite.getGlobalBounds().height, 0);
					break;
				default:
					break;
				}
			default:
				break;
			}
		}
	}

	virtual void Draw(sf::RenderWindow& window)
	{
		window.draw(*this);
	}

	virtual void Reset()
	{
		setPosition(m_maiPos);
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const 
	{
		target.draw(m_sprite, states);
	}

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_maiPos;

	friend class Car;
};
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

class Car : public GameObject {
public:
	Car(std::string path, sf::Vector2f position, unsigned int speed, Frog& frog, unsigned int rotation)
		: m_frog{frog}, m_mainPos{position}, m_speed{speed}
	{
		if (!m_texture.loadFromFile(path))
		{
			std::cout << path << " don't exsist" << '\n';
		}
		else
			m_sprite.setTexture(m_texture);

		Reset();
	}
	
	virtual void Update(sf::RenderWindow& window, float dt)
	{
		m_sprite.setPosition(getPosition());
		
		if (getPosition().x > window.getSize().x)
			setPosition(0, m_mainPos.y);

		if (m_sprite.getGlobalBounds().intersects(m_frog.m_sprite.getGlobalBounds()))
		{
			std::cout << "Collision\n";
			m_frog.Reset();
		}

		move(m_speed * dt, 0);
	}

	virtual void HandleEvent(sf::RenderWindow& window)
	{
		sf::Event event;
		while(window.poolEvent(event))
		{
			if(event.type == sf::Event::Close)
				Game::isPlaying = false;
		}
	}

	virtual void Draw(sf::RenderWindow& window)
	{
		window.draw(*this);
	}

	virtual void Reset()
	{
		setPosition(m_mainPos);
	}


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_sprite, states);
	}

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_mainPos;

	Frog& m_frog;

	int m_speed;
};

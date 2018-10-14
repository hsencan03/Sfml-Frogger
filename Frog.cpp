#include "Frog.hpp"

Frog::Frog(std::string path, sf::Vector2f position)
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

void Frog::Update(sf::RenderWindow& window, float dt)
{
	m_sprite.setPosition(getPosition());
}

void Frog::HandleEvent(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			Game::instance->isPlaying = false;
			break;
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

void Frog::Draw(sf::RenderWindow& window)
{
	window.draw(*this);
}

void Frog::Reset()
{
	setPosition(m_maiPos);
}

void Frog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
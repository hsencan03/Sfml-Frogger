#include "Car.hpp"

#include "Frog.hpp"

Car::Car(std::string path, sf::Vector2f position, unsigned int speed, unsigned int rotation)
	: m_mainPos{ position }, m_speed{ speed }, m_rotation{rotation}
{
	if (!m_texture.loadFromFile(path))
	{
		std::cout << path << " don't exsist" << '\n';
	}
	else
		m_sprite.setTexture(m_texture);

	Reset();
}

void Car::Update(sf::RenderWindow& window, float dt)
{
	m_sprite.setPosition(getPosition());

	if (getPosition().x > window.getSize().x)
		setPosition(0, m_mainPos.y);
	else if (getPosition().x < 0)
		setPosition(window.getSize().x, m_mainPos.y);

	if (m_sprite.getGlobalBounds().intersects(Game::instance->m_frog->m_sprite.getGlobalBounds()))
	{
		std::cout << "Collision\n";
		Game::instance->m_frog->Reset();
	}
	
	if (m_rotation == 1)
		move(m_speed * dt, 0);
	else if (m_rotation == 2)
		move(-1 * (m_speed * dt), 0);
	else
		std::cout << "Error rotation has to be 1 or 2\n";
}

void Car::HandleEvent(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		Game::instance->isPlaying = false;
	}
}

void Car::Draw(sf::RenderWindow& window)
{
	window.draw(*this);
}

void Car::Reset()
{
	setPosition(m_mainPos);
}

void Car::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}
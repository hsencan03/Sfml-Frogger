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
#include "Game.hpp"

class Frog : public GameObject {
public:
	Frog(std::string path, sf::Vector2f position);

	virtual void Update(sf::RenderWindow& window, float dt) override;

	virtual void HandleEvent(sf::RenderWindow& window) override;

	virtual void Draw(sf::RenderWindow& window) override;

	virtual void Reset() override;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_maiPos;

	friend class Car;
};

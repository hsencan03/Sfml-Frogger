#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace sf
{
	class RenderWindow;
}

class GameObject : public sf::Drawable, public sf::Transformable {
public:
	virtual void Update(sf::RenderWindow& window, float dt) = 0;
	virtual void HandleEvent(sf::RenderWindow& window) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Reset() = 0;
};
#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>

class Frog;
class Car;
class GameObject;

class Game {
public:
	static void constructor(int width, int height, std::string title);

	static Game* getInstance();

	~Game();

private:
	void run();
	void reset();

private:
	static Game* instance;

	Game(int width, int height, std::string title);

private:
	sf::RenderWindow* m_window;

	std::vector<GameObject*> m_cars;
	Frog* m_frog;

	bool isPlaying = true;
	float deltaTime{ 1 };

	sf::Music music;

	friend class Car;
	friend class Frog;
};
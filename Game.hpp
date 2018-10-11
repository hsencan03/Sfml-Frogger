#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/Music.hpp>

#include "Frog.hpp"
#include "Car.hpp"

class Game {
public:
	static bool isPlaying;		
public:
	Game(int width, int height, std::string title)
	{
		//Creating window
		m_window.create(sf::VideoMode(width, height), title);
		m_window.setFramerateLimit(30);

		if (!music.openFromFile("assets/music.ogg"))
		{
			std::cout << "assets / music.ogg is not exsist \n";
		}

		m_frog = new Frog("assets/life.png", sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y - 50));
		for (int i = 0; i < 1; i++)
		{
			m_cars.emplace_back(new Car("assets/car1.png", sf::Vector2f(m_window.getSize().x / 2, m_window.getSize().y / 2), 100, *m_frog));
		}

		run();
	}
	~Game()
	{
		if (m_frog != nullptr)
			delete m_frog;
	}

private:
	void run() 
	{
		music.setLoop(true);
		music.setVolume(20);
		music.play();

		sf::Clock deltaClock;
		while (isPlaying)
		{
			m_frog->Update(m_window, deltaTime);
			for (int i = 0; i < m_cars.size(); i++)
				m_cars[i]->Update(m_window, deltaTime);


			m_frog->HandleEvent(m_window);

			m_window.clear();

			m_frog->Draw(m_window);
			for (int i = 0; i < m_cars.size(); i++)
			m_cars[i]->Draw(m_window);
			
			m_window.display();

			deltaTime = deltaClock.restart().asSeconds();
		}
	}

	void reset()
	{
		m_frog->Reset();
		for(int i = 0; i < m_cars.size(); i++)
			m_cars[i]->Reset();
	}

private:
	sf::RenderWindow m_window;

	Frog* m_frog;
	std::vector<GameObject*> m_cars;

	bool isPlaying{ false };
	float deltaTime{ 1 };

	sf::Music music;
};

Game::isPlaying = true;

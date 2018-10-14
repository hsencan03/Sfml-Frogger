#include "Game.hpp"

#include "Frog.hpp"
#include "Car.hpp"

Game::Game(int width, int height, std::string title)
{
	//Creating window
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
	m_window->setFramerateLimit(30);

	if (!music.openFromFile("assets/music.ogg"))
	{
		std::cout << "assets / music.ogg is not exsist \n";
	}

	m_frog = new Frog("assets/life.png", sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y - 50));
	
	m_cars.emplace_back(new Car("assets/car1.png", sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 - 100), 100, 1));
	m_cars.emplace_back(new Car("assets/car2.png", sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 - 50), 100, 2));
	m_cars.emplace_back(new Car("assets/tractor.png", sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2), 50, 1));
	m_cars.emplace_back(new Car("assets/truck.png", sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 + 50), 75, 2));
	m_cars.emplace_back(new Car("assets/car1.png", sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 + 100), 100, 1));
	m_cars.emplace_back(new Car("assets/car3.png", sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 + 150), 100, 2));
	
}

Game::~Game()
{
	if (m_window != nullptr)
		delete m_window;
	if (m_frog != nullptr)
		delete m_frog;
	if (instance != nullptr)
		delete instance;
}

void Game::run()
{
	music.setLoop(true);
	music.setVolume(20);
	music.play();

	sf::Clock deltaClock;
	while (isPlaying)
	{
		m_frog->Update(*m_window, deltaTime);
		for (int i = 0; i < m_cars.size(); i++)
			m_cars[i]->Update(*m_window, deltaTime);


		m_frog->HandleEvent(*m_window);

		m_window->clear();

		m_frog->Draw(*m_window);
		for (int i = 0; i < m_cars.size(); i++)
			m_cars[i]->Draw(*m_window);

		m_window->display();

		deltaTime = deltaClock.restart().asSeconds();
	}
}

void Game::reset()
{
	m_frog->Reset();
	for (int i = 0; i < m_cars.size(); i++)
		m_cars[i]->Reset();
}

Game* Game::instance = nullptr;

void Game::constructor(int width, int height, std::string title)
{
	instance = new Game(width, height, title);
	Game::instance->run();
}

Game* Game::getInstance()
{
	if (instance == nullptr)
		std::cout << "You need to call constructor\n";

	return instance;
}
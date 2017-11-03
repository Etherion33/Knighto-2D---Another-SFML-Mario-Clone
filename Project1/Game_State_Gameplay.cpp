#include <SFML\Graphics.hpp>

#include <iostream>
#include "Game_State_Menu.h"
#include "Game_State_Gameplay.h"
#include "Game_State.h"

void Game_State_Gameplay::draw(const float dt)
{
	this->game->window.clear(sf::Color::Black);
	this->game->window.setView(this->guiView);
	this->game->window.draw(this->game->background);

	this->game->window.setView(this->gameView);
	level.draw(this->game->window, dt);
	player.draw(this->game->window, dt);

	return;
}

void Game_State_Gameplay::update(const float dt)
{
	sf::Vector2f pos(0.f, 0.f);
	ImGui::SFML::Update(this->game->window, sf::seconds(dt));
	this->gameView.setCenter(player.getPosition());
	this->player.update(dt);
	this->level.update(dt);

	ImGui::Begin("Debug window");
	ImGui::Text("FPS: %lf", 1.f / dt);
	ImGui::Text("Window position: X : %d", this->game->window.getPosition().x); ImGui::SameLine(200); ImGui::Text("Y: %d", this->game->window.getPosition().y);
	ImGui::Text("Player position: X : %lf", this->player.getPosition().x); ImGui::SameLine(220); ImGui::Text("Y: %lf", this->player.getPosition().y);
	ImGui::Text("Level width: %d", level.m_width); ImGui::SameLine(220); ImGui::Text(" height: %d", level.m_height);
	ImGui::End();
	ImGuiIO& io = ImGui::GetIO();

	if (io.MouseDown[1])
	{
		ImGui::OpenPopup("Context menu");
		std::cout << "Prawy " << std::endl;
		ImGui::BeginPopup("Context menu");
		ImGui::MenuItem("Test menu");
		ImGui::Separator();
		if (ImGui::MenuItem("Main menu"))
		{
			this->game->popState();
		}
		if (ImGui::MenuItem("Exit"))
		{
			this->game->window.close();
		}
		ImGui::Text("Placeholder");
		ImGui::Text("Placeholder");
		ImGui::Text("Placeholder");
		ImGui::Text("Placeholder");

		ImGui::EndPopup();
	}

	//std::cout << "\nPlayer X: " << this->player.getPlayerPos().x << " Y: " << this->player.getPlayerPos().y << std::endl;
	return;
}

void Game_State_Gameplay::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		bool noKeyWasPressed = true;

		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			this->game->window.close();
			break;
		}
		/* Resize the window */
		case sf::Event::Resized:
		{
			gameView.setSize(event.size.width, event.size.height);
			guiView.setSize(event.size.width, event.size.height);
			this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
			this->game->background.setScale(
				float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
				float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				player.move(-player.getSpeed().x, 0);
				noKeyWasPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				player.move(player.getSpeed().x, 0);
				noKeyWasPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				player.move(0, -player.getSpeed().y);
				noKeyWasPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				player.move(0, player.getSpeed().y);
				noKeyWasPressed = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				noKeyWasPressed = false;
			}

			if (noKeyWasPressed)
			{
				player.stop();
			}
			noKeyWasPressed = true;
			break;
		}
		default: break;
		}
	}

	return;
}

Game_State_Gameplay::Game_State_Gameplay(Game* game, std::string selectedLevel)
{
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->guiView.setSize(pos);
	this->gameView.setSize(pos);
	pos *= 0.5f;
	this->guiView.setCenter(pos);

	level = Level(selectedLevel, game->tileAtlas);
	player = Player(this->game->texmgr.getRef("knight"), this->game->texmgr.getRef("knightSS"));
	player.setPosition({ 100.f, 100.f });
	level.addEntity(new Player(this->game->texmgr.getRef("orc"), this->game->texmgr.getRef("orcSS")));

	//sf::Vector2f center(this->player.getPlayerPos().x*0.5, this->player.getPlayerPos().y*0.5);
	//gameView.setCenter(center);

	sf::Vector2f centre(this->level.m_width / 2, this->level.m_height / 2);
	centre *= float(this->level.m_TileSize);
	gameView.setCenter(centre);
	gameView.zoom(0.25f);
	//player.setPosition(centre);

	this->actionState = ActionState::NONE;
}
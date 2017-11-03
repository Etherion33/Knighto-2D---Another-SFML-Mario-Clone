#include <SFML\Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "Game_State.h"
#include "Game_State_Menu.h"
#include "Game_State_Gameplay.h"
#include "Game_State_Editor.h"

sf::Vector2i new_level_size(64, 16);
char new_level_filename[255];
static bool create_level_window = false;
static bool load_level_window = false;

void Game_State_Menu::draw(const float dt)
{
	this->game->window.clear(sf::Color::Black);

	this->game->window.setView(this->view);

	this->game->window.draw(this->game->background);
	//this->game->window.resetGLStates();
	//ImGui::SFML::Render(this->game->window);
	return;
}

void Game_State_Menu::update(const float dt)
{
	//std::cout << "dt:" << dt << std::endl;

	ImGui::SFML::Update(game->window, sf::seconds(dt));
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
	ImGui::Begin("Main menu");
	ImGui::Text("Knighto - 2D Platformer with basic gui");
	if (ImGui::Button("New game"))
	{
		create_level_window = true;
	}
	if (ImGui::Button("Load game"))
	{
		load_level_window = true;
		//this->loadgame();
	}
	if (ImGui::Button("Level editor"))
	{
		this->editLevel();
		return;
	}
	if (ImGui::Button("Exit game"))
	{
		this->game->window.close();
	}
	if (create_level_window)
	{
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
		ImGui::Begin("New level creator", &create_level_window);
		ImGui::Text("Create new level");

		if (ImGui::CollapsingHeader("Settings"))
		{
			if (ImGui::TreeNode("Properties"))
			{
				ImGui::InputText("Filename", new_level_filename, 255);
				ImGui::InputInt("Width", &new_level_size.x);
				ImGui::InputInt("Height", &new_level_size.y);

				ImGui::TreePop();
			}
		}
		if (ImGui::Button("Create!"))
		{
			sf::Clock creationTime;
			Level level;
			level.create(new_level_filename, new_level_size.x, new_level_size.y, this->game->tileAtlas);
			sf::Time elapsedCTime = creationTime.getElapsedTime();
			std::cout << "Level created in " << elapsedCTime.asSeconds() << "\n Level size: " << new_level_size.x << "x" << new_level_size.y << std::endl;
			create_level_window = false;
		}
		ImGui::End();
	}
	if (load_level_window)
	{
		std::string fname;
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
		ImGui::Begin("Load game", &load_level_window);
		std::vector<std::string> level_filenames;
		std::vector<int> level_filesize;

		int nLevels = 0;
		for (auto &p : std::experimental::filesystem::directory_iterator("."))
		{
			fname = p.path().string();
			if (fname.find(".dat") != std::string::npos)
			{
				std::cout << fname << std::endl;
				fname = fname.substr(2, fname.size());
				level_filenames.push_back(fname);
				level_filesize.push_back(std::experimental::filesystem::file_size(p));
				nLevels++;
			}
		}
		ImGui::Text("Load selected game level");
		ImGui::BeginChild("child", ImVec2(0, 20 * nLevels), true);
		static bool* selected = new bool[nLevels]();
		int chosen = 0;
		for (int i = 0; i < nLevels; i++) {
			ImGui::Selectable(level_filenames.at(i).c_str(), &selected[i]); ImGui::SameLine(300); ImGui::Text(" %d bytes", level_filesize.at(i));
			if (selected[i] == true)
			{
				chosen = i;
			}
		}
		ImGui::EndChild();
		ImGui::Text("Chosen level:"); ImGui::SameLine(100); ImGui::Text(level_filenames.at(chosen).c_str());
		if (ImGui::Button("Load!"))
		{
			this->loadgame(level_filenames.at(chosen));
		}
		if (ImGui::Button("Delete!"))
		{
			std::string command = "del " + level_filenames.at(chosen);
			system(command.c_str());
		}
		ImGui::End();
	}
	ImGui::End();
	ImGui::ShowTestWindow();
}

void Game_State_Menu::handleInput()
{
	sf::Event event;

	while (this->game->window.pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);

		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
		/* Resize the window */
		case sf::Event::Resized:
		{
			this->view.setSize(event.size.width, event.size.height);
			this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0)));
			this->game->background.setScale(
				float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
				float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape) this->game->window.close();
			break;
		}
		default: break;
		}
	}

	return;
}

Game_State_Menu::Game_State_Menu(Game* game)
{
	ImGui::NewFrame();

	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}

void Game_State_Menu::loadgame(std::string filename)
{
	std::cout << "Loaded level:" << filename << std::endl;
	this->game->pushState(new Game_State_Gameplay(this->game, filename));
}

void Game_State_Menu::editLevel()
{
	this->game->pushState(new Game_State_Editor(this->game));
}
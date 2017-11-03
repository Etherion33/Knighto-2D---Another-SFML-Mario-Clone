#include "Game_State_Editor.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "Game_State.h"
#include "Game_State_Menu.h"
#include "Game_State_Gameplay.h"

static bool game_editor_level_creator = false;
static bool game_editor_level_loader = false;
static bool game_editor_window = false;

static void Game_Editor_Level_Creator(bool* p_open);

void Game_State_Editor::draw(const float dt)
{
	this->game->window.clear(sf::Color::Black);

	this->game->window.setView(this->view);

	this->game->window.draw(this->game->background);

	m_Level.draw(this->game->window, dt);
}

void Game_State_Editor::update(const float dt)
{
	ImGui::SFML::Update(this->game->window, sf::seconds(dt));
	if (game_editor_level_creator) Game_Editor_Level_Creator(&game_editor_level_creator);
	if (game_editor_level_loader) load_level(&game_editor_level_loader);
	if (game_editor_window) edit_level(this->game, &game_editor_window);

	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Knighto - Level Editor", NULL, false, false);
			ImGui::MenuItem("New level", NULL, &game_editor_level_creator);	//Create new level
			ImGui::MenuItem("Open", "Ctrl+O", &game_editor_level_loader); // Load existing level
			if (ImGui::BeginMenu("Open Recent"))
			{
				//Open last edited level
				ImGui::MenuItem("fish_hat.c");
				ImGui::MenuItem("fish_hat.inl");
				ImGui::MenuItem("fish_hat.h");
				if (ImGui::BeginMenu("More.."))
				{
					ImGui::MenuItem("Hello");
					ImGui::MenuItem("Sailor");
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				//Save level as is
			}
			if (ImGui::MenuItem("Save As.."))
			{
				//Save level with new name
			}
			ImGui::Separator();
			if (ImGui::BeginMenu("Options"))
			{
				static bool enabled = true;
				ImGui::MenuItem("Enabled", "", &enabled);
				ImGui::BeginChild("child", ImVec2(0, 60), true);
				for (int i = 0; i < 10; i++)
					ImGui::Text("Scrolling Text %d", i);
				ImGui::EndChild();
				static float f = 0.5f;
				static int n = 0;
				static bool b = true;
				ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
				ImGui::InputFloat("Input", &f, 0.1f);
				ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
				ImGui::Checkbox("Check", &b);
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("Quit", "Alt+F4"))
			{
				this->game->window.close();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

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
	ImGui::ShowTestWindow();
}

void Game_State_Editor::handleInput()
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

Game_State_Editor::Game_State_Editor(Game * game)
{
	ImGui::NewFrame();
	this->game = game;
	sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
	this->view.setSize(pos);
	pos *= 0.5f;
	this->view.setCenter(pos);
}

void Game_Editor_Level_Creator(bool * p_open)
{
	ImGui::SetNextWindowSize(ImVec2(430, 450), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Level Creator", p_open))
	{
		ImGui::End();
		return;
	}
	ImGui::Text("Test window text");

	ImGui::End();
}

void Game_State_Editor::load_level(bool * p_open)
{
	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Load level", p_open))
	{
		ImGui::End();
		return;
	}
	std::string fname;
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
		m_Level = Level(level_filenames.at(chosen), game->tileAtlas);
		game_editor_level_loader = false;
		game_editor_window = true;
	}
	if (ImGui::Button("Delete!"))
	{
		std::string command = "del " + level_filenames.at(chosen);
		system(command.c_str());
	}
	ImGui::End();
}

void Game_State_Editor::edit_level(Game* game, bool *p_open)
{
	sf::Clock frameTime;
	sf::Time elapsed = frameTime.restart();
	if (!ImGui::Begin("Level editor", p_open))
	{
		ImGui::End();
		return;
	}
	bool open_popup = ImGui::Button("Tile Atlas");

	if (open_popup)
	{
		ImGui::OpenPopup("mypicker");
	}
	if (ImGui::BeginPopup("mypicker"))
	{
		// FIXME: Adding a drag and drop example here would be perfect!
		ImGui::Text("Tile Atlas");
		ImGui::Separator();
		ImGui::BeginGroup();
		ImGui::Text("Current");
		// current tile
		ImGui::Separator();
		ImGui::Text("Tileset");
		for (auto it = this->game->tileAtlas.begin(); it != this->game->tileAtlas.end(); ++it)
		{
			ImGui::Selectable(it->first.c_str());
		}
		ImGui::EndGroup();
		ImGui::EndPopup();
	}
	Tile tile;

	for (int y = 0; y < m_Level.m_height; y++)
	{
		for (int x = 0; x < m_Level.m_width; x++)
		{
			static int new_tileType;
			tile = m_Level.GetTile(x, y);
			new_tileType = (int)tile.m_TileType;
			ImGui::Image(tile.m_TileSprite);
			//ImGui::Text("%d", new_tileType); 
			//ImGui::InputTextMultiline("pole:", &new_tileType,m_Level.m_height * m_Level.m_width);
		}
		ImGui::SameLine(10.f);
		ImGui::NewLine();
	}

	ImGui::End();
}
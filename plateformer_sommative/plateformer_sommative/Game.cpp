#include "Game.h"
#include <fstream>
#include <iostream>

//arrays that setupp map
bool box[TILEMAP_HEIGHT * TILEMAP_WIDTH] = { false };
int tiles[TILEMAP_HEIGHT * TILEMAP_WIDTH] = { 0 };

//function to save field
void save()
{
	std::ofstream save;
	std::ofstream tile_type_save;

	save.open("map.txt");
	while (save.is_open())
	{
		for (const auto element : box)
		{
			if (element)
			{
				save << "1\n";
			}
			else
			{
				save << "0\n";
			}
		}
		save.close();
	}

	tile_type_save.open("tile.txt");
	while (tile_type_save.is_open())
	{
		for (const auto element : tiles)
		{
			switch (element)
			{
			case 0:
				tile_type_save << "0\n";
				break;
			case 1:
				tile_type_save << "1\n";
				break;
			case 2:
				tile_type_save << "2\n";
				break;
			case 3:
				tile_type_save << "3\n";
				break;
			default:
				break;
			}
		}
		tile_type_save.close();
	}
}

//function to load the field
void load()
{
	std::string tile;

	std::ifstream file;
	file.open("map.txt");

	int i = 0;
	while (file.is_open())
	{
		while (file)
		{
			getline(file, tile);

			if (tile == "1")
			{
				box[i] = true;
				i++;
			}
			else
			{
				i++;
			}
		}
		file.close();
	}

	std::string tile_type;

	std::ifstream save;
	save.open("tile.txt");

	int location = 0;
	while (save.is_open())
	{
		while (save)
		{
			getline(save, tile_type);

			if (tile_type == "0")
			{
				tiles[location] = 0;
				location++;
			}
			else if (tile_type == "1")
			{
				tiles[location] = 1;
				location++;
			}
			else if (tile_type == "2")
			{
				tiles[location] = 2;
				location++;
			}
			else if (tile_type == "3")
			{
				tiles[location] = 3;
				location++;
			}
			else
			{
				location++;
			}
		}
		save.close();
	}

}

//constructor that load all shapes and textures
Game::Game()
{
	//load of all textures
	plateform_texture.loadFromFile("sprite/plateform.png");
	right.loadFromFile("sprite/mob_Right.png");
	left.loadFromFile("sprite/mob_Left.png");
	coin_texture.loadFromFile("sprite/coin.png");
	air.loadFromFile("sprite/air.png");
	ground_surface_texture.loadFromFile("sprite/ground_surface.png");
	ground.loadFromFile("sprite/ground.png");
	start_texture.loadFromFile("sprite/portail_start.png");
	end_texture.loadFromFile("sprite/portail_start.png");
	eye_texture.loadFromFile("sprite/eye_boost.png");
	illusion_left_texture.loadFromFile("sprite/left_arrow.png");
	illusion_down_texture.loadFromFile("sprite/down_arrow.png");
	double_jump_texture.loadFromFile("sprite/double_jump_texture.png");
	speed_power_texture.loadFromFile("sprite/speed_texture.png");
	backgorund_texture.loadFromFile("sprite/background.png");
	initial_check_point_texture.loadFromFile("sprite/check_point0.png");
	check_point_touched_texture.loadFromFile("sprite/check_point1.png");


	//regular tile shape
	tile_shape.setSize(sf::Vector2f(TILE_SIZE_PX, TILE_SIZE_PX));
	tile_shape.setFillColor(sf::Color(209, 147, 67));
	tile_shape.setTexture(&plateform_texture);

	//create check point
	initial_check_point.setSize(sf::Vector2f(20.0f, 35.0f));
	initial_check_point.setPosition(2124.0f, 149.0f);
	initial_check_point.setOrigin(initial_check_point.getSize().x / 2, initial_check_point.getSize().y);
	initial_check_point.setTexture(&initial_check_point_texture);

	//start block
	start.setSize(sf::Vector2f(TILE_SIZE_PX, 75.0f));
	start.setFillColor(sf::Color(255, 255, 255));
	start.setTexture(&start_texture);
	start.setPosition(0.0f, 0.0f);

	//tp block
	teleportation.setSize(sf::Vector2f(TILE_SIZE_PX, 75.0f));
	teleportation.setFillColor(sf::Color(0, 255, 0));
	teleportation.setTexture(&start_texture);
	teleportation.setPosition(2500.0f, 705.0f);

	//end block
	end.setSize(sf::Vector2f(TILE_SIZE_PX, 75.0f));
	end.setFillColor(sf::Color(255, 0, 0));
	end.setTexture(&start_texture);
	end.setPosition(4774.0f, 100.0f);

	//eye power up block
	eye.setSize(sf::Vector2f(40.0f, 20.0f));
	eye.setFillColor(sf::Color(255, 255, 255));
	eye.setTexture(&eye_texture);
	eye.setPosition(3650.0f, 150.0f);

	//double jump power up
	double_jump.setSize(sf::Vector2f(TILE_SIZE_PX, TILE_SIZE_PX));
	double_jump.setFillColor(sf::Color(255, 255, 255));
	double_jump.setTexture(&double_jump_texture);
	double_jump.setPosition(14.0f, 800.0f);

	//speed power up
	speed_power.setSize(sf::Vector2f(TILE_SIZE_PX, TILE_SIZE_PX));
	speed_power.setFillColor(sf::Color(255, 255, 255));
	speed_power.setTexture(&speed_power_texture);
	speed_power.setPosition(3925.0f, 1400.0f);

	//arrow named illusions that goes to the left (lore)
	illusions_left.setSize(sf::Vector2f(TILE_SIZE_PX, 50.0f));
	illusions_left.setFillColor(sf::Color(0, 0, 0, 0));
	illusions_left.setTexture(&illusion_left_texture);
	illusions_left.setPosition(3627.0, 50.0f);

	//arrow named illusions that goes down (lore)
	illusion_down.setSize(sf::Vector2f(TILE_SIZE_PX, 50.0f));
	illusion_down.setFillColor(sf::Color(0, 0, 0, 0));
	illusion_down.setTexture(&illusion_down_texture);
	illusion_down.setPosition(997.0f, 50.0f);

	// Create cursor shape
	cursor_shape.setSize(sf::Vector2f(TILE_SIZE_PX, TILE_SIZE_PX));
	cursor_shape.setFillColor(sf::Color(209, 147, 67, 0));
	cursor_shape.setOutlineColor(sf::Color(250, 250, 250));
	cursor_shape.setOutlineThickness(-3);

	//player square shape
	the_square.setSize(sf::Vector2f(25, 25));
	the_square.setFillColor(sf::Color(255, 255, 255));
	the_square.setOrigin(the_square.getSize().x / 2, the_square.getSize().y);
	the_square.setTexture(&right);

	//create a coin
	coin.setSize(sf::Vector2f(30.0f, 50.0f));
	coin.setFillColor(sf::Color(255, 255, 255));
	coin.setTexture(&coin_texture);
	coin.setPosition(100.0f, 100.0f);
	coin.setOrigin(coin.getSize().x / 2, coin.getSize().y / 2);

	//background setupp
	background.setSize(sf::Vector2f(EDGE_MAP_LENGTH, EDGE_MAP_HEIGHT));
	background.setPosition(0.0f, -10.0f);
	background.setTexture(&backgorund_texture);
}

//set window
void Game::init()
{
	window_.create(sf::VideoMode(1200, 1200), "Windows");
	window_.setFramerateLimit(30);

}

//set view
void Game::SetView()
{
	sf::View view(sf::Vector2f(the_square.getPosition().x, the_square.getPosition().y), sf::Vector2f(window_.getSize().x, window_.getSize().y));
	window_.setView(view);
}

//set all events
void Game::HandleEvent()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window_.close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::U)
			{
				save();
			}
			if (event.key.code == sf::Keyboard::Space)
			{
				if (grounded_)
				{
					player_vel_.y = -15;
					jumped_once_ = true;
				}
				if (jumped_once_)
				{
					if (is_double_jump_active_ && !grounded_)
					{
						player_vel_.y = -15;
						jumped_once_ = false;
					}
				}
			}
		}
	}
}

//set limit for collisions
void Game::SetCollisionLimit(float& limit_x_low, float& limit_x_high, float& limit_y_low, float& limit_y_high)
{
	limit_x_low = -1000000000.f;
	limit_x_high = 1000000000.f;
	limit_y_low = -1000000000.f;
	limit_y_high = 1000000000.f;

	sf::Vector2i player_coords = pos_to_coords(player_pos_);
	constexpr int margin = 1;

	if (tile_at(player_coords + sf::Vector2i(1, 0)))
	{
		limit_x_high = (player_coords.x + 1) * TILE_SIZE_PX - margin;
	}
	if (tile_at(player_coords + sf::Vector2i(-1, 0)))
	{
		limit_x_low = (player_coords.x) * TILE_SIZE_PX + margin;
	}
	if (tile_at(player_coords + sf::Vector2i(0, 1)))
	{
		limit_y_high = (player_coords.y + 1) * TILE_SIZE_PX - margin;
	}
	if (tile_at(player_coords + sf::Vector2i(0, -1)))
	{
		limit_y_low = (player_coords.y) * TILE_SIZE_PX + margin;
	}
}

//set player movement
void Game::player_movement(sf::Vector2f& delta)
{
	delta = sf::Vector2f(0, 0);
	constexpr float player_speed = 5;
	constexpr float player_boost_speed = 10.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		the_square.setTexture(&left);

		if (!is_speed_active_)
		{
			delta += sf::Vector2f(-player_speed, 0);
		}
		else if (is_speed_active_)
		{
			delta += sf::Vector2f(-player_boost_speed, 0);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		the_square.setTexture(&right);

		if (!is_speed_active_)
		{
			delta += sf::Vector2f(player_speed, 0);
		}
		else if (is_speed_active_)
		{
			delta += sf::Vector2f(player_boost_speed, 0);
		}
	}
}

//set gravity
void Game::gavity_and_falling_max_speed()
{
	// Falling speed limit
	if (player_vel_.y > 10.0f)
	{
		player_vel_.y = 10.0f;
	}

	// Gravity
	player_vel_.y += 1.0f;
}

//set player collision with tiles
void Game::set_player_movement_and_collision_with_tile(float limit_x_low, float limit_x_high, float limit_y_low, float limit_y_high, sf::Vector2f& delta)
{
	delta += sf::Vector2f(0, player_vel_.y);

	player_pos_ += delta;
	if (player_pos_.x >= limit_x_high - (the_square.getSize().x / 2))
	{
		player_pos_.x = limit_x_high - (the_square.getSize().x / 2);
	}
	if (player_pos_.x <= limit_x_low + (the_square.getSize().x / 2))
	{
		player_pos_.x = limit_x_low + (the_square.getSize().x / 2);
	}
	grounded_ = false;
	if (player_pos_.y >= limit_y_high)
	{
		player_pos_.y = limit_y_high;
		grounded_ = true;
	}
	if (player_pos_.y <= limit_y_low + the_square.getSize().y) {
		player_pos_.y = limit_y_low + the_square.getSize().y;
		player_vel_.y = 0;
	}
}

//level editor system
void Game::mouse_hovering_system(sf::Vector2i& mouse_tile)
{
	// Determine tile coordinates that the mouse is hovering
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
	mouse_tile = sf::Vector2i((mouse_pos.x + the_square.getPosition().x - window_.getSize().x / 2) / TILE_SIZE_PX, (mouse_pos.y + the_square.getPosition().y - window_.getSize().y / 2) / TILE_SIZE_PX);


	//quand je clique gauche -> colision, clique droit -> pas colision.
	bool mouse_left = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool mouse_right = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	if (mouse_left || mouse_right)
	{

		box[mouse_tile.y * TILEMAP_WIDTH + mouse_tile.x] = mouse_left;


		if (in_bounds(mouse_tile))
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
			{
				tiles[mouse_tile.y * TILEMAP_WIDTH + mouse_tile.x] = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
			{
				tiles[mouse_tile.y * TILEMAP_WIDTH + mouse_tile.x] = 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
			{
				tiles[mouse_tile.y * TILEMAP_WIDTH + mouse_tile.x] = 2;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
			{
				tiles[mouse_tile.y * TILEMAP_WIDTH + mouse_tile.x] = 3;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
			{
				tiles[mouse_tile.y * TILEMAP_WIDTH + mouse_tile.x] = 4;
			}
		}
	}
}

//draw elements
void Game::draw_background_and_tile()
{
	window_.draw(background);

	// draw the tilemap
	for (int y = 0; y < TILEMAP_HEIGHT; y++)
	{
		for (int x = 0; x < TILEMAP_WIDTH; x++)
		{
			int index = y * TILEMAP_WIDTH + x;

			if (tiles[index] == 0)
			{
				tile_shape.setPosition(x * TILEMAP_HEIGHT, y * TILEMAP_HEIGHT);
				tile_shape.setTexture(&air);
				tile_shape.setFillColor(sf::Color(255, 255, 255, 0));
				window_.draw(tile_shape);
			}
			if (tiles[index] == 1)
			{
				tile_shape.setFillColor(sf::Color(255, 255, 255, 244));
				tile_shape.setPosition(x * TILEMAP_HEIGHT, y * TILEMAP_HEIGHT);
				tile_shape.setTexture(&plateform_texture);
				tile_shape.setOrigin(0.0f, PLATEFORM_HEIGHT_SETUPP);
				window_.draw(tile_shape);
			}
			if (tiles[index] == 2)
			{
				tile_shape.setFillColor(sf::Color(255, 255, 255, 244));

				tile_shape.setPosition(x * TILEMAP_HEIGHT, y * TILEMAP_HEIGHT);
				tile_shape.setTexture(&ground_surface_texture);
				window_.draw(tile_shape);
			}
			if (tiles[index] == 3)
			{
				tile_shape.setFillColor(sf::Color(255, 255, 255, 244));

				tile_shape.setPosition(x * TILEMAP_HEIGHT, y * TILEMAP_HEIGHT);
				tile_shape.setTexture(&ground);
				window_.draw(tile_shape);
			}
		}
	}
}
void Game::draw_cursor_tile(sf::Vector2i mouse_tile)
{
	// draw selection cursor
	cursor_shape.setPosition(mouse_tile.x * TILE_SIZE_PX, mouse_tile.y * TILE_SIZE_PX);
	window_.draw(cursor_shape);
}

//system that chek coins one by one
void Game::system_to_calculate_coins_one_by_one()
{
	if (!coin1_)
	{
		coin.setPosition(721.0f, 50.0f);
		window_.draw(coin);
		if (the_square.getPosition().y <= coin.getPosition().y + coin.getSize().y / 2 && the_square.getPosition().y >= coin.getPosition().y - coin.getSize().y / 2)
		{
			if (the_square.getPosition().x <= coin.getPosition().x + coin.getSize().x / 2 && the_square.getPosition().x >= coin.getPosition().x - coin.getSize().x / 2)
			{
				coin.setPosition(-100.0f, -100.0f);
				number_of_coins_collected_++;
				coin1_ = true;
			}
		}

	}
	if (!coin2_)
	{
		coin.setPosition(1000.0f, 150.0f);
		window_.draw(coin);
		if (the_square.getPosition().y <= coin.getPosition().y + coin.getSize().y / 2 && the_square.getPosition().y >= coin.getPosition().y - coin.getSize().y / 2)
		{
			if (the_square.getPosition().x <= coin.getPosition().x + coin.getSize().x / 2 && the_square.getPosition().x >= coin.getPosition().x - coin.getSize().x / 2)
			{
				coin.setPosition(-100.0f, -100.0f);
				number_of_coins_collected_++;
				coin2_ = true;

			}
		}
	}
	if (!coin3_)
	{
		coin.setPosition(1500.0f, 150.0f);
		window_.draw(coin);
		if (the_square.getPosition().y <= coin.getPosition().y + coin.getSize().y / 2 && the_square.getPosition().y >= coin.getPosition().y - coin.getSize().y / 2)
		{
			if (the_square.getPosition().x <= coin.getPosition().x + coin.getSize().x / 2 && the_square.getPosition().x >= coin.getPosition().x - coin.getSize().x / 2)
			{
				coin.setPosition(-100.0f, -100.0f);
				number_of_coins_collected_++;
				coin3_ = true;

			}
		}
	}
	if (!coin4_)
	{
		coin.setPosition(3830.0f, 300.0f);
		window_.draw(coin);
		if (the_square.getPosition().y <= coin.getPosition().y + coin.getSize().y / 2 && the_square.getPosition().y >= coin.getPosition().y - coin.getSize().y / 2)
		{
			if (the_square.getPosition().x <= coin.getPosition().x + coin.getSize().x / 2 && the_square.getPosition().x >= coin.getPosition().x - coin.getSize().x / 2)
			{
				coin.setPosition(-100.0f, -100.0f);
				number_of_coins_collected_++;
				coin4_ = true;

			}
		}
	}
	if (!coin5_)
	{
		coin.setPosition(2770.0f, 1350.0f);
		window_.draw(coin);
		if (the_square.getPosition().y <= coin.getPosition().y + coin.getSize().y / 2 && the_square.getPosition().y >= coin.getPosition().y - coin.getSize().y / 2)
		{
			if (the_square.getPosition().x <= coin.getPosition().x + coin.getSize().x / 2 && the_square.getPosition().x >= coin.getPosition().x - coin.getSize().x / 2)
			{
				coin.setPosition(-100.0f, -100.0f);
				number_of_coins_collected_++;
				coin5_ = true;

			}
		}
	}
	if (!coin6_)
	{
		coin.setPosition(128.0f, 1050.0f);
		window_.draw(coin);
		if (the_square.getPosition().y <= coin.getPosition().y + coin.getSize().y / 2 && the_square.getPosition().y >= coin.getPosition().y - coin.getSize().y / 2)
		{
			if (the_square.getPosition().x <= coin.getPosition().x + coin.getSize().x / 2 && the_square.getPosition().x >= coin.getPosition().x - coin.getSize().x / 2)
			{
				coin.setPosition(-100.0f, -100.0f);
				number_of_coins_collected_++;
				coin6_ = true;

			}
		}
	}
}

//player collision for power_ups/checkpoint
void Game::collision_for_power_up_and_checkpoint()
{
	//collision of eye power up
	if (the_square.getPosition().y <= eye.getPosition().y + eye.getSize().y / 2 && the_square.getPosition().y >= eye.getPosition().y - eye.getSize().y / 2)
	{
		if (the_square.getPosition().x <= eye.getPosition().x + eye.getSize().x / 2 && the_square.getPosition().x >= eye.getPosition().x - eye.getSize().x / 2)
		{
			eye.setPosition(-100.0f, -2000.0f);
			eye_of_god_ = true;
		}
	}

	//collision of double jump power up
	if (the_square.getPosition().y <= double_jump.getPosition().y + double_jump.getSize().y / 2 && the_square.getPosition().y >= double_jump.getPosition().y - double_jump.getSize().y / 2)
	{
		if (the_square.getPosition().x <= double_jump.getPosition().x + double_jump.getSize().x / 2 && the_square.getPosition().x >= double_jump.getPosition().x - double_jump.getSize().x / 2)
		{
			double_jump.setPosition(-100.0f, -2000.0f);
			is_double_jump_active_ = true;
		}
	}

	//collision for the speed boost
	if (the_square.getPosition().y <= speed_power.getPosition().y + speed_power.getSize().y / 2 && the_square.getPosition().y >= speed_power.getPosition().y - speed_power.getSize().y / 2)
	{
		if (the_square.getPosition().x <= speed_power.getPosition().x + speed_power.getSize().x / 2 && the_square.getPosition().x >= speed_power.getPosition().x - speed_power.getSize().x / 2)
		{
			speed_power.setPosition(-100.0f, -2000.0f);
			is_speed_active_ = true;
		}
	}

	if (the_square.getPosition().y <= initial_check_point.getPosition().y && the_square.getPosition().y >= initial_check_point.getPosition().y - initial_check_point.getSize().y / 2)
	{
		if (the_square.getPosition().x <= initial_check_point.getPosition().x + initial_check_point.getSize().x / 2 && the_square.getPosition().x >= initial_check_point.getPosition().x - initial_check_point.getSize().x / 2)
		{
			check_point_active_ = true;
			initial_check_point.setTexture(&check_point_touched_texture);
		}
	}
}

//player collision for end and tp
void Game::collision_for_end_and_portal()
{
	if (the_square.getPosition().y <= end.getPosition().y + end.getSize().y / 2 && the_square.getPosition().y >= end.getPosition().y - end.getSize().y / 2)
	{
		if (the_square.getPosition().x <= end.getPosition().x + end.getSize().x / 2 && the_square.getPosition().x >= end.getPosition().x - end.getSize().x / 2)
		{
			window_.close();
		}
	}

	//collision of the teleportation portal
	if (the_square.getPosition().y <= teleportation.getPosition().y + teleportation.getSize().y / 2 && the_square.getPosition().y >= teleportation.getPosition().y - teleportation.getSize().y / 2)
	{
		if (the_square.getPosition().x <= teleportation.getPosition().x + teleportation.getSize().x / 2 && the_square.getPosition().x >= teleportation.getPosition().x - teleportation.getSize().x / 2)
		{
			the_square.setPosition(50.0f, 50.0f);
			player_pos_ = sf::Vector2f(0.0f, 0.0f);
		}
	}
}

//set death
void Game::effect_of_death()
{
	the_square.setPosition(player_pos_);

	int number_of_death = 0;

	//place to manage if you fall
	if (the_square.getPosition().y >= EDGE_MAP_RESPAWN)
	{
		if (!check_point_active_)
		{
			the_square.setPosition(50.0f, 50.0f);
			player_pos_ = sf::Vector2f(0.0f, 0.0f);
			number_of_death++;
		}
		else
		{
			the_square.setPosition(initial_check_point.getPosition().x, initial_check_point.getPosition().y);
			player_pos_ = sf::Vector2f(initial_check_point.getPosition().x, initial_check_point.getPosition().y);
			number_of_death++;
		}
		coin1_ = false;
		coin2_ = false;
		coin3_ = false;
		coin4_ = false;
		coin5_ = false;
		coin6_ = false;
		number_of_coins_collected_ = 0;
		if (number_of_death == 3)
		{
			window_.close();
		}
	}
}

//power up for game design
void Game::effect_of_vision_power()
{
	if (eye_of_god_)
	{
		illusions_left.setFillColor(sf::Color(255, 255, 255, 244));
		illusion_down.setFillColor(sf::Color(255, 255, 255, 244));
	}
}

//graphical frame
void Game::graphical_frame()
{
	window_.draw(initial_check_point);
	window_.draw(speed_power);
	window_.draw(teleportation);
	window_.draw(double_jump);
	window_.draw(illusions_left);
	window_.draw(illusion_down);
	window_.draw(end);
	window_.draw(eye);
	window_.draw(the_square);
	window_.draw(start);
	window_.display();
}

void Game::loop()
{
	//load level
	load();

	while (window_.isOpen())
	{

		system("cls");
		std::cout << "number of coins you got : " << number_of_coins_collected_ << "\n";


		SetView();

		if (grounded_)
		{
			player_vel_.y = 0;
		}

		HandleEvent();

		float limit_x_low;
		float limit_x_high;
		float limit_y_low;
		float limit_y_high;


		SetCollisionLimit(limit_x_low, limit_x_high, limit_y_low, limit_y_high);

		// moving the player!
		sf::Vector2f delta;
		player_movement(delta);

		gavity_and_falling_max_speed();


		set_player_movement_and_collision_with_tile(limit_x_low, limit_x_high, limit_y_low, limit_y_high, delta);


		sf::Vector2i mouse_tile;
		mouse_hovering_system(mouse_tile);

		// clear the window with black color
		window_.clear(sf::Color::Black);

		draw_background_and_tile();

		draw_cursor_tile(mouse_tile);

		system_to_calculate_coins_one_by_one();


		collision_for_power_up_and_checkpoint();

		collision_for_end_and_portal();


		effect_of_death();

		//effect of the eye of god power up -> makes you see things unexpected
		effect_of_vision_power();

		std::cout << the_square.getPosition().x << "\n";
		std::cout << the_square.getPosition().y;

		graphical_frame();
	}
}

#pragma once
#include <SFML/Graphics.hpp>

#define TILEMAP_WIDTH 200
#define TILEMAP_HEIGHT 50
#define TILE_SIZE_PX 50
#define PLATEFORM_HEIGHT_SETUPP 18
#define EDGE_MAP_RESPAWN 1500
#define EDGE_MAP_LENGTH 5000
#define EDGE_MAP_HEIGHT 2000

//maps
extern bool box[TILEMAP_HEIGHT * TILEMAP_WIDTH];
extern int tiles[TILEMAP_HEIGHT * TILEMAP_WIDTH];

//funciton to save and load the game
void save();
void load();


class Game
{
#pragma region all_textures 
	sf::Texture plateform_texture;
	sf::Texture right;
	sf::Texture left;
	sf::Texture coin_texture;
	sf::Texture air;
	sf::Texture ground_surface_texture;
	sf::Texture ground;
	sf::Texture start_texture;
	sf::Texture end_texture;
	sf::Texture eye_texture;
	sf::Texture illusion_left_texture;
	sf::Texture illusion_down_texture;
	sf::Texture double_jump_texture;
	sf::Texture speed_power_texture;
	sf::Texture backgorund_texture;
	sf::Texture initial_check_point_texture;
	sf::Texture check_point_touched_texture;
#pragma endregion

#pragma region all_rectangle shapes
	sf::RectangleShape tile_shape;
	sf::RectangleShape initial_check_point;
	sf::RectangleShape start;
	sf::RectangleShape teleportation;
	sf::RectangleShape end;
	sf::RectangleShape eye;
	sf::RectangleShape double_jump;
	sf::RectangleShape speed_power;
	sf::RectangleShape illusions_left;
	sf::RectangleShape illusion_down;
	sf::RectangleShape cursor_shape;
	sf::RectangleShape the_square;
	sf::RectangleShape coin;
	sf::RectangleShape background;
#pragma endregion

	//bool to see if player is in bounds
	bool in_bounds(sf::Vector2i coords)
	{
		return coords.x >= 0
			&& coords.x < TILEMAP_WIDTH
			&& coords.y >= 0
			&& coords.y < TILEMAP_HEIGHT;
	}

	//bool qui permet de savoir si collision ou non
	bool collision_check(sf::Vector2f position)
	{
		sf::Vector2i coord;
		coord.x = position.x / TILE_SIZE_PX;
		coord.y = position.y / TILE_SIZE_PX;

		if (coord.x < 0 || coord.y < 0 || coord.x >= TILEMAP_WIDTH || coord.y >= TILEMAP_HEIGHT)
		{
			return true;
		}

		int index = coord.y * TILEMAP_WIDTH + coord.x;
		bool tile_solid = box[index];

		return tile_solid;
	}

	//bool that refers to tile 
	bool tile_at(sf::Vector2i tile_coord)
	{
		if (tile_coord.x < 0 || tile_coord.y < 0 || tile_coord.x >= TILEMAP_WIDTH || tile_coord.y >= TILEMAP_HEIGHT)
		{
			return true;
		}
		const int index = tile_coord.y * TILEMAP_WIDTH + tile_coord.x;
		return box[index];
	}

	//transform pos into tile coordonate
	sf::Vector2i pos_to_coords(sf::Vector2f world_position)
	{
		sf::Vector2i coord;
		coord.x = std::floor(world_position.x / TILE_SIZE_PX);
		coord.y = std::floor(world_position.y / TILE_SIZE_PX);
		return coord;
	}



	int number_of_coins_collected_ = 0;

	//bools 
	bool coin1_ = false;
	bool coin2_ = false;
	bool coin3_ = false;
	bool coin4_ = false;
	bool coin5_ = false;
	bool coin6_ = false;
	bool check_point_active_ = false;
	bool eye_of_god_ = false;
	bool is_double_jump_active_= false;
	bool jumped_once_ = false;
	bool is_speed_active_ = false;
	bool grounded_ = false;

	sf::Vector2f player_pos_ = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f player_vel_ = sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f player_sprint_speed_ = sf::Vector2f(0.0f, 0.0f);


	sf::RenderWindow window_;


public:
	//constructor
	Game();

	//all methods that does a specific thing quoted in their name
	void init();
	void SetView();
	void HandleEvent();
	void SetCollisionLimit(float& limit_x_low, float& limit_x_high, float& limit_y_low, float& limit_y_high);
	void player_movement(sf::Vector2f& delta);
	void gavity_and_falling_max_speed();
	void set_player_movement_and_collision_with_tile(float limit_x_low, float limit_x_high, float limit_y_low,
		float limit_y_high, sf::Vector2f& delta);
	void mouse_hovering_system(sf::Vector2i& mouse_tile);
	void draw_background_and_tile();
	void draw_cursor_tile(sf::Vector2i mouse_tile);
	void system_to_calculate_coins_one_by_one();
	void collision_for_power_up_and_checkpoint();
	void collision_for_end_and_portal();
	void effect_of_death();
	void effect_of_vision_power();
	void graphical_frame();

	//loop of this game
	void loop();
};


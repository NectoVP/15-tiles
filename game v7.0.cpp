#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
int WinMain()
{
	std::srand(std::time(nullptr));
	sf::RenderWindow gameWindow;
	sf::RenderWindow picWindow;
	gameWindow.create(sf::VideoMode(600, 600), "");
	picWindow.create(sf::VideoMode(600, 600), "");
	gameWindow.setFramerateLimit(60);
	sf::Event event;

	sf::Image img;
	img.loadFromFile("test.jpg");
	sf::Texture fullimgtext;
	fullimgtext.loadFromImage(img);
	sf::Sprite fullsprite;
	fullsprite.setTexture(fullimgtext);
	int factor = img.getSize().x / 4;
	fullsprite.setScale((600.f / 4) / factor, (600.f / 4) / factor);

	std::vector <sf::Sprite> sprite_tiles(16);
	std::vector <sf::Texture> text_tiles(16);

	sf::Image small_img;

	small_img.create(factor, factor, sf::Color::Green);

	for (int m = 0; m < 4; m++) {
		for (int n = 0; n < 4; n++) {
			for (int i = 0; i < factor; ++i) {
				for (int j = 0; j < factor; ++j) {
					small_img.setPixel(i, j, img.getPixel(i + n * factor, j + m * factor));
				}
			}
			text_tiles[n * 4 + m].loadFromImage(small_img);
			sprite_tiles[n * 4 + m].setTexture(text_tiles[n * 4 + m]);
			sprite_tiles[n * 4 + m].setScale((600.f / 4) / factor, (600.f / 4) / factor);
			sf::Vector2f pos;
			pos.x = n * 150.f;
			pos.y = m * 150.f;
			sprite_tiles[n * 4 + m].setPosition(pos);
			sprite_tiles.push_back(sprite_tiles[n * 4 + m]);
		}
	}

	sf::Image img_void;
	img_void.create(600, 600, sf::Color::Green);
	sf::Texture tex_void;
	tex_void.loadFromImage(img_void);
	int void_index = 15;
	text_tiles[15].swap(tex_void);

	sf::Vector2i winpos;
	winpos.x = 355.f;
	winpos.y = 240.f;
	gameWindow.setPosition(winpos);
	winpos.x = 955.f;
	picWindow.setPosition(winpos);

	sf::Text text;
	sf::Font font;
	font.loadFromFile("calibri.ttf");
	text.setFont(font);
	text.setString("press f2 to mix tiles");

	while (gameWindow.isOpen() || picWindow.isOpen()) {
		while (gameWindow.pollEvent(event) || picWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				gameWindow.close();
				picWindow.close();
			}
			if (event.key.code == sf::Keyboard::F2) {
				for (int i = 0; i < 50; ++i) {
					int a = std::rand() % 15;
					int b = std::rand() % 15;
					text_tiles[a].swap(text_tiles[b]);
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{


				if (event.key.code == sf::Keyboard::Left && void_index / 4 != 3) {
					if (void_index < 16)
					{
						text_tiles[void_index + 4].swap(text_tiles[void_index]);
						void_index = void_index + 4;
					}
				}
				if (event.key.code == sf::Keyboard::Right && void_index / 4 != 0) {
					if (void_index >= 0)
					{
						text_tiles[void_index - 4].swap(text_tiles[void_index]);
						void_index = void_index - 4;
					}
				}
				if (event.key.code == sf::Keyboard::Up && void_index % 4 != 3) {
					if (void_index < 16)
					{
						text_tiles[void_index + 1].swap(text_tiles[void_index]);
						void_index = void_index + 1;
					}
				}
				if (event.key.code == sf::Keyboard::Down && void_index % 4 != 0) {
					if (void_index >= 0)
					{
						text_tiles[void_index - 1].swap(text_tiles[void_index]);
						void_index = void_index - 1;
					}
				}

			}

		}

		gameWindow.clear();
		picWindow.clear();

		for (int i = 0; i < 16; ++i)
			gameWindow.draw(sprite_tiles[i]);
		picWindow.draw(fullsprite);
		picWindow.draw(text);

		gameWindow.display();
		picWindow.display();
	}

	return 0;
}

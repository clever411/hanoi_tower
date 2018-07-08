#include <cstring>
#include <iostream>
#include <future>
#include <memory>

#include <SFML/Graphics.hpp>

#include <clever/SFML/CellPrinter.hpp>
#include <clever/SFML/FieldAdapter.hpp>

#include "HanoiTower.hpp"



using namespace clever;
using namespace sf;
using namespace std;





// global objects
	// sfml
RenderWindow window;
VideoMode vmode = VideoMode::getDesktopMode();
char const *TITLE = "Application";
unsigned int FRAMERATE_LIMIT = 60u;

Event event;


	// other
typedef Field<int> field_type;
typedef CellPrinter<int> cellprinter_type;
typedef FieldAdapter<
	field_type::value_type, cellprinter_type
> fieldadapter_type;

HanoiTower tower;
field_type field;

fieldadapter_type fieldadapter;





// init
void init_window()
{
	window.create(vmode, TITLE, Style::None);
	window.setPosition({0u, 0u});
	window.setFramerateLimit(FRAMERATE_LIMIT);
	return;
}

void init_tower()
{
	// parameters
	constexpr unsigned int const HEIGHT = 8u;

	// create
	HanoiTowerData d;
	d.first = new int[HEIGHT];
	d.second = new int[HEIGHT];
	d.third = new int[HEIGHT];
	d.height = HEIGHT;

	// clear
	memset(d.first, 0, sizeof(*d.first)*HEIGHT);
	memset(d.second, 0, sizeof(*d.second)*HEIGHT);
	memset(d.third, 0, sizeof(*d.third)*HEIGHT);

	// boid tower
	for(size_t i = 0; i < HEIGHT; ++i)
	{
		d.first[i] = HEIGHT-i;
	}

	// set
	tower.setData(d);

	return;
}

void init_field()
{
	constexpr unsigned int const
		WIDTH = 47u,
		HEIGHT = 8u;

	field.w = WIDTH;
	field.h = HEIGHT;
	field.d = new field_type::value_type[ field.w*field.h ];

	field.clear(0);
	field.at(0, 0) = 1;
	return;
}

void init_fieldadapter()
{
	fieldadapter.setSize(
		conversion<float>( window.getSize() )
	);

	fieldadapter.setField(
		shared_ptr< field_type >(
			&field,
			[](field_type *)->void {}
		)
	);

	fieldadapter.update();

	fieldadapter.setPosition(
		0.0f,
		( window.getSize().x - fieldadapter.getSize().x ) / 2
	);

	return;
}





// main
int main( int argc, char *argv[] )
{
	init_window();
	init_tower();
	init_field();
	init_fieldadapter();

	tower.reflect(field);
	
	while(window.isOpen()) {
		if(window.pollEvent(event)) {

			switch(event.type) {
			case Event::KeyPressed:

				switch(event.key.code) {
				case sf::Keyboard::C:
					window.close();
					break;
				// algorithm
				case sf::Keyboard::S:
					if(!tower.isRun()) 
						tower.run(0, 2);
					else
						tower.pause( !tower.pause() );
					break;
				case sf::Keyboard::R:
					tower.interrupt().wait();
					init_tower();
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}

		}

		// update
		tower.reflect(field);
		fieldadapter.update();

		// draw
		window.clear(Color::White);
		window.draw(fieldadapter);
		window.display();

		this_thread::yield();
	}
	tower.interrupt();


	return 0;
}





// end

#ifndef LIS_SFML__CELL_PRINTER_HPP
#define LIS_SFML__CELL_PRINTER_HPP

#include <SFML/Graphics.hpp>





template<typename T>
class CellPrinter: public sf::RectangleShape
{
public:
	typedef T value_type;



	// methods
	CellPrinter()
	{
		setFillColor(sf::Color::Transparent);
		setSideSize(25.0f);
		return;
	}

	CellPrinter &setSideSize(float side)
	{
		setSize( { side, side } );
		setOrigin( { side/2.0f, side/2.0f } );
		return *this;
	}

	CellPrinter &set(value_type const &val)
	{
		switch(val)
		{
		case 0:
			setFillColor(sf::Color::White);
			break;
		case 1:
			setFillColor(sf::Color::Black);
			break;
		case 2:
			setFillColor(sf::Color::Red);
			break;
		case 3:
			setFillColor(sf::Color::Green);
			break;
		case 4:
			setFillColor(sf::Color::Blue);
			break;
		case 5:
			setFillColor(sf::Color::Yellow);
			break;
		case 6:
			setFillColor(sf::Color::Magenta);
			break;
		case 7:
			setFillColor(sf::Color::Cyan);
			break;
		default:
			setFillColor(sf::Color::Transparent);
		}
		return *this;
	}


	
};





#endif

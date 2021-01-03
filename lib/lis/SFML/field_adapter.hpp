#ifndef LIS_HEXAGONAL_FIELD_ADAPTER_HPP
#define LIS_HEXAGONAL_FIELD_ADAPTER_HPP

#include <memory>
#include <type_traits>

#include <SFML/Graphics.hpp>

#include <lis/point.hpp>
#include <lis/meta.hpp>





namespace lis
{
	
	
	
	
	
	
	
struct SquareFieldTag {};
struct HexagonFieldTag {};

/*
 * Printer — это класс, который должен содержать следующие 
 * функции:
 * 	setPosition( PointF ); — установить позицию,
 * 		устанавливается притом центр, где должно быть
 * 		напечатана фигура
 * 	setSideSize( float ); — установить размер стороны: для
 * 		квадрата — это, собственно, размер его стороны;
 * 		для шестиугольника — это радиус описанной 
 * 		окружности
 * 	set( value_type ); — установить значение, из которого
 * 		должен определяться вид напечатанного
 */

template<class FieldType, class Printer, class FieldTag = SquareFieldTag>
class FieldAdapter: public sf::Transformable, public sf::Drawable
{
public:	
	// types
	typedef FieldTag field_tag;
	typedef typename FieldType::value_type value_type;
	typedef FieldType field_type;
	typedef std::shared_ptr<field_type> fieldptr_type;
	typedef Printer printer_type;
	typedef std::shared_ptr<printer_type> printerptr_type;
	
	
	
	
	
	// create
	FieldAdapter(
		fieldptr_type field = nullptr,
		PointF size = {400.0f, 200.0f}
	);
	
	
	
	
	
	// core
	FieldAdapter &update();

	inline PointI cursorOn(float x, float y) const;
	PointI cursorOn(PointF p) const;

	virtual void draw(
		sf::RenderTarget &target,
		sf::RenderStates states = sf::RenderStates::Default
	) const override;
	
	
	
	
	// set, get
		// field
	FieldAdapter &setField(fieldptr_type newfield);
	fieldptr_type getField() const;
	

		// printer
	FieldAdapter &setPrinter(printerptr_type newprinter);
	printerptr_type getPrinter() const;
	
	
		// size
	FieldAdapter &setSize(PointF size);
	PointF getSize() const;


		// grid
	FieldAdapter &setDrawGridEnable(bool enable);
	bool getDrawGridEnable() const;

	FieldAdapter &setGridThickness(float newthick);
	float getGridThickness() const;

	FieldAdapter &setGridColor(sf::Color const &newcolor);
	sf::Color const &getGridColor() const;



private:
	// function implement
	struct SquareImplement
	{
		static constexpr PointF const OFF{ 0.5, 0.5 };

		inline static PointI cursorOn(
			PointF p, FieldAdapter const &f
		);

		inline static PointF off(float side);

		inline static void adjust_size(FieldAdapter &f);

		inline static void draw_grid(FieldAdapter &f);

	};

	struct HexagonImplement
	{
		static constexpr PointF const OFF{ 1.0, 0.866025 };

		inline static PointI cursorOn(
			PointF p, FieldAdapter const &f
		);

		inline static PointF off(float side);

		inline static void adjust_size(FieldAdapter &f);

		inline static void draw_grid(FieldAdapter &f);


	};

	typedef typename IF<
		std::is_same< field_tag, SquareFieldTag>::value,
		SquareImplement,
		HexagonImplement
	>::type imp;

	friend imp;







	// other
	void adjust_();

	// data-members
		// main
	fieldptr_type field_;
	mutable printerptr_type printer_ =
		printerptr_type(new printer_type);

		// sizes
	PointF size_;
	float side_;

		// background
	sf::RenderTexture rtexture_;
	sf::Sprite sprite_;
	bool drawgrid_ = true;
	float gridthick_ = 2.0f;
	sf::Color gridcolor_ = sf::Color::White;


};





#include "_field_adapter_implement.hpp"




// typedefs
template<class FieldType, class PrinterType>
using SquareFieldAdapter = FieldAdapter<FieldType, PrinterType, SquareFieldTag>;

template<class FieldType, class PrinterType>
using HexagonFieldAdapter = FieldAdapter<FieldType, PrinterType, HexagonFieldTag>;





}





#endif

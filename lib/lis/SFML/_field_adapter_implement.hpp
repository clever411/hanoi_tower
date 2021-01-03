#include <algorithm>
#include <cmath>





// create
template<class FieldType, class Printer, class FieldTag>
FieldAdapter<FieldType, Printer, FieldTag>::FieldAdapter(
	fieldptr_type field,
	PointF size
): field_(field), size_(size)
{
	adjust_();
	return;
}





// core
template<class FieldType, class Printer, class FieldTag>
FieldAdapter<FieldType, Printer, FieldTag> &
FieldAdapter<FieldType, Printer, FieldTag>::update()
{
	adjust_();
	return *this;
}

template<class FieldType, class Printer, class FieldTag>
PointI FieldAdapter<FieldType, Printer, FieldTag>::cursorOn(PointF p) const
{
	return imp::cursorOn(p, *this);
}

template<class FieldType, class Printer, class FieldTag>
inline PointI FieldAdapter<FieldType, Printer, FieldTag>::cursorOn(
	float x, float y
) const
{
	return imp::cursorOn({x, y}, *this);
}

template<class FieldType, class Printer, class FieldTag>
void FieldAdapter<FieldType, Printer, FieldTag>::draw(
	sf::RenderTarget &target,
	sf::RenderStates states
) const
{
	states.transform *= getTransform();
	if(drawgrid_)
		target.draw(sprite_, states);
	for(auto b = field_->begin(), e = field_->end(); b != e; ++b)
	{
		printer_->setPosition(
			field_->origin(b, side_) +
			imp::off(side_)
		);
		printer_->set(*b);
		target.draw(*printer_, states);
	}

	return;
}





// field
template<class FieldType, class Printer, class FieldTag>
FieldAdapter<FieldType, Printer, FieldTag> &
FieldAdapter<FieldType, Printer, FieldTag>::setField(
	fieldptr_type newfield
)
{
	field_ = newfield;
	return *this;
}

template<class FieldType, class Printer, class FieldTag>
typename FieldAdapter<FieldType, Printer, FieldTag>::fieldptr_type 
FieldAdapter<FieldType, Printer, FieldTag>::getField() const
{
	return field_;
}





// printer
template<class FieldType, class Printer, class FieldTag>
FieldAdapter<FieldType, Printer, FieldTag> &
FieldAdapter<FieldType, Printer, FieldTag>::setPrinter(
	printerptr_type newprinter
)
{
	printer_ = newprinter;
	adjust_();
	return *this;
}

template<class FieldType, class Printer, class FieldTag>
typename FieldAdapter<FieldType, Printer, FieldTag>::printerptr_type
FieldAdapter<FieldType, Printer, FieldTag>::getPrinter() const
{
	return printer_;
}





// size
template<class FieldType, class Printer, class FieldTag>
FieldAdapter<FieldType, Printer, FieldTag> &
FieldAdapter<FieldType, Printer, FieldTag>::setSize(
	PointF newsize
)
{
	size_ = newsize;
	adjust_();
	return *this;
}

template<class FieldType, class Printer, class FieldTag>
PointF FieldAdapter<FieldType, Printer, FieldTag>::getSize() const
{
	return size_;
}





// grid
template<class FieldType, class Printer, class FieldTag>
FieldAdapter<FieldType, Printer, FieldTag> &
FieldAdapter<FieldType, Printer, FieldTag>::setDrawGridEnable(bool enable)
{
	drawgrid_ = enable;
	adjust_();
	return *this;
}

template<class FieldType, class Printer, class FieldTag>
bool 
FieldAdapter<FieldType, Printer, FieldTag>::getDrawGridEnable() const
{
	return drawgrid_;
}



template<class FieldType, class Printer, class FieldTag>
FieldAdapter<FieldType, Printer, FieldTag> &
FieldAdapter<FieldType, Printer, FieldTag>::setGridThickness(float newthick)
{
	gridthick_ = newthick;
	adjust_();
	return *this;
}

template<class FieldType, class Printer, class FieldTag>
float 
FieldAdapter<FieldType, Printer, FieldTag>::getGridThickness() const
{
	return gridthick_;
}



template<class FieldType, class Printer, class FieldTag>
FieldAdapter<FieldType, Printer, FieldTag> &
FieldAdapter<FieldType, Printer, FieldTag>::setGridColor(
	sf::Color const &newcolor
)
{
	gridcolor_ = newcolor;
	adjust_();
	return *this;
}

template<class FieldType, class Printer, class FieldTag>
sf::Color const &
FieldAdapter<FieldType, Printer, FieldTag>::getGridColor() const
{
	return gridcolor_;
}







// private
template<class FieldType, class Printer, class FieldTag>
void FieldAdapter<FieldType, Printer, FieldTag>::adjust_()
{
	if(!field_)
		return;
	imp::adjust_size(*this);
	printer_->setSideSize(
		side_ - (drawgrid_ ? gridthick_/2.0f : 0.0f)
	);

	if(!drawgrid_)
		return;


	// grid
	rtexture_.create(size_.x, size_.y);
	imp::draw_grid(*this);
	rtexture_.display();
	sprite_.setTexture( rtexture_.getTexture(), true );


	return;
}







// implement
	// square
template<class FieldType, class Printer, class FieldTag>
inline PointI
FieldAdapter<FieldType, Printer, FieldTag>::SquareImplement::cursorOn(
	PointF p, FieldAdapter const &f
)
{
	return { int(p.x / f.side_), int(p.y / f.side_) };
}

template<class FieldType, class Printer, class FieldTag>
inline PointF
FieldAdapter<FieldType, Printer, FieldTag>::SquareImplement::off(float side)
{
	return OFF*side;
}

template<class FieldType, class Printer, class FieldTag>
inline void FieldAdapter<FieldType, Printer, FieldTag>::SquareImplement::adjust_size(
	FieldAdapter &f
)
{
	f.side_ = std::min(
		f.size_.x / f.field_->w,
		f.size_.y / f.field_->h
	);
	f.size_ = {
		f.field_->w * f.side_,
		f.field_->h * f.side_
	};
	return;
}

template<class FieldType, class Printer, class FieldTag>
inline void FieldAdapter<FieldType, Printer, FieldTag>::SquareImplement::draw_grid(
	FieldAdapter &f
)
{
	// prepare rect
	sf::RectangleShape rect;
	float rectside = f.side_ - f.gridthick_/2.0f;
	rect.setSize( { rectside, rectside } );
	rect.setOrigin(
		rectside / 2.0f,
		rectside / 2.0f
	);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(f.gridthick_);
	rect.setOutlineColor(f.gridcolor_);

		// draw in rtexture
	f.rtexture_.clear(sf::Color::Transparent);
	for(auto b = f.field_->begin(), e = f.field_->end(); b != e; ++b)
	{
		rect.setPosition(
			f.field_->origin(b, f.side_) + off(f.side_)
		);
		f.rtexture_.draw(rect);
	}

	return;
}
	
	
	
	
	
	// hexagon
template<class FieldType, class Printer, class FieldTag>
inline PointI
FieldAdapter<FieldType, Printer, FieldTag>::HexagonImplement::cursorOn(
	PointF p, FieldAdapter const &f
)
{
	p -= off(f.side_);
	PointI fp, sp;
	int const
		i = int( p.x / (1.5f*f.side_) ),
		j = int( p.y / (0.866025*f.side_) );
	if(i%2 == j%2)
	{
		fp = { i, j };
		sp = { i+1, j+1 };
	}
	else
	{
		fp = { i+1, j };
		sp = { i, j+1 };
	}
	return
		f.field_->origin(fp, f.side_).dis(p) <
		f.field_->origin(sp, f.side_).dis(p) ? fp : sp;
}

template<class FieldType, class Printer, class FieldTag>
inline PointF
FieldAdapter<FieldType, Printer, FieldTag>::HexagonImplement::off(float side)
{
	return OFF*side;
}

template<class FieldType, class Printer, class FieldTag>
inline void FieldAdapter<FieldType, Printer, FieldTag>::HexagonImplement::adjust_size(
	FieldAdapter &f
)
{
	f.side_ = std::min(
		f.size_.x / ( 3.0f * f.field_->w + 0.5f ),
		1.154701f*f.size_.y / ( 1.0f + f.field_->h )
	);
	f.size_.x = (3.0f * f.field_->w + 0.5) * f.side_;
	f.size_.y = 0.866025 * f.side_ * (1 + f.field_->h);

	return;
}

template<class FieldType, class Printer, class FieldTag>
inline void FieldAdapter<FieldType, Printer, FieldTag>::HexagonImplement::draw_grid(
	FieldAdapter &f
)
{
	// prepare circle
	sf::CircleShape circle;
	circle.setPointCount(6);
	circle.setRadius( f.side_ - f.gridthick_/2.0f );
	circle.setRotation(90);
	circle.setOrigin(
		circle.getRadius(),
		circle.getRadius()
	);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(f.gridthick_);
	circle.setOutlineColor(f.gridcolor_);

		// draw in rtexture
	f.rtexture_.clear(sf::Color::Transparent);
	for(auto b = f.field_->begin(), e = f.field_->end(); b != e; ++b)
	{
		circle.setPosition(
			f.field_->origin(b, f.side_) + off(f.side_)
		);
		f.rtexture_.draw(circle);
	}

	return;
}







// end

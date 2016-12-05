#ifndef QSDLCOLOR_H
#define QSDLCOLOR_H

#include <QColor>
#include <SDL/SDL_video.h>

class QSdlColor
{
	SDL_Color color;
public:
	QSdlColor(int red, int green, int blue){
		color.r = red;
		color.g = green;
		color.b = blue;
	}

	QSdlColor(QColor color){
		this->color.r = color.red();
		this->color.g = color.green();
		this->color.b = color.blue();
	}

	SDL_Color getSdlColor(){
		return color;
	}

	QColor getColor(){
		return QColor(color.r, color.g, color.b);
	}

	int getRed(){
		return color.r;
	}

	int getGreen(){
		return color.g;
	}

	int getBlue(){
		return color.b;
	}

	static SDL_Color generateColor(int red, int green, int blue){
		QSdlColor c(red, green, blue);
		return c.getSdlColor();
	}
};

#endif // QSDLCOLOR_H

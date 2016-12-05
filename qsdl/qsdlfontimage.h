#ifndef QSDLFONTIMAGE_H
#define QSDLFONTIMAGE_H

#include <QtCore>
#include <SDL/SDL_ttf.h>
#include "qsdlexception.h"
#include "com/qsdlsurface.h"
#include "com/qsdlcolor.h"

class QSdlFontImage : public QObject
{
	Q_OBJECT
	TTF_Font *font = nullptr;
	QSdlSurface *fontSurface = nullptr;

	bool openFont(const QString &fontfile, int pixelSize){
		this->font = TTF_OpenFont(fontfile.toUtf8().data(), pixelSize);
		if(this->font == nullptr){
			return false;
		}else{
			return true;
		}
	}

public:
	enum QSdlTtfStyle{
		Sdl_TtfStyleNormal = TTF_STYLE_NORMAL,
		Sdl_TtfStyleBold = TTF_STYLE_BOLD,
		Sdl_TtfStyleItalic = TTF_STYLE_ITALIC,
		Sdl_TtfStyleUnderline = TTF_STYLE_UNDERLINE,
		Sdl_TtfStyleStrikethrough = TTF_STYLE_STRIKETHROUGH
	};

	QSdlTtfStyle getFontStyle(){
		return (QSdlTtfStyle)(TTF_GetFontStyle(this->font));
	}

	void setFontStyle(QSdlTtfStyle style){
		TTF_SetFontStyle(this->font, (int)(style));
	}

	QSdlTtfStyle getFontOutline(){
		return (QSdlTtfStyle)(TTF_GetFontOutline(this->font));
	}

	void setFontOutline(QSdlTtfStyle style){
		TTF_SetFontOutline(this->font, (int)(style));
	}

	enum QSdlTtfHinting{
		Sdl_TtfHintingNormal = TTF_HINTING_NORMAL,
		Sdl_TtfHintingLight = TTF_HINTING_LIGHT,
		Sdl_TtfHintingMono = TTF_HINTING_MONO,
		Sdl_TtfHintingNone = TTF_HINTING_NONE
	};

	QSdlTtfHinting getFontHinting(){
		return (QSdlTtfHinting)(TTF_GetFontHinting(this->font));
	}

	void setFontHinting(QSdlTtfHinting hinting){
		TTF_SetFontHinting(this->font, hinting);
	}

	explicit QSdlFontImage(const QString &fontfile, int pixelSize, QObject *parent = 0) throw(QSdlException): QObject(parent){
		try{
			if(TTF_Init() < 0){
				throw QSdlException(tr("QSdlFontImage: TTF_Init() failed: {$sdl_error}."));
				return;
			}

			if(!this->openFont(fontfile, pixelSize)){
				throw QSdlException(tr("QSdlFontImage: TTF_OpenFont() failed: {$sdl_error}."));
			}
		}catch(...){
			throw;
		}
	}

	~QSdlFontImage(){
		if(this->font != nullptr){
			TTF_CloseFont(this->font);
		}
		if(this->fontSurface != nullptr){
			delete this->fontSurface;
			this->fontSurface = nullptr;
		}
		if(this->isInit()){
			TTF_Quit();
		}
	}

	int getFontHeight(){
		return TTF_FontHeight(this->font);
	}

	int getFontAscent(){
		return TTF_FontAscent(this->font);
	}

	int getFontDecent(){
		return TTF_FontDescent(this->font); // returns minus number
	}

	bool getFontKerning(){
		return TTF_GetFontKerning(this->font) > 0? true: false;
	}

	void setFontKerning(bool allowed){
		TTF_SetFontKerning(this->font, allowed?1:0);
	}

	long getFontFaces(){
		return TTF_FontFaces(this->font);
	}

	int getFontFaceIsFixedWidth(){
		return TTF_FontFaceIsFixedWidth(this->font);
	}

	QString getFontFaceFamilyName(){
		return QString(TTF_FontFaceFamilyName(this->font));
	}

	QString getFontFaceStyleName(){
		return QString(TTF_FontFaceStyleName(this->font));
	}

	bool glaphIsProvided(QChar ch){
		return TTF_GlyphIsProvided(this->font, ch.unicode());
	}

	QSize textSize(const QString &text){
		int w = 0;
		int h = 0;
		if(TTF_SizeUTF8(this->font, text.toUtf8().data(), &w, &h) < 0){
			return QSize();
		}else{
			return QSize(w, h);
		}
	}

	QSdlSurface *toSurface(const QString &string, QSdlColor color){
		if(this->fontSurface != nullptr){
			delete this->fontSurface;
			this->fontSurface = nullptr;
		}
		this->fontSurface = new QSdlSurface(TTF_RenderUTF8_Solid(this->font, string.toUtf8().data(), color.getSdlColor()));
		return this->fontSurface;
	}

	QSdlSurface *toSurface(const QString &string, QSdlColor color, QSdlColor background){
		if(this->fontSurface != nullptr){
			delete this->fontSurface;
			this->fontSurface = nullptr;
		}
		this->fontSurface = new QSdlSurface(TTF_RenderUTF8_Shaded(this->font, string.toUtf8().data(), color.getSdlColor(), background.getSdlColor()));
		return this->fontSurface;
	}

	QSdlSurface *toSurfaceAlpha(const QString &string, QSdlColor color){
		if(this->fontSurface != nullptr){
			delete this->fontSurface;
			this->fontSurface = nullptr;
		}
		this->fontSurface = new QSdlSurface(TTF_RenderUTF8_Blended(this->font, string.toUtf8().data(), color.getSdlColor()));
		return this->fontSurface;
	}

	bool isInit(){
		return TTF_WasInit() != 0? true: false;
	}

signals:

public slots:
};

#endif // QSDLFONTIMAGE_H

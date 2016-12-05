#ifndef QSDLMIXER_H
#define QSDLMIXER_H

#include <QObject>
#include "../global.h"
#include <SDL/SDL_mixer.h>
#include "../qsdlexception.h"

class QSdlMixer : public QObject
{
	Q_OBJECT

public:
	enum QSdlMixInitFlags{
		Sdl_InitFlac = MIX_INIT_FLAC,
		Sdl_InitMod = MIX_INIT_MOD,
		Sdl_InitMp3 = MIX_INIT_MP3,
		Sdl_InitOgg = MIX_INIT_OGG,
		Sdl_InitFluidsynth = MIX_INIT_FLUIDSYNTH,
		Sdl_InitCommon = Sdl_InitMod | Sdl_InitMp3 | Sdl_InitOgg,
		Sdl_InitAll = Sdl_InitFlac | Sdl_InitMod | Sdl_InitMp3 | Sdl_InitOgg
	};

	enum QSdlMixMusicType{
		Sdl_MusicNone = MUS_NONE,
		Sdl_MusicCmd = MUS_CMD,
		Sdl_MusicWav = MUS_WAV,
		Sdl_MusicMod = MUS_MOD,
		Sdl_MusicMid = MUS_MID,
		Sdl_MusicOgg = MUS_OGG,
		Sdl_MusicMp3 = MUS_MP3,
		Sdl_MusicMp3Mad = MUS_MP3_MAD,
		Sdl_MusicFlac = MUS_FLAC,
		Sdl_MusicModPlug = MUS_MODPLUG
	};

	static const int SdlMixChennels = MIX_CHANNELS;
	static const int SdlMixDefaultFrequency = MIX_DEFAULT_FREQUENCY;
	static const int SdlMixDefaultFormat = MIX_DEFAULT_FORMAT;
	static const int SdlMixDefaultChannels = MIX_DEFAULT_CHANNELS;
	static const int SdlMixMaxVolume = MIX_MAX_VOLUME;

	static const int SdlFirstFreeChannel = -1;
	static const int SdlPlayInifinitely = -1;

	explicit QSdlMixer(QSdlMixInitFlags flags = Sdl_InitCommon, QObject *parent = 0, bool *ok = nullptr) throw(QSdlException) : QObject(parent){
		setOk(false);
		try{
			int returnFlags = Mix_Init((int)flags);
			if(returnFlags != 0){
				setOk(true);
				return;
			}else{
				setOk(false);
				throw QSdlException(tr("QSdlMixer: Cannot init mixer: %1").arg(SDL_GetError()));
			}
		}catch(...){
			throw;
		}
	}

	virtual ~QSdlMixer(){
		Mix_Quit();
	}

	bool isAudioChannelOpened(int *freq = nullptr, quint16 *format = nullptr, int *channels = nullptr){
		if(freq == nullptr || format == nullptr || channels == nullptr){
			int _freq = 0, _channels = 0;
			quint16 _format = 0;
			int isOpened = Mix_QuerySpec(&_freq, &_format, &_channels);
			if(isOpened == 1){
				return true;
			}else{
				return false;
			}
		}else{
			int isOpened = Mix_QuerySpec(freq, format, channels);
			if(isOpened == 1){
				return true;
			}else{
				return false;
			}
		}
	}

protected:
	virtual bool openAudio(int freq, quint16 format, int channels, int chunksize){
		return(Mix_OpenAudio(freq, format, channels, chunksize) <0 ? false: true);
	}

	virtual void closeAudio(){
		Mix_CloseAudio();
	}

	Mix_Music *loadMusic(const QString &filename){
		return Mix_LoadMUS(filename.toUtf8().data());
	}

	Mix_Chunk *loadSound(const QString &filename){
		return Mix_LoadWAV(filename.toUtf8().data());
	}

//	virtual bool play(int channel = SdlFirstFreeChannel, int loops = 0) Pure;

//	virtual bool play(int loops) Pure;

//	virtual bool isPlaying() Pure;

	static QStringList getAvailableDecoders();

signals:

public slots:
};

#endif // QSDLMIXER_H

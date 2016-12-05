#ifndef QSDLMUSIC_H
#define QSDLMUSIC_H

#include "com/qsdlmixer.h"

class QSdlMusic : public QSdlMixer
{
	Mix_Music *music = nullptr;
public:
	QSdlMusic(QSdlMixInitFlags flags = QSdlMixer::Sdl_InitCommon, QObject *parent = nullptr, bool *ok = nullptr) throw(QSdlException)
		: QSdlMixer(flags, parent, ok)
	{
		try{
			if(isAudioChannelOpened()){
				return;
			}else{
				if(!openAudio(SdlMixDefaultFrequency, SdlMixDefaultFormat, SdlMixDefaultChannels, 4096)){
					throw QSdlException(tr("QSdlMusic: OpenAudio failed: {$sdl_error}"));
					return;
				}
			}
		}catch(...){
			throw;
		}
	}

	~QSdlMusic(){
		if(this->isPlaying()){
			this->stop();
		}
		Mix_FreeMusic(this->music);
		Mix_CloseAudio();
	}

	void setMusic(const QString &filename){
		this->music = loadMusic(filename);
	}

	bool isPlaying(){
		return (Mix_PlayingMusic() == 0? false: true);
	}

	bool isPaused(){
		return (Mix_PausedMusic() == 0? false: true);
	}

	void pause(){
		Mix_PauseMusic();
	}

	void resume(){
		Mix_ResumeMusic();
	}

	void rewind(){
		Mix_RewindMusic();
	}

	void stop(){
		Mix_HaltMusic();
	}

	void setVolume(int volume = 128){
		Mix_VolumeMusic(volume);
	}

	int getVolume(){
		return Mix_VolumeMusic(-1);
	}

	bool play(int loops = 0){
		if(this->music == nullptr){
			return false;
		}
		if(this->isPlaying()){
			return false;
		}
		return Mix_PlayMusic(this->music, loops) < 0? false: true;
	}

	static QStringList getAvailableDecoders(){
		QStringList list;
		int length = Mix_GetNumMusicDecoders();
		for(int i = 0; i<length; i++){
			list.append(QString(Mix_GetMusicDecoder(i)));
		}
		return list;
	}
};

#endif // QSDLMUSIC_H

#ifndef QSDLSOUND_H
#define QSDLSOUND_H

#include "com/qsdlmixer.h"

class QSdlSound : public QSdlMixer
{
	Mix_Chunk *sound = nullptr;
public:
	QSdlSound(QSdlMixInitFlags flags = QSdlMixer::Sdl_InitCommon, QObject *parent = nullptr, bool *ok = nullptr) throw(QSdlException)
		: QSdlMixer(flags, parent, ok)
	{
		try{
			if(isAudioChannelOpened()){
				return;
			}else{
				if(!openAudio(SdlMixDefaultFrequency, SdlMixDefaultFormat, SdlMixDefaultChannels, 4096)){
					throw QSdlException(tr("QSdlSound: OpenAudio failed: {$sdl_error}"));
					return;
				}
			}
		}catch(...){
			throw;
		}
	}
	~QSdlSound(){
		if(this->isPlaying()){
			this->stop();
		}
		Mix_FreeChunk(this->sound);
		Mix_CloseAudio();
	}

	void setSound(const QString &wav){
		this->sound = loadSound(wav.toUtf8().data());
	}

	bool isPlaying(int channel = -1){
		return (Mix_Playing(channel) == 0? false: true);
	}

	bool isPaused(int channel = -1){
		return (Mix_Paused(channel) == 0? false: true);
	}

	void pause(int channel = -1){
		Mix_Pause(channel);
	}

	void resume(int channel = -1){
		Mix_Resume(channel);
	}

	void setVolume(int volume = 128, int channel = -1){
		Mix_Volume(channel, volume);
	}

	int getVolume(int channel = -1){
		return Mix_Volume(channel, -1);
	}

	bool play(int channel = -1, int loops = 0){
		if(this->sound == nullptr){
			return false;
		}
		if(this->isPlaying(channel)){
			return false;
		}
		return Mix_PlayChannel(channel, this->sound, loops) < 0? false: true;
	}

	void stop(int channel = -1){
		Mix_HaltChannel(channel);
	}

	static QStringList getAvailableDecoders(){
		QStringList list;
		int length = Mix_GetNumChunkDecoders();
		for(int i = 0; i<length; i++){
			list.append(QString(Mix_GetChunkDecoder(i)));
		}
		return list;
	}
};

#endif // QSDLSOUND_H

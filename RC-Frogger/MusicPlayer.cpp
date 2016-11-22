#include "MusicPlayer.h"


namespace GEX {
	MusicPlayer::MusicPlayer() :
		_music(),
		_filename(),
		_volume(10.f)
	{
		_filename[MusicID::MissionTheme] = "../Media/Music/MissionTheme.ogg";
		_filename[MusicID::MenuTheme] = "../Media/Music/MenuTheme.ogg";
	}

	void GEX::MusicPlayer::play(MusicID theme)
	{
		std::string filename = _filename[theme];

		if (!_music.openFromFile(filename))
			throw std::runtime_error("Music " + filename + " could not be loaded");

		_music.setVolume(_volume);
		_music.setLoop(true);
		_music.play();
	}

	void GEX::MusicPlayer::stop()
	{
		_music.stop();
	}

	void GEX::MusicPlayer::setPaused(bool paused)
	{
		if (paused)
			_music.pause();
		else
			_music.play();
	}

	void GEX::MusicPlayer::setVolume(float volume)
	{
		_volume = volume;
	}
		
}
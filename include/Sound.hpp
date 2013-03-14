/// @file Client_Server.hpp
/// @brief Header file for Client_Server.hpp
/// @author Eric Hamdan erichamdan@gmail.com

#ifndef SOUND
#define SOUND

#include <string>
#include <map>
#include "Buffer.hpp"
#include "Client_Server.hpp"
#include "Node.hpp"

#define NEW_PAUSED 0
#define NEW 1

namespace ColliderPlusPlus {

  /// This class represents a user manipulable Soundfile Player, essentially mirroring
  /// the OAS class of the same name by Shreenidhi Chowkwale
  /// @ref https://github.com/CalVR/Open-Audio-Server/blob/master/client/src/Sound.h
  class Sound 
  {
    public:
	
        /// Create a new sound source 
	/// Channel count is determined by file
	Sound(Client_Server * cs, const std::string &filepath, int initAction = 0);
  
      	/// Deallocates server-side buffer associated with this instance
	~Sound();


        // {@
	/// @name Playback Functions
	
	/// Play the sound source from specified position. Default is beginning of file
        /// @param[in] float Playback position seconds
        void _play();

      //  void _play(float seconds);
 
        /// Pauses the sound source at the current playback position
        void _stop();

        /// Stops playing the sound source. Playback will resume from the beginning
      //  void _pause();

        int _loop(bool loop);
        // @}

//	void _setPlaybackPosition(float seconds);

  //      void _setGain(float gain);

//	void _setPitch(float pitchScalar);

  //      void _fade(float finalGain, float fadeDuration);
 
    private:

        void _init(const std::string &filepath, Client_Server * cs);
	
	Client_Server * _cs;
	Buffer * _buffer;
        Synth * _synth;
	std::string _filePath;

        std::map<std::string, float> args;
	
	float _pitchScalar;
	float _gain;
        int _initAction;
	bool _isLooping;
        bool _isPlaying;
  };
} //namespace ColliderPlusPlus
#endif

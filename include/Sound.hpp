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
	Sound(Client_Server * cs, const std::string &filepath, int initAction = 0);
  
      	/// Deallocates server-side buffer associated with this instance
	~Sound();

        // {@
	/// @name Playback Functions
	
	/// Play the sound source from the last position.
        void _play();

        /// Pauses the sound source at the current playback position
        void _stop();

        /// Set the looping state
	/// false = no looping, true = looping 
        /// @param[in] bool loop
        int _loop(bool loop);
        // @}
       
        /*// {@
	/// @name Sound Parameter Functions

        /// Set the current playback position in seconds 
        /// @param[in] float seconds
	void _setPlaybackPosition(float seconds);
  
        /// Set the current gain from 0 - 1
        /// @param[in] float gain
        void _setGain(float gain);

        /// Set the current playback rate
	/// 1 is regular, 2 is double speed, .5 half speed etc.
	/// @param[in] float rateScalar
        void _setRate(float rateScalar);

        /// Initiate a linear fade in/out relative to the
        /// gain at the time this function is called
        /// @param[in] float final gain
        /// @param[in] float fade duration
        void _fade(float finalGain, float fadeDuration);
        // @}*/
 
    private:

        void _init(Client_Server * cs, const std::string &filepath, int initAction);
	
	Client_Server * _cs;
	Buffer * _buffer;
        Synth *  _synth;
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

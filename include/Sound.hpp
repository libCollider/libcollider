/// @file Client_Server.hpp
/// @brief Header file for Client_Server.hpp
/// @author Eric Hamdan erichamdan@gmail.com

#ifndef SOUND
#define SOUND

#include <string>

namespace ColliderPlusPlus {

  /// This class represents a user manipulable Soundfile Player, essentially mirroring
  /// the OAS class of the same name by Shreenidhi Chowkwale
  /// @ref https://github.com/CalVR/Open-Audio-Server/blob/master/client/src/Sound.h
  class Sound 
  {
    public:
	
        /// Create a new sound source 
	/// Channel count is determined by file
	Sound(const std::string &filepath = "");
  
      	/// Deallocates server-side buffer associated with this instance
	~Sound();

        // {@
	/// @name Playback Functions
	
	/// Play the sound source from specified position. Default is beginning of file
        /// @param[in] float Playback position seconds
        void play(float seconds = 0);
 
        /// Pauses the sound source at the current playback position
        void pause();

        /// Stops playing the sound source. Playback will resume from the beginning
        void stop();

        void loop(bool loop);
        // @}

	void setPlaybackPosition(float seconds);

        void setGain(float gain);

	void setPitch(float pitchScalar);

        void fade(float finalGain, float fadeDuration);
 
        


    private:
  }
} //namespace ColliderPlusPlus
#endif

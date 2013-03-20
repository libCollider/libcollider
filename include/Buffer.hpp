/// @file Buffer.hpp
/// @brief Header file for Buffer.hpp
/// @author Eric Hamdan erichamdan@gmail.com
#ifndef BUFFER
#define BUFFER

#include "Client_Server.hpp"
#include <string>

namespace ColliderPlusPlus {

  /// This class represents a client-side version of a server buffer
  class Buffer
  {
    public:

        /// Default Constructor
        Buffer();
  
        /// Create a Buffer with buffer number specified by bufNum parameter
	/// @param[in] Client_Server instance
        /// @param[in] int Buffer Number
	Buffer(Client_Server * cs, int bufNum);
   
        /// Destructor
        ~Buffer();
  
        /// Returns this Buffer's number as an int
        /// @returns int Buffer Number
        int _getBufNum() const {return _bufNum;} //return id of server-side buffer
  
        /// Returns this Buffer's sample frame count as an int
        /// @returns int Buffer sample frame count
	int _getFrameNum() const {return _numFrames;} //return sample frames of server-side buffer

        /// Returns this Buffer's channel count as an int
        /// @returns int Buffer channel count
	int _getChanNum() const {return _numChans;}
 
        /// Returns this Buffer's sample rate
        /// @returns int Buffer sample rate
 	int _getSampRate() const {return _sampRate;}

        /// Returns the file path of this Buffer's loaded soundfile
        /// @returns const std::string& Soundfile Path
	const std::string& _getFilePath() const {return _filePath;}

        /// Returns true if the Node was freed from the server by 
        /// calling _free() BEFORE the destructor of this Node is called
        /// @returns true if freed from server with _free() prior to destruction
        bool _getManuallyFreed() const {return _manuallyFreed;}

        /// Command server to allocate memory for this Buffer
        /// @param[in] Client_Server& Client_Server instance
        /// @param[in] int Number of Sample Frames
        /// @param[in] int Number of Channels
        void _alloc(int numFrames, int numChannels);

        /// Command server to free memory associated with this Buffer
        /// @param[in] Client_Server& Client_Server instance
	void _free();

        /// Command server to query this Buffer
        /// @param[in] Client_Server& Client_Server instance
        void _query(); //Finish me

        /// Command server to load specified Soundfile into Buffer and allocate
        /// just enough space for the Soundfile with the given offset
        /// specified by startFileFrame
        /// @param[in] Client_Server& Client_Server instance
        /// @param[in] const std::string& Soundfile Path
        /// @param[in] int Read file from this sample
        /// @param[in] int Number of Sample Frames to allocate, -1 loads whole Soundfile
	void _allocRead(const std::string& filePath, 
				       	  int startFileFrame = 0,
						 int numFrames = -1); 

    private:
	int _bufNum;
	int _numFrames;
	int _numChans;
	int _sampRate;
	const std::string _filePath;
        bool _manuallyFreed;
	Client_Server * _cs;
  };
} //namespace ColliderPlusPlus

#endif


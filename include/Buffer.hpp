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

        /// Create a Buffer with buffer number specified by bufNum parameter
	/// @param[in] ClientServer instance
        /// @param[in] int Buffer Number
	Buffer(Client_Server * cs, int bufNum);
   
        /// Destructor
        ~Buffer();
  
        /// Returns this Buffer's number as an int
        /// @returns int Buffer Number
        int getBufNum() const {return bufNum;} //return id of server-side buffer
  
        /// Returns this Buffer's sample frame count as an int
        /// @returns int Buffer sample frame count
	int getFrameNum() const {return numFrames;} 

        /// Returns this Buffer's channel count as an int
        /// @returns int Buffer channel count
	int getChanNum() const {return numChans;}
 
        /// Returns this Buffer's sample rate
        /// @returns int Buffer sample rate
 	int getSampRate() const {return sampRate;}

        /// Returns true if the Node was freed from the server by 
        /// calling free() BEFORE the destructor of this Node is called
        /// @returns true if freed from server with free() prior to destruction
        bool getManuallyFreed() const {return manuallyFreed;}

        /// Set this Buffer's buffer number
        /// @param[in] int buffer number
        void setBufNum(int bufNum) {bufNum = bufNum;}

        /// Set this Buffer's frame count
        /// @param[in] int frame count
        void setNumFrames(int numFrames) {numFrames = numFrames;}
    
        /// Set this Buffer's channel count
        /// @param[in] int channel count
        void setNumChans(int numChans) {numChans = numChans;}
 
        /// Set this Buffer's sample rate
        /// @param[in] int sample rate
        void setSampRate(float sampRate) {sampRate = sampRate;}

        /// Command server to allocate memory for this Buffer
        /// @param[in] ClientServer& ClientServer instance
        /// @param[in] int Number of Sample Frames
        /// @param[in] int Number of Channels
        void alloc(int numFrames, int numChannels);

        /// Command server to free memory associated with this Buffer
        /// @param[in] ClientServer& ClientServer instance
	void free();

        /// Send a query for this Buffer to the server and use
        /// the reply to populate the # of frames, channels, and sample rate
        /// of this client-side representation
        /// @param[in] ClientServer& ClientServer instance
        void sync(); 

        /// Command server to load specified Soundfile into Buffer and allocate
        /// just enough space for the Soundfile with the given offset
        /// specified by startFileFrame
        /// @param[in] ClientServer& ClientServer instance
        /// @param[in] const std::string& Soundfile Path
        /// @param[in] int Read file from this sample
        /// @param[in] int Number of Sample Frames to allocate, -1 loads whole Soundfile
	void allocRead(const std::string& filePath, 
				       	  int startFileFrame = 0,
						 int numFrames = -1); 

    private:
	int bufNum;
	int numFrames;
	int numChans;
	int sampRate;
        bool manuallyFreed;
	Client_Server * cs;
  };
} //namespace ColliderPlusPlus

#endif


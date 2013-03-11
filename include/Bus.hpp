/// @file Bus.hpp
/// @brief Header file for Bus.hpp
/// @author Eric Hamdan erichamdan@gmail.com
#ifndef BUS
#define BUS

#include <vector>

namespace ColliderPlusPlus {

  /// This class represents a client-side version of a server bus
  class Bus
  {
    public:
    
        /// Default Constructor
	Bus();
   
        /// Destructor
        ~Bus();

        void _setFloats(std::vector<float> &values);

    private:


  };
} //namespace ColliderPlusPlus

#endif



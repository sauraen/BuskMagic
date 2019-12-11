#if defined (_WIN32) || defined (_WIN64)
  #define       JUCE_WIN32 1
  #define       JUCE_WINDOWS 1
#elif defined (LINUX) || defined (__linux__)
  #define     JUCE_LINUX 1
#elif defined (__APPLE_CPP__) || defined (__APPLE_CC__)
  #define     JUCE_MAC 1
#else
  #error "Unknown platform!"
#endif

#if defined(JUCE_MAC) || defined(JUCE_LINUX)

#include "libusb-0.1.12/usb.c"
#include "libusb-0.1.12/error.c"
#include "libusb-0.1.12/descriptors.c"
#if defined(JUCE_MAC)
#include "libusb-0.1.12/darwin.c"
#elif defined(JUCE_LINUX)
#include "libusb-0.1.12/linux.c"
#endif

#elif defined(JUCE_WINDOWS)

#error "TODO add libusb-win32!"

#else

#error "Platform not supported!"

#endif

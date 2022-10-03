#pragma once
#include "JuceHeader.h"

extern "C" {

#if defined(JUCE_MAC) || defined(JUCE_LINUX)
#include "libusb-0.1.12/usb.h"
#elif defined(JUCE_WINDOWS)
//TODO set up libusb-win32
#else
#error "Platform not supported!"
#endif

};

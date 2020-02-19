#include <atomic>

#include "../config.h"

struct Mask{
    // hue range
    std::atomic_int lowH = {default_lowH};
    std::atomic_int highH = {default_highH};
    // saturation range
    std::atomic_int lowS = {default_lowS};
    std::atomic_int highS = {default_highS};
    // value range
    std::atomic_int lowV = {default_lowV};
    std::atomic_int highV = {default_highV};
};

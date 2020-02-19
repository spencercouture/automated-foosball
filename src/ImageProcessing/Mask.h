#include <atomic>

#include "../config.h"

struct Mask{
    // hue range
    int lowH = {default_lowH};
    int highH = {default_highH};
    // saturation range
    int lowS = {default_lowS};
    int highS = {default_highS};
    // value range
    int lowV = {default_lowV};
    int highV = {default_highV};
};

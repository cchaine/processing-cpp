#include "putils.h"

bool boolean(int value) {
    return value != 0;
}

bool boolean(std::string value) {
    return !strcmp(value.c_str(), "true");
}


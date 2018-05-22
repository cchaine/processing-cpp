#ifndef PUTILS_H
#define PUTILS_H

#include <cmath>
#include <string>
#include <iostream>

const double HALF_PI = M_PI / 2;
const double PI = M_PI;
const double QUARTER_PI = M_PI / 4;
const double TAU = 2 * M_PI;
const double TWO_PI = 2 * M_PI;

template<class T, typename std::enable_if<(std::is_integral<T>()), int>::type = 0>
std::string binary(T value, int digits) {
    int a = value;
    std::string bin = "";
    for(int i = 0; i < digits; i++) {
        bin += std::to_string((a >> (digits - 1 - i)) & 1);
    }
    return bin;

}

template<class T, typename std::enable_if<(std::is_integral<T>()), int>::type = 0> 
std::string binary(T value) {
    return binary(value, 32);
}

bool boolean(int value);
bool boolean(std::string value);

template<class T, typename std::enable_if<(std::is_integral<T>()), int>::type = 0>
std::string hex(T value, int digits) {
    int a = value;
    std::string hex = "";
    for(int i = 0; i < digits/4; i++) {
        int digit = (a >> (digits - 4*(i+1))) & 15;
        std::cout << digit << std::endl;
        if(digit >= 10) {
            hex += char(digit + 55);
        } else {
            hex += std::to_string(digit);
        }
    }
    return hex;
}
#endif

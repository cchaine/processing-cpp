#include <iostream>
#include "customSketch.h"

int main() {
    CustomSketch *  s = new CustomSketch(800, 600);
    s->run();
    delete(s);
}

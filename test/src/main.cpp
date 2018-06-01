#include <iostream>
#include "sketch.h"

int main() {
    Sketch *  s = new Sketch();
    s->run();
    delete(s);
}

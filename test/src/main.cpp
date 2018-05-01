#include <iostream>
#include "sketch.h"

int main() {
    Sketch *  s = new Sketch();
    s->start();
    delete(s);
}

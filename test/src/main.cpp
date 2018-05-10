#include <iostream>
#include "customSketch.h"

int main() {
    CustomSketch *  s = new CustomSketch();
    s->run();
    delete(s);
}

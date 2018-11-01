# processing-cpp

`processing-cpp` is a port in C++ of the Processing library originally written in Java

This port was made by [Clément Chaine](https://github.com/cchaine).

<p align="center">
<img width="500" alt="capture d ecran 2018-11-01 a 21 35 10" src="https://user-images.githubusercontent.com/18381262/47878240-148d7480-de1e-11e8-9757-7d86070e9c73.png">
</p>

## Install

```
git clone https://github.com/cchaine/processing-cpp.git
cd processing-cpp
cmake .
make install
```

## Getting started

To start using the processing-cpp library, you need to create a `Sketch` class that inherits from the `PSketch` class

```cpp
#ifndef SKETCH_H
#define SKETCH_H

#include "psketch.h"

class Sketch : public PSketch {
public:
    Sketch();
    void setup();
    void draw();
    void keyEvent(int key, int action);
};

#endif
```

```cpp
#include "sketch.h"

int main() {
    Sketch * s = new Sketch();
    s->run();
    delete(s);
}
```

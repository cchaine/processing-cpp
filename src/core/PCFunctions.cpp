#include "PCFunctions.h"

#include "PCSketch.h"
extern PCShaderProgram* pcShaderProgram;
extern PCQuad* pcQuad;
extern std::map<std::string, PCTriangle*> pcTriangles;

void frameRate(int value) {
    if(value > 0){
        TARGET_FPS = value;
    } else {
        std::cout << "Can't set a framerate lower than 1\nUse noLoop() instead of framerate(0)" << std::endl;
    }
}

void background(int r, int g, int b) {
    glClearColor(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void rectMode(int value) {
    RECTMODE = value;
}

void imageMode(int value) {
    IMAGEMODE = value;
}

void rect(int x, int y, int width, int height) {
    glm::mat4 model = glm::mat4();
    model = glm::translate(model, glm::vec3(x + width / 2*RECTMODE + TRANSLATE.x, y + height / 2*RECTMODE + TRANSLATE.y, 0.0f));  
    
    model = glm::translate(model, glm::vec3(-0.5f * width * RECTMODE, -0.5f * height * RECTMODE, 0.0f)); 
    if(ANGLEMODE == RADIANS){
        model = glm::rotate(model, -ROTATE, glm::vec3(0.0f, 0.0f, 1.0f)); 
    }else{
        model = glm::rotate(model, float(-ROTATE * TWO_PI / 360.0), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    model = glm::translate(model, glm::vec3(0.5f * width * RECTMODE, 0.5f * height * RECTMODE, 0.0f));

    model = glm::scale(model, glm::vec3(width / 2, height / 2, 1.0f));

    pcShaderProgram->uniform4m("model", model);

    pcShaderProgram->uniform3f("fillColor", FILLCOLOR);
    pcShaderProgram->uniform1i("isTex", 0);

    pcShaderProgram->use();
    glBindVertexArray(pcQuad->getVao());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    std::stringstream ss;
    ss << x1 << y1 << x2 << y2 << x3 << y3;
    std::string hash = ss.str();

    PCTriangle* triangle;

    std::map<std::string, PCTriangle*>::iterator it;
    it = pcTriangles.find(hash);
    if(it == pcTriangles.end()){
        float vertices[] = {
            x1, y1,
            x2, y2,
            x3, y3
        };
        for(int i = 0; i < 6; i++){
            std::cout << vertices[i] << std::endl;
        }
        triangle = new PCTriangle(vertices);
        pcTriangles.insert(std::pair<std::string, PCTriangle*>(hash, triangle));
    } else {
        triangle = pcTriangles[hash];
    }

    glm::mat4 model = glm::mat4();
    model = glm::translate(model, glm::vec3(TRANSLATE.x, TRANSLATE.y, 0.0f));  
    
    if(ANGLEMODE == RADIANS){
        model = glm::rotate(model, -ROTATE, glm::vec3(0.0f, 0.0f, 1.0f)); 
    }else{
        model = glm::rotate(model, float(-ROTATE * TWO_PI / 360.0), glm::vec3(0.0f, 0.0f, 1.0f));
    }

    pcShaderProgram->uniform4m("model", model);

    pcShaderProgram->uniform3f("fillColor", FILLCOLOR);
    pcShaderProgram->uniform1i("isTex", 0);

    pcShaderProgram->use();
    glBindVertexArray(triangle->getVao());
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void fill(int value) {
    fill(value, value, value);
}

void fill(int r, int g, int b) {
    FILLCOLOR = glm::vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
}

void image(PImage* texture, int x, int y) {
    image(texture, x, y, texture->getOriginalWidth(), texture->getOriginalHeight());
}

void image(PImage* texture, int x, int y, const short preferredSize, int value) {
    if(preferredSize == PREFERRED_WIDTH) {
        int width = value;
        int height = texture->getHeightFromPreferredWidth(value);
        image(texture, x, y, width, height);
    }else if(preferredSize == PREFERRED_HEIGHT) {
        int height = value;
        int width = texture->getWidthFromPreferredHeight(value);
        image(texture, x, y, width, height);
    }
}

void image(PImage* texture, int x, int y, int width, int height) {
    glm::mat4 model = glm::mat4();
    model = glm::translate(model, glm::vec3(x + width / 2*IMAGEMODE + TRANSLATE.x, y + height / 2*IMAGEMODE + TRANSLATE.y, 0.0f));  
    
    model = glm::translate(model, glm::vec3(-0.5f * width * IMAGEMODE, -0.5f * height * IMAGEMODE, 0.0f)); 
    if(ANGLEMODE == RADIANS){
        model = glm::rotate(model, -ROTATE, glm::vec3(0.0f, 0.0f, 1.0f)); 
    }else{
        model = glm::rotate(model, float(-ROTATE * TWO_PI / 360.0), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    model = glm::translate(model, glm::vec3(0.5f * width * IMAGEMODE, 0.5f * height * IMAGEMODE, 0.0f));

    model = glm::scale(model, glm::vec3(width / 2, height / 2, 1.0f));

    pcShaderProgram->uniform4m("model", model);

    pcShaderProgram->uniform3f("fillColor", FILLCOLOR);
    pcShaderProgram->uniform1i("tex", 0);
    pcShaderProgram->uniform1i("isTex", 1);

    pcShaderProgram->use();
    glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
    glBindVertexArray(pcQuad->getVao());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

PImage* loadImage(std::string path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int w, h;
    unsigned char* image = SOIL_load_image(path.c_str(), &w, &h, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    SOIL_free_image_data(image);

    PImage* texture = new PImage(textureID, w, h);
    return texture;
}

int randInt(int left, int right) {
    return rand() % right + left;
}

int randInt(int right) {
    return randInt(0, right);
}

float map(float value, float start1, float stop1, float start2, float stop2) {
    float result = value;
    result -= start1;
    float stop3 = stop1 - start1;
    float stop4 = stop2 - start2;
    result = stop4 / stop3 * result;
    return result;
}

void pushMatrix() {
    if(TRANSLATE_STACK->size() <= 30){
        TRANSLATE_STACK->push_back(TRANSLATE);
        ROTATE_STACK->push_back(ROTATE);
	RECTMODE_STACK->push_back(RECTMODE);
    }else{
        std::cout << "pushMatrix() can't be called more than 30 times.\nYou may have forgotten to popMatrix()" << std::endl;
        exit(-1);
    }
}

void resetMatrix() {
    TRANSLATE = glm::vec2(0.0, 0.0);
    ROTATE = 0;
    RECTMODE = CORNER;
}

void popMatrix() {
    TRANSLATE = TRANSLATE_STACK->back();
    TRANSLATE_STACK->pop_back();
    ROTATE = ROTATE_STACK->back();
    ROTATE_STACK->pop_back();
    RECTMODE = RECTMODE_STACK->back();
    RECTMODE_STACK->pop_back();
}

void translate(float x, float y) {
    TRANSLATE = glm::vec2(TRANSLATE.x + x, TRANSLATE.y + y);
}

void rotate(float angle) {
    ROTATE += angle;
}

void angleMode(int value) {
    ANGLEMODE = value;
}

void resetTranslation() {
    TRANSLATE = glm::vec2(0.0, 0.0);
}

void resetRotation() {
    ROTATE = 0.0;
}

void lineWeight(int value) {
    LINEWEIGHT = value;
}

void line(float x1, float y1, float x2, float y2) {
  pushMatrix();
  rectMode(CORNER);
  
  glm::vec2 vect = glm::vec2(x2 - x1, y2 - y1);
  glm::vec2 vectN = glm::normalize(vect);
  glm::vec2 ex = glm::vec2(0, 1);

  float angle = acos(glm::dot(vectN, ex));
  if(ANGLEMODE == DEGREES){
    angle *= 180/PI;
  }

  float length = glm::length(vect);
  
  translate(x1, y1);
  if(vect.x < 0){
    rotate(-angle+ 90*ANGLEMODE + PI/2*(1-ANGLEMODE));
    length *= -1;
   }else{
    rotate(angle - 90*ANGLEMODE - PI/2*(1-ANGLEMODE));
   }
  rect(0, 0, length, LINEWEIGHT);

  popMatrix();
}

/* render.h */
#pragma once

#include <iostream>
#include <map>
#include <cstdlib>
#include <vector>
#include <array>

//fontisms
#include "ft2build.h"
#include FT_FREETYPE_H

//glisms
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "gtc/matrix_transform.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <initializer_list>

enum class Align {
    Left = 0, 
    Center = 1, 
    Right = 2, 
    Bottom = Left, 
    Top = Right,
};

enum class Shape {
    Rectangle = 0,
    Circle = 1,
    OutlinedCircle = 2,

};

class Shader
{
public:
    // the program ID
    unsigned int ID;
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};


/* Map with char(glyphname) and a struct for conveniently storing glyph data */
struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

void RenderShape(Shape shape,
                 Shader& s,
                 const std::array<Align, 2>& align,
                 float x, float y, float w, float h,
                 glm::vec4 color);

void RenderText(std::map<char, Character> fCharacters,
                Shader& s,
                const std::string& text,
                const std::array<Align, 2>& align,
                float x, float y, float scale,
                glm::vec4 color);

std::map<char, Character> fontLoad(const char* fontPath);

/* glyph shader paths */
inline const char* glyph_vertexShaderPath = "shaders/glyph.vs.glsl";
inline const char* glyph_fragmentShaderPath = "shaders/glyph.fs.glsl";

extern std::map<char, Character> Characters;
extern unsigned int VAO, VBO;
extern int fbw, fbh;
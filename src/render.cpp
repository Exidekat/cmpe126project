/* some shader/render stuff */
#include "render.h"

Shape::Shape(ShapeForm form, glm::vec4 color) {
    this->form = form;
    this->color = color;
}
Glyph::Glyph(std::map<char, Character> fCharacters, glm::vec4 color) : Shape(ShapeForm::Glyph, color) {
    this->fCharacters = fCharacters;
}

//define shader
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(-1);
    };
    // similar for Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(-1);
    };
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        exit(-1);
    }
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}
void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

/* Function for rendering a Circle or Rectangle */
void RenderShape(Shape shape,
                 Shader& s,
                 const std::array<Align, 2>& align,
                 float x, float y, float w, float h) {
    switch (shape.form) {
        case ShapeForm::Rectangle: {
            s.use();
            float xpos = x;
            float ypos = y;
            switch (align[0]) {
                case Align::Center:
                    xpos = xpos - (w / 2);
                    break;
                case Align::Right:
                    xpos = xpos - w;
                    break;
                case Align::Left:
                    break;
            }
            switch (align[1]) {
                case Align::Center:
                    ypos = ypos - (h / 2);
                    break;
                case Align::Top:
                    ypos = ypos - h;
                    break;
                case Align::Bottom:
                    break;
            }
            // update VBO for them VERTS
            float vertices[6][4] = {
                    {xpos,     ypos,     0.0f, 0.0f},
                    {xpos + w, ypos,     0.0f, 1.0f},
                    {xpos + w, ypos + h, 1.0f, 0.0f},
                    {xpos,     ypos + h, 1.0f, 1.0f}
            };
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            // render quad
            glUniform4f(glGetUniformLocation(s.ID, "uColor"), shape.color.x, shape.color.y, shape.color.z,
                        shape.color.w);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            break;
        }
        case ShapeForm::Circle: {
            s.use();
            glUniform2f(glGetUniformLocation(s.ID, "uCenter"), x, y);
            glUniform4f(glGetUniformLocation(s.ID, "uColor"), shape.color.x, shape.color.y, shape.color.z,
                        shape.color.w);
            glUniform1f(glGetUniformLocation(s.ID, "uRadius2"), 100 * 100);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            break;
        }
        case ShapeForm::OutlinedCircle:
        case ShapeForm::Glyph:
        default:
            break;
    }
}

/* Function for rendering line of text */
void RenderText(Glyph shape,
                Shader& s,
                const std::string& text,
                const std::array<Align, 2>& align,
                float x, float y, float scale) {
    // activate corresponding render state	
    s.use();
    glUniform4f(glGetUniformLocation(s.ID, "textColor"), shape.color.x, shape.color.y, shape.color.z, shape.color.w);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    // iterate through all characters
    std::string::const_iterator c;
    switch (align[0]) {
        case Align::Center: //shift to the horizontal center
            for (c = text.begin(); c != text.end(); c++) {
                Character ch = shape.fCharacters[*c];
                x -= (ch.Advance >> 6) * scale / 2; // bitshift by 6 to get value in pixels (2^6 = 64)
            }
            break;
        case Align::Right: //shift to the far right
            for (c = text.begin(); c != text.end(); c++) {
                Character ch = shape.fCharacters[*c];
                x -= (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
            }
            break;
        case Align::Bottom:
            break;
    }
    float originLineShift = 0.0f;
    switch (align[1]) {
        case Align::Center: //shift to the vertical center
            for (c = text.begin(); c != text.end(); c++) {
                Character ch = shape.fCharacters[*c];
                originLineShift += (ch.Size.y) * scale;
            }
            y -= originLineShift / text.size() / 2;
            break;
        case Align::Top: //shift to the top

            for (c = text.begin(); c != text.end(); c++) {
                Character ch = shape.fCharacters[*c];
                originLineShift += (ch.Size.y) * scale;
            }
            y -= originLineShift / text.size();
            break;
        case Align::Left:
            break;
    }
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = shape.fCharacters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

std::map<char, Character> fontLoad(const char* fontPath) {
    std::map<char, Character> Characters;
    /* Load fontface with Freetype */
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library." << std::endl;
        glfwTerminate();
        exit(-1);
    }
    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font." << std::endl;
        glfwTerminate();
        exit(-1);
    }
    /* The pixel font size we'd like to extract from this face: */
    FT_Set_Pixel_Sizes(face, 0, 48); // 0: dynamically calculate
    /* Test; Load a glyph, 'X' */
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYPE: Failed to load Glyph." << std::endl;
        glfwTerminate();
        exit(-1);
    }
    /* Load and texture map all glyphs*/
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "Attempted to load ASCII char: " << c << std::endl;
            std::cout << "ERROR::FREETYPE: Failed to load Glyph, continuing." << std::endl;
            glfwTerminate();
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    /* Clear FreeType resources */
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return Characters;
}

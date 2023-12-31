#ifndef H_Wordle
#define H_Wordle

#include <iostream>
#include <algorithm>
#include <random>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <map>

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "vec2.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "stackType.h"
#include "queueType.h"
#include "render.h"

enum State {
    Menu,
    Game,
    Gameover,
};
enum Option {
    Play,
    Quit,
};

inline stackType<char>* userinp;

static double limitFPS = 60.0;
inline double timeNow;
inline bool gameActive = true;
inline Option gameOption = Option::Play;
inline State gameState = State::Menu;
inline std::string answer;
inline std::string displayText = "";
inline char charinp;
inline std::vector<std::vector<std::vector<char>>> gameBoard(6, std::vector<std::vector<char>>(5, std::vector<char>(2)));
inline int attempts;
inline int errorTime = 0; // used to print the x for 2 seconds

void window_size_callback(GLFWwindow* window, int width, int height);
void char_callback(GLFWwindow* window, unsigned int codepoint);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void update();
void resetGameBoard();
void initGuess();

inline std::vector<std::string> *words;
inline std::vector<std::string> *wordsPossible;
inline std::vector<std::string> *answers;

void getWords(std::vector<std::string> &v, std::string path);
bool checkForRepeats(std::string word, std::string guess, char letter, std::string currentOutput);
std::string gameLogic(std::string word, std::string guess);
std::map<std::string, std::vector<std::string>*> getProbs(std::string actual);
std::map<std::string, double> getEntropyMap();
double calculateExpectedEntropyOfAWord(std::string word);
#endif

#include "wordle.h"

void window_size_callback(GLFWwindow* window, int width, int height) {
    /* Keep window size at something kosher */
    glfwGetFramebufferSize(window, &fbw, &fbh);
    glViewport(0, 0, fbw, fbh);
}
void char_callback(GLFWwindow* window, unsigned int codepoint) {
    // codepoint is unicode value for key
    // std::cout << "ASCII Pressed: "<< char(codepoint) << "\n";
    charinp = toupper(codepoint);
    switch(gameState) {
        case(Menu):
        case(Gameover):
            if (charinp == 'W' || charinp == 'I')
                gameOption = Play;
            else if (charinp == 'S' || charinp == 'K')
                gameOption = Quit;
            break;
        case(Game):
            if (charinp > 'Z' || charinp < 'A')  // filter out invalid letters
                return;
            if (!userinp->isFullStack())
                userinp->push(charinp);
            break;
    }
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        gameActive = false; // game can be exited anytime using ESCAPE
    switch(gameState) {
        case (Menu):
            if (key == GLFW_KEY_UP && action == GLFW_PRESS)
                gameOption = Play;
            else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
                gameOption = Quit;
            else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
                switch (gameOption) {
                    case (Play):
                        gameState = Game;
                        resetGameBoard();
                        break;
                    case (Quit):
                        gameActive = false;
                        break;
                }
            break;
        case (Game):
            if (action == GLFW_PRESS && displayText == "You win!") {
                gameState = Menu;
                delete userinp;
                userinp = new stackType<char>(5);
                displayText = "";
                attempts = 0;
            } else if ((key == GLFW_KEY_DELETE || key == GLFW_KEY_BACKSPACE) && action == GLFW_PRESS && !userinp->isEmptyStack()) {
                userinp->pop();
            } else if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
                if (!userinp->isFullStack()) {
                    errorTime = 2;
                    break;
                }
                for (const auto & i : *wordsPossible) {
                    // std::cout << i << " =?= " << userinp << std::endl;
                    if (displayText == i) {
                        initGuess();
                        break;
                    }
                }
                if (userinp->isFullStack() && displayText != "You win!")
                    errorTime = 2;
                break;
            }
            break;
        case (Gameover):
            if (action == GLFW_PRESS) {
                gameState = Menu;
                delete userinp;
                userinp = new stackType<char>(5);
                attempts = 0;
            }
            break;
    }
}

void update() {
    // Any game logic that must update without user input goes here
    if (attempts > 5 && displayText != "You win!") {
        displayText = "The Word Was " + answer;
        gameState = Gameover;
    }
}

void resetGameBoard() {
    attempts = 0;
    std::cout << "Resetting board...\n";
    delete words;
    words = new std::vector<std::string>();
    getWords(*words, "src/words.txt");
    for (auto & i : gameBoard) {
        for (auto & j : i) {
            for (char & k : j) {
                k = ' ';
            }
        }
    }
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,(*answers).size()-1);
    answer = (*answers)[dist(rng)];
    std::cout << "The answer to this game is: " << answer << "\n";
}

void initGuess() {
    std::cout << "That's a word!\n";
    std::string hints;
    hints = gameLogic(answer, displayText);
    for (int i = 0; i < 5; i++) {
        gameBoard[attempts][i][0] = displayText[i];
        gameBoard[attempts][i][1] = hints[i];
    }
    std::cout << hints <<"\n";
    attempts++;
    if (hints == "ggggg") {
        std::cout << "You win!\n";
        displayText = "You win!";
    } else {
        errorTime = 2;
	    double wordMap = calculateExpectedEntropyOfAWord(displayText);
	    //std::cout << wordMap[userinp] << std::endl;
        for (auto i : displayText) userinp->pop();
    }
}

//
// Created by prat on 17/11/18.
//

#include "Splash.hpp"
#include "libs/LOG/Logger.hpp"
#include <random>

/**
 * Constructor of Splash
 */
Splash::Splash() : window(nullptr) {
}

/**
 * Splash destructor
 * Close the file
 */
Splash::~Splash() {
    this->myFile.close();
}

/**
 * Splash init function.
 * @param window Window where you want the splash to be displayed
 * @param fontPath Text font path
 */
void Splash::init(std::shared_ptr<gfx::Window> &&window, const std::string &fontPath) {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    this->window = window;
    this->myFile.open("assets/menu/splash.txt");
    this->window->getTextManager()->loadFont("splashFont", fontPath);
}

/**
 * Splash displayer on window function
 */
void Splash::display() {
    auto textManager = this->window->getTextManager();
    this->size = 1;
    this->rotation = -30;
    this->msgName = "splashMsg";
    this->color.insert({{"R", 255}, {"G", 102}, {"B", 0}, {"A", 255}});
    std::string msg = getMsg();
    textManager->addText("splashFont", 30, msg, this->msgName);
    textManager->setColor(this->msgName, this->color.find("R")->second, this->color.find("G")->second, this->color.find("B")->second, this->color.find("A")->second);
    textManager->setCenter(this->msgName, {textManager->getSize(this->msgName).x / 2, textManager->getSize(this->msgName).y / 2});
    textManager->setPosition(this->msgName, {930, 170});
    textManager->setRotation(this->msgName, this->rotation);
}

/**
 * Animation of the splash function
 * @param min
 * @param max
 */
void Splash::animation(float min, float max) {
    auto textManager = this->window->getTextManager();

    if (this->size >= max)
        this->increase = false;
    if (this->size <= min)
        this->increase = true;
    if (this->increase) {
        this->size += 0.02;
        this->rotation += 1.1;
    }
    else {
        this->size -= 0.02;
        this->rotation -= 1.1;
    }
    textManager->setRotation(this->msgName, this->rotation);
    textManager->setScale(this->msgName, this->size, this->size);
}

/**
 * Function that gets the string used for the splash
 * @return the string used for the splash
 */
std::string Splash::getMsg() {
    auto lines = getLines();
    std::string msg = lines.at(std::rand() % lines.size());
    return msg;
}

/**
 * Function that reads the file and put in vector
 * @return the vector of lines
 */
std::vector<std::string> Splash::getLines() {
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(this->myFile, line)) {
        lines.push_back(line);
    }
    return lines;
}

void Splash::switching(bool b) {
    if (b) {
        this->color.find("A")->second = 255;
        this->window->getTextManager()->setColor(this->msgName, this->color.find("R")->second, this->color.find("G")->second, this->color.find("B")->second, this->color.find("A")->second);
    }
    else {
        this->color.find("A")->second = 0;
        this->window->getTextManager()->setColor(this->msgName, this->color.find("R")->second,
                                                 this->color.find("G")->second, this->color.find("B")->second, this->color.find("A")->second);
    }
}


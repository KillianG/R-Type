//
// Created by prat on 17/11/18.
//

#ifndef R_TYPE_SPLASH_HPP
#define R_TYPE_SPLASH_HPP


#include <fstream>
#include <vector>
#include <libs/GFX/Window.hpp>

/**
 * Splash Class
 * Funny text displayed of the menu
 */
class Splash {
public:
    Splash();
    ~Splash();

    void init(std::shared_ptr<gfx::Window> &&window, const std::string &fontPath);
    void display();
    void animation(float min, float max);
    void switching(bool b);
private:
    std::unordered_map<std::string, uint8_t> color;
    std::string getMsg();
    std::vector<std::string> getLines();
    std::fstream myFile;
    std::string msgName;
    std::vector<std::string> lines;
    std::shared_ptr<gfx::Window> window;
    bool increase = true;
    float size;
    float rotation;
    gfx::Vector2Float pos;
};


#endif //R_TYPE_SPLASH_HPP

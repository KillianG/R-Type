//
// Created by NANAA on 20/11/18.
//

#ifndef R_TYPE_SETTINGS_HPP
#define R_TYPE_SETTINGS_HPP

#include <iostream>

struct Settings {

	Settings() : volume(0.5), upKey("Z"), downKey("S"), leftKey("Q"), rightKey("D"), shootKey("Space") {} ;

	float volume = 0.5;
	std::string upKey = "Z";
	std::string downKey = "S";
	std::string leftKey = "Q";
	std::string rightKey = "D";
	std::string shootKey = "Space";
};


#endif //R_TYPE_SETTINGS_HPP

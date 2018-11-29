# General SRCS

#Client SRCS
      set(CLIENT_SRCS Client/MainMenu/Button.cpp
              Client/MainMenu/Button.hpp
        Client/MainMenu/MenuButton.cpp
        Client/MainMenu/MenuButton.hpp
        Client/MainMenu/MainMenu.hpp
        Client/MainMenu/MainMenu.cpp
        Client/MainMenu/Splash.cpp
        Client/MainMenu/Splash.hpp
        Client/MainMenu/Settings.hpp
        Client/game/Game.cpp
        Client/game/Game.hpp
              Client/OptionsMenu/OptionsMenu.hpp
              Client/OptionsMenu/OptionsMenu.cpp
              )

#Server SRCS
set(SERVER_SRCS
        Server/sources/Server.cpp
        Server/includes/Server.hpp
        Server/sources/GameEngine.cpp
        Server/sources/GameConfig.cpp
        Server/sources/GameInfo.cpp
        Server/levelParsing/ParsingLevel.cpp
        Server/sources/DynamicLoader.cpp
        Server/sources/DynamicLoaderManager.cpp
        )


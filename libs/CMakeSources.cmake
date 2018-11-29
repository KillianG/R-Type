#ECS
set(ECS_HEADERS
        ECS/ComponentManager.hpp
        ECS/Manager.hpp
        ECS/System.hpp
        ECS/utiles.hpp)

set(ECS_SRCS
        ECS/Manager.cpp
        ECS/System.cpp)

set(ECS_RESOURCES
        ${ECS_HEADERS}
        ${ECS_SRCS})

#GFX
set(GFX_HEADERS
        GFX/GfxManager.hpp
        GFX/Window.hpp
        GFX/Sprite.hpp
        GFX/KeyboardManager.hpp
        GFX/Singleton.hpp
        GFX/Mouse.hpp
        GFX/SoundManager.hpp
        GFX/Events.hpp
        GFX/TextManager.hpp
        GFX/ResourceManager.hpp)

set(GFX_SRCS
        GFX/GfxManager.cpp
        GFX/Window.cpp
        GFX/Sprite.cpp
        GFX/KeyboardManager.cpp
        GFX/Mouse.cpp
        GFX/SoundManager.cpp
        GFX/Events.cpp
        GFX/TextManager.cpp
        GFX/ResourceManager.cpp)

set(GFX_RESOURCES
        ${GFX_HEADERS}
        ${GFX_SRCS})

#Logger
set(LOGGER_HEADERS
        LOG/Logger.hpp)

set(LOGGER_SRCS
        LOG/Logger.cpp)

set(LOGGER_RESOURCES
        ${LOGGER_HEADERS}
        ${LOGGER_SRCS})

#Exception
set(EXCEPTION_HEADERS
        Exception/Exception.hpp)

set(EXCEPTION_SRCS
        Exception/Exception.cpp)

set(EXCEPTION_RESOURCES
        ${EXCEPTION_HEADERS}
        ${EXCEPTION_SRCS})

#EventManager
set(EVT_HEADERS
        EventManager/BaseEvent.hpp
        EventManager/Receiver.hpp
        EventManager/ClassTypeId.hpp
        EventManager/EventManager.hpp)

set(EVT_SRCS
        EventManager/ClassTypeId.cpp)

set(EVT_RESOURCES
        ${EVT_HEADERS}
        ${EVT_SRCS})

#Network
set(NETWORK_HEADER
        Network/socket/include/ISocketManager.hpp
        Network/RFC/MyRfcClient.hpp
        Network/RFC/MyRfcServer.hpp
        Network/networkUtils.hpp

        Network/socket/include/UdpSocket.hpp
        Network/socket/include/TcpSocket.hpp
        Network/socket/include/TcpManager.hpp
        )
set(NETWORK_SRCS
        Network/socket/src/UdpSocket.cpp
        Network/socket/src/TcpManager.cpp
        Network/socket/src/TcpSocket.cpp
        )

set(NETWORK_RESOURCES
        ${NETWORK_HEADERS}
        ${NETWORK_SRCS})

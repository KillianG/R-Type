//
// Created by killian on 03/11/18.
// Epitech 3 years remaining
// See http://github.com/KillianG
//

#ifndef R_TYPE_SINGLETON_HPP
#define R_TYPE_SINGLETON_HPP

#include <mutex>
#include "../LOG/Logger.hpp"

namespace gfx {
    template<class T>
    class Singleton {
    public:
        static T &get();

    private:
        T &operator=(const T &) = delete;

    protected:
        std::mutex m_mutex;
    };

    /**
     * getter for the instance of the singleton
     * @tparam T The type of the singleton
     * @return the instalnce of singleton with type T
     */
    template<class T>
    T &Singleton<T>::get() {
        static T m_instance;
        return m_instance;
    }
}

#else

namespace gfx {
 //   class Singleton;
//    Singleton<gfx::Manager>;
};


#endif //R_TYPE_SINGLETON_HPP

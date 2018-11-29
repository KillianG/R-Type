/**
 * Unit_tests for EventManager
 */

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include <algorithm>
#include "catch.hpp"
#include "../EventManager.hpp"

class Vector2i {
public:
	Vector2i(int v1, int v2) : x(v1), y(v2) {};
public:
	int x { 0 };
	int y { 0 };
};

class TestEvent : public BaseEvent {};

class ComplexEvent : public BaseEvent {
public:
	ComplexEvent(Vector2i vect) : _vect(vect) {};
public:
	Vector2i _vect;
};

class TestReceiver : public Receiver<TestReceiver> {
public:
	TestReceiver() {
		_evtMgr.subscribe<TestEvent>(*this);
		_evtMgr.subscribe<ComplexEvent>(*this);
	}

public:
    EventManager _evtMgr {};
	void receive(const TestEvent event) {
#ifdef __linux__ 
		std::cout << "\033[1;33m" << __PRETTY_FUNCTION__ << "\033[0m" << std::endl;
#endif
	};
	void receive(const ComplexEvent event) {
#ifdef __linux__ 

		std::cout << "\033[1;33m" << __PRETTY_FUNCTION__ << " [" << event._vect.x << "][" << event._vect.y << "]\033[0m" << std::endl;
#endif
	};
};


TEST_CASE("EventManager", "[EvtMgr]") {
	SECTION("Events") {
		TestReceiver receiver;
		std::cout << "Emit TestEvent" << std::endl;
		receiver._evtMgr.emit<TestEvent>();
		receiver._evtMgr.unsubscribe<TestEvent>(receiver);
		std::cout << "\033[1;32m" << "Unscribed to TestEvent" << "\033[0m" << std::endl;
		std::cout << "Emit TestEvent" << std::endl;
		receiver._evtMgr.emit<TestEvent>();
	}

	SECTION("Advanceds Events") {
		TestReceiver receiver;
		/**
		 * With ctor
		 */
		receiver._evtMgr.emit<ComplexEvent>(Vector2i(666, 777));
		/**
		 * Without ctor
		 */
		receiver._evtMgr.emit<ComplexEvent>(std::forward<Vector2i>({888, 999}));
	}
}

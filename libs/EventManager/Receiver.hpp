#pragma once

struct BaseReceiver {
	virtual ~BaseReceiver() = default;
};

/**
 * @brief All Receivers must inherit from Receiver
 *
 * CRTP (Curiously Recurring Template Pattern)
 *
 */
template <typename Derived>
struct Receiver : public BaseReceiver {
};

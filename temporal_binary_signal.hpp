#ifndef TEMPORAL_BINARY_SIGNAL_HPP
#define TEMPORAL_BINARY_SIGNAL_HPP

#include <iostream>

enum class State {
    off,
    just_on,
    on,
    just_off
};

class TemporalBinarySignal {
public:
    TemporalBinarySignal();

    void set_on();
    void set_off();
// process must be called every timestep
    void process();
    State get_state() const;

private:
    State current_state; // Current state of the temporal binary signal
    bool raw_signal;     
};

#endif // TEMPORAL_BINARY_SIGNAL_HPP

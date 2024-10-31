#ifndef TEMPORAL_BINARY_SIGNAL_HPP
#define TEMPORAL_BINARY_SIGNAL_HPP

#include <iostream>

enum class State { on, off, just_on, just_off };

class TemporalBinarySignal {
  public:
    TemporalBinarySignal();

    void set_signal(bool value);
    void set_on();
    void set_off();
    // process must be called every timestep
    void process();
    State get_state() const;
    bool is_just_on();
    bool is_just_off();
    bool is_on();
    bool is_off();

  private:
    State current_state; // Current state of the temporal binary signal
    bool raw_signal;
};

#endif // TEMPORAL_BINARY_SIGNAL_HPP

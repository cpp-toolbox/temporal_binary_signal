#ifndef TEMPORAL_BINARY_SIGNAL_HPP
#define TEMPORAL_BINARY_SIGNAL_HPP

#include <iostream>
#include <vector>

enum class State { on, off, just_on, just_off };

class TemporalBinarySignal {
  public:
    TemporalBinarySignal();
    ~TemporalBinarySignal();

    void set_signal(bool value);
    void set_on();
    void set_off();
    void toggle_state();
    // process must be called every timestep
    void process();
    State get_state() const;
    bool is_just_on() const;
    bool is_just_off() const;
    bool has_just_changed() const;
    bool is_on() const;
    bool is_off() const;

    // static function to process all active signals
    static void process_all();

  private:
    State current_state; // current state of the temporal binary signal
    bool raw_signal;

    // static container to keep track of all active signals
    static std::vector<TemporalBinarySignal *> active_signals;
};

#endif // TEMPORAL_BINARY_SIGNAL_HPP

#ifndef TEMPORAL_BINARY_SIGNAL_HPP
#define TEMPORAL_BINARY_SIGNAL_HPP

#include <iostream>
#include <vector>
#include <chrono>

#include "sbpt_generated_includes.hpp"

enum class State { on, off, just_on, just_off };

class TemporalBinarySignal {
  public:
    TemporalBinarySignal();
    ~TemporalBinarySignal();

    void set_signal(bool value);
    void set_on();
    void set_off();
    void toggle_state();
    // todo about to add a history buffer as to when it was called, then we can do analsis on that I think..
    // process must be called every timestep
    void process();
    State get_current_state() const;
    std::string get_current_state_string();

    // this function should be called
    State get_next_state() const;

    bool logging_enabled = false;

    bool is_on() const;
    bool is_off() const;
    bool is_just_on() const;
    bool is_just_off() const;
    bool has_just_changed() const;

    bool next_is_on() const;
    bool next_is_off() const;
    bool next_is_just_on() const;
    bool next_is_just_off() const;
    bool next_has_just_changed() const;

    bool is_on(State state) const;
    bool is_off(State state) const;
    bool is_just_on(State state) const;
    bool is_just_off(State state) const;

    // true iff signal has entered the just on state twice within the last second
    bool is_double_tapped();

    // static function to process all active signals
    static void process_all();

  private:
    State current_state; // current state of the temporal binary signal
    bool raw_signal;
    int num_times_signal_set_since_last_process = 0;

    ExpiringTemporalVector<State> state_history{std::chrono::seconds(5)};

    // static container to keep track of all active signals
    static std::vector<TemporalBinarySignal *> active_signals;
};

#endif // TEMPORAL_BINARY_SIGNAL_HPP

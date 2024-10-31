#include "temporal_binary_signal.hpp"

TemporalBinarySignal::TemporalBinarySignal() 
    : current_state(State::off), raw_signal(false) {}

void TemporalBinarySignal::set_on() {
    raw_signal = true;
}

void TemporalBinarySignal::set_off() {
    raw_signal = false;
}

// Update the state based on the previous raw signal state and the current signal state
void TemporalBinarySignal::process() {
    switch (current_state) {
        case State::on:
            if (!raw_signal) {
                current_state = State::just_off; 
            }
            break;
        case State::off:
            if (raw_signal) {
                current_state = State::just_on; 
            }
            break;
        case State::just_on:
            current_state = raw_signal ? State::on : State::just_off;
            break;
        case State::just_off:
            current_state = not raw_signal ? State::off : State::just_on;
            break;
    }
}

State TemporalBinarySignal::get_state() const {
    return current_state;
}

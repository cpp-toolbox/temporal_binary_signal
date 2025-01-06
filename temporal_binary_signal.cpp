#include "temporal_binary_signal.hpp"

#include <algorithm> // included for std::remove

// Initialize the static container
std::vector<TemporalBinarySignal *> TemporalBinarySignal::active_signals;

TemporalBinarySignal::TemporalBinarySignal() : current_state(State::off), raw_signal(false) {
    // Add this instance to the active signals list
    active_signals.push_back(this);
}

TemporalBinarySignal::~TemporalBinarySignal() {
    active_signals.erase(std::remove(active_signals.begin(), active_signals.end(), this), active_signals.end());
}

void TemporalBinarySignal::set_signal(bool value) { raw_signal = value; }

void TemporalBinarySignal::set_on() { raw_signal = true; }

void TemporalBinarySignal::set_off() { raw_signal = false; }

void TemporalBinarySignal::toggle_state() { raw_signal = not raw_signal; }

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
        current_state = !raw_signal ? State::off : State::just_on;
        break;
    }
}

State TemporalBinarySignal::get_state() const { return current_state; }

bool TemporalBinarySignal::is_on() const { return current_state == State::on; }

bool TemporalBinarySignal::is_off() const { return current_state == State::off; }

bool TemporalBinarySignal::is_just_on() const { return current_state == State::just_on; }

bool TemporalBinarySignal::is_just_off() const { return current_state == State::just_off; }

bool TemporalBinarySignal::has_just_changed() const { return this->is_just_on() or this->is_just_off(); }

void TemporalBinarySignal::process_all() {
    for (auto *signal : active_signals) {
        signal->process();
    }
}

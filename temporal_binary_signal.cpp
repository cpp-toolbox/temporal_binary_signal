#include "temporal_binary_signal.hpp"

#include <algorithm> // included for std::remove

std::vector<TemporalBinarySignal *> TemporalBinarySignal::active_signals;

TemporalBinarySignal::TemporalBinarySignal() : current_state(State::off), raw_signal(false) {
    active_signals.push_back(this);
}

TemporalBinarySignal::~TemporalBinarySignal() {
    active_signals.erase(std::remove(active_signals.begin(), active_signals.end(), this), active_signals.end());
}

std::string TemporalBinarySignal::get_current_state_string() {
    switch (current_state) {
    case State::on:
        return "on";
    case State::off:
        return "off";
    case State::just_on:
        return "just_on";
    case State::just_off:
        return "just_off";
    default:
        return "unknown";
    }
}
void TemporalBinarySignal::set_signal(bool value) { raw_signal = value; }

void TemporalBinarySignal::set_on() { raw_signal = true; }

void TemporalBinarySignal::set_off() { raw_signal = false; }

void TemporalBinarySignal::toggle_state() { raw_signal = not raw_signal; }

void TemporalBinarySignal::process() {
    State next_state = get_next_state();
    current_state = next_state;
    state_history.add(next_state);
}

State TemporalBinarySignal::get_current_state() const { return current_state; }

State TemporalBinarySignal::get_next_state() const {
    // in the followin gswitch if a case is unhandled it means that the default state should be to use the value of
    // current_state, therefore
    State next_state = current_state;

    switch (current_state) {
    case State::on:
        if (!raw_signal) {
            next_state = State::just_off;
        }
        break;
    case State::off:
        if (raw_signal) {
            next_state = State::just_on;
        }
        break;
    case State::just_on:
        next_state = raw_signal ? State::on : State::just_off;
        break;
    case State::just_off:
        next_state = !raw_signal ? State::off : State::just_on;
        break;
    }
    return next_state;
}

bool TemporalBinarySignal::is_on() const { return is_on(current_state); }
bool TemporalBinarySignal::is_off() const { return is_off(current_state); }
bool TemporalBinarySignal::is_just_on() const { return is_just_on(current_state); }
bool TemporalBinarySignal::is_just_off() const { return is_just_off(current_state); }
bool TemporalBinarySignal::has_just_changed() const { return this->is_just_on() or this->is_just_off(); }

bool TemporalBinarySignal::next_is_on() const { return is_on(get_next_state()); }
bool TemporalBinarySignal::next_is_off() const { return is_off(get_next_state()); }
bool TemporalBinarySignal::next_is_just_on() const { return is_just_on(get_next_state()); }
bool TemporalBinarySignal::next_is_just_off() const { return is_just_off(get_next_state()); }
bool TemporalBinarySignal::next_has_just_changed() const { return this->next_is_just_on() or this->next_is_just_off(); }

bool TemporalBinarySignal::is_on(State state) const { return state == State::on; }
bool TemporalBinarySignal::is_off(State state) const { return state == State::off; }
bool TemporalBinarySignal::is_just_on(State state) const { return state == State::just_on; }
bool TemporalBinarySignal::is_just_off(State state) const { return state == State::just_off; }

bool TemporalBinarySignal::is_double_tapped() {
    auto now = std::chrono::steady_clock::now();
    auto one_second_ago = now - std::chrono::seconds(1);
    auto recent_elements = state_history.get_elements_since(one_second_ago);

    int just_on_count = 0;
    for (const State &element : recent_elements) {
        if (element == State::just_on) {
            just_on_count++;
            if (just_on_count == 2) {
                return true;
            }
        }
    }

    return false;
}

/*bool TemporalBinarySignal::about_to_just_change() const {  }*/

void TemporalBinarySignal::process_all() {
    for (auto *signal : active_signals) {
        signal->process();
    }
}

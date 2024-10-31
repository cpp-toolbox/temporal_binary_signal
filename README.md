# temporal_binary_signal
A temporal binary signal is a binary signal along with information related to the possible states it can have over time. 

# details

If that sounds complicated don't worry it's probably something you've run into a few times when working on games, 
for example if you work with keypresses, then sometimes a signal comes in every tick about whether the key is actively being pressed,
you then check if the signal *just* changed and do some specific behavior then, eg shoot a gun or do a certain action.

This small class makes this behavior very simple to model.

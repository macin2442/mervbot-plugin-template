# MERVBot Plugin Template

## About

This is an example bare-bones plugin for MERVBot without any function.

## Dependencies



## Build Instructions

On Debian Bullseye

```
# install dependencies
sudo apt install cmake build-essential

git submodule update --init --recursive

# install dependencies required by mervbot (see `dep/mervbot/README.md`)

mkdir build
cd build
cmake ..
make
```

## Execution

In `build/Spawns.txt` all bot instances are defined. Each bot instance has
a configuration field for its username, password, the arena it enter,
a list of plugins (in the form of dynamically linked libraries) it
will load, a staff password and additional plugin parameters.

In order to start the bots run `cd build && ./mervbot`. To exit press
any key.

Players can interact with the bots by private messaging them. `build/Operators.txt`
defines who gets which privileges when providing the correct password.
Players have to private message the bot with `/!login $PASSWORD` to login.
`/!help` lists additional commands that can be issued given the current
privileges of the player. `/!version` reports loaded plugins.

For an exhaustive list of commands please check `build/Commands.txt` which
can also be used for defining additional command aliases.
# Atari 2600 Emulator
This emulator tries to emulate the Atari 2600 as accurate as needed without having to much performance going away

## User
### Release build
```sh
# configure build as release build (use -G <buildsystem> to change the build system)
cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release

# build the emulator (compiled binary is at ./build/atari2600)
cmake --build ./build
```

### Run
The emulator is under development and not ready to be used for emulating Atari2600 games or generic 6507 programs. \
When you run the emulator it will load a hard coded program that ends per BRK. \
You won't notice any of this, because a release build won't print debug stuff.

## Dev
### Status
- Able to emulate all load, transfer and store operations
- Uses a array as memory to cover $0 - $FFFF without mirror locations
- Loads a fake rom and executes that
- Exits on BRK and dumps all registers

#### Opcodes
20.31% (including illegal opcodes)
```sh
# prints out the text above
python3 scripts/gen_opcodes.py -p
```

### What to do?
While implementing all opcodes has highest priority i think making the memory map is also very important for the accuracy, but at the moment I'm not very sure how important ALL mirror locations are, so i will do the opcodes first.

### Before a commit
Update README.md (this file)

### Tricks
- If implemented a new Opcode
```sh
# first delete the function from the file and then run this (yeah, its kinda shitty ik)
python3 scripts/gen_opcodes.py >> src/cpu/opcodes.c

# then use the command below to replace the implemented opcode percentage in the README
sed -i -e "s/.\{2\}\..\{2\}\%\ \(.*\)/$(python3 scripts/gen_opcodes.py -p)/" README.md
```


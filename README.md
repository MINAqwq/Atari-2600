# Atari 2600 Emulator

This emulator tries to emulate the Atari 2600 as accurate as needed without having to much performance going away


## User



### Release build

```sh
# configure build as release build)
# if you don't know wich compiler u want to use just take use `cc`
sh ./scripts/init.sh [compiler] Release

# build the emulator (compiled binary is at ./build/atari2600)
sh ./scripts/build.sh
```

### Run

The emulator is under development and not ready to be used for emulating Atari2600 games or generic 6507 programs. \
When you run the emulator it will load a hard coded program that ends per BRK. \
You won't notice any of this, because a release build won't print debug stuff.


## Dev



### Debug build

```sh
sh ./scripts/init.sh [compiler] Debug
```


### Status

- Able to emulate all load, transfer, store, stack, logical, arithmetic, increment and decrement operations
- Uses a array as memory to cover $0 - $FFFF without mirror locations
- Loads a fake rom and executes that
- Exits on BRK and dumps all registers


#### Opcodes

55.86% (including illegal opcodes)
```sh
# prints out the text above
python3 scripts/gen_opcodes.py -p
```


### What to do?

Legal opcodes are finished soon and the memory mirroring is also working. Next to do is emulating the TIA to
control the CPU and draw on a window.
The current dummy tia memory gets indexed by a number and i would like to keep it like this.
So we need to make the object structure right or implement a `tia_writ(uint8_t register, uint8_t byte)` function or something like that.

Opcodes im working on atm:
- CLC
- CLD
- CLI
- CLV
- SEC
- SED
- SEI


### Before a commit
- Test your opcodes
- Update README.md (this file)


### Tricks

- If implemented a new Opcode
```sh
# first delete the function from the file and then run this (yeah, its kinda shitty ik)
python3 scripts/gen_opcodes.py >> src/cpu/opcodes.c

# then use the command below to replace the implemented opcode percentage in the README
sed -i -e "s/.\{2\}\..\{2\}\%\ \(.*\)/$(python3 scripts/gen_opcodes.py -p)/" README.md
```



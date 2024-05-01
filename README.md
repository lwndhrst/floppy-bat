# Floppy Bat

Flappy Bird but it's a Floppy Bat.

```sh
git clone https://github.com/lwndhrst/floppy-bat.git --recursive
```

## Building

### Debug

```sh
cmake -B build/debug -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=DEBUG
```

```sh
cmake --build build/debug
```

### Release

```sh
cmake -B build/release -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=RELEASE
```

```sh
cmake --build build/release
```

**Language**: [English](#) | [中文](README.zh.md)

---

# emsdk Simple Usage Notes

## Clone

- https://github.com/emscripten-core/emsdk.git

## Install

```shell
./emsdk install latest
./emsdk activate latest
```

## Start

```shell
source ./emsdk_env.sh
```

## Run

```shell
emcc hello.c -o hello.js -s WASM=1 -O3 -m32
```

```shell
emcc hello.c -o output.js -s WASM=1 -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'
```

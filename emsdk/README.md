# emsdk 简单的使用笔记

## clone

- https://github.com/emscripten-core/emsdk.git

## install

```shell
./emsdk install latest
./emsdk activate latest
```

## start

```shell
source ./emsdk_env.sh
```

## run

```shell
emcc hello.c -o hello.js -s WASM=1 -O3 -m32
```

```shell
emcc hello.c -o output.js -s WASM=1 -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'
```

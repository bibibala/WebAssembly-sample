**语言**: [中文](#) | [English](README.en.md)

---

# Javy 简介

[Javy](https://github.com/bytecodealliance/javy) 是由 Bytecode Alliance 推出的工具链，可以将 JavaScript 代码编译为 WebAssembly (Wasm) 模块。它适用于需要在 Wasm 环境中运行 JS 代码的场景，支持 ECMAScript 2020 标准，基于 WASI 规范。

## 安装 Javy

1. 前往 [Javy Releases](https://github.com/bytecodealliance/javy/releases) 下载适合你操作系统的预编译二进制文件。
2. 解压后将 `javy` 可执行文件加入环境变量（可选）。

## 编写 JS 示例

本目录下的 `index.js` 示例

## 编译 JS 为 Wasm

```shell
javy build index.js -o index.wasm
```

## 运行 Wasm 模块

推荐使用 [Wasmtime](https://github.com/bytecodealliance/wasmtime) 运行：

```shell
echo '{"n": 1, "bar": "hello"}' | wasmtime index.wasm
```

输出示例：
```
{"foo":2,"newBar":"hello!"}
```

## 注意事项
- Javy 生成的 Wasm 仅支持 WASI 环境，不能直接在浏览器运行。
- 仅支持 stdin/stdout 进行输入输出。
- 不支持 Node.js/Promise/异步等高级 JS 特性。
- 适合数据处理、计算等场景。

## 参考链接
- [Javy 官方文档](https://github.com/bytecodealliance/javy)
- [Javy 使用教程](https://blog.csdn.net/gitblog_01225/article/details/143040205)

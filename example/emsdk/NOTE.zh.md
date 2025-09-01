**语言**: [中文](#) | [English](NOTE.en.md)

---

在使用 **Emscripten SDK (emsdk)** 将 C/C++ 编译为 WebAssembly 时，Emscripten 提供了许多工具和宏来控制函数、变量的导出和行为。以下是类似 `EMSCRIPTEN_KEEPALIVE` 的常用方法和宏的列表：

---

### 1. **`EMSCRIPTEN_KEEPALIVE`**

确保函数或变量在编译时不会被优化掉，并导出为 WebAssembly 模块的一部分，供 JavaScript 调用。

#### 用法示例：

```cpp
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int add(int a, int b) {
    return a + b;
}
```

使用时，需要通过 WebAssembly 实例的 `Module` 调用，例如：

```javascript
Module._add(1, 2) // 输出: 3
```

---

### 2. **`EXPORT_NAME`**

设置生成的 WebAssembly 模块的名称，用于 JavaScript 初始化时的命名。

#### 用法示例：

```bash
emcc your_code.cpp -s EXPORT_NAME="MyModule" -o your_code.js
```

然后在 JavaScript 中加载：

```javascript
MyModule().then(instance => {
  console.log(instance._add(1, 2))
})
```

---

### 3. **`EXPORTED_FUNCTIONS`**

显式指定需要导出的函数列表，防止函数因未使用被优化掉。

#### 用法示例：

在编译时添加参数：

```bash
emcc your_code.cpp -s EXPORTED_FUNCTIONS="['_add', '_subtract']" -o your_code.js
```

Emscripten 会确保这些函数被导出并可通过 JavaScript 调用：

```javascript
Module._add(1, 2) // 调用导出的 `add` 函数
```

---

### 4. **`EMSCRIPTEN_BINDINGS`**

通过 Emscripten 的 **embind** 工具导出 C++ 类、函数或变量，使它们以更自然的方式与 JavaScript 交互。

#### 用法示例：

```cpp
#include <emscripten/bind.h>

int add(int a, int b) {
    return a + b;
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("add", &add);
}
```

在 JavaScript 中使用：

```javascript
import Module from "./your_code.js"

Module().then(instance => {
  console.log(instance.add(1, 2)) // 输出 3
})
```

---

### 5. **`MAIN_MODULE` 和 `SIDE_MODULE`**

用于模块化开发，允许将多个 WebAssembly 模块进行链接和动态加载。

- **`MAIN_MODULE`:** 定义主模块。
- **`SIDE_MODULE`:** 定义侧模块，供主模块加载。

#### 用法示例：

编译主模块：

```bash
emcc main.cpp -o main.js -s MAIN_MODULE=1
```

编译侧模块：

```bash
emcc side.cpp -o side.wasm -s SIDE_MODULE=1
```

在主模块中加载侧模块：

```javascript
Module.loadDynamicLibrary("side.wasm", { global: true, nodelete: true })
```

---

### 6. **`ALLOW_MEMORY_GROWTH`**

允许 WebAssembly 内存动态增长，防止因内存不足导致运行时崩溃。

#### 用法示例：

```bash
emcc your_code.cpp -s ALLOW_MEMORY_GROWTH=1 -o your_code.js
```

---

### 7. **`MODULARIZE`**

将生成的模块包装在一个函数中，使其可以通过 `import` 动态加载。

#### 用法示例：

```bash
emcc your_code.cpp -s MODULARIZE=1 -o your_code.js
```

在 JavaScript 中：

```javascript
import Module from "./your_code.js"

Module().then(instance => {
  console.log(instance._add(1, 2))
})
```

---

### 8. **`ASYNCIFY`**

用于支持异步操作，例如处理 `await` 或回调。

#### 用法示例：

```bash
emcc your_code.cpp -s ASYNCIFY -o your_code.js
```

C++ 代码：

```cpp
#include <emscripten.h>
#include <chrono>
#include <thread>

EMSCRIPTEN_KEEPALIVE
void asyncFunction() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EM_ASM({ console.log("Async complete"); });
}
```

在 JavaScript 中：

```javascript
Module._asyncFunction()
```

---

### 9. **`EM_ASM` 和 `EM_JS`**

用于在 C/C++ 中直接嵌入 JavaScript 代码。

#### **`EM_ASM`**

嵌入简单的 JavaScript 代码。

```cpp
#include <emscripten.h>

void callJs() {
    EM_ASM({
        console.log("Hello from C++!");
    });
}
```

#### **`EM_JS`**

嵌入带返回值的 JavaScript 代码。

```cpp
#include <emscripten.h>

EM_JS(int, getNumber, (), {
    return 42;
});
```

---

### 10. **`FETCH`**

支持异步加载文件或数据。

#### 用法示例：

```bash
emcc your_code.cpp -o your_code.js -s FETCH=1
```

C++ 代码：

```cpp
#include <emscripten/fetch.h>

void download(const char* url) {
    emscripten_fetch_t* fetch = emscripten_fetch(EMSCRIPTEN_FETCH_LOAD_TO_MEMORY, url);
    emscripten_fetch_close(fetch);
}
```

---

### 总结

| **功能**          | **方法/宏**                  | **用途**                                    |
| ----------------- | ---------------------------- | ------------------------------------------- |
| 导出函数/变量     | `EMSCRIPTEN_KEEPALIVE`       | 导出函数/变量，防止被优化掉。               |
| 显式指定导出函数  | `EXPORTED_FUNCTIONS`         | 显式导出指定函数。                          |
| 设置模块名称      | `EXPORT_NAME`                | 设置 WebAssembly 模块的名称。               |
| 绑定 C++ 与 JS    | `EMSCRIPTEN_BINDINGS`        | 使用 embind 导出类、函数、变量。            |
| 动态加载模块      | `MAIN_MODULE`, `SIDE_MODULE` | 支持模块化开发，加载多个 WebAssembly 模块。 |
| 内存动态增长      | `ALLOW_MEMORY_GROWTH`        | 允许 WebAssembly 内存动态增长。             |
| 包装模块为函数    | `MODULARIZE`                 | 将模块包装为动态加载函数。                  |
| 异步支持          | `ASYNCIFY`                   | 支持异步操作（如 `await`）。                |
| 嵌入 JS 代码      | `EM_ASM`, `EM_JS`            | 在 C++ 中直接嵌入 JavaScript 代码。         |
| 文件/数据异步加载 | `FETCH`                      | 支持通过异步方式加载文件或数据。            |

通过这些方法和宏，你可以精细控制 Emscripten 的行为，使 C/C++ 和 JavaScript/WebAssembly 之间的交互更加高效。

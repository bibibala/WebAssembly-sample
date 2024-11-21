Cheerp 提供了一些特殊的属性（如 `[[cheerp::jsexport]]`）来支持从 C++ 导出到 JavaScript 的交互。这些属性允许开发者细粒度地控制导出函数、类、变量或对象的行为。

---

### 1. **`[[cheerp::jsexport]]`**
用于将 C++ 的函数、变量、类或方法导出到 JavaScript，使其可直接被 JavaScript 调用。

#### 用法示例：
```cpp
#include <cheerp/clientlib.h>

// 导出普通函数
[[cheerp::jsexport]]
int add(int a, int b) {
    return a + b;
}

// 导出全局变量
[[cheerp::jsexport]]
int globalValue = 42;

// 导出类
class [[cheerp::jsexport]] MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}

    [[cheerp::jsexport]] int getValue() const {
        return value;
    }

    [[cheerp::jsexport]] void setValue(int v) {
        value = v;
    }
};
```

---

### 2. **`[[cheerp::genericjs]]`**
将 C++ 函数转换为纯 JavaScript 函数，而不是 WebAssembly。这种函数完全用 JavaScript 实现，主要用于需要直接操作 DOM 或运行在 JavaScript 运行时的代码。

#### 用法示例：
```cpp
#include <cheerp/clientlib.h>

// 用于与 JavaScript 交互，例如操作 DOM
[[cheerp::genericjs]]
void logToConsole(const char* msg) {
    client::console.log(msg);
}
```

---

### 3. **`[[cheerp::wasm]]`**
将函数标记为需要编译为 WebAssembly 的函数。适用于性能关键代码。

#### 用法示例：
```cpp
#include <cheerp/clientlib.h>

// 此函数强制编译为 WebAssembly
[[cheerp::wasm]]
int multiply(int a, int b) {
    return a * b;
}
```

---

### 4. **`[[cheerp::noinline]]`**
防止函数被内联编译。在调试或需要函数明确分离时使用。

#### 用法示例：
```cpp
[[cheerp::noinline]]
int calculate(int a, int b) {
    return a + b;
}
```

---

### 5. **`[[cheerp::dontinline]]`**
与 `[[cheerp::noinline]]` 类似，确保函数不被内联，通常用于确保函数边界存在。

#### 用法示例：
```cpp
[[cheerp::dontinline]]
int subtract(int a, int b) {
    return a - b;
}
```

---

### 6. **`[[cheerp::static]]`**
用于强制将成员函数或变量导出为静态的。

#### 用法示例：
```cpp
class [[cheerp::jsexport]] Utility {
public:
    [[cheerp::static]]
    static int add(int a, int b) {
        return a + b;
    }
};
```

---

### 7. **`[[cheerp::client]]`**
指定函数或对象在 JavaScript 环境中存在（例如 `window` 或 `document`）。

#### 用法示例：
```cpp
#include <cheerp/client.h>

// 访问 JavaScript 的 `document` 对象
client::Document* doc = client::document;

// 定义一个 JavaScript 函数
[[cheerp::client]]
void alertMessage(const char* msg) {
    client::alert(msg);
}
```

---

### 8. **`[[cheerp::main]]`**
指定程序的入口点（`main`），通常用于生成 WebAssembly。

#### 用法示例：
```cpp
[[cheerp::main]]
int main() {
    return 0;
}
```

---

### 9. **`[[cheerp::wasm_only]]`**
将整个模块标记为仅生成 WebAssembly，禁止 JavaScript 生成。

#### 用法示例：
```cpp
#include <cheerp/clientlib.h>

// 模块完全被编译为 WebAssembly
[[cheerp::wasm_only]]
int fastCompute(int a, int b) {
    return a * b;
}
```

---

### 总结
| 属性                  | 描述                                                                 |
|-----------------------|--------------------------------------------------------------------|
| `[[cheerp::jsexport]]` | 导出函数、变量、类或方法到 JavaScript。                              |
| `[[cheerp::genericjs]]` | 将 C++ 函数转换为纯 JavaScript 函数。                               |
| `[[cheerp::wasm]]`     | 强制将函数编译为 WebAssembly。                                      |
| `[[cheerp::noinline]]` | 防止函数被内联编译。                                               |
| `[[cheerp::dontinline]]` | 防止函数被内联，类似于 `[[cheerp::noinline]]`。                    |
| `[[cheerp::static]]`   | 导出静态成员函数或变量。                                           |
| `[[cheerp::client]]`   | 指定 JavaScript 环境中的对象或函数。                                |
| `[[cheerp::main]]`     | 指定程序的入口点。                                                 |
| `[[cheerp::wasm_only]]`| 将整个模块强制标记为仅生成 WebAssembly，不生成 JavaScript。          |

这些属性可以根据需要组合使用，以便优化性能或控制导出的行为。
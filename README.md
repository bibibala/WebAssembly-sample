**Language**: [English](#) | [中文](README.zh.md)

---

Both Cheerp and Emscripten (EMSDK is the Emscripten Development Kit) are toolchains for compiling C/C++ code to WebAssembly (WASM), but they have some significant differences in functionality, design philosophy, and use cases. Here are their main differences:

---

### **1. Basic Positioning**

| Feature      | Cheerp                                           | Emscripten (EMSDK)                          |
| ------------ | ------------------------------------------------ | ------------------------------------------- |
| **Target**   | Focuses on compiling C++ to high-performance code suitable for Web use | More general-purpose, supports generating WebAssembly and asm.js code |
| **Output Target** | Can generate pure `.wasm` files, also supports output with bridging `.js` | Usually generates `.js` (as bridge) and `.wasm` files |
| **Design Philosophy** | Lightweight, easy integration                     | Feature-rich, but larger files, complex generation |

---

### **2. Output File Differences**

| Feature                    | Cheerp                               | Emscripten                              |
| -------------------------- | ------------------------------------ | --------------------------------------- |
| **Generated JavaScript File** | Lightweight, basically only provides WebAssembly bridging | Heavier, contains extensive runtime and Polyfill |
| **File Dependencies**       | More inclined to use WebAssembly directly | Provides complete JS runtime, works with WASM |
| **Runtime Overhead**        | Smaller (more concise code)          | Larger (more comprehensive functionality, supports more complex scenarios) |

---

### **3. Supported Features**

| Feature               | Cheerp                           | Emscripten                                |
| --------------------- | -------------------------------- | ----------------------------------------- |
| **WebAssembly Export** | Supported, lighter weight, but requires explicit export definition | Full support, can be configured via `EXPORTED_FUNCTIONS` |
| **Multi-threading Support** | Partial support                  | Strong support, built-in WebWorker encapsulation |
| **File System Simulation (FS)** | No built-in file system simulation | Provides `MEMFS` and `NODEFS` file system simulation |
| **Standard Library Support** | Supports common C++ standard libraries | Supports complete C/C++ standard library (larger overhead) |
| **Async API Support** | Partial support, requires manual implementation | Strong support, provides Asyncify and other tools |

---

### **4. Use Cases**

| Scenario              | Cheerp                                         | Emscripten                                    |
| --------------------- | ---------------------------------------------- | --------------------------------------------- |
| **Lightweight Apps**  | Very suitable, generates smaller code, especially suitable for small WASM applications | Less suitable, larger runtime overhead        |
| **Complex Games/Engine Porting** | Not very suitable, lacks direct support for complex scenarios | Very suitable, widely used for Unity, Unreal engine porting |
| **Multi-threading/Complex I/O** | Not very suitable, requires manual implementation of multi-threading and file systems | Very suitable, built-in support for multi-threading and simulated file systems |
| **Cross-platform Support** | Optimized for Web, more suitable for direct browser execution | More general-purpose, supports Node.js and multiple platforms |

---

### **5. Performance and Optimization**

| Feature            | Cheerp                               | Emscripten                               |
| ------------------ | ------------------------------------ | ---------------------------------------- |
| **Performance Optimization** | More focused on generating small files and direct WASM function calls | Focuses on compatibility, but generates more complex code, larger runtime |
| **asm.js Support** | Not supported                        | Supported, can be used for browsers that don't support WASM |

---

### **6. Usage**

- **Cheerp**: Simpler, usually compiled through `clang`:

  ```bash
  clang++ -target cheerp -o output.js your_code.cpp
  ```

  Or directly generate `.wasm` files:

  ```bash
  clang++ -target cheerp -cheerp-mode=wasm -o output.wasm your_code.cpp
  ```

- **Emscripten**: Slightly more complex configuration, compiled using `emcc`:
  ```bash
  emcc your_code.cpp -o output.js -s EXPORTED_FUNCTIONS=['_main']
  ```

---

### **7. File Size Comparison**

| Tool           | Simple C++ Program Generated File Size | Complete WebAssembly Project |
| -------------- | -------------------------------------- | ----------------------------- |
| **Cheerp**     | Smaller, usually only a few KB         | Smaller files, lightweight runtime |
| **Emscripten** | Larger, usually includes 100KB+ runtime | Larger files, more comprehensive functionality |

---

### **8. Summary**

- **Choose Cheerp for scenarios:**

  - Want to generate small WebAssembly files.
  - Don't need complex functionality, such as file system simulation, multi-threading support.
  - Suitable for lightweight Web applications or tools.

- **Choose Emscripten for scenarios:**
  - Need complete C++ standard library support.
  - Want to port complex applications, such as game engines or multi-threaded programs.
  - Not strict about file size requirements, but need comprehensive functionality.

If your goal is lightweight WASM applications for browsers, **Cheerp is more suitable**; if you need to port large projects and want higher functional compatibility, **Emscripten is more powerful**.

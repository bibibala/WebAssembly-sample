<template>
  <div>
    <div>Example of calling cheerp js</div>
    <input v-model="first" />
    <input v-model="second" />
    <button @click="computation">computation</button>
    <span>RESULT: {{ result }}</span>
  </div>

  <div>
    <div>Example of calling cheerp wasm</div>
    <input v-model="third" />
    <input v-model="fourth" />
    <button @click="computationWasm">computation</button>
    <span>RESULT: {{ wasmRes }}</span>
  </div>
</template>

<script setup lang="ts">
import { onMounted, ref } from "vue"
// @ts-ignore
import hello from "../Cheerp/hello.js"

const first = ref<number>(0)
const second = ref<number>(0)
const result = ref<string>("")

async function computation() {
  const data = await hello()
  result.value = String(data.add(first.value, second.value))
}

/**
 *
 * wasm
 *
 */

interface WasmModule {
  i: (third: number, fourth: number) => number
}

const module = ref<WasmModule | null>(null)

onMounted(() => {
  loadWasm()
})

async function loadWasm() {
  const response = await fetch("cheerpWasm.wasm")
  const buffer = await response.arrayBuffer()
  const { instance } = await WebAssembly.instantiate(buffer)
  // @ts-ignore
  module.value = instance.exports as WasmModule
}

const third = ref<number>(0)
const fourth = ref<number>(0)
const wasmRes = ref<string>("")

async function computationWasm() {
  if (module.value && typeof module.value.i === "function") {
    wasmRes.value = String(module.value.i(third.value, fourth.value))
  }
}
</script>

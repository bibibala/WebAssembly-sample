<template>
  <div>
    <div>Cheerp JS</div>
    <input v-model="first"/>
    <input v-model="second"/>
    <button @click="computation">Cheerp js computation</button>
    <span>RESULT: {{ result }}</span>
  </div>

  <div>
    <div>Cheerp wasm</div>
    <input v-model="third"/>
    <input v-model="fourth"/>
    <button @click="computationWasm">Cheerp wasm computation</button>
    <span>RESULT: {{ wasmRes }}</span>
  </div>
</template>

<script setup lang="ts">
import { ref } from "vue";
import hello from './Cheerp/hello.js'


const first = ref(0)
const second = ref(0)
const result = ref('')

async function computation() {
  const data = await hello()
  result.value = data.add(first.value, second.value)
}


async function loadWasm() {
  const response = await fetch('cheerpWasm.wasm');
  const buffer = await response.arrayBuffer();
  const {instance} = await WebAssembly.instantiate(buffer);
  return instance.exports;
}


const third = ref(0)
const fourth = ref(0)
const wasmRes = ref('')

async function computationWasm() {
  const wasm = await loadWasm()
  // 方法1: 直接调用导出的函数
  if (typeof wasm.i === 'function') {
    wasmRes.value = wasm.i(third.value, fourth.value)
  }
}
</script>
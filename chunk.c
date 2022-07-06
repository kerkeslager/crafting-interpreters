#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initLineArray(LineArray* array) {
  array->lines = NULL;
  array->capacity = 0;
  array->count = 0;
}

void writeLineArray(LineArray* array, int line) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->lines = GROW_ARRAY(LineRun, array->lines,
        oldCapacity, array->capacity);
  }

  array->lines[array->count].number = line;
  array->lines[array->count].run = 1;
  array->count++;
}

void freeLineArray(LineArray* array) {
  FREE_ARRAY(LineRun, array->lines, array->capacity);
  initLineArray(array);
}

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  initLineArray(&chunk->lines);
  initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  freeLineArray(&chunk->lines);
  initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(
      uint8_t,
      chunk->code,
      oldCapacity,
      chunk->capacity
    );
  }

  chunk->code[chunk->count] = byte;
  writeLineArray(&chunk->lines, line);
  chunk->count++;
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int offset) {
  int lineRunIndex = 0;
  int cumulativeOffset = 0;

  for(int lineRunIndex = 0; lineRunIndex < chunk->lines.count; lineRunIndex++) {
    cumulativeOffset += chunk->lines.lines[lineRunIndex].run;

    if(cumulativeOffset > offset) {
      return chunk->lines.lines[lineRunIndex].number;
    }
  }

  fprintf(stderr, "%s\n", "Offset is outside line runs");
  exit(1);
}

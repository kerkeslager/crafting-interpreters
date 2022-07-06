#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "memory.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_RETURN,
} OpCode;

typedef struct {
  int capacity;
  int count;
  int* lines;
} LineArray;

void initLineArray(LineArray* array);
void writeLineArray(LineArray* array, int line);
void freeLineArray(LineArray* array);

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  LineArray lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
int addConstant(Chunk* chunk, Value value);
int getLine(Chunk* chunk, int offset);

#endif

#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef struct {
  Chunk* chunk;

  /*
   * TODO Move this inside of run() as a local variable, so that it gets
   * stored in a register. This is used frequently so we want it fast.
   */
  uint8_t* ip;
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();

InterpretResult interpret(Chunk* chunk);

#endif

#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "value.h"
#include "object.h"

void printValue(Value value) {
    switch (value.type) {
      case VAL_BOOL:
        printf(AS_BOOL(value) ? "true" : "false");
        break;
      case VAL_NIL: printf("nil"); break;
      case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
      case VAL_OBJ: printObject(value); break;
    }
}

bool valuesEqual(Value a, Value b) {
  if (a.type != b.type) return false;

  switch (a.type) {
    case VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
    case VAL_NIL:    return true;
    case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
    case VAL_OBJ:    return AS_OBJ(a) == AS_OBJ(b);
      /*
       * TODO
       *
       * Note that the above implementation assumes both a and b
       * are interned. This is correct in Lox because all strings are
       * interned (See section 20.5 of Crafting Interpreters).
       *
       * However, this is a point where I disagree with Nystrom (a statement
       * which I will qualify by saying that I have only read up to chapter
       * 20.5 so far, and it seems possible that Nystrom will fix this problem
       * in the later chapters on garbage collection).
       *
       * Interning strings that come from the code is a good idea, because
       * once you start running, the code doesn't continue increasing in size.
       * But interning ALL strings means that programs which do a lot of
       * operations on strings, such as text editors, will continue interning
       * more and more strings which are never released. This is a memory
       * leak!
       *
       * As such, I'm keeping the original comparison code, with an
       * optimization that checks hashes, below, with a reminder to remove
       * the other changes related to interning all strings in section 20.5.
      {
        ObjString* aString = AS_STRING(a);
        ObjString* bString = AS_STRING(b);

        // TODO Profile to see which of the first two comparisons is a good
        // idea.
        return aString->length == bString->length &&
          aString->hash == bString->hash &&
          memcmp(aString->chars, bString->chars, aString->length) == 0;
      }
      */
    default:         return false; // Unreachable.
  }
}

void initValueArray(ValueArray* array) {
  array->values = NULL;
  array->capacity = 0;
  array->count = 0;
}

void writeValueArray(ValueArray* array, Value value) {
  if (array->capacity < array->count + 1) {
    int oldCapacity = array->capacity;
    array->capacity = GROW_CAPACITY(oldCapacity);
    array->values = GROW_ARRAY(Value, array->values,
        oldCapacity, array->capacity);
  }

  array->values[array->count] = value;
  array->count++;
}

void freeValueArray(ValueArray* array) {
  FREE_ARRAY(Value, array->values, array->capacity);
  initValueArray(array);
}

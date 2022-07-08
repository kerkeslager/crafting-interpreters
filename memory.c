#include <stdio.h>
#include <stdlib.h>

#include "memory.h"
#include "vm.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  void* result = realloc(pointer, newSize);

  if(result == NULL) {
    fprintf( stderr, "%s\n", "Unable to reallocate");
    exit(1);
  }

  return result;
}

static void freeObject(Obj* object) {
  switch (object->type) {
    case OBJ_STRING:
      {
        ObjString* string = (ObjString*)object;
        FREE_ARRAY(char, string->chars, string->length + 1);
        FREE(ObjString, object);
        break;
      }

    // TODO Explicitly handle any other types that could be in here, even if handling is just "return;".
  }
}


void freeObjects() {
  Obj* object = vm.objects;
  while (object != NULL) {
    Obj* next = object->next;
    freeObject(object);
    object = next;
  }
}

#include "OpTree.h"

Op* createOp(uint32_t id) {
    Op* op = (Op*)malloc(sizeof(BasicBlock));
    op->id = id;
    return op;
}

Arg* createArg(uint32_t id, char* description) {
    Op* op = (Op*)malloc(sizeof(BasicBlock));
    op->id = id;
    return op;
}

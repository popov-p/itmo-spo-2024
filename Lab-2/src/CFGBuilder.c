#include "CFGBuilder.h"
#include "AST.h"


void writeBlock(int num, FILE *file, enum BasicBlockType type) {
    if (type == standard) {
        fprintf(file, "    node%d [label=\"BB%d\"];\n", num, num); //NOLINT
    }
    if (type == merge) {
        fprintf(file, "    node%d [label=\"MERGE\"];\n", num); //NOLINT
    }

}

void writeCFGEdges(CFG* cfg, FILE *file) {
    for (int i = 0; i < cfg->block_count; i++) {
        for(int j = 0; j < cfg->blocks[i]->successor_count; j++) {
            fprintf(file, "    node%d -> node%d;\n", i, cfg->blocks[i]->successors[j]); //NOLINT
        }
    }
}

void cfg_walker(CFG* cfg, AST* node, int* lastBlockIndex, ProcessedNodes* processedNodes) {
    if (node == NULL) return;

    if (isProcessed(processedNodes, node)) {
        printf("Debug :: BB :: Already processed node: %s\n", node->token);
        return;
    }


    addProcessed(processedNodes, node);

    char* name = node->token;
        int childCount = node->child_count;
    printf("Debug :: BB :: Visiting node: %s\n", (char*)name);

    if (strcmp(name, "IF") == 0) {
        BasicBlock* ifBlock = createBasicBlock(node);
        addBasicBlock(cfg, ifBlock);
        int currentBlockIndex = cfg->block_count - 1;

        if (*lastBlockIndex != -1) {
            addSuccessor(cfg->blocks[*lastBlockIndex], currentBlockIndex);
        }

        *lastBlockIndex = currentBlockIndex;  // Устанавливаем lastBlockIndex для IF

        // Обход true ветви
        int trueBranchIndex = currentBlockIndex; // Запоминаем индекс для true ветви
        cfg_walker(cfg, getChild(node, 1), &trueBranchIndex, processedNodes);

        // Обход false ветви, если есть
        int falseBranchIndex = -1;
        if (childCount > 2) {  // Есть ELSE блок
            falseBranchIndex = currentBlockIndex; // Запоминаем индекс для false ветви
            cfg_walker(cfg, getChild(node, 2), &falseBranchIndex, processedNodes);
        }

        // Создаем mergeBlock после обработки обеих ветвей
        BasicBlock* mergeBlock = createBasicBlock(NULL);
        addBasicBlock(cfg, mergeBlock);
        int mergeBlockIndex = cfg->block_count - 1;

        // Добавляем переход от true ветви к mergeBlock
        if (trueBranchIndex != -1) {
            addSuccessor(cfg->blocks[trueBranchIndex], mergeBlockIndex);
        }

        // Добавляем переход от false ветви к mergeBlock
        if (falseBranchIndex != -1) {
            addSuccessor(cfg->blocks[falseBranchIndex], mergeBlockIndex);
        }

        *lastBlockIndex = mergeBlockIndex; // Обновляем lastBlockIndex на mergeBlock

        printf("Debug :: BB :: found IF block\n");
    }

    else if (strcmp(name, "=") == 0) {
        if (*lastBlockIndex != -1) {
            BasicBlock* assignBlock = createBasicBlock(node);
            addBasicBlock(cfg, assignBlock);
            int currentBlockIndex = cfg->block_count - 1;
            addSuccessor(cfg->blocks[*lastBlockIndex], currentBlockIndex);
            *lastBlockIndex = currentBlockIndex;

            char* lhs = getChild(node, 0)->token;
            char* rhs = getChild(node, 1)->token;
            printf("BB :: found assignment: %s = %s\n", lhs, rhs);
        }
    }


    for (int i = 0; i < childCount; i++) {
        AST* child = getChild(node, i);
        cfg_walker(cfg, child, lastBlockIndex, processedNodes);
    }

    if (strcmp(node->token, "CALL") == 0) {
        BasicBlock* block = createBasicBlock(node);
        addBasicBlock(cfg, block);
        int currentBlockIndex = cfg->block_count - 1;
        if (*lastBlockIndex != -1) {
            addSuccessor(cfg->blocks[*lastBlockIndex], currentBlockIndex);
        }
        *lastBlockIndex = currentBlockIndex;
        char* func_name = getChild(node, 0)->token;
        printf("Debug :: BB :: found CALL: %s\n", func_name);
    }
}

CFG* generateCFG(AST* head) {
    CFG* cfg = initEmptyCFG();
    ProcessedNodes* pn = createProcessedNodes(100);
    int* lastBlockIndex = (int*)malloc(sizeof(int));
    *lastBlockIndex = -1;
    cfg_walker(cfg, head, lastBlockIndex, pn);
    free(lastBlockIndex);
    free(pn);
    return cfg;
}

void outputCFG(CFG* cfg, FILE* file) {
    fprintf(file, "digraph G {\n"); //NOLINT
    fprintf(file, "    rankdir=TB;\n"); //NOLINT
    fprintf(file, "    start [label=\"%s\"];\n", "Начало"); //NOLINT
    fprintf(file, "    end [label=\"%s\"];\n", "Конец");

    if(cfg->block_count == 0) {
        fprintf(file, "    start -> end;\n");
        return;
    }

    for (int i = 0; i < cfg->block_count; i++) {
        BasicBlock* bb = cfg->blocks[i];
        if(!bb->node)
            writeBlock(i, file, merge);
        else
            writeBlock(i, file, standard);
    }

    writeCFGEdges(cfg, file);
    fprintf(file, "    start -> node%d;\n", 0);
    fprintf(file, "    node%d -> end;\n", cfg->block_count-1);
    for (int i = 0; i < cfg->block_count; i++) {
        outputSubgraph(cfg, i, file);
    }
    fprintf(file, "}\n"); //NOLINT
}



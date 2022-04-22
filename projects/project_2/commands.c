#include "commands.h"
#include "cli.h"

CommandNode *commandHistory;

//int commandsInit() {
//    CommandNode commandNode;
//    commandNode.command = NONE;
//    commandHistory = &commandNode;
//    return 0;
//}

// Command enum

// [SW] function to print/draw the terminal window / GUI/CLI
int SWCommand() {
    drawCards(columns, foundations);
    return 0;
}

// function to handle commands

#include "commands.h"
#include "cli.h"

// Command enum

// [SW] function to print/draw the terminal window / GUI/CLI
int SWCommand() {
    drawCards(columns, foundations);
    return 0;
}

// function to handle commands

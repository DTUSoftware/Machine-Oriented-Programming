#include <stdbool.h>
#include "commands.h"  // Import the commands
#include "cli.h"  // The command-line interface
#include "yukon.h"  // The game

int main() {
    CommandNode startCommandNode;
    startCommandNode.command = NONE;
    startCommandNode.status = 200;
    moveHistory = &startCommandNode;
    lastCommand = &startCommandNode;

    while (true) {
        int status = readCommand();
        // QQ break
        if (status == 200 && lastCommand->command == QQ) {
            break;
        }
    }

    return 0;
}

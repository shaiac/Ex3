#include <vector>
#include "commandsControl.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        const char* filename = argv[1];
        CommandsControl *coco = new CommandsControl();
        coco->ReadLexer(filename);
        coco->Praser();
        delete(coco);
    } else {
        cout << "Need to give file name as argument" << endl;
    }

    return 0;
}

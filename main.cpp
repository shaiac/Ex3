#include <vector>
#include "commandsControl.h"

using namespace std;

int main() {
    CommandsControl *coco = new CommandsControl();
    coco->ReadLexer("fly.txt");
    coco->Praser();
    delete(coco);
    return 0;
}

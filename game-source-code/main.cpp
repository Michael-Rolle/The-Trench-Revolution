#include "GameManager.h"
#include <memory>

int main(){
    auto gameManager = make_unique<GameManager>();
    gameManager->run();
    return 0;
}

#include <iostream>

//Including TowerOfHanoi header file in order to use 
//TowerGame class which is defined in the file TowerOfHanoi.h.
#include "TowerOfHanoi.h"


int main(int argc, char const *argv[])
{
    // The game starts with three disks

    //Instanciating game object from TowerGame class.
    TowerGame game(3);

    //invoking play method on game object.
    game.play();
    return 0;
}


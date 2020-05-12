#include <iostream>
#include "Management.h"
using namespace std;
int main()
{
    Management management;
    //////////////////////////////////////////////////////
    management.loadUserfile();
    management.loadEnemyfile();
    management.seletUser();
    management.loadMapfile();
    management.printMap();
    /////////////////////////////////////////////////////
}
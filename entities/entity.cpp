#include "entity.h"
#include "../source/constants.h"

void EntityList::entListLoop()
{
    do {

        exeBaseAddress = (uintptr_t)GetModuleHandle(nullptr);
        localPlayer = *(Entity**)(exeBaseAddress + 0x17E0A8);
        entityList = (DWORD*)(exeBaseAddress + 0x18AC04);
        numPlayers = (*(int*)(exeBaseAddress + 0x191FD4));

    } while (!exeBaseAddress && !localPlayer && !entityList && !numPlayers);

    std::vector<Entity*> list;

    for (int i = 1; i <= numPlayers; i++)
    {
        DWORD* enemyOffset = (DWORD*)(*entityList + (i * 4));
        if (!enemyOffset)
            continue;

        Entity* enemy = (Entity*)(*enemyOffset);

        if (!localPlayer)
            continue;

        if (!enemy)
            continue;

        if (enemy->health > 100 || enemy->health <= 0)
            continue;
        
        list.push_back(enemy);
    }

    entities.clear();
    entities.assign(list.begin(), list.end());
}
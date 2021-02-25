#include "Nuker.h"

Nuker::Nuker() : IModule(VK_NUMPAD5, Category::WORLD, "Break multiple blocks at once") {
	this->registerIntSetting("radius", &this->nukerRadius, this->nukerRadius, 1, 10);
	this->registerBoolSetting("veinminer", &this->veinMiner, this->veinMiner);
	this->registerBoolSetting("autotool", &this->autotool, this->autotool);
	this->registerBoolSetting("auto destroy", &this->autodestroy, this->autodestroy);
	this->registerBoolSetting("MyMines", &this->MyMines, this->MyMines);



}

Nuker::~Nuker() {
}

const char* Nuker::getModuleName() {
	return ("Nuker");
}


	void Nuker::findToolNuker(int* PicSlot,bool* NoPicInHand) {
	C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
	C_Inventory* inv = supplies->inventory;
/////////////////////////////// If you already got a pic in hand, skip findtool() and return true ///////////
		C_ItemStack* stack = inv->getItemStack(supplies->selectedHotbarSlot);
	if (stack->item != nullptr) {
		if ((*stack->item)->isMiningTool()) {
			*NoPicInHand = false;
		} else {
			for (int n = 0; n < 9; n++) {
				C_ItemStack* stack = inv->getItemStack(n);
				if (stack->item != nullptr) {
					if ((*stack->item)->isMiningTool()) {
						*PicSlot = n;
						supplies->selectedHotbarSlot = n;
						NoPicInHand = false;
					}
				}
			}
		}

	}
}


void Nuker::onTick(C_GameMode* gm) {
	bool NoPicInHand = true;
	int PicSlot = NULL;
	if (!autodestroy) return;
	// if autotool is checked go and find a tool and set StartMining to true if there is any else set it to false
	if (autotool) {
		findToolNuker(&PicSlot, &NoPicInHand);
	}

	vec3_ti tempPos = *gm->player->getPos();
	for (int x = -nukerRadius; x < nukerRadius; x++) {
		for (int y = -nukerRadius; y < nukerRadius; y++) {
			for (int z = -nukerRadius; z < nukerRadius; z++) {
				tempPos.x = (int)gm->player->getPos()->x + x;
				tempPos.y = (int)gm->player->getPos()->y + y;
				tempPos.z = (int)gm->player->getPos()->z + z;
				int X = tempPos.x = (int)gm->player->getPos()->x + x;
				int Y = (int)gm->player->getPos()->y + y;
				int Z = tempPos.z = (int)gm->player->getPos()->z + z;

				bool inDoomyWall = (Z == -65980 && Y >= 136 && X <= -20989 && X >= -20998 || X == -20988 && Y >= 136 && Z >= -65989 && Z <= -65982);
				bool inMezoWall = (X == -20999 && Y >= 115 && Z >= -66055 && Z <= -66012);
				bool Server2One = (X == 5 || X == 11 && Y >= 35 && Z >= 0 && Z <= 8);
				bool inMyMines = inDoomyWall || inMezoWall || Server2One;

				if (tempPos.y > 0 && gm->player->region->getBlock(tempPos)->toLegacy()->material->isSolid) {
					if (autotool) {
						C_PlayerInventoryProxy* supplies = g_Data.getLocalPlayer()->getSupplies();
						C_Inventory* inv = supplies->inventory;
						if (MyMines) {
							if (inMyMines) {
								if (NoPicInHand == false) {
									gm->destroyBlock(&tempPos, 1);
								} 
							}
						}
					}
				}
			}
		}
	}
}
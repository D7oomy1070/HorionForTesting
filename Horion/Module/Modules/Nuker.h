#pragma once
#include "Module.h"

class Nuker : public IModule {
private:
	int delay = 0;
	int nukerRadius = 4;
	bool veinMiner = false;
	bool autodestroy = true;
	bool autotool = true;
	bool MyMines = false;
	void findTool(int* PickSlot,bool* NoPicInHand);
	//void findTool();
	int Ticks{0};



public:
	Nuker();
	~Nuker();

	
	inline bool isAutoMode() { return autodestroy; };
	int getNukerRadius() { return nukerRadius; };

	inline bool isVeinMiner() { return veinMiner; };
	// Inherited via IModule
	virtual const char* getModuleName() override;
	void findTool(int* PicSlot, *bool NoPicInHand);
	virtual void onTick(C_GameMode* gm) override;
	
	void isItInBoard(int x,int y,int z) {
		
	}
};

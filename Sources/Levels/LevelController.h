#pragma once

#include <Sources/Levels/Level.h>
#include <Sources/Graphics.h>

class LevelController
{
private:
	Level * m_pCurrentLevel;

public:
	LevelController();
	~LevelController();

	void LoadLevel(Level * level);
	void ChangeLevel(Level * level);

	void CreateLevelDeviceResources();
	void ReleaseLevelDeviceResources();

	void Update(float dt, HWND hwnd);
	void Render();
};


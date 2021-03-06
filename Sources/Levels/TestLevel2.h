#pragma once

#include <vector>
#include <Sources/Levels/Level.h>
#include <Sources/Players/Player.h>
#include <Sources/Actors/Enemy.h>
#include <Sources/Interfaces/IActor.h>
#include <Sources/Players/PlayerHealthUI.h>



//�����ʿ�
class TestLevel2 : public Level
{
private:
	SpriteSheet		m_SpriteSheet;
	DX_Input*		m_pInput;
	D2D1_RENDER_TARGET_PROPERTIES m_renderProperties;
	bool m_bIsInitialized;

	//Render List
	Player * m_pPlayer;
	std::vector<Enemy>  m_RenderEnemy;
	std::vector<IActor> m_RenderEnvir;
public:
	TestLevel2(DX_Input * pInput);
	TestLevel2(DX_Input * pInput, Player * pPlayer);
	~TestLevel2();

	virtual void Load()   override;
	virtual void Unload() override;
	virtual void Render() override;
	virtual void Update(float dt, HWND hwnd) override;
};


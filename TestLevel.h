#pragma once

#include "Level.h"

class TestLevel : public Level
{
private:
	Graphics			  * m_pGraphics;

	IWICBitmapDecoder	  * m_pDecoder;
	IWICBitmapFrameDecode * m_pFrameDecode;
	IWICFormatConverter	  * m_pConvertedBitmap;
	D2D1_RENDER_TARGET_PROPERTIES m_renderProperties;
	ID2D1Bitmap	* m_pBitmap;

	wchar_t * m_lpszFilePath;
	bool m_bIsInitialized;
public:
	TestLevel(Graphics * gfx);
	~TestLevel();
	
	void Load()   override;
	void Unload() override;
	void Render() override;
	void Update() override;
};


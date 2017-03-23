#include "TestLevel.h"



TestLevel::TestLevel(Graphics * gfx)
	:m_pGraphics(gfx),
	 m_bIsInitialized(true),
	 m_lpszFilePath(L"Level_Background1.jpg")
{
}

TestLevel::~TestLevel()
{
}

void TestLevel::Load() 
{
	assert(m_bIsInitialized == true);

	m_pGraphics->GetImagingFactory()->CreateDecoderFromFilename(
		m_lpszFilePath,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&m_pDecoder
	);

	m_pDecoder->GetFrame(0, &m_pFrameDecode);

	m_pGraphics->GetImagingFactory()->CreateFormatConverter(&m_pConvertedBitmap);

	m_pConvertedBitmap->Initialize(
		m_pFrameDecode,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeCustom
	);

	m_renderProperties = D2D1::RenderTargetProperties();
	m_pGraphics->GetD2DFactory()->GetDesktopDpi(&m_renderProperties.dpiX, &m_renderProperties.dpiY);
	m_pGraphics->GetRenderTaget()->CreateBitmapFromWicBitmap(m_pConvertedBitmap, NULL, &m_pBitmap);


}

void TestLevel::Unload() 
{
	GameUtils::SafeRelease(&m_pDecoder);
	GameUtils::SafeRelease(&m_pFrameDecode);
	GameUtils::SafeRelease(&m_pConvertedBitmap);
	GameUtils::SafeRelease(&m_pBitmap);
}

void TestLevel::Render() 
{
	assert(m_bIsInitialized == true);

	//RECT rect; GetWindowRect(m_pGraphics->GetRenderTaget()->GetHwnd(), &rect);

	D2D1_SIZE_F size = m_pGraphics->GetRenderTaget()->GetSize();

	D2D1_RECT_F rect;
	rect.bottom = size.height;
	rect.left   = 0;
	rect.right  = size.width;
	rect.top    = 0;
		
	m_pGraphics->GetRenderTaget()->DrawBitmap(m_pBitmap, rect);
}

void TestLevel::Update()
{

}
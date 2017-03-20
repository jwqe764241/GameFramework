#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(wchar_t* fileName, Graphics * gfx)
	: gfx(gfx),
	m_pBitmap(NULL),
	m_pBitmapBrush(NULL)
{
	LoadBitmapFromFile(fileName, &m_pBitmap);
	m_spriteWidth = m_pBitmap->GetSize().width;
	m_spriteWidth = m_pBitmap->GetSize().height;
	m_spriteAcross = 1;
}

SpriteSheet::SpriteSheet(wchar_t * fileName, Graphics * gfx, UINT spriteWidth, UINT spriteHeight)
	: SpriteSheet(fileName, gfx)
{
	m_spriteWidth = spriteWidth;
	m_spriteHeight = spriteHeight;
	m_spriteAcross = (UINT)m_pBitmap->GetSize().width / spriteWidth;
}

SpriteSheet::~SpriteSheet()
{
	GameUtils::SafeRelease(&m_pBitmap);
	GameUtils::SafeRelease(&m_pBitmapBrush);
}

void SpriteSheet::Draw()
{
	gfx->GetRenderTaget()->DrawBitmap(
		m_pBitmap,
		D2D1::RectF(0.f, 0.f,
			m_pBitmap->GetSize().width,
			m_pBitmap->GetSize().height),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(0.f, 0.f,
			m_pBitmap->GetSize().width,
			m_pBitmap->GetSize().height)
	);
}

void SpriteSheet::Draw(UINT index, UINT x, UINT y)
{
	D2D1_RECT_F src = D2D1::RectF(
		(FLOAT)((index % m_spriteAcross) * m_spriteWidth),
		(FLOAT)((index / m_spriteAcross) * m_spriteHeight),
		(FLOAT)((index % m_spriteAcross) * m_spriteWidth) + m_spriteWidth,
		(FLOAT)((index / m_spriteAcross) * m_spriteHeight) + m_spriteHeight
	);

	D2D1_RECT_F dest = D2D1::RectF(
		x, y,
		x + m_spriteWidth, y + m_spriteHeight
	);

	gfx->GetRenderTaget()->DrawBitmap(
		m_pBitmap,
		dest,
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		src
	);
}

HRESULT SpriteSheet::LoadBitmapFromFile(
	PCWSTR resourceName,
	ID2D1Bitmap** ppBitmap)
{
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;
	IWICStream *pStream = NULL;
	IWICFormatConverter *pConverter = NULL;
	IWICBitmapScaler *pScaler = NULL;

	DWORD imageFileSize = 0;

	HRESULT hr = gfx->GetImagingFactory()->CreateDecoderFromFilename(
		resourceName,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		hr = gfx->GetImagingFactory()->CreateFormatConverter(&pConverter);
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
		);
	}

	if (SUCCEEDED(hr))
	{
		hr = gfx->GetRenderTaget()->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	GameUtils::SafeRelease(&pDecoder);
	GameUtils::SafeRelease(&pSource);
	GameUtils::SafeRelease(&pStream);
	GameUtils::SafeRelease(&pConverter);
	GameUtils::SafeRelease(&pScaler);

	return hr;
}
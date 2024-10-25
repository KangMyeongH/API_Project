#include "pch.h"
#include "Image.h"

Image::Image() = default;

Image::~Image()
{
	mImage->Release();
	mImage = nullptr;
}

void Image::LoadMyImage(const wchar_t* filepath)
{
	IWICImagingFactory* wicFactory;

	CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));

	IWICBitmapDecoder* decoder;
	IWICBitmapFrameDecode* frame;
	IWICFormatConverter* converter;

	if (S_OK == wicFactory->CreateDecoderFromFilename(filepath, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder))
	{
		if (S_OK == decoder->GetFrame(0, &frame))
		{
			if (S_OK == wicFactory->CreateFormatConverter(&converter))
			{
				if (S_OK == converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeCustom))
				{
					if (S_OK == gDeviceContext->CreateBitmapFromWicBitmap(converter,nullptr,&mImage))
					{
						int result = 1;
					}
				}
				converter->Release();
			}
			frame->Release();
		}
		decoder->Release();
	}

	wicFactory->Release();
}

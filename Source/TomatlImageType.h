#ifndef TOMATL_WINDOWS_BITMAP_IMAGE
#define TOMATL_WINDOWS_BITMAP_IMAGE

typedef BOOL(WINAPI* UpdateLayeredWinFunc) (HWND, HDC, POINT*, SIZE*, HDC, POINT*, COLORREF, BLENDFUNCTION*, DWORD);
static UpdateLayeredWinFunc updateLayeredWindow = nullptr;

/*bool Desktop::canUseSemiTransparentWindows() noexcept
{
if (updateLayeredWindow == nullptr && !juce_isRunningInWine())
updateLayeredWindow = (UpdateLayeredWinFunc)getUser32Function("UpdateLayeredWindow");

return updateLayeredWindow != nullptr;
}*/

//==============================================================================

class WindowsBitmapImage : public ImagePixelData
{
public:
	WindowsBitmapImage(const Image::PixelFormat format,
		const int w, const int h, const bool clearImage)
		: ImagePixelData(format, w, h)
	{
		jassert(format == Image::RGB || format == Image::ARGB);

		static bool alwaysUse32Bits = isGraphicsCard32Bit(); // NB: for 32-bit cards, it's faster to use a 32-bit image.

		pixelStride = (alwaysUse32Bits || format == Image::ARGB) ? 4 : 3;
		lineStride = -((w * pixelStride + 3) & ~3);

		zerostruct(bitmapInfo);
		bitmapInfo.bV4Size = sizeof (BITMAPV4HEADER);
		bitmapInfo.bV4Width = w;
		bitmapInfo.bV4Height = h;
		bitmapInfo.bV4Planes = 1;
		bitmapInfo.bV4CSType = 1;
		bitmapInfo.bV4BitCount = (unsigned short)(pixelStride * 8);

		if (format == Image::ARGB)
		{
			bitmapInfo.bV4AlphaMask = 0xff000000;
			bitmapInfo.bV4RedMask = 0xff0000;
			bitmapInfo.bV4GreenMask = 0xff00;
			bitmapInfo.bV4BlueMask = 0xff;
			bitmapInfo.bV4V4Compression = BI_BITFIELDS;
		}
		else
		{
			bitmapInfo.bV4V4Compression = BI_RGB;
		}

		HDC dc = GetDC(0);
		hdc = CreateCompatibleDC(dc);
		ReleaseDC(0, dc);

		SetMapMode(hdc, MM_TEXT);

		hBitmap = CreateDIBSection(hdc, (BITMAPINFO*)&(bitmapInfo), DIB_RGB_COLORS,
			(void**)&bitmapData, 0, 0);

		previousBitmap = SelectObject(hdc, hBitmap);

		if (format == Image::ARGB && clearImage)
			zeromem(bitmapData, (size_t)std::abs(h * lineStride));

		imageData = bitmapData - (lineStride * (h - 1));
	}

	~WindowsBitmapImage()
	{
		SelectObject(hdc, previousBitmap); // Selecting the previous bitmap before deleting the DC avoids a warning in BoundsChecker
		DeleteDC(hdc);
		DeleteObject(hBitmap);
	}

	ImageType* createType() const override                       { return new NativeImageType(); }

	LowLevelGraphicsContext* createLowLevelContext() override
	{
		sendDataChangeMessage();
		return new LowLevelGraphicsSoftwareRenderer(Image(this));
	}

	void initialiseBitmapData(Image::BitmapData& bitmap, int x, int y, Image::BitmapData::ReadWriteMode mode) override
	{
		bitmap.data = imageData + x * pixelStride + y * lineStride;
		bitmap.pixelFormat = pixelFormat;
		bitmap.lineStride = lineStride;
		bitmap.pixelStride = pixelStride;

		if (mode != Image::BitmapData::readOnly)
			sendDataChangeMessage();
	}

	ImagePixelData* clone() override
	{
		WindowsBitmapImage* im = new WindowsBitmapImage(pixelFormat, width, height, false);

		for (int i = 0; i < height; ++i)
			memcpy(im->imageData + i * lineStride, imageData + i * lineStride, (size_t)lineStride);

		return im;
	}

	static RECT getWindowRect(HWND hwnd)
	{
		RECT r;
		GetWindowRect(hwnd, &r);
		return r;
	}

	void blitToWindow(HWND hwnd, HDC dc, const bool transparent,
		const int x, const int y,
		const uint8 updateLayeredWindowAlpha) noexcept
	{
		SetMapMode(dc, MM_TEXT);

		if (transparent)
		{
			RECT windowBounds = getWindowRect(hwnd);

			POINT p = { -x, -y };
			POINT pos = { windowBounds.left, windowBounds.top };
			SIZE size = { windowBounds.right - windowBounds.left,
				windowBounds.bottom - windowBounds.top };

			BLENDFUNCTION bf;
			bf.AlphaFormat = 1;
			bf.BlendFlags = 0;
			bf.BlendOp = AC_SRC_OVER;
			bf.SourceConstantAlpha = updateLayeredWindowAlpha;

			updateLayeredWindow(hwnd, 0, &pos, &size, hdc, &p, 0, &bf, 2);
		}
		else
		{
			StretchDIBits(dc,
				x, y, width, height,
				0, 0, width, height,
				bitmapData, (const BITMAPINFO*)&bitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
		}
	}

	HBITMAP hBitmap;
	HGDIOBJ previousBitmap;
	BITMAPV4HEADER bitmapInfo;
	HDC hdc;
	uint8* bitmapData;
	int pixelStride, lineStride;
	uint8* imageData;

private:
	static bool isGraphicsCard32Bit()
	{
		HDC dc = GetDC(0);
		const int bitsPerPixel = GetDeviceCaps(dc, BITSPIXEL);
		ReleaseDC(0, dc);
		return bitsPerPixel > 24;
	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WindowsBitmapImage)
};

class TomatlImageType : public ImageType
{
public:
	TomatlImageType() {}
	~TomatlImageType() {}

	ImagePixelData::Ptr create(Image::PixelFormat format, int width, int height, bool clearImage) const override
	{
#ifdef JUCE_WINDOWS
		return new WindowsBitmapImage(format, width, height, clearImage);
#else
		NativeImageType t;
		return t.create(format, width, height, clearImage);
#endif
	}

	int getTypeID() const override
	{
		return 100;
	}
};

#endif
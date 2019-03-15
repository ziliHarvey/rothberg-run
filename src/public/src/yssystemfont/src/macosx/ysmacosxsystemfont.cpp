/* ////////////////////////////////////////////////////////////

File Name: ysmacosxsystemfont.cpp
Copyright (c) 2017 Soji Yamakawa.  All rights reserved.
http://www.ysflight.com

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//////////////////////////////////////////////////////////// */

#include <stdio.h>
#include "../yssystemfont.h"

extern "C" unsigned char *YsMacOSXSystemFont_AllocBuffer(size_t bufSize)
{
	unsigned char *buf=new unsigned char [bufSize];
	return buf;
}

extern "C" void *YsMacOSXSystemFont_CreateContext(void);
extern "C" void YsMacOSXSystemFont_FreeContext(void *ctxtPtr);
extern "C" int YsMacOSXSystemFont_SelectSystemFontWithHeight(void *ctxtPtr,unsigned int height);
extern "C" int YsMacOSXSystemFont_SelectSystemFont(void *ctxtPtr);
extern "C" unsigned char *YsMacOSXSystemFont_RGBABitmap(
	void *ctxtPtr,
	unsigned int *wid,unsigned int *hei,unsigned int *dstBytePerLine,
	const wchar_t str[],unsigned int dstBitPerPixel,
	const unsigned char fgCol[3],const unsigned char bgCol[3],
	int reverse);
extern "C" void YsMacOSXSystemFont_GetTightBitmapSize(void *ctxPtr,int *wid,int *hei,const wchar_t str[]);

YsSystemFontCache::YsSystemFontCache()
{
	internal=(InternalData *)YsMacOSXSystemFont_CreateContext();
}

YsSystemFontCache::~YsSystemFontCache()
{
	YsMacOSXSystemFont_FreeContext(internal);
}

YSRESULT YsSystemFontCache::RequestDefaultFont(void)
{
	return (YSRESULT)YsMacOSXSystemFont_SelectSystemFont(internal);
}

YSRESULT YsSystemFontCache::RequestDefaultFontWithHeight(int height)
{
	return (YSRESULT)YsMacOSXSystemFont_SelectSystemFontWithHeight(internal,height);
}

YSRESULT YsSystemFontCache::MakeSingleBitBitmap(YsSystemFontTextBitmap &bmp,const wchar_t wStr[],YSBOOL reverse) const
{
	unsigned int wid,hei,bytePerLine;
	const unsigned int bitPerPixel=1;
	const unsigned char fgCol[3]={255,255,255},bgCol[3]={0,0,0};

	unsigned char *dat=
		YsMacOSXSystemFont_RGBABitmap(internal,&wid,&hei,&bytePerLine,wStr,bitPerPixel,fgCol,bgCol,reverse);
	if(NULL!=dat)
	{
		bmp.SetBitmap(wid,hei,bytePerLine,bitPerPixel,dat);
		return YSOK;
	}
	return YSERR;
}

YSRESULT YsSystemFontCache::MakeRGBABitmap(YsSystemFontTextBitmap &bmp,const wchar_t wStr[],const unsigned char fgCol[3],const unsigned char bgCol[3],YSBOOL reverse) const
{
	unsigned int wid,hei,bytePerLine;
	const unsigned int bitPerPixel=32;

	unsigned char *dat=
		YsMacOSXSystemFont_RGBABitmap(internal,&wid,&hei,&bytePerLine,wStr,bitPerPixel,fgCol,bgCol,reverse);
	if(NULL!=dat)
	{
		bmp.SetBitmap(wid,hei,bytePerLine,bitPerPixel,dat);
		return YSOK;
	}
	return YSERR;
}

YSRESULT YsSystemFontCache::MakeGrayScaleAndAlphaBitmap(YsSystemFontTextBitmap &bmp,const wchar_t wStr[],unsigned char fgColS,unsigned char bgColS,YSBOOL reverse) const
{
	const unsigned char fgCol[3]={fgColS,fgColS,fgColS},bgCol[3]={bgColS,bgColS,bgColS};

	unsigned int wid,hei,bytePerLine;
	const unsigned int bitPerPixel=16;

	unsigned char *dat=
		YsMacOSXSystemFont_RGBABitmap(internal,&wid,&hei,&bytePerLine,wStr,bitPerPixel,fgCol,bgCol,reverse);
	if(NULL!=dat)
	{
		bmp.SetBitmap(wid,hei,bytePerLine,bitPerPixel,dat);
		return YSOK;
	}
	return YSERR;
}

YSRESULT YsSystemFontCache::GetTightBitmapSize(int &wid,int &hei,const wchar_t wStr[]) const
{
	YsMacOSXSystemFont_GetTightBitmapSize(internal,&wid,&hei,wStr);
	return YSOK;
}


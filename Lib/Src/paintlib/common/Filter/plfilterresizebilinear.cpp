/*
/--------------------------------------------------------------------
|
|      $Id: plfilterresizebilinear.cpp,v 1.13 2004/09/11 12:41:36 uzadow Exp $
|
|      Copyright (c) 1996-2002 Ulrich von Zadow
|
\--------------------------------------------------------------------
*/

#include "plfilterresizebilinear.h"
#include "..\plbitmap.h"
#include "pl2passscale.h"


PLFilterResizeBilinear::PLFilterResizeBilinear (int NewXSize, int NewYSize)
  : PLFilterResize (NewXSize, NewYSize)
{
}

void PLFilterResizeBilinear::Apply(PLBmpBase * pBmpSource, PLBmp * pBmpDest) const
{
  PLASSERT(pBmpSource->GetBitsPerPixel()==32 || pBmpSource->GetBitsPerPixel()==24);

  // Create a new Bitmap 
  pBmpDest->Create(m_NewXSize,
                   m_NewYSize,
                   pBmpSource->GetPixelFormat(),
                   NULL, 0, 
                   pBmpSource->GetResolution());
                     
  // Create a Filter Class from template
  PLBilinearContribDef f(0.64);
  if (pBmpSource->GetBitsPerPixel() == 32) 
  {
    C2PassScale <CDataRGBA_UBYTE> sS(f);
    sS.Scale ((CDataRGBA_UBYTE::_RowType *) pBmpSource->GetLineArray(), 
               pBmpSource->GetWidth(), 
               pBmpSource->GetHeight(), 
               (CDataRGBA_UBYTE::_RowType *) pBmpDest->GetLineArray(),
               pBmpDest->GetWidth(),
               pBmpDest->GetHeight());
  }
  else
  {
    C2PassScale <CDataRGB_UBYTE> sS(f);
    sS.Scale ((CDataRGB_UBYTE::_RowType *) pBmpSource->GetLineArray(), 
               pBmpSource->GetWidth(), 
               pBmpSource->GetHeight(), 
               (CDataRGB_UBYTE::_RowType *) pBmpDest->GetLineArray(),
               pBmpDest->GetWidth(),
               pBmpDest->GetHeight());
  }
}

/*
/--------------------------------------------------------------------
|
|      $Log: plfilterresizebilinear.cpp,v $
|      Revision 1.13  2004/09/11 12:41:36  uzadow
|      removed plstdpch.h
|
|      Revision 1.12  2004/09/11 10:30:40  uzadow
|      Linux build fixes, automake dependency fixes.
|
|      Revision 1.11  2004/09/09 16:52:45  artcom
|      refactored PixelFormat
|
|      Revision 1.10  2004/07/28 13:55:48  artcom
|      Added 24 bpp support to plfilterresizebilinear.
|
|      Revision 1.9  2004/06/15 10:26:13  uzadow
|      Initial nonfunctioning version of plbmpbase.
|
|      Revision 1.8  2003/11/05 15:17:26  artcom
|      Added ability to specify initial data in PLBitmap::Create()
|
|      Revision 1.7  2002/08/04 20:08:01  uzadow
|      Added PLBmpInfo class, ability to extract metainformation from images without loading the whole image and proper greyscale support.
|
|      Revision 1.6  2002/03/31 13:36:42  uzadow
|      Updated copyright.
|
|      Revision 1.5  2001/10/16 17:12:27  uzadow
|      Added support for resolution information (Luca Piergentili)
|
|      Revision 1.4  2001/10/03 14:00:29  uzadow
|      Much improved quality in FilterResizeBilinear.
|
|      Revision 1.3  2001/09/30 16:57:25  uzadow
|      Improved speed of 2passfilter.h, code readability changes.
|
|      Revision 1.2  2001/09/16 20:57:17  uzadow
|      Linux version name prefix changes
|
|      Revision 1.1  2001/09/16 19:03:23  uzadow
|      Added global name prefix PL, changed most filenames.
|
|      Revision 1.5  2001/01/15 15:05:31  uzadow
|      Added PLBmp::ApplyFilter() and PLBmp::CreateFilteredCopy()
|
|      Revision 1.4  2000/01/16 20:43:15  anonymous
|      Removed MFC dependencies
|
|      Revision 1.3  1999/12/08 16:31:40  Ulrich von Zadow
|      Unix compatibility
|
|      Revision 1.2  1999/12/08 15:39:46  Ulrich von Zadow
|      Unix compatibility changes
|
|      Revision 1.1  1999/10/21 16:05:18  Ulrich von Zadow
|      Moved filters to separate directory. Added Crop, Grayscale and
|      GetAlpha filters.
|
|      Revision 1.1  1999/10/19 21:29:45  Ulrich von Zadow
|      Added filters.
|
|
\--------------------------------------------------------------------
*/

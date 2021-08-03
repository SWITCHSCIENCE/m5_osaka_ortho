#ifndef M5TILEIMAGEVIEWER_H
#define M5TILEIMAGEVIEWER_H

#include <Arduino.h>
#include <M5Core2.h>
#include "TileImage.h"

class M5TileImageViewer : public TileImage::Viewer
{
public:
    void (*willLoadImageCallback)(const char *path, uint8_t level, int col, int row);
    TFT_eSprite spriteCache;
    TFT_eSPI &display;
    M5TileImageViewer(TFT_eSPI &display, TileImage::ImageSource &imgsrc, int numCaches = 28)
        : TileImage::Viewer(imgsrc, numCaches), spriteCache(&display), display(display), willLoadImageCallback(NULL){};
    void prepareCache(void);
    void loadImageToCache(TileImage::Rect dst, uint8_t level, int column, int row);
    void drawNoImage(TileImage::Rect rect);
    void drawCachedImage(TileImage::Point dst, TileImage::Rect src);
};

#endif

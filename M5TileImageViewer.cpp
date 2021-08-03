#include "M5TileImageViewer.h"

static const uint16_t NO_IMAGE_COLOR = BLUE;

void M5TileImageViewer::prepareCache(void)
{
    uint32_t tsz = imageSource.tileSize;
    spriteCache.createSprite(tileCache.numCaches * tsz, tsz);
    for (int i = 0; i < tileCache.numCaches; i++)
    {
        tileCache.values[i] = {int32_t(i * tsz), 0, tsz, tsz};
    }
}

void M5TileImageViewer::loadImageToCache(TileImage::Rect dst, uint8_t level, int column, int row)
{
    char url[128];
    imageSource.getImageUrl(url, sizeof(url), level, column, row);
    if (SD.exists(url))
    {
        if (willLoadImageCallback)
        {
            willLoadImageCallback(url, level, column, row);
        }
        spriteCache.fillRect(dst.x, dst.y, dst.w, dst.h, NO_IMAGE_COLOR);
        spriteCache.drawJpgFile(SD, url, dst.x, dst.y, dst.w, dst.h, 0, 0);
    }
}

void M5TileImageViewer::drawNoImage(TileImage::Rect rect)
{
    display.fillRect(rect.x, rect.y, rect.w, rect.h, NO_IMAGE_COLOR);
}

void M5TileImageViewer::drawCachedImage(TileImage::Point dst, TileImage::Rect src)
{
    uint16_t iw = spriteCache.width();
    uint16_t *fb = (uint16_t *)spriteCache.frameBuffer(16) + iw * src.y + src.x;
    bool oldSwapBytes = display.getSwapBytes();
    display.setSwapBytes(false);
    for (int i = 0; i < src.h; i++)
    {
        display.pushImage(dst.x, dst.y + i, src.w, 1, fb);
        fb += iw;
    }
    display.setSwapBytes(oldSwapBytes);
}

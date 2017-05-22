#include <QImage>

#ifndef TILE_H
#define TILE_H

// Tile function to compare and assess the pixel tile and the picture_folder[c] channels: r, g, b, a.

class Tile
{
public:
    Tile ();
    Tile (int r, int g, int b, int a, int x, int y){
        r_tile = r;
        g_tile = g;
        b_tile = b;
        a_tile = a;
        baseX = x;
        baseY = y;
    }
    ~Tile ();

    int findBestPicture(QList<QColor> samplecolors);
    QImage applyBestPicture(QImage canvas, QImage bestPicture, int tileSize);

private:
    // From class Tile public input to private input.
    int r_tile,g_tile,b_tile,a_tile;
    int baseX, baseY;
    QList<QImage> samplepictures;
};

#endif // TILE_H

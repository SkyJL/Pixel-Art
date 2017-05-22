#include "tile.h"
#include <QDebug>
#include <QPainter>

Tile::Tile()
{

}

Tile::~Tile()
{

}


int Tile::findBestPicture(QList<QColor> samplecolors){

    QImage tempImg;
    int r_sample,g_sample,b_sample,a_sample;

    int tempSampleColor = 1000;
    int tempIndex;

    for(int i = 0; i < samplecolors.count(); i++){ // length
        r_sample = samplecolors[i].red();
        g_sample = samplecolors[i].green();
        b_sample = samplecolors[i].blue();
        a_sample = samplecolors[i].alpha();


        // loop through sample color list
        // for every sample color, compare its value range with the color range of the tile
        // condition to update the good sample image


        int ColorRange = abs(r_tile - r_sample) + abs(b_tile - b_sample) +  abs(g_tile  - g_sample) +  abs(a_tile  - a_sample);

         if ( ColorRange <= tempSampleColor ){

            tempSampleColor = ColorRange;

            tempIndex = i;
         }

    }

    return tempIndex;

}

QImage Tile::applyBestPicture(QImage lithograph, QImage bestPicture, int tileSize){

    QPainter painter;

    painter.begin(&lithograph);

    bestPicture.scaled(tileSize,tileSize);

    painter.drawImage(baseX, baseY, bestPicture);

    painter.end();

    return lithograph;
}

/*
 * Tiled Map Editor (Qt)
 * Copyright 2008 Tiled (Qt) developers (see AUTHORS file)
 *
 * This file is part of Tiled (Qt).
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307, USA.
 */

#include "tileset.h"
#include "tile.h"

#include <QBitmap>

using namespace Tiled;

Tileset::~Tileset()
{
    qDeleteAll(mTiles);
}

Tile *Tileset::tileAt(int id) const
{
    return (id < mTiles.size()) ? mTiles.at(id) : 0;
}

bool Tileset::loadFromImage(const QString &fileName)
{
    Q_ASSERT(mTileWidth > 0 && mTileHeight > 0);

    QImage image(fileName);
    if (image.isNull())
        return false;

    QPixmap pixmap = QPixmap::fromImage(image);

    if (mTransparentColor.isValid()) {
        QImage mask = image.createMaskFromColor(mTransparentColor.rgb());
        pixmap.setMask(QBitmap::fromImage(mask));
    }

    const int stopWidth = pixmap.width() - mTileWidth;
    const int stopHeight = pixmap.height() - mTileHeight;

    mTiles.clear();

    for (int y = mMargin; y <= stopHeight; y += mTileHeight + mTileSpacing)
        for (int x = mMargin; x <= stopWidth; x += mTileWidth + mTileSpacing)
            mTiles.append(new Tile(pixmap.copy(x, y, mTileWidth, mTileHeight),
                                   mTiles.size(),
                                   this));

    mColumnCount = (pixmap.width() - mMargin * 2 + mTileSpacing)
                   / (mTileWidth + mTileSpacing);
    mImageSource = fileName;
    return true;
}

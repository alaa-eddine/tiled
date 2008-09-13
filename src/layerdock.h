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

#ifndef LAYERDOCK_H
#define LAYERDOCK_H

#include <QDockWidget>

class QModelIndex;
class QTreeView;
class QUndoStack;

namespace Tiled {
namespace Internal {

class MapDocument;

/**
 * The dock widget that displays the map layers.
 */
class LayerDock : public QDockWidget
{
    Q_OBJECT

public:
    /**
     * Constructor.
     */
    LayerDock(QUndoStack *undoStack, QWidget *parent = 0);

    /**
     * Sets the map for which the layers should be displayed.
     */
    void setMapDocument(MapDocument *mapDocument);

private slots:
    void currentRowChanged(const QModelIndex &index);
    void currentLayerChanged(int index);

private:
    MapDocument *mMapDocument;
    QTreeView *mLayerView;
};

} // namespace Internal
} // namespace Tiled

#endif // LAYERDOCK_H
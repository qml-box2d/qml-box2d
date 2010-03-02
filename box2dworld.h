/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the QmlArcade.
 *
 * QmlArcade is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * QmlArcade is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QmlArcade.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BOX2DENGINE_H
#define BOX2DENGINE_H

#include <QDeclarativeItem>

class b2World;

/**
 * Wrapper class around a Box2D world.
 */
class Box2DWorld : public QDeclarativeItem
{
    Q_OBJECT

public:
    explicit Box2DWorld(QDeclarativeItem *parent = 0);

private:
    b2World *mWorld;
};

QML_DECLARE_TYPE(Box2DWorld)

#endif // BOX2DENGINE_H

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

#include "box2dplugin.h"

#include "box2dworld.h"

Box2DPlugin::Box2DPlugin(QObject *parent) :
    QDeclarativeExtensionPlugin(parent)
{
}

void Box2DPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Box2DWorld>(uri, 2, 0, "World");
}

Q_EXPORT_PLUGIN2(Box2DPlugin, Box2DPlugin)

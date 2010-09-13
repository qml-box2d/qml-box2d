/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the Box2D QML plugin.
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "box2dplugin.h"

#include "box2dworld.h"
#include "box2dbody.h"

Box2DPlugin::Box2DPlugin(QObject *parent) :
    QDeclarativeExtensionPlugin(parent)
{
}

void Box2DPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Box2DWorld>(uri, 2, 0, "World");
    qmlRegisterType<Box2DBody>(uri, 2, 0, "Body");
}

Q_EXPORT_PLUGIN2(Box2DPlugin, Box2DPlugin)

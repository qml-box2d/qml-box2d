/*
 * Box2D QML plugin
 * Copyright (C) 2010 Nokia Corporation
 *
 * This file is part of the Box2D QML plugin.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library;  If not, see <http://www.gnu.org/licenses/>.
 */

#include "box2dplugin.h"

#include "box2dworld.h"
#include "box2dbody.h"
#include "box2ddebugdraw.h"
#include "box2dfixture.h"

Box2DPlugin::Box2DPlugin(QObject *parent) :
    QDeclarativeExtensionPlugin(parent)
{
}

void Box2DPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("Box2D"));

    qmlRegisterType<Box2DWorld>(uri, 1, 0, "World");
    qmlRegisterType<Box2DBody>(uri, 1, 0, "Body");
    qmlRegisterType<Box2DFixture>();
    qmlRegisterType<Box2DBox>(uri, 1, 0, "Box");
    qmlRegisterType<Box2DCircle>(uri, 1, 0, "Circle");
    qmlRegisterType<Box2DPolygon>(uri, 1, 0, "Polygon");
    qmlRegisterType<Box2DDebugDraw>(uri, 1, 0, "DebugDraw");
}

Q_EXPORT_PLUGIN2(Box2DPlugin, Box2DPlugin)

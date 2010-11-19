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

#ifndef BOX2DPLUGIN_H
#define BOX2DPLUGIN_H

#include <QDeclarativeExtensionPlugin>

/**
 * A plugin that exposes Box2D to QML in the form of declarative items.
 */
class Box2DPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT

public:
    explicit Box2DPlugin(QObject *parent = 0);

    void registerTypes(const char *uri);
};

#endif // BOX2DPLUGIN_H

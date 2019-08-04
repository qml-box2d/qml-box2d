/*
 * box2dplugin.cpp
 * Copyright (c) 2010-2011 Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 * Copyright (c) 2011 Daker Fernandes Pinheiro <daker.pinheiro@openbossa.org>
 * Copyright (c) 2011 Joonas Erkinheimo <joonas.erkinheimo@nokia.com>
 *
 * This file is part of the Box2D QML plugin.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "box2dplugin.h"

#include "box2dworld.h"
#include "box2dbody.h"
#include "box2ddebugdraw.h"
#include "box2dfixture.h"
#include "box2djoint.h"
#include "box2ddistancejoint.h"
#include "box2dprismaticjoint.h"
#include "box2drevolutejoint.h"
#include "box2dmotorjoint.h"
#include "box2dweldjoint.h"
#include "box2dpulleyjoint.h"
#include "box2dfrictionjoint.h"
#include "box2dwheeljoint.h"
#include "box2dmousejoint.h"
#include "box2dgearjoint.h"
#include "box2dropejoint.h"
#include "box2dcontact.h"
#include "box2draycast.h"

const int versionMajor = 2;
const int versionMinor = 0;

Box2DPlugin::Box2DPlugin(QObject *parent) :
    QQmlExtensionPlugin(parent)
{
}

void Box2DPlugin::registerTypes(const char *uri)
{
#if !defined(STATIC_PLUGIN_BOX2D)
    Q_ASSERT(QLatin1String(uri) == QLatin1String("Box2D"));
#endif

    qmlRegisterType<Box2DWorld>(uri, versionMajor, versionMinor, "World");
    qmlRegisterUncreatableType<Box2DProfile>(uri, versionMajor, versionMinor, "Profile",
                                             QStringLiteral("Property group of World"));
    qmlRegisterType<Box2DBody>(uri, versionMajor, versionMinor, "Body");
    qmlRegisterUncreatableType<Box2DFixture>(uri, versionMajor, versionMinor, "Fixture",
                                             QStringLiteral("Base type for Box, Circle etc."));
    qmlRegisterType<Box2DBox>(uri, versionMajor, versionMinor, "Box");
    qmlRegisterType<Box2DCircle>(uri, versionMajor, versionMinor, "Circle");
    qmlRegisterType<Box2DPolygon>(uri, versionMajor, versionMinor, "Polygon");
    qmlRegisterType<Box2DChain>(uri, versionMajor, versionMinor, "Chain");
    qmlRegisterType<Box2DEdge>(uri, versionMajor, versionMinor, "Edge");
    qmlRegisterType<Box2DDebugDraw>(uri, versionMajor, versionMinor, "DebugDraw");
    qmlRegisterUncreatableType<Box2DJoint>(uri, versionMajor, versionMinor, "Joint",
                                           QStringLiteral("Base type for DistanceJoint, RevoluteJoint etc."));
    qmlRegisterType<Box2DDistanceJoint>(uri, versionMajor, versionMinor, "DistanceJoint");
    qmlRegisterType<Box2DPrismaticJoint>(uri, versionMajor, versionMinor, "PrismaticJoint");
    qmlRegisterType<Box2DRevoluteJoint>(uri, versionMajor, versionMinor, "RevoluteJoint");
    qmlRegisterType<Box2DMotorJoint>(uri, versionMajor, versionMinor, "MotorJoint");
    qmlRegisterType<Box2DWeldJoint>(uri, versionMajor, versionMinor, "WeldJoint");
    qmlRegisterType<Box2DPulleyJoint>(uri, versionMajor, versionMinor, "PulleyJoint");
    qmlRegisterType<Box2DFrictionJoint>(uri, versionMajor, versionMinor, "FrictionJoint");
    qmlRegisterType<Box2DWheelJoint>(uri, versionMajor, versionMinor, "WheelJoint");
    qmlRegisterType<Box2DMouseJoint>(uri, versionMajor, versionMinor, "MouseJoint");
    qmlRegisterType<Box2DGearJoint>(uri, versionMajor, versionMinor, "GearJoint");
    qmlRegisterType<Box2DRopeJoint>(uri, versionMajor, versionMinor, "RopeJoint");
    qmlRegisterType<Box2DRayCast>(uri, versionMajor, versionMinor, "RayCast");

    qmlRegisterUncreatableType<Box2DContact>(uri, versionMajor, versionMinor, "Contact", QStringLiteral("Contact class"));
}

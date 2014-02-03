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

Box2DPlugin::Box2DPlugin(QObject *parent) :
    QQmlExtensionPlugin(parent)
{
}

void Box2DPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("Box2D"));

    qmlRegisterType<Box2DWorld>(uri, 1, 1, "World");
    qmlRegisterType<Box2DBody>(uri, 1, 1, "Body");
    qmlRegisterUncreatableType<Box2DFixture>(uri, 1,0, "Fixture",
                                             QStringLiteral("Base type for Box, Circle etc."));
    qmlRegisterType<Box2DBox>(uri, 1, 1, "Box");
    qmlRegisterType<Box2DCircle>(uri, 1, 1, "Circle");
    qmlRegisterType<Box2DPolygon>(uri, 1, 1, "Polygon");
    qmlRegisterType<Box2DChain>(uri, 1, 1, "Chain");
    qmlRegisterType<Box2DEdge>(uri, 1, 1, "Edge");
    qmlRegisterType<Box2DDebugDraw>(uri, 1, 1, "DebugDraw");
    qmlRegisterUncreatableType<Box2DJoint>(uri, 1, 1, "Joint",
                                           QStringLiteral("Base type for DistanceJoint, RevoluteJoint etc."));
    qmlRegisterType<Box2DDistanceJoint>(uri, 1, 1, "DistanceJoint");
    qmlRegisterType<Box2DPrismaticJoint>(uri, 1, 1, "PrismaticJoint");
    qmlRegisterType<Box2DRevoluteJoint>(uri, 1, 1, "RevoluteJoint");
    qmlRegisterType<Box2DMotorJoint>(uri, 1, 1, "MotorJoint");
    qmlRegisterType<Box2DWeldJoint>(uri, 1, 1, "WeldJoint");
    qmlRegisterType<Box2DPulleyJoint>(uri, 1, 1, "PulleyJoint");
    qmlRegisterType<Box2DFrictionJoint>(uri, 1, 1, "FrictionJoint");
    qmlRegisterType<Box2DWheelJoint>(uri, 1, 1, "WheelJoint");
    qmlRegisterType<Box2DMouseJoint>(uri, 1, 1, "MouseJoint");
    qmlRegisterType<Box2DGearJoint>(uri, 1, 1, "GearJoint");
    qmlRegisterType<Box2DRopeJoint>(uri, 1, 1, "RopeJoint");

}

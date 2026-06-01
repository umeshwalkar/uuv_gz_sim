#include "HydrodynamicsPlugin.hpp"

#include <gz/plugin/Register.hh>

#include <gz/sim/Link.hh>

#include <cmath>
#include <iostream>

using namespace gz;
using namespace sim;

//////////////////////////////////////////////////
void HydrodynamicsPlugin::Configure(
    const Entity &_entity,
    const std::shared_ptr<const sdf::Element> &,
    EntityComponentManager &,
    EventManager &)
{
    this->model = Model(_entity);

    std::cout
        << "[HydrodynamicsPlugin] Loaded"
        << std::endl;
}

//////////////////////////////////////////////////
void HydrodynamicsPlugin::PreUpdate(
    const UpdateInfo &,
    EntityComponentManager &_ecm)
{
    auto linkEntity =
        this->model.LinkByName(
            _ecm,
            "base_link");

    if (linkEntity == kNullEntity)
        return;

    Link link(linkEntity);

    auto linVel =
        link.WorldLinearVelocity(_ecm);

    auto angVel =
        link.WorldAngularVelocity(_ecm);

    if (!linVel || !angVel)
        return;

    const double u = linVel->X();
    const double v = linVel->Y();
    const double w = linVel->Z();

    const double p = angVel->X();
    const double q = angVel->Y();
    const double r = angVel->Z();

    math::Vector3d dragForce(
        -Xu * u * std::abs(u),
        -Yv * v * std::abs(v),
        -Zw * w * std::abs(w));

    math::Vector3d dragTorque(
        -Kp * p,
        -Mq * q,
        -Nr * r);

    link.AddWorldWrench(
        _ecm,
        dragForce,
        dragTorque);
}

//////////////////////////////////////////////////
GZ_ADD_PLUGIN(
    HydrodynamicsPlugin,
    gz::sim::System,
    gz::sim::ISystemConfigure,
    gz::sim::ISystemPreUpdate)

GZ_ADD_PLUGIN_ALIAS(
    HydrodynamicsPlugin,
    "HydrodynamicsPlugin")
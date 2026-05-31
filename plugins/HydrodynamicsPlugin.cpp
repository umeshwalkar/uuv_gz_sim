#include "HydrodynamicsPlugin.hpp"

#include <gz/plugin/Register.hh>

#include <gz/sim/Link.hh>
// #include <gz/sim/components/WorldLinearVelocity.hh>
// #include <gz/sim/components/WorldAngularVelocity.hh>
#include <gz/sim/components/LinearVelocity.hh>
#include <gz/sim/components/AngularVelocity.hh>

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
        << "HydrodynamicsPlugin loaded"
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

    math::Vector3d force(
        -Xu * u * std::abs(u),
        -Yv * v * std::abs(v),
        -Zw * w * std::abs(w));

    math::Vector3d torque(
        -Kp * p,
        -Mq * q,
        -Nr * r);

    link.AddWorldWrench(
        _ecm,
        force,
        torque);
}

//////////////////////////////////////////////////
GZ_ADD_PLUGIN(
    HydrodynamicsPlugin,
    gz::sim::System,
    HydrodynamicsPlugin::ISystemConfigure,
    HydrodynamicsPlugin::ISystemPreUpdate)
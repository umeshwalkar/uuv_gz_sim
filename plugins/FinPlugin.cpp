#include "FinPlugin.hpp"

#include <gz/plugin/Register.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/Link.hh>
// #include <gz/sim/components/WorldLinearVelocity.hh>
#include <gz/sim/components/LinearVelocity.hh>

using namespace gz;
using namespace sim;

//////////////////////////////////////////////////
void FinPlugin::Configure(
    const Entity &_entity,
    const std::shared_ptr<const sdf::Element> &,
    EntityComponentManager &,
    EventManager &)
{
    this->model = Model(_entity);

    std::cout << "[FinPlugin] Loaded" << std::endl;
}

//////////////////////////////////////////////////
void FinPlugin::PreUpdate(
    const UpdateInfo &,
    EntityComponentManager &_ecm)
{
    auto linkEntity = this->model.LinkByName(_ecm, "base_link");

    if (linkEntity == kNullEntity)
        return;

    Link link(linkEntity);
    auto vel = link.WorldLinearVelocity(_ecm);
    if (!vel)
        return;

    double u = vel->X();

    // VERY SIMPLE CONTROL MODEL (phase 1)
    double finForce = Kfin * u * u;

    // Apply yaw moment (simplified)
    link.AddWorldWrench(
        _ecm,
        math::Vector3d(0, 0, 0),
        math::Vector3d(0, 0, finForce));
}

//////////////////////////////////////////////////
GZ_ADD_PLUGIN(
    FinPlugin,
    gz::sim::System,
    FinPlugin::ISystemConfigure,
    FinPlugin::ISystemPreUpdate)
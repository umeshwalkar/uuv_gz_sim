#pragma once

#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>

class HydrodynamicsPlugin :
    public gz::sim::System,
    public gz::sim::ISystemConfigure,
    public gz::sim::ISystemPreUpdate
{
public:

    void Configure(
        const gz::sim::Entity &_entity,
        const std::shared_ptr<const sdf::Element> &_sdf,
        gz::sim::EntityComponentManager &_ecm,
        gz::sim::EventManager &_eventMgr) override;

    void PreUpdate(
        const gz::sim::UpdateInfo &_info,
        gz::sim::EntityComponentManager &_ecm) override;

private:

    gz::sim::Model model{
        gz::sim::kNullEntity
    };

    double Xu = 50.0;
    double Yv = 100.0;
    double Zw = 100.0;

    double Kp = 20.0;
    double Mq = 20.0;
    double Nr = 20.0;
};
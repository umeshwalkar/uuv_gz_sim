#pragma once

#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/transport/Node.hh>

#include <gz/msgs/double.pb.h>

class ActuatorPlugin :
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

    void OnThrust(const gz::msgs::Double &_msg);

    void OnFinTL(const gz::msgs::Double &_msg);
    void OnFinTR(const gz::msgs::Double &_msg);
    void OnFinBL(const gz::msgs::Double &_msg);
    void OnFinBR(const gz::msgs::Double &_msg);

private:

    // gz::sim::Model model{kNullEntity};
    
    gz::sim::Model model{gz::sim::kNullEntity};
    // gz::sim::Model model;

    gz::transport::Node node;

    double thrustPercent{0.0};

    double finTL{0.0};
    double finTR{0.0};
    double finBL{0.0};
    double finBR{0.0};

    // Tune these later
    double maxThrustForce{500.0};

    double pitchGain{8.0};
    double yawGain{8.0};
    double rollGain{4.0};
};
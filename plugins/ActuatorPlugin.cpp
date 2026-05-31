#include "ActuatorPlugin.hpp"

#include <gz/plugin/Register.hh>

#include <gz/sim/Link.hh>

using namespace gz;
using namespace sim;

/////////////////////////////////////////////////
void ActuatorPlugin::Configure(
    const Entity &_entity,
    const std::shared_ptr<const sdf::Element> &,
    EntityComponentManager &,
    EventManager &)
{
    this->model = Model(_entity);

    std::cout
        << "[ActuatorPlugin] Loaded"
        << std::endl;

    this->node.Subscribe(
        "/uuv/cmd/thrust",
        &ActuatorPlugin::OnThrust,
        this);

    this->node.Subscribe(
        "/uuv/cmd/fin_tl",
        &ActuatorPlugin::OnFinTL,
        this);

    this->node.Subscribe(
        "/uuv/cmd/fin_tr",
        &ActuatorPlugin::OnFinTR,
        this);

    this->node.Subscribe(
        "/uuv/cmd/fin_bl",
        &ActuatorPlugin::OnFinBL,
        this);

    this->node.Subscribe(
        "/uuv/cmd/fin_br",
        &ActuatorPlugin::OnFinBR,
        this);
}

/////////////////////////////////////////////////
void ActuatorPlugin::OnThrust(
    const msgs::Double &_msg)
{
    this->thrustPercent = _msg.data();

    if (this->thrustPercent < 0.0)
        this->thrustPercent = 0.0;

    if (this->thrustPercent > 100.0)
        this->thrustPercent = 100.0;
}

/////////////////////////////////////////////////
void ActuatorPlugin::OnFinTL(
    const msgs::Double &_msg)
{
    this->finTL = _msg.data();
}

/////////////////////////////////////////////////
void ActuatorPlugin::OnFinTR(
    const msgs::Double &_msg)
{
    this->finTR = _msg.data();
}

/////////////////////////////////////////////////
void ActuatorPlugin::OnFinBL(
    const msgs::Double &_msg)
{
    this->finBL = _msg.data();
}

/////////////////////////////////////////////////
void ActuatorPlugin::OnFinBR(
    const msgs::Double &_msg)
{
    this->finBR = _msg.data();
}

/////////////////////////////////////////////////
void ActuatorPlugin::PreUpdate(
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

    //----------------------------------------
    // THRUST
    //----------------------------------------

    const double thrustForce =
        (this->thrustPercent / 100.0) *
        this->maxThrustForce;

    link.AddWorldForce(
        _ecm,
        math::Vector3d(
            thrustForce,
            0.0,
            0.0));

    //----------------------------------------
    // X-FIN MIXER
    //----------------------------------------

    const double pitchCmd =
        (finTL + finTR)
      - (finBL + finBR);

    const double yawCmd =
        (finTR + finBR)
      - (finTL + finBL);

    const double rollCmd =
        (finTL + finBR)
      - (finTR + finBL);

    const double pitchMoment =
        pitchGain * pitchCmd;

    const double yawMoment =
        yawGain * yawCmd;

    const double rollMoment =
        rollGain * rollCmd;

    //----------------------------------------
    // APPLY MOMENTS
    //----------------------------------------

    link.AddWorldWrench(
        _ecm,
        math::Vector3d::Zero,
        math::Vector3d(
            rollMoment,
            pitchMoment,
            yawMoment));
}

/////////////////////////////////////////////////
GZ_ADD_PLUGIN(
    ActuatorPlugin,
    gz::sim::System,
    ActuatorPlugin::ISystemConfigure,
    ActuatorPlugin::ISystemPreUpdate)

GZ_ADD_PLUGIN_ALIAS(
    ActuatorPlugin,
    "ActuatorPlugin")
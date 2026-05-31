#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/Link.hh>
#include <gz/sim/Util.hh>
// #include <gz/sim/components/WorldPose.hh>
#include <gz/plugin/Register.hh>
#include <iostream>

using namespace gz;
using namespace sim;

class ThrusterPlugin :
    public System,
    public ISystemConfigure,
    public ISystemPreUpdate
{
public:

    void Configure(
        const Entity& entity,
        const std::shared_ptr<const sdf::Element>&,
        EntityComponentManager&,
        EventManager&) override
    {
        this->model = Model(entity);

        std::cout << "ThrusterPlugin loaded" << std::endl;
    }

    void PreUpdate(
        const UpdateInfo&,
        EntityComponentManager& ecm) override
    {
        auto linkEntity =
            this->model.LinkByName(ecm, "base_link");

        if (kNullEntity == linkEntity)
            return;

        Link link(linkEntity);

        constexpr double thrust = 500.0;

        link.AddWorldWrench(
            ecm,
            math::Vector3d(thrust, 0, 0),
            math::Vector3d::Zero);
    }

private:

    Model model{kNullEntity};
};

GZ_ADD_PLUGIN(
    ThrusterPlugin,
    gz::sim::System,
    ThrusterPlugin::ISystemConfigure,
    ThrusterPlugin::ISystemPreUpdate)
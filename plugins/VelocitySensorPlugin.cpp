#include <gz/sim/System.hh>
// #include <gz/sim/components/WorldLinearVelocity.hh>
#include <gz/sim/components/LinearVelocity.hh>
#include <gz/plugin/Register.hh>

#include <gz/transport/Node.hh>
#include <gz/msgs/vector3d.pb.h>

class VelocitySensorPlugin :
    public gz::sim::System,
    public gz::sim::ISystemConfigure,
    public gz::sim::ISystemPostUpdate
{
public:

    void Configure(
        const gz::sim::Entity &_entity,
        const std::shared_ptr<const sdf::Element> &,
        gz::sim::EntityComponentManager &,
        gz::sim::EventManager &) override
    {
        this->modelEntity = _entity;

        this->pub =
            node.Advertise<gz::msgs::Vector3d>(
                "/uuv/velocity");
    }

    void PostUpdate(
        const gz::sim::UpdateInfo &,
        const gz::sim::EntityComponentManager &_ecm) override
    {
        auto vel =
            _ecm.Component<
                gz::sim::components::WorldLinearVelocity>(
                    modelEntity);

        if (!vel)
            return;

        gz::msgs::Vector3d msg;

        msg.set_x(vel->Data().X());
        msg.set_y(vel->Data().Y());
        msg.set_z(vel->Data().Z());

        pub.Publish(msg);
    }

private:

    gz::sim::Entity modelEntity{
        gz::sim::kNullEntity};

    gz::transport::Node node;
    gz::transport::Node::Publisher pub;
};

GZ_ADD_PLUGIN(
    VelocitySensorPlugin,
    gz::sim::System,
    gz::sim::ISystemConfigure,
    gz::sim::ISystemPostUpdate)

GZ_ADD_PLUGIN_ALIAS(
    VelocitySensorPlugin,
    "VelocitySensorPlugin")
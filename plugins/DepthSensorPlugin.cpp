#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/Link.hh>

#include <gz/sim/components/Pose.hh>

#include <gz/plugin/Register.hh>

#include <gz/transport/Node.hh>

#include <gz/msgs/double.pb.h>

#include <iostream>

class DepthSensorPlugin :
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

        this->depthPub =
            this->node.Advertise<gz::msgs::Double>(
                "/uuv/depth");

        std::cout
            << "[DepthSensorPlugin] Publishing /uuv/depth"
            << std::endl;
    }

    void PostUpdate(
        const gz::sim::UpdateInfo &,
        const gz::sim::EntityComponentManager &_ecm) override
    {
        auto pose =
            _ecm.Component<gz::sim::components::Pose>(
                this->modelEntity);

        if (!pose)
            return;

        double zWorld = pose->Data().Pos().Z();

        // NED convention:
        // z=0 surface
        // depth positive downward
        double depth = -zWorld;

        if (depth < 0.0)
            depth = 0.0;

        gz::msgs::Double msg;
        msg.set_data(depth);

        this->depthPub.Publish(msg);
    }

private:

    gz::sim::Entity modelEntity{
        gz::sim::kNullEntity};

    gz::transport::Node node;

    gz::transport::Node::Publisher depthPub;
};

GZ_ADD_PLUGIN(
    DepthSensorPlugin,
    gz::sim::System,
    gz::sim::ISystemConfigure,
    gz::sim::ISystemPostUpdate)

GZ_ADD_PLUGIN_ALIAS(
    DepthSensorPlugin,
    "DepthSensorPlugin")
#include <gz/sim/System.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/EntityComponentManager.hh>
// #include <gz/sim/UpdateInfo.hh>
#include <gz/plugin/Register.hh>
#include <gz/transport/Node.hh>
#include <gz/msgs/imu.pb.h>
// #include <gz/msgs/altimeter.pb.h>
#include <gz/msgs/double.pb.h>

#include <functional>
#include <iostream>
#include <mutex>

class StateEstimatorPlugin : public gz::sim::System,
                             public gz::sim::ISystemConfigure,
                             public gz::sim::ISystemPreUpdate
{
public:
  void Configure(
      const gz::sim::Entity &entity,
      const std::shared_ptr<const sdf::Element> &sdf,
      gz::sim::EntityComponentManager &ecm,
      gz::sim::EventManager & /*eventMgr*/) override
  {
    std::cout << "[StateEstimatorPlugin] Configured\n";

    this->modelEntity = entity;

    this->imuTopic = "/uuv/imu";

    this->imuSubscribed =
        this->node.Subscribe<gz::msgs::IMU>(
            this->imuTopic,
            std::function<void(const gz::msgs::IMU &)>(
                [this](const gz::msgs::IMU &_msg)
                {
                  this->OnImu(_msg);
                }));

    this->depthTopic = "/uuv/depth";

    this->depthSubscribed =
        this->node.Subscribe<gz::msgs::Double>(
            this->depthTopic,
            std::function<void(const gz::msgs::Double &)>(
                [this](const gz::msgs::Double &_msg)
                {
                  this->OnDepth(_msg);
                }));

    if (!this->depthSubscribed)
    {
      std::cerr
          << "[StateEstimatorPlugin] Failed to subscribe "
          << this->depthTopic
          << std::endl;
    }
  }

  // void PreUpdate(
  //     const gz::sim::UpdateInfo & /*info*/,
  //     gz::sim::EntityComponentManager & /*ecm*/) override
  // {
  //   std::lock_guard<std::mutex> lock(this->mutex);
  // }

  void PreUpdate(
      const gz::sim::UpdateInfo & /*info*/,
      gz::sim::EntityComponentManager & /*ecm*/) override
  {
    std::lock_guard<std::mutex> lock(this->mutex);

    // Future EKF / observer goes here

    static uint64_t counter = 0;

    if (++counter % 500 == 0)
    {
      std::cout
          << "[State] Depth="
          << depthMeters
          << " m"
          << std::endl;
    }
  }

private:
  void OnDepth(const gz::msgs::Double &msg)
  {
    std::lock_guard<std::mutex> lock(this->mutex);

    this->depthMeters = msg.data();

    std::cout
        << "[Depth] "
        << depthMeters
        << " m"
        << std::endl;
  }

  void OnImu(const gz::msgs::IMU &msg)
  {
    std::lock_guard<std::mutex> lock(this->mutex);

    lastAccX = msg.linear_acceleration().x();
    lastAccY = msg.linear_acceleration().y();
    lastAccZ = msg.linear_acceleration().z();

    lastGyroX = msg.angular_velocity().x();
    lastGyroY = msg.angular_velocity().y();
    lastGyroZ = msg.angular_velocity().z();

    std::cout << "[IMU] ax=" << lastAccX
              << " ay=" << lastAccY
              << " az=" << lastAccZ << "\n";
  }

private:
  gz::sim::Entity modelEntity;
  gz::transport::Node node;

  bool imuSubscribed{false};
  std::string imuTopic;

  bool depthSubscribed{false};
  std::string depthTopic;

  std::mutex mutex;

  double lastAccX{0}, lastAccY{0}, lastAccZ{0};
  double lastGyroX{0}, lastGyroY{0}, lastGyroZ{0};
  double depthMeters{0.0};
};

GZ_ADD_PLUGIN(
    StateEstimatorPlugin,
    gz::sim::System,
    StateEstimatorPlugin::ISystemConfigure,
    StateEstimatorPlugin::ISystemPreUpdate)

GZ_ADD_PLUGIN_ALIAS(StateEstimatorPlugin, "StateEstimatorPlugin")
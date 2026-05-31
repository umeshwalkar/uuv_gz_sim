- Tell Gazebo where plugin lives
export GZ_SIM_SYSTEM_PLUGIN_PATH=/workspace/build


- Tell Gazebo where model lives
export GZ_SIM_RESOURCE_PATH=/workspace/models

- check
echo $GZ_SIM_SYSTEM_PLUGIN_PATH
echo $GZ_SIM_RESOURCE_PATH

- Run
gz sim /workspace/worlds/ocean.sdf


grep -n "AddWorld" /usr/include/gz/sim8/gz/sim/Link.hh
grep -n "AddWorld" /usr/include/gz/sim8/gz/sim/Model.hh


cd /workspace/build
rm -rf *
cmake ../plugins
make -j$(nproc)

gz sim /workspace/worlds/ocean.sdf
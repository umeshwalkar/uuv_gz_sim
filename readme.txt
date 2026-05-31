- Tell Gazebo where plugin lives
export GZ_SIM_SYSTEM_PLUGIN_PATH=/workspace/build


- Tell Gazebo where model lives
export GZ_SIM_RESOURCE_PATH=/workspace/models

- Add this to your .bashrc inside container with above
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/workspace/build

- check
echo $GZ_SIM_SYSTEM_PLUGIN_PATH
echo $GZ_SIM_RESOURCE_PATH
echo $LD_LIBRARY_PATH

- Run
gz sim /workspace/worlds/ocean.sdf


- Run these commands to check modules
grep -n "AddWorld" /usr/include/gz/sim8/gz/sim/Link.hh
grep -n "AddWorld" /usr/include/gz/sim8/gz/sim/Model.hh
grep -R "class WorldLinearVelocity" /usr/include/gz/sim8/gz/sim/components 2>/dev/null
grep -R "class LinearVelocity" /usr/include/gz/sim8/gz/sim/components 2>/dev/null

ls /usr/include/gz/sim8/gz/sim/components | grep Velocity

find /usr/include/gz/sim8 -name "*LinearVelocity*"
find /usr/include/gz/sim8 -name "*AngularVelocity*"

- build plugins
cd /workspace/build
rm -rf *   // always check the intended ditrectory/folder before command, there is no recyclebin
cmake ../plugins
make -j$(nproc)

- run the simulation
gz sim /workspace/worlds/ocean.sdf
gz sim --verbose models/my_auv/model.sdf
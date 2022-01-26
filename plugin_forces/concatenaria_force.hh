/*
 * Copyright (C) 2021 Dronus SPA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
/* Desc: Low level force applied to the drone
 * Author: Michele Belletti
 */

namespace gazebo
{
    /*
    // Default PID gains
    static double kPIDPitchP = 5.0;
    */

    //Doxygen is the de facto standard tool for generating documentation from annotated C++ sources
    // the special signs are for Doxygen

    class GAZEBO_VISIBLE concatenaria_plugin : public WorldPlugin
    {
        /// \brief constructor plugin
        public: concatenaria_plugin();
        
        /// \brief destructor
        public: ~concatenaria_plugin();


        //public: void force_applied();

        /// \brief load parameters from the sdf file 
        public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf);

        /// \brief function that is called every iteration of simulation
        public: void OnUpdate();

        /// \brief function calc the concatenarian forces
        public: void calculate_force(ignition::math::Pose3d pose_1, ignition::math::Pose3d pose_2);

        /*******************************************************************************************/

        //define variable for world and models 
        private: physics::WorldPtr world;
        private: physics::ModelPtr drone0;
        private: physics::ModelPtr drone1;

        //used for update at each iteration
        private: event::ConnectionPtr updateConnection;

        //distance between base_link and cable attach
        //private: ignition::math::Vector3 pose_attachment_relative_base = ignition::math::Vector3(0,0,0.01);

        //force for 1 attachment
        struct forces_torque {
            ignition::math::Vector3<double> forces;
            ignition::math::Vector3<double> torques;
        };
        private: forces_torque ft_drone1;
        private: forces_torque ft_drone2;

        /*

        struct drone{
            physics::ModelPtr model;
            struct forces_torques;
            std::array<double,3>
        }

        */

        //link used 
        private: physics::LinkPtr link_drone_0;
        private: physics::LinkPtr link_drone_1;

        //names of things
        private: std::string name_link = "base_link";
        private: std::string name_0_drone = "iris0";
        private: std::string name_1_drone = "iris1";
    };
}

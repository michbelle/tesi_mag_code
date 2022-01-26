
//link to api used http://osrf-distributions.s3.amazonaws.com/gazebo/api/11.0.0/classgazebo_1_1WorldPlugin.html


#include "gazebo/gazebo.hh"

#include <gazebo/transport/transport.hh>

#include <gazebo/msgs/msgs.hh>

//#include <functional>

#include <gazebo/common/Assert.hh> //launch exception
#include <gazebo/common/Console.hh> //gzerr and other console print
#include <gazebo/common/Plugin.hh>

#include <gazebo/physics/physics.hh>

#include <ignition/transport.hh>
//#include <ignition/transport/Node.hh>
#include <ignition/msgs.hh>
#include <ignition/math/AxisAlignedBox.hh> //to check if base link is inside the area of attach


#include "concatenaria_force.hh"




using gazebo::concatenaria_plugin;
GZ_REGISTER_WORLD_PLUGIN(concatenaria_plugin)



/////////////////////////////////////////////////////////////////////////////////////

concatenaria_plugin::concatenaria_plugin()
{
  printf("\nCostruction of concatenaria plugin!\n");
}

/////////////////////////////////////////////////////////////////////////////////////

concatenaria_plugin::~concatenaria_plugin()
{
  printf("\nShutdown concatenaria plugin!\n");
}

/////////////////////////////////////////////////////////////////////////////////////

//this function it the second funcion after the contructor
//load the first parameter in fuction of the type of the plugin and
//  can be used for read the information of the sdf file attached to the plugin

void concatenaria_plugin::Load(physics::WorldPtr _world, sdf::ElementPtr _sdf){
  
  
  this->world = _world;


  // Listen to the update event. This event is broadcast every
  // simulation iteration.
  //used for using the update function for each iteration
  this->updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&concatenaria_plugin::OnUpdate, this));

}

void concatenaria_plugin::calculate_force(ignition::math::Pose3d pose_1, ignition::math::Pose3d pose_2){
  
  auto position_xyz_1 = pose_1.Pos();
  auto position_xyz_2 = pose_2.Pos();

  /*common::Time*/
  double time = this->world->RealTime().Double(); //SimTime ()
  printf("the time now is %f", time);
  

  //modello_concatenaria
  //return force_1_model and force_2_model

  

  //scomposizione delle forze normali al piano e coppie generate rispetto al centro di massa (se no creare il proprio modello ed evitare questo)
  /*
  for x,y,z:
  if distanza tra attachemnt e centro di massa drone > 0 allora la forza è una coppia {
     coppia = i * distanza (attachement, pose)
     i=0

  }
  */
  
  this->ft_drone1.forces={0,13,0};
  this->ft_drone1.torques={0,13,0};
  this->ft_drone2.forces={0,0,25};
  this->ft_drone2.torques={0,0,0};
}





/////////////////////////////////////////////////////////////////////////////////////


void concatenaria_plugin::OnUpdate(){
  //check code to see the names of models inside the simulation
  
  auto list_pointer = this->world->Models();
  /*
  for (auto n : list_pointer){
      printf( "\t%s",n->GetName().c_str());
      this->counter_trash_0 ++;
    }
  printf("\n");
  */

  this->drone0 = this->world->ModelByName(this->name_0_drone);
  this->drone1 = this->world->ModelByName(this->name_1_drone);

  if (this->drone0 != NULL && this->drone1 != NULL){

    /*
    //check the names of links
    auto list_pointers_link_drones = this->drone0->GetLinks();
    for (auto n : list_pointers_link_drones){
      printf( "\t%s",n->GetName().c_str());
    }
    printf("\n");
    */

    //take the center of mass that is located in base link

    this->link_drone_0 =  this->drone0->GetChildLink(this->name_link);
    this->link_drone_1 =  this->drone1->GetChildLink(this->name_link);


    // TODO it is right? need to check or add a link equal at the attachment distance and then solve using that end of the link (the center of this link has to be at the attachemnt position then move the center of mass/visual/collition to the position of the real center)
    //auto pose_attach_first_0 = this->link_drone_0->getPose().CoordPositionAdd(this->pose_attachment_relative_base);
    //auto pose_attach_first_1 = this->link_drone_1->getPose().CoordPositionAdd(this->pose_attachment_relative_base);
    auto pose_attach_first_0 = this->link_drone_0->WorldPose();
    auto pose_attach_first_1 = this->link_drone_1->WorldPose();


    this->calculate_force(pose_attach_first_0,pose_attach_first_1);
    


    this->link_drone_0->AddRelativeForce(this->ft_drone1.forces);
    this->link_drone_0->AddRelativeTorque(this->ft_drone1.torques);

    this->link_drone_1->AddRelativeForce(this->ft_drone1.forces);
    this->link_drone_1->AddRelativeTorque(this->ft_drone1.torques);
    
    
  }


  
}
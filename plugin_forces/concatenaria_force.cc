
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
/* 
array::Vector 2*[6] calculate_force(auto model1, auto model2, ignition::math::Vector3d pose_attachment_concatenaria ){
  
  ignition::Pose3d model1_pose = model1->getPose();
  ignition::Pose3d model2_pose = model2->getPose();
  attachment_pose1 = model1_pose +  pose_attachment_concatenaria;
  attachment_pose2 = model2_pose +  pose_attachment_concatenaria;
  
  modello_concatenaria
  return force_1_model and force_2_model

  //scomposizione delle forze normali al piano e coppie generate rispetto al centro di massa (se no creare il proprio modello ed evitare questo)

  for x,y,z:
  if distanza tra attachemnt e centro di massa drone > 0 allora la forza è una coppia {
     coppia = i * distanza (attachement, pose)
     i=0

  }
  return force_torque = 2*{0,0,0,0,0,0};
}

array::Vector this->force_torque=2*{0,0,0,0,0,0};
ignition::vector3d this->attachment_pose;
*/



/////////////////////////////////////////////////////////////////////////////////////


void concatenaria_plugin::OnUpdate(){
  //check code to see the names of models inside the simulation
  
  auto list_pointer = this->world->Models();
  for (auto n : list_pointer){
      printf( "\t%s",n->GetName().c_str());
      this->counter_trash_0 ++;
    }
  printf("\n");
  
  this->drone0 = this->world->ModelByName("iris0");
  this->drone1 = this->world->ModelByName("iris1");

  if (this->drone0 != NULL && this->drone1 != NULL){

    //check the names of links
    auto list_pointers_link_drones = this->drone0->GetLinks();
    for (auto n : list_pointers_link_drones){
      printf( "\t%s",n->GetName().c_str());
    }
    printf("\n");

    /*
    forces_torques = calculate_force(this->drone0,this->drone1,this->attachment_pose);

    ignition::math::Vector3d 
    
    this->drone0_link = this->drone->GetLink(this->drone0_name_centerofmass = "base_link")

    this->drone0_link->AddRelativeForce();
    this->drone0_link->AddRelativeTorque();
    */
    
  }


  /*
  auto drone0 = &list_pointer[0];
  std::cout << typeid(drone0).name() << std::endl;
  */

  /* test code for see the names of parts of the drone and nest
  if(this->drone!=NULL && this->nest!=NULL){
    auto test1 = this->drone->GetLinks();
    auto test2 = this->nest->GetLinks();
    printf("scan drone links");
    
    
    for (auto n : test1){
      printf("\t");
      printf( n->GetName().c_str());
    }
    printf("\n");

    for (auto n : test2){
      printf("\t");
      printf( n->GetName().c_str());
    }

    printf("\n\n\n\n\n");
  }
  
 */


  
}
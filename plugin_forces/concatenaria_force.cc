
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




/////////////////////////////////////////////////////////////////////////////////////


void concatenaria_plugin::OnUpdate()
{
  
  auto list_pointer = this->world->Models();
  for (auto n : list_pointer){
      printf( "\t%s",n->GetName().c_str());
    }
  printf("\n");
  
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
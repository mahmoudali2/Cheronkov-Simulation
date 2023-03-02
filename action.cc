//Implementation of the ActionInitialization class

#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build () const
{

// Generator and run action defifnition    
    MyPrimaryGenerator *generator = new MyPrimaryGenerator();
    SetUserAction(generator);

    MyRunAction *runAcion = new MyRunAction();
    SetUserAction(runAcion);

// if there are required event action , stepping, ..etc .. it should be defined here too
}
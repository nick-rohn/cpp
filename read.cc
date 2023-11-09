#include <iostream>
#include <fstream>

int read( std::ifstream& file,
        double& x_decay, double& y_decay, double& z_decay,
        int* charge,
        double* p_x, double* p_y, double* p_z ){
    //read coordinates event
    file >> x_decay >> y_decay >> z_decay;

    //read number of particles
    int n_particles;
    file >> n_particles;
    
    //read charge and momenta of particles
    for( int i = 0; i < n_particles; ++i ){
        file >> charge[i];
        file >> p_x[i] >> p_y[i] >> p_z[i];
    }

    return n_particles;
}
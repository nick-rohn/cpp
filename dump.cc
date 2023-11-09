#include <iostream>

void dump( int ev_number,
        int n_particles,
        double x_decay, double y_decay, double z_decay,
        int* charge,
        double* p_x, double* p_y, double* p_z ){

    // write event data
    std::cout << ev_number << ' '
              << x_decay << ' ' << y_decay << ' ' << z_decay << ' '
              << n_particles ;
    
    // write particle data
    for ( int i = 0; i < n_particles; ++i ){
        std::cout << ' '
                  << charge[i] << ' '
                  << p_x[i] << ' ' << p_y[i] << ' ' << p_z[i];
    }

    std::cout << std::endl;

    return;

}
#include <iostream>
#include <fstream>

int read( std::ifstream& file,
        double& x_decay, double& y_decay, double& z_decay,
        int* charge,
        double* p_x, double* p_y, double* p_z );

void dump( int ev_number,
        int n_particles,
        double x_decay, double y_decay, double z_decay,
        int* charge,
        double* p_x, double* p_y, double* p_z );


int main( int argc, char *argv[] ){
    //open input file
    const char* name = argv[1];
    std::ifstream file( name );
    
    //event variables
    int ev_number;
    int n_particles;
    double x_decay, y_decay, z_decay;
    int charge[10];
    double p_x[10], p_y[10], p_z[10];

    //loop over events
    while( file >> ev_number ){
        n_particles = read( file, x_decay, y_decay, z_decay, charge, p_x, p_y, p_z );
        dump( ev_number, n_particles, x_decay, y_decay, z_decay, charge, p_x, p_y, p_z );
    }

    return 0;
    
}
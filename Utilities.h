#ifndef Utilities_h
#define Utilities_h

class Utilities {

    public:
        // compute energy from momentum x,y,z components and invariant mass
        static double Energy( double p_x, double p_y, double p_z, double inv_mass );
        static double InvariantMass( double p_x, double p_y, double p_z, double energy);

};


#endif
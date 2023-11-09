#ifndef Event_h
#define Event_h

struct Particle;

struct Event {
    int ev_number;
    double x_decay, y_decay, z_decay;
    int n_particles;
    Particle** particles;
};

#endif
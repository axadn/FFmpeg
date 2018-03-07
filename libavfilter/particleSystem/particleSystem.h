typedef struct particle particle;

typedef struct particleSystem particleSystem;

particleSystem * createParticleSystem();

void addParticle(particleSystem * system, float position[2], float velocity[2], int life);

//frees the particle sytem and all active and inactive (in the pool) particles
void deleteParticleSystem(particleSystem * system); 

void updateParticleSystem(particleSystem * system);
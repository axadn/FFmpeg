typedef struct particleSystem particleSystem;

particleSystem * createParticleSystem();
void addParticle(particleSystem * system, float position[2], float velocity[2], int life);
void deleteParticleSystem(particleSystem * system); 
void updateParticleSystem(particleSystem * system);
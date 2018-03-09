typedef struct particle particle;
typedef struct particle{
    float position[2];
    float velocity[2];
    int age;
    int life;
    particle * next;
    particle * prev;
} particle;

typedef struct particleList{
    particle * head;
    particle * tail;
} particleList;

typedef struct particlePool{
    particle * head;
}particlePool;

typedef struct particleSystem{
    particleList list;
    particlePool pool;
}particleSystem;

particleSystem * createParticleSystem(void);
void addParticle(particleSystem * system, float position[2], float velocity[2], int life);
void deleteParticleSystem(particleSystem * system); 
void updateParticleSystem(particleSystem * system);

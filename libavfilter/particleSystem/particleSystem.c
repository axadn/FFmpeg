#include "particleSytem.h"
struct particle{
    float position[2];
    float velocity[2];
    int age;
    int life;
    particle * next;
    particle * prev;
} particle;

struct particleSystem{
    particleList list;
    particlePool pool;
}particleSystem;

typedef struct particleList{
    particle * head;
    particle * tail;
} particleList;

typedef struct particlePool{
    particle * head;
}particlePool;


particle * newParticle(particlePool * pool){
    particle * newParticle;
    if(pool->head == NULL){
        newParticle = malloc(sizeof(particle));
    }
    else{
        newParticle = pool->head;
        pool->head = pool->head->next;
    }
    return newParticle;
}

void addParticleToList(particle* part, particleList * list){
    if(list->head == NULL){
        list->head = part;
        list->tail = part;
    }
    else{
        part->prev = list->tail;
        list->tail->next = part;
        list->tail = part;
    }
    list->tail->next = NULL;
}

void addParticleToPool(particle * part, particlePool * pool){
    particle->next = pool->head;
    pool->head = particle;
}

void removeParticleFromList(particle * part, particleList * list){
    if(part == list->head){
        list->head = part->next;
    }
    else{
        part->prev->next = part->next;
    }
    if(part == list->tail){
        list->tail = part->prev;
    }
    else{
        part->next->prev = part->prev;
    }
}

void killParticle(particleSystem * system, particle * part){
    removeParticleFromList(part, system->list);
    addParticleToPool(part, system->pool);
}

void updateParticle(particle* part){
    ++part.age;
    for(int i = 0; i < 2; ++i){
        part->position[i] += part->velocity[i];
    }
}
void addParticle(particleSystem * system, float position[2], float velocity[2], int life){
    particle * part = newParticle(system->pool);
    part.age = 0;
    for(int i = 0; i < 2; ++i){
        part.position[i] = position[i];
        part.velocity[i] = velocity[i];
    }
    part.life = life;
    addParticleToList(part, system->list);
}

void updateParticleSystem(particleSystem * system){
    particle * part = system->list->head;
    particle * nextParticle;
    while(part != NULL){
        updateParticle(part);
        nextParticle = part->next;
        if(part->age > part->life){
            killParticle(system, part);
        }
        part = nextParticle;
    }
}


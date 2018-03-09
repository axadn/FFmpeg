#include "particleSystem.h"
#include <stdlib.h>

static particle * newParticle(particlePool * pool){
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

static void addParticleToList(particle* part, particleList * list){
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

static void addParticleToPool(particle * part, particlePool * pool){
    part->next = pool->head;
    pool->head = part;
}

static void removeParticleFromList(particle * part, particleList * list){
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

static void killParticle(particleSystem * system, particle * part){
    removeParticleFromList(part, &system->list);
    addParticleToPool(part, &system->pool);
}

static void updateParticle(particle* part){
    ++part->age;
    for(int i = 0; i < 2; ++i){
        part->position[i] += part->velocity[i];
    }
}
void addParticle(particleSystem * system, float position[2], float velocity[2], int life){
    particle * part = newParticle(&system->pool);
    part->age = 0;
    for(int i = 0; i < 2; ++i){
        part->position[i] = position[i];
        part->velocity[i] = velocity[i];
    }
    part->life = life;
    addParticleToList(part, &system->list);
}

void updateParticleSystem(particleSystem * system){
    particle * part = system->list.head;
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

void deleteParticleSystem(particleSystem * system){
    particle * part = system->list.head;
    while(part != NULL){
        free(part);
        part = part->next;
    }
    part = system->pool.head;
    while(part != NULL){
        free(part);
        part = part->next;
    }
    free(system);
}

particleSystem * createParticleSystem(){
    return (particleSystem*) malloc(sizeof(particleSystem));
}

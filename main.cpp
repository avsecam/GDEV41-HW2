#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <raymath.h>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PARTICLE_RADIUS = 7.5f;
const int PARTICLE_ARRAY_SIZE = 1000;

const int EMISSION_RATE = 25;


struct Particle {
  bool isActive;
  Vector2 position;
  Vector2 direction;
  float speed;
  float lifeTime;
  Color color;

  Particle() {
    isActive = false;
    position.x = 0.0f;
    position.y = 0.0f;
    direction.x = 0.0f;
    direction.y = 0.0f;
    speed = 0.0f;
    lifeTime = 0.0f;
    color.r = 255;
    color.g = 0;
    color.b = 0;
    color.a = 255;
  }
};


int findInactiveParticleIndex(Particle* array, const int size);
void emitParticleSpacebar(Particle& particle);
void updateParticles(Particle* array, const int size);
float randf(const float min, const float max);


int main() {
  Particle* particles = new Particle[PARTICLE_ARRAY_SIZE];
  // All particles are inactive at this point. Step 4

  int nextInactiveParticleIndex = findInactiveParticleIndex(particles, PARTICLE_ARRAY_SIZE);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Loop, Input Handling, and Frames");
  while (!WindowShouldClose()) {
    nextInactiveParticleIndex = findInactiveParticleIndex(particles, PARTICLE_ARRAY_SIZE);

    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyDown(KEY_SPACE)) {
      if (nextInactiveParticleIndex != -1) {
        emitParticleSpacebar(particles[nextInactiveParticleIndex]);
      }
      // printf("%.2f\n", particles[nextInactiveParticleIndex].direction.y);
    }

    updateParticles(particles, PARTICLE_ARRAY_SIZE);

    EndDrawing();
  }
  delete particles;
  CloseWindow();
  return 0;
}


int findInactiveParticleIndex(Particle* array, const int size) {
  for (int i = 0; i < size; i++) {
    if (!array[i].isActive) {
      return i;
    }
  }
  return -1;
}


void emitParticleSpacebar(Particle& particle) {
  particle.isActive = true;
  particle.position.x = WINDOW_WIDTH / 2;
  particle.position.y = WINDOW_HEIGHT;
  particle.direction.x = rand() % 3 - 1;
  particle.direction.y = -1.0f;
  particle.direction = Vector2Normalize(particle.direction);
  particle.speed = rand() % 5 + 5;
  particle.lifeTime = rand() % 4 + 2;
  particle.color.r = rand() % 256;
  particle.color.g = rand() % 256;
  particle.color.b = rand() % 256;
  particle.color.a = 255;

  DrawCircle(particle.position.x, particle.position.y, PARTICLE_RADIUS, particle.color);
}


void updateParticles(Particle* array, const int size) {
  for (int i = 0; i < size; i++) {
    Particle& particle = array[i];
    if (particle.lifeTime <= 0.0f) {
      particle.isActive = false;
    }
    if (particle.isActive) {
      particle.position.x += particle.direction.x * particle.speed / 10;
      particle.position.y += particle.direction.y * particle.speed / 10;
      particle.lifeTime -= 0.01f;
      particle.color.a -= Normalize(0.01f, 0.0f, 255.0f);
      DrawCircle(particle.position.x, particle.position.y, PARTICLE_RADIUS, particle.color);
    }
  }
}


float randf(const float min, const float max) {
  
}
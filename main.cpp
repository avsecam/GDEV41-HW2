#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <raymath.h>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PARTICLE_RADIUS = 5;
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
void emitParticleMouse(Particle& particle, const int mouseX, const int mouseY);
void updateParticles(Particle* array, const int size);
float randf(const float min, const float max);


int main() {
  Particle* particles = new Particle[PARTICLE_ARRAY_SIZE];
  // All particles are inactive at this point. Step 4

  int nextInactiveParticleIndex = findInactiveParticleIndex(particles, PARTICLE_ARRAY_SIZE);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Loop, Input Handling, and Frames");
  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(BLACK);

    if (IsKeyDown(KEY_SPACE)) {
      nextInactiveParticleIndex = findInactiveParticleIndex(particles, PARTICLE_ARRAY_SIZE);
      if (nextInactiveParticleIndex != -1) {
        emitParticleSpacebar(particles[nextInactiveParticleIndex]);
      }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      nextInactiveParticleIndex = findInactiveParticleIndex(particles, PARTICLE_ARRAY_SIZE);
      if (nextInactiveParticleIndex != -1) {
        emitParticleMouse(particles[nextInactiveParticleIndex], GetMouseX(), GetMouseY());
      }
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
  particle.direction.x = randf(-1.0f, 1.0f);
  particle.direction.y = -1.0f;
  particle.direction = Vector2Normalize(particle.direction);
  particle.speed = randf(5.0f, 10.0f);
  particle.lifeTime = randf(2.0f, 5.0f);
  particle.color.r = rand() % 256;
  particle.color.g = rand() % 256;
  particle.color.b = rand() % 256;
  particle.color.a = 255;

  DrawCircle(particle.position.x, particle.position.y, PARTICLE_RADIUS, particle.color);
}


void emitParticleMouse(Particle& particle, const int mouseX, const int mouseY) {
  particle.isActive = true;
  particle.position.x = mouseX;
  particle.position.y = mouseY;
  particle.direction.x = randf(-1.0f, 1.0f);
  particle.direction.y = randf(-1.0f, 1.0f);
  particle.direction = Vector2Normalize(particle.direction);
  particle.speed = randf(5.0f, 10.0f);
  particle.lifeTime = randf(0.5f, 2.0f);
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
      particle.position.x += particle.direction.x * particle.speed / 20;
      particle.position.y += particle.direction.y * particle.speed / 20;
      particle.lifeTime -= 0.01f;
      particle.color.a -= Normalize(0.01f, 0.0f, 255.0f);
      DrawCircle(particle.position.x, particle.position.y, PARTICLE_RADIUS, particle.color);
    }
  }
}


// https://cplusplus.com/forum/beginner/81180/
float randf(const float min, const float max) {	
  float result = (rand() / static_cast<float>(RAND_MAX) * (max + 1)) + min;
  return result;
}
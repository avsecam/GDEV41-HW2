#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <raymath.h>
#include <fstream>
#include <string>



const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PARTICLE_RADIUS = 5;
const int PARTICLE_ARRAY_SIZE = 1000;
const int EMISSION_RATE_MIN = 1;
const int EMISSION_RATE_MAX = 50;


MouseButton cursorMouseInput, bottomCenterMouseInput;
KeyboardKey cursorKeyboardInput, bottomCenterKeyboardInput;
KeyboardKey decreaseBottomCenterEmissionRate;
KeyboardKey increaseBottomCenterEmissionRate;
KeyboardKey decreaseCursorEmissionRate;
KeyboardKey increaseCursorEmissionRate;


struct Particle {
  bool isActive = false;
  Vector2 position;
  Vector2 direction;
  float speed;
  float maxLifeTime;
  float lifeTime;
  Color color;
};


int findInactiveParticleIndex(Particle* array, const int size);
void emitParticleSpacebar(Particle& particle);
void emitParticleMouse(Particle& particle, const int mouseX, const int mouseY);
void updateParticles(Particle* array, const int size, const float deltaTime);
float randf(const float min, const float max);


int main() {
  std::ifstream configFile("./config.ini");
  std::string s, i, k;
  int keyNumber;
  while(configFile >> s >> i >> k)
  {
    keyNumber = std::stoi(k);
    if(s == "EMIT_BOTTOM_CENTER")
    {
      if (i == "keyboard") // If number is less than 6, it is a mouse input
      {
        bottomCenterKeyboardInput = KeyboardKey(keyNumber);
      }
      else if (i == "mouse")
      {
        bottomCenterMouseInput = MouseButton(keyNumber);
      }    
    }
    else if(s == "EMIT_CURSOR")
    {
      if (i == "keyboard") // If number is less than 6, it is a mouse input
      {
        cursorKeyboardInput = KeyboardKey(keyNumber);
      }
      else if (i == "mouse")
      {
        cursorMouseInput = MouseButton(keyNumber);
      }
    }
    else if(s == "DECREASE_BOTTOM_CENTER_RATE")
    {
      decreaseBottomCenterEmissionRate = KeyboardKey(keyNumber);
    }
    else if(s == "INCREASE_BOTTOM_CENTER_RATE")
    {
      increaseBottomCenterEmissionRate = KeyboardKey(keyNumber);
    }
    else if(s == "DECREASE_CURSOR_RATE")
    {
      decreaseCursorEmissionRate = KeyboardKey(keyNumber);
    }
    else if(s == "INCREASE_CURSOR_RATE")
    {
      increaseCursorEmissionRate = KeyboardKey(keyNumber);
    }
  }
  int emissionRateSpacebar = 20; // [1, 50]
  int emissionRateMouse = 40;
  float particleTimeSpacebar = 1.0f / emissionRateSpacebar; // Max time before another particle is emitted
  float particleTimeMouse = 1.0f / emissionRateMouse;
  float particleCooldownSpacebar = particleTimeSpacebar; // Remaining time before emission
  float particleCooldownMouse = particleTimeMouse;
  

  Particle* particles = new Particle[PARTICLE_ARRAY_SIZE];
  // All particles are inactive at this point. Step 4

  int nextInactiveParticleIndex = findInactiveParticleIndex(particles, PARTICLE_ARRAY_SIZE);

  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Game Loop, Input Handling, and Frames");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    if (IsKeyDown(bottomCenterMouseInput|bottomCenterKeyboardInput)) {
      nextInactiveParticleIndex = findInactiveParticleIndex(particles, PARTICLE_ARRAY_SIZE);
      if (nextInactiveParticleIndex != -1 && particleCooldownSpacebar == particleTimeSpacebar) {
        emitParticleSpacebar(particles[nextInactiveParticleIndex]);
      } 
    }

    if (IsMouseButtonDown(cursorMouseInput|cursorKeyboardInput)) {
      nextInactiveParticleIndex = findInactiveParticleIndex(particles, PARTICLE_ARRAY_SIZE);
      if (nextInactiveParticleIndex != -1 && particleCooldownMouse == particleTimeMouse) {
        emitParticleMouse(particles[nextInactiveParticleIndex], GetMouseX(), GetMouseY());
      }
    }

    if (IsKeyPressed(decreaseBottomCenterEmissionRate) && emissionRateSpacebar > EMISSION_RATE_MIN) {
      emissionRateSpacebar--;
      particleTimeSpacebar = 1.0f / emissionRateSpacebar;
      printf("spacebar emission %i\n", emissionRateSpacebar);
    } else if (IsKeyPressed(increaseBottomCenterEmissionRate) && emissionRateSpacebar < EMISSION_RATE_MAX) {
      emissionRateSpacebar++;
      particleTimeSpacebar = 1.0f / emissionRateSpacebar;
      printf("spacebar emission %i\n", emissionRateSpacebar);
    } else if (IsKeyPressed(decreaseCursorEmissionRate) && emissionRateMouse < EMISSION_RATE_MAX) {
      emissionRateMouse--;
      particleTimeMouse = 1.0f / emissionRateMouse;
      printf("mouse emission %i\n", emissionRateMouse);
    } else if (IsKeyPressed(increaseCursorEmissionRate) && emissionRateMouse < EMISSION_RATE_MAX) {
      emissionRateMouse++;
      particleTimeMouse = 1.0f / emissionRateMouse;
      printf("mouse emission %i\n", emissionRateMouse);
    }

    updateParticles(particles, PARTICLE_ARRAY_SIZE, GetFrameTime());

    EndDrawing();

    particleCooldownSpacebar -= GetFrameTime();
    particleCooldownMouse -= GetFrameTime();
    if (particleCooldownSpacebar <= 0.0f) particleCooldownSpacebar = particleTimeSpacebar;
    if (particleCooldownMouse <= 0.0f) particleCooldownMouse = particleTimeMouse;
  }
  delete particles;
  CloseWindow();
  return 0;
}


// Returns the index of the first inactive particle in the array
int findInactiveParticleIndex(Particle* array, const int size) {
  for (int i = 0; i < size; i++) {
    if (!array[i].isActive) {
      return i;
    }
  }
  return -1;
}


// Emit particles from the bottom center of window
void emitParticleSpacebar(Particle& particle) {
  particle.isActive = true;
  particle.position.x = WINDOW_WIDTH / 2;
  particle.position.y = WINDOW_HEIGHT;
  particle.direction.x = randf(-1.0f, 1.0f);
  particle.direction.y = -1.0f;
  particle.direction = Vector2Normalize(particle.direction);
  particle.speed = randf(50.0f, 100.0f);
  particle.maxLifeTime = randf(2.0f, 5.0f);
  particle.lifeTime = particle.maxLifeTime;
  particle.color.r = rand() % 256;
  particle.color.g = rand() % 256;
  particle.color.b = rand() % 256;
  particle.color.a = 255;

  DrawCircle(particle.position.x, particle.position.y, PARTICLE_RADIUS, particle.color);
}


// Emit particles from mouse position
void emitParticleMouse(Particle& particle, const int mouseX, const int mouseY) {
  particle.isActive = true;
  particle.position.x = mouseX;
  particle.position.y = mouseY;
  particle.direction.x = randf(-1.0f, 1.0f);
  particle.direction.y = randf(-1.0f, 1.0f);
  particle.direction = Vector2Normalize(particle.direction);
  particle.speed = randf(50.0f, 100.0f);
  particle.maxLifeTime = randf(0.5f, 2.0f);
  particle.lifeTime = particle.maxLifeTime;
  particle.color.r = rand() % 256;
  particle.color.g = rand() % 256;
  particle.color.b = rand() % 256;
  particle.color.a = 255;

  DrawCircle(particle.position.x, particle.position.y, PARTICLE_RADIUS, particle.color);
}


// Updates all particles in the array
void updateParticles(Particle* array, const int size, const float deltaTime) {
  for (int i = 0; i < size; i++) {
    Particle& particle = array[i];
    if (particle.lifeTime <= 0.0f) {
      particle.isActive = false;
    }
    if (particle.isActive) {
      particle.position.x += particle.direction.x * particle.speed * deltaTime;
      particle.position.y += particle.direction.y * particle.speed * deltaTime;
      particle.lifeTime -= deltaTime;
      particle.color.a = Remap(particle.lifeTime, 0.0f, particle.maxLifeTime, 0.0f, 255.0f);
      DrawCircle(particle.position.x, particle.position.y, PARTICLE_RADIUS, particle.color);
    }
  }
}


// https://cplusplus.com/forum/beginner/81180/
// Returns a random float within min and max
float randf(const float min, const float max) {	
  float result = (rand() / static_cast<float>(RAND_MAX) * (max + 1)) + min;
  return result;
}

void readConfigFile()
{
  
}

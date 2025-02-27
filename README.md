
# OpenGL Black Hole Simulation

This project is a **real-time particle simulation** inspired by the mesmerizing visuals of a black hole. Using **OpenGL 4.1 Core Profile** and **GLFW**, it creates a swirling vortex where particles spiral inward, fade as they approach the event horizon, and continuously respawn at the outer boundary.

## 🌌 Features

- Dynamic **swirling particle system** simulating accretion disk motion
- **Alpha blending** for smooth fading effects
- Customizable **forces, spawn radius, particle lifespan**, and more
- **Cross-platform build** with CMake (macOS, Linux, Windows)

## 📦 Requirements

- A **C++17-compatible compiler**
- [**CMake**](https://cmake.org/) (3.10+ recommended)
- [**GLFW**](https://www.glfw.org/)
- A **GPU with OpenGL 4.1+ support**

> **Note for macOS users**: OpenGL is deprecated by Apple, but this project uses the **Core Profile (4.1)**. You may need to define flags to suppress warnings.

---

## 🔧 Building & Running

### 1️⃣ Clone the repository
```bash
git clone https://github.com/dimasximik/OpenGL_BlackHole_Simulation.git
cd OpenGL_BlackHole_Simulation
```

### 2️⃣ Create a build directory & compile
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### 3️⃣ Run the simulation
- **On macOS/Linux**:
  ```bash
  ./blackhole
  ```
- **On Windows**:
  ```bash
  blackhole.exe
  ```

### ⚠️ Notes for macOS users
If you see OpenGL deprecation warnings, add these defines **before** including GLFW:
```cpp
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
```
CMake automatically sets up the OpenGL Core Profile:
```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

---

## 📁 Folder Structure

```
OpenGL_BlackHole_Simulation/
├─ CMakeLists.txt
├─ shaders/
│   ├─ vertex.glsl
│   └─ fragment.glsl
└─ src/
   ├─ main.cpp
   ├─ ParticleSystem.cpp
   ├─ ParticleSystem.h
   ├─ ShaderProgram.cpp
   └─ ShaderProgram.h
```

- **shaders/** → Contains the vertex & fragment shaders for rendering.
- **src/** → Core simulation logic, including the particle system and OpenGL shader utilities.
- **CMakeLists.txt** → Handles project build configuration.

---

## 🎛️ Customization

All key physics parameters can be tweaked in `ParticleSystem.cpp`. Adjust **swirl force, radial force, gravity, spawn radius**, and more:
```cpp
m_swirlForce = 10.0f;
m_radialForce = -16.0f;
m_gravity     = 0.0f;
m_minRadius   = 20.0f;
m_spawnMinR   = 120.0f;
m_spawnMaxR   = 130.0f;
```
Experiment with these values to create different accretion disk effects!

---

## 📜 License

This project is distributed under the [MIT License](https://opensource.org/license/mit)

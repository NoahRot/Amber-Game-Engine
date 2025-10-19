🛠 Mandatory Components (Core Engine)
These are the absolute essentials to get your engine running. Start with these.

1️⃣ Core System

    [ ] Engine (Main entry point to manage initialization and shutdown)
    [V] Logger (Singleton to handle logging/debugging)
    [V] Config Manager (Handles engine settings, file-based config loading, etc.)

2️⃣ Windowing & Graphics

    [V] Window (SDL2-based window creation and management)
    [V] Renderer (OpenGL context setup and rendering pipeline)
    [V] ShaderManager (Handles GLSL shaders)
    [V] TextureManager (Loads and manages OpenGL textures)

3️⃣ Input Handling

    [V] InputManager (Manages keyboard, mouse, and gamepad input using SDL events)

4️⃣ Game Loop

    [V] TimeManager (Keeps track of delta time and FPS)
    [ ] EventManager (Handles SDL events)
    [ ] SceneManager (Switches between different game states/scenes)

5️⃣ Resource Management

    [V] AssetManager (Handles loading/unloading of textures, models, sounds, etc.)
    [ ] FileSystem (File loading, paths, etc.)

🔹 Good to Have (Improves Usability & Performance)
These are not strictly required but make the engine more functional and optimized.

6️⃣ Rendering Improvements

    [ ] Mesh (Basic model/geometry management)
    [ ] Material (Handles shaders, textures, and properties)
    [ ] Framebuffer (Allows post-processing, screen effects)
    [V] Font Rendering (Using FreeType for text rendering)
    [ ] 2D Renderer (Batch rendering for sprites, UI elements)

7️⃣ Audio

    [V] AudioManager (Using SDL_mixer or OpenAL for sound effects and music)
    [ ] AudioSource (Component to play sounds in 3D space)

8️⃣ Scene & Entity System

    [ ] Entity (Base class for objects in the world)
    [ ] ComponentSystem (Basic ECS architecture for extensibility)
    [ ] TransformComponent (Handles position, rotation, scale)

9️⃣ Physics (Basic)

    [ ] PhysicsWorld (Using Box2D or Bullet for physics simulation)
    [ ] ColliderComponent (Defines collision shapes)
    [ ] RigidbodyComponent (Handles movement and forces)

🔹 Optional / Advanced (For Later Development)
These are complex but will significantly enhance the engine.

🔟 Advanced Rendering

    [ ] Deferred Rendering (Optimized rendering pipeline)
    [ ] Shadow Mapping (Dynamic lighting/shadows)
    [ ] Post-Processing (Bloom, motion blur, etc.)
    [ ] PBR (Physically-Based Rendering) (Realistic lighting and materials)

🔟 Scripting & AI

    [ ] Scripting System (Lua or Python integration for gameplay logic)
    [ ] AI System (Pathfinding, behavior trees)

🔟 Networking

    [ ] Networking Module (Using ENet or custom UDP/TCP for multiplayer support)

🔟 Editor / Debugging

    [ ] Engine Editor (ImGui-based UI for level editing)
    [ ] Profiler (FPS counter, memory tracking)

### ADDED LATER

🛠 Mandatory / Core
    [V] Error Handling System (Centralized error reporting, assertions)
    [ ] Cross-Platform Abstraction (Windows, Linux, macOS support)
    [ ] Build System Integration (CMake, premake, etc.)

🔹 Good to Have
    [ ] Hot Reloading (Reload assets/shaders at runtime)
    [ ] Localization/Internationalization (Text and asset localization)
    [ ] Input Remapping (User-configurable controls)
    [ ] Animation System (Skeletal and sprite animation support)
    [ ] Camera System (Multiple camera types, transitions)
    [ ] Lighting System (Basic lights, light manager)
    [ ] Particle System (For effects like fire, smoke, etc.)
    [ ] UI System (Buttons, sliders, layout, etc.)
    [ ] Save/Load System (Serialization for game state)
    [V] Math Library (Vectors, matrices, quaternions, etc.)

🔹 Optional / Advanced
    [ ] Virtual File System (Pack assets, mount archives)
    [ ] Terrain System (Heightmaps, LOD)
    [ ] Occlusion Culling (Performance optimization)
    [ ] Reflection/Serialization System (For editor and scripting integration)
    [ ] Resource Streaming (Load assets asynchronously)
    [ ] Multithreading/Job System (Parallel tasks, worker threads)
    [ ] Debug Drawing (Draw lines, shapes for debugging physics, AI, etc.)
    [V] Unit Testing Framework (Automated tests for engine modules)
    [ ] Crash Reporting (Collect crash dumps, logs)
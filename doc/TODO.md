Core Modules
- Engine Core: Initialization, shutdown, main loop.
- Logger: Logging and debugging output.
- Configuration Manager: Loads and manages engine settings.
Window & Graphics
- Window: SDL2-based window creation and management.
- Renderer: OpenGL context setup, draw calls, and pipeline.
- Shader: Compiles and manages GLSL shaders.
- Texture: Loads and manages textures.
- Mesh/VertexArray/Buffer: Manages geometry data.
- Material: Handles shader and texture properties.
Input
- Input Manager: Handles keyboard, mouse, and gamepad input via SDL events.
Game Loop & Timing
- Time Manager: Delta time, FPS calculation.
- Event Manager: Handles SDL events and custom engine events.
Resource Management
- Asset Manager: Loads/unloads textures, models, sounds.
- File System: File I/O, path management.
Audio
- Audio Manager: Sound playback (SDL_mixer or OpenAL).
Scene & Entity System
- Scene Manager: Manages different game scenes/states.
- Entity/Component System: Basic ECS for game objects.
- Transform Component: Position, rotation, scale.
Physics (Optional)
- Physics World: Basic physics simulation (Box2D/Bullet).
- Collider/Rigidbody Components: Collision and movement.
UI & Font Rendering
- Font Renderer: Text rendering (FreeType).
- 2D Renderer: Sprites and UI elements.
Serialization
- Serializer: Save/load engine state, configuration, and assets.

Optional/Advanced:
- Scripting (Lua/Python)
- Networking
- Editor (ImGui)
- Advanced rendering (shadows, PBR, post-processing)
- AI

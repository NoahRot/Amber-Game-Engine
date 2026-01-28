#pragma once

#include "mat/Math.hpp"
#include "Asset/AssetHandle.hpp"
#include "Graphic/Texture.hpp"
#include "Logger/Logger.hpp"
#include "UI/Renderer.hpp"
#include "Event/Event.hpp"

#include <memory>
#include <typeindex>
#include <functional>

namespace AMB::UI {

enum class UI_PositionType {
    absolute,
    relative,
    grid
};

enum class UI_Anchor {
    TL, TC, TR,
    CL, CC, CR,
    BL, BC, BR
};

struct UI_Position {
    UI_PositionType type;
    UI_Anchor anchor;
    mat::Vec2f position;
};

struct UI_Grid {
    UI_Grid();

    UI_Grid(int row_, int columns_);

    int row;
    int column;
};

enum class UI_ElementState {
    Normal, Hovered, Focused, Pressed, Disabled
};

class UI_Element {
public:
    UI_Element(UI_ElementState state, UI_Position position, mat::Vec2f dimension, UI_Grid grid);

    virtual void update(const EventManager& event_manager) = 0;

    virtual void submit(UI_Renderer& ui_renderer) {}

    void add_child(std::shared_ptr<UI_Element> child);

    std::vector<std::shared_ptr<UI_Element>> get_children();

    void set_parent(UI_Element* parent);

    void set_position(const mat::Vec2f& position);

    mat::Vec2f get_absolute_position() const;

    void set_dimension(const mat::Vec2f& dimension);

    mat::Vec2f get_position() const;

    mat::Vec2f get_dimension() const;

    UI_ElementState get_state() const;

    void set_focus(bool focus);
    bool is_focus() const;

    void set_grid(const UI_Grid& grid);
    bool has_grid() const;
    UI_Grid get_grid() const;

protected:
    UI_ElementState p_state;
    UI_Position p_position;
    mat::Vec2f p_dimension;
    std::vector<std::shared_ptr<UI_Element>> p_childrens;
    UI_Element* p_parent;
    UI_Grid p_grid; 
};

enum UI_DrawMode {
    Flat,
    Texture,
    Text
};

class UI_Drawable : public UI_Element {
public:
    UI_Drawable(UI_ElementState state, UI_Position position, mat::Vec2f dimension, UI_Grid grid, mat::Vec4f color, mat::Vec2f texture_pos, mat::Vec2f texture_dim, UI_DrawMode draw_mode);

    virtual void submit(UI_Renderer& ui_renderer) = 0;

protected:
    mat::Vec4f p_color;
    mat::Vec2f p_texture_pos;
    mat::Vec2f p_texture_dim;
    UI_DrawMode p_draw_mode;
};

class UI_Container : public UI_Element {
public:
    UI_Container(UI_ElementState state, mat::Vec2f position, mat::Vec2f dimension, UI_Grid grid);

    virtual void update(const EventManager& event_manager) override;

private:

};

class UI_Panel : public UI_Drawable {
public:
    UI_Panel(UI_ElementState state, UI_Position position, mat::Vec2f dimension, UI_Grid grid, mat::Vec4f color, mat::Vec2f texture_pos, mat::Vec2f texture_dim, UI_DrawMode draw_mode);

    virtual void update(const EventManager& event_manager) override;

    virtual void submit(UI_Renderer& ui_renderer) override;

private:

};

class UI_Button : public UI_Element {
public:
    using Callback = std::function<void()>;

    UI_Button(UI_ElementState state, UI_Position position, mat::Vec2f dimension, UI_Grid grid, Callback function);

    virtual void update(const EventManager& event_manager) override;

    void set_on_click(Callback cb);

private:
    Callback m_function;
};

class UI_Label : public UI_Drawable {
public:
    UI_Label(UI_ElementState state, UI_Position position, UI_Grid grid, mat::Vec4f color, const std::string& text);

    mat::Vec2f compute_dimension(Font& font);

    virtual void update(const EventManager& event_manager) override;

    virtual void submit(UI_Renderer& ui_renderer) override;

private:
    std::string m_text;
};

}
#include "UI/Elements.hpp"

namespace AMB::UI {

UI_Grid::UI_Grid()
: row(-1), column(-1)
{}

UI_Grid::UI_Grid(int row_, int column_)
: row(row_), column(column_)
{
    if (row < 1) { row = 1; }
    if (column < 1) { column = 1; }
}

bool p_visible;
bool p_focus;
UI_Position p_position;
mat::Vec2f p_dimension;
std::vector<std::shared_ptr<UI_Element>> p_childrens;
UI_Element* p_parent;
UI_Grid p_grid; 

UI_Element::UI_Element(UI_ElementState state, UI_Position position, mat::Vec2f dimension, UI_Grid grid)
: p_state(state), p_position(position), p_dimension(dimension), p_parent(nullptr), p_grid(grid)
{}

void UI_Element::add_child(std::shared_ptr<UI_Element> child) {
    p_childrens.push_back(child);

    child->set_parent(this);
}

std::vector<std::shared_ptr<UI_Element>> UI_Element::get_children() {
    return p_childrens;
}

void UI_Element::set_parent(UI_Element* parent) {
    p_parent = parent;
}

void UI_Element::set_position(const mat::Vec2f& position) {
    p_position.position = position;
}

mat::Vec2f UI_Element::get_absolute_position() const {
    mat::Vec2f parent_pos{0.0f, 0.0f};
    if (p_parent) {
        parent_pos = p_parent->get_absolute_position();
    }

    switch (p_position.type)
    {
    case UI_PositionType::absolute:
        return p_position.position;
    
    case UI_PositionType::relative:
        return parent_pos + p_position.position;

    case UI_PositionType::grid:
        if (!p_parent || !p_parent->has_grid()) {
            return {0.0f, 0.0f};
        }
        {
        UI_Grid parent_grid = p_parent->get_grid();
        mat::Vec2f prent_dim = p_parent->get_dimension();
        mat::Vec2f parent_cell = {prent_dim[0]/parent_grid.column, prent_dim[1]/parent_grid.row};
        mat::Vec2f parent_pos = p_parent->get_absolute_position() + parent_cell * p_position.position;
        
        mat::Vec2f anchor{0.0f, 0.0f};

        switch (p_position.anchor)
        {
        case UI_Anchor::TL:
            anchor = {0.0f, 1.0f};
            return parent_pos + anchor*(parent_cell - p_dimension);

        case UI_Anchor::TC:
            anchor = {0.5f, 1.0f};
            return parent_pos + anchor*(parent_cell - p_dimension);

        case UI_Anchor::TR:
            anchor = {1.0f, 1.0f};
            return parent_pos + anchor*(parent_cell - p_dimension);

        case UI_Anchor::CL:
            anchor = {0.0f, 0.5f};
            return parent_pos + anchor*(parent_cell - p_dimension);

        case UI_Anchor::CC:
            anchor = {0.5f, 0.5f};
            return parent_pos + anchor*(parent_cell - p_dimension);

        case UI_Anchor::CR:
            anchor = {1.0f, 0.5f};
            return parent_pos + anchor*(parent_cell - p_dimension);

        case UI_Anchor::BL:
            anchor = {0.0f, 0.0f};
            return parent_pos + anchor*(parent_cell - p_dimension);

        case UI_Anchor::BC:
            anchor = {0.5f, 0.0f};
            return parent_pos + anchor*(parent_cell - p_dimension);

        case UI_Anchor::BR:
            anchor = {1.0f, 0.0f};
            return parent_pos + anchor*(parent_cell - p_dimension);
        
        default:
            return mat::Vec2f{0.0f, 0.0f};
        }
        }

    default:
        break;
    }

    return mat::Vec2f{0.0f, 0.0f};
}

void UI_Element::set_dimension(const mat::Vec2f& dimension) {
    p_dimension = dimension;
}

mat::Vec2f UI_Element::get_position() const {
    return p_position.position;
}

mat::Vec2f UI_Element::get_dimension() const {
    return p_dimension;
}

UI_ElementState UI_Element::get_state() const {
    return p_state;
}

void UI_Element::set_grid(const UI_Grid& grid) {
    p_grid = grid;
}

bool UI_Element::has_grid() const {
    return p_grid.column > 0 && p_grid.row > 0;
}

UI_Grid UI_Element::get_grid() const {
    return p_grid;
}

UI_Drawable::UI_Drawable(UI_ElementState state, UI_Position position, mat::Vec2f dimension, UI_Grid grid, mat::Vec4f color, mat::Vec2f texture_pos, mat::Vec2f texture_dim, UI_DrawMode draw_mode)
: UI_Element(state, position, dimension, grid), p_color(color), p_texture_pos(texture_pos), p_texture_dim(texture_dim), p_draw_mode(draw_mode)
{}

// ==========
// Container
// ==========

UI_Container::UI_Container(UI_ElementState state, mat::Vec2f position, mat::Vec2f dimension, UI_Grid grid) 
: UI_Element(state, UI_Position{UI_PositionType::absolute, UI_Anchor::TL, position}, dimension, grid)
{}

void UI_Container::update(const EventManager& event_manager) {

}

// ==========
// Panel
// ==========

UI_Panel::UI_Panel(UI_ElementState state, UI_Position position, mat::Vec2f dimension, UI_Grid grid, mat::Vec4f color, mat::Vec2f texture_pos, mat::Vec2f texture_dim, UI_DrawMode draw_mode)
:UI_Drawable(state, position, dimension, grid, color, texture_pos, texture_dim, draw_mode)
{}

void UI_Panel::update(const EventManager& event_manager) {

}

void UI_Panel::submit(UI_Renderer& ui_renderer) {
    mat::Vec2f position = get_absolute_position();

    UI_Vertex ui_vertices[4] = {
        UI_Vertex{position[0],                  position[1],                    p_color[0], p_color[1], p_color[2], p_color[3], p_texture_pos[0],                       p_texture_pos[1],                       float(p_draw_mode)},
        UI_Vertex{position[0] + p_dimension[0], position[1],                    p_color[0], p_color[1], p_color[2], p_color[3], p_texture_pos[0] + p_texture_dim[0],    p_texture_pos[1],                       float(p_draw_mode)},
        UI_Vertex{position[0] + p_dimension[0], position[1] + p_dimension[1],   p_color[0], p_color[1], p_color[2], p_color[3], p_texture_pos[0] + p_texture_dim[0],    p_texture_pos[1] + p_texture_dim[1],    float(p_draw_mode)},
        UI_Vertex{position[0],                  position[1] + p_dimension[1],   p_color[0], p_color[1], p_color[2], p_color[3], p_texture_pos[0],                       p_texture_pos[1] + p_texture_dim[1],    float(p_draw_mode)} 
    };
    ui_renderer.submit_quad(ui_vertices);
}

// ==========
// Button
// ==========

UI_Button::UI_Button(UI_ElementState state, UI_Position position, mat::Vec2f dimension, UI_Grid grid, Callback function) 
: UI_Element(state, position, dimension, grid), m_function(function)
{}

void UI_Button::update(const EventManager& event_manager) {
    int x,y;
    mat::Vec2f pos = get_absolute_position();
    event_manager.mouse().mouse_position(x, y);
    if (event_manager.mouse().button_down(AMB::MouseButton::MOUSE_LEFT) && 
        pos[0] < x && pos[0] + p_dimension[0] > x &&
        pos[1] < y && pos[1] + p_dimension[1] > y) {
            m_function();
    }
}

// ==========
// Label
// ==========

void UI_Button::set_on_click(Callback cb){
    m_function = std::move(cb);
}

UI_Label::UI_Label(UI_ElementState state, UI_Position position, UI_Grid grid, mat::Vec4f color, const std::string& text)
: UI_Drawable(state, position, mat::Vec2f{0.0f, 0.0f}, grid, color, {0.0f, 0.0f}, {0.0f, 0.0f}, UI_DrawMode::Text), m_text(text)
{}

mat::Vec2f UI_Label::compute_dimension(Font& font) {
    float max_x(0), current_x(0), current_y(0);

    for (uint32_t i(0) ; i < m_text.size() ; ++i) {
        if (m_text[i] == '\n') {
            if (current_x > max_x) {
                max_x = current_x;
            }
            current_x = 0;
            current_y += font.get_height();

        }else{
            const Character& c = font.get_char(m_text[i]);
            current_x += c.advance >> 6;
        }
    }

    if (current_x > max_x) {
        max_x = current_x;
    }

    return mat::Vec2f{max_x, current_y};
}

void UI_Label::update(const EventManager& event_manager) {

}

void UI_Label::submit(UI_Renderer& ui_renderer) {
    float current_x(0), current_y(0);
    float r=p_color[0], g=p_color[1], b=p_color[2], a=p_color[3];
    Font& font = ui_renderer.get_font();
    p_dimension = compute_dimension(font);
    mat::Vec2f position = get_absolute_position();

    for (uint32_t i(0) ; i < m_text.size() ; ++i) {
        if (m_text[i] == '\n') {
            current_x = 0;
            current_y -= font.get_height();

        }else{
            const Character& c = font.get_char(m_text[i]);

            float x_(position[0] + current_x + c.bearing_x);
            float y_(position[1] + current_y - c.height + c.bearing_y);

            UI_Vertex  vertex[4] = {
                UI_Vertex{x_,           y_,            r, g, b, a,   c.u,        c.v + c.h, float(UI_DrawMode::Text)}, // Bottom left
                UI_Vertex{x_ + c.width, y_,            r, g, b, a,   c.u + c.w,  c.v + c.h, float(UI_DrawMode::Text)}, // Bottom right
                UI_Vertex{x_ + c.width, y_ + c.height, r, g, b, a,   c.u + c.w,  c.v      , float(UI_DrawMode::Text)}, // Top right
                UI_Vertex{x_,           y_ + c.height, r, g, b, a,   c.u,        c.v      , float(UI_DrawMode::Text)} // Top left
            };
            ui_renderer.submit_quad(vertex);

            current_x += c.advance >> 6;
        }
    }
}

}
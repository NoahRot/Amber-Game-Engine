#include "UI/Menu.hpp"

namespace AMB::UI {

Menu::Menu(mat::Vec2f position, mat::Vec2f dimension, const Drawable& drawable)
: m_root(nullptr), m_focus(true), m_draw(true)
{
    //m_root = std::make_shared<Panel>(position, dimension, drawable);

    Logger::instance().log(Debug, "Menu created");
}

std::shared_ptr<Panel> Menu::get_root() {
    return m_root;
}

void Menu::recursive_submit(std::shared_ptr<Element> element, Renderer& renderer) {
    element->submit(renderer);
    for (auto ptr : element->get_children()) {
        if (ptr) {
            recursive_submit(ptr, renderer);
        }
    }
}

void Menu::submit(Renderer& renderer) {
    recursive_submit(m_root, renderer);
}

void Menu::recursive_update(std::shared_ptr<Element> element, UI_InputTransfert& input) {
    element->update(input);
    for (auto ptr : element->get_children()) {
        if (ptr) {
            recursive_update(ptr, input);
        }
    }
}

void Menu::update(EventManager& event_manager) {
    UI_InputTransfert input(event_manager);
    input.manage(event_manager);
    recursive_update(m_root, input);
}



MenuFactory::MenuFactory(mat::Vec2f position, mat::Vec2f dimension, mat::Vec4f color, bool has_grid, Grid grid)
: m_menu(nullptr), m_element_stack()
{
    Drawable drawable;
    drawable.color = color;
    if (has_grid && grid.exist && grid.column > 0 && grid.row > 0) {
        drawable.grid = grid;
    }
    drawable.render_mode = RenderMode::Flat;

    m_menu = std::make_shared<Menu>(position, dimension, drawable);
    m_element_stack.push(m_menu->get_root());

    Logger::instance().log(Debug, "MenuFactory created");
    std::cout << "MenuFactory created"<< std::endl;
}

MenuFactory::MenuFactory(mat::Vec2f position, mat::Vec2f dimension, mat::Vec2f uv_pos, mat::Vec2f uv_dim, bool has_grid, Grid grid)
: m_menu(nullptr), m_element_stack()
{
    Drawable drawable;
    if (has_grid && grid.exist && grid.column > 0 && grid.row > 0) {
        drawable.grid = grid;
    }
    drawable.render_mode = RenderMode::Texture;
    drawable.texture_dimension = uv_dim;
    drawable.texture_position = uv_pos;
    
    m_menu = std::make_shared<Menu>(position, dimension, drawable);
    m_element_stack.push(m_menu->get_root());

    Logger::instance().log(Debug, "MenuFactory created");
    std::cout << "MenuFactory created"<< std::endl;
}

MenuFactory& MenuFactory::begin_panel(mat::Vec2f position, mat::Vec2f dimension, mat::Vec4f color, bool in_grid, Alignement alignement, bool has_grid, Grid grid) {
    Logger::instance().log(Debug, "Begin Panel");
    std::shared_ptr<Element> parent = m_element_stack.top();

    Drawable drawable;
    drawable.color = color;
    drawable.render_mode = RenderMode::Flat;
    if (in_grid) {
        drawable.grid_position = mat::Vec2i{(int)position[0], (int)position[1]};
        if     (alignement == Alignement::TL) { drawable.positionning = ElementPositionning::grid_TL; }
        else if(alignement == Alignement::TC) { drawable.positionning = ElementPositionning::grid_TC; }
        else if(alignement == Alignement::TR) { drawable.positionning = ElementPositionning::grid_TR; }
        else if(alignement == Alignement::CL) { drawable.positionning = ElementPositionning::grid_CL; }
        else if(alignement == Alignement::CC) { drawable.positionning = ElementPositionning::grid_CC; }
        else if(alignement == Alignement::CR) { drawable.positionning = ElementPositionning::grid_CR; }
        else if(alignement == Alignement::BL) { drawable.positionning = ElementPositionning::grid_BL; }
        else if(alignement == Alignement::BC) { drawable.positionning = ElementPositionning::grid_BC; }
        else if(alignement == Alignement::BR) { drawable.positionning = ElementPositionning::grid_BR; }
        else { drawable.positionning = ElementPositionning::grid_CC; }
    }else{
        drawable.positionning = ElementPositionning::relative;
    }

    if (has_grid && grid.exist && grid.column > 0 && grid.row > 0) {
        drawable.grid = grid;
    }

    //std::shared_ptr<Panel> p = std::make_shared<Panel>(position, dimension, drawable);
    //m_element_stack.top()->add_child(p);
    //m_element_stack.push(p);

    Logger::instance().log(Debug, "End Panel");
    return *this;
}

MenuFactory& MenuFactory::begin_image(mat::Vec2f position, mat::Vec2f dimension, mat::Vec2f uv_pos, mat::Vec2f uv_dim, bool in_grid, Alignement alignement, bool has_grid, Grid grid) {
    Logger::instance().log(Debug, "Begin Image");
    std::shared_ptr<Element> parent = m_element_stack.top();

    Drawable drawable;
    drawable.texture_position = uv_pos;
    drawable.texture_dimension = uv_dim;
    drawable.render_mode = RenderMode::Texture;
    if (in_grid) {
        drawable.grid_position = mat::Vec2i{(int)position[0], (int)position[1]};
        if     (alignement == Alignement::TL) { drawable.positionning = ElementPositionning::grid_TL; }
        else if(alignement == Alignement::TC) { drawable.positionning = ElementPositionning::grid_TC; }
        else if(alignement == Alignement::TR) { drawable.positionning = ElementPositionning::grid_TR; }
        else if(alignement == Alignement::CL) { drawable.positionning = ElementPositionning::grid_CL; }
        else if(alignement == Alignement::CC) { drawable.positionning = ElementPositionning::grid_CC; }
        else if(alignement == Alignement::CR) { drawable.positionning = ElementPositionning::grid_CR; }
        else if(alignement == Alignement::BL) { drawable.positionning = ElementPositionning::grid_BL; }
        else if(alignement == Alignement::BC) { drawable.positionning = ElementPositionning::grid_BC; }
        else if(alignement == Alignement::BR) { drawable.positionning = ElementPositionning::grid_BR; }
        else { drawable.positionning = ElementPositionning::grid_CC; }
    }else{
        drawable.positionning = ElementPositionning::relative;
    }

    //std::shared_ptr<Panel> p = std::make_shared<Panel>(position, dimension, drawable);
    //m_element_stack.top()->add_child(p);
    //m_element_stack.push(p);

    Logger::instance().log(Debug, "End image");
    return *this;
}

MenuFactory& MenuFactory::begin_button(mat::Vec2f position, mat::Vec2f dimension, void (*callback)(), bool in_grid, Alignement alignement, bool has_grid, Grid grid) {
    Logger::instance().log(Debug, "Begin Button");
    std::shared_ptr<Element> parent = m_element_stack.top();

    Drawable drawable;
    if (in_grid) {
        drawable.grid_position = mat::Vec2i{(int)position[0], (int)position[1]};
        if     (alignement == Alignement::TL) { drawable.positionning = ElementPositionning::grid_TL; }
        else if(alignement == Alignement::TC) { drawable.positionning = ElementPositionning::grid_TC; }
        else if(alignement == Alignement::TR) { drawable.positionning = ElementPositionning::grid_TR; }
        else if(alignement == Alignement::CL) { drawable.positionning = ElementPositionning::grid_CL; }
        else if(alignement == Alignement::CC) { drawable.positionning = ElementPositionning::grid_CC; }
        else if(alignement == Alignement::CR) { drawable.positionning = ElementPositionning::grid_CR; }
        else if(alignement == Alignement::BL) { drawable.positionning = ElementPositionning::grid_BL; }
        else if(alignement == Alignement::BC) { drawable.positionning = ElementPositionning::grid_BC; }
        else if(alignement == Alignement::BR) { drawable.positionning = ElementPositionning::grid_BR; }
        else { drawable.positionning = ElementPositionning::grid_CC; }
    }else{
        drawable.positionning = ElementPositionning::relative;
    }

    if (has_grid && grid.exist && grid.column > 0 && grid.row > 0) {
        drawable.grid = grid;
    }

    //std::shared_ptr<Button> p = std::make_shared<Button>(position, dimension, drawable, callback);
    //m_element_stack.top()->add_child(p);
    //m_element_stack.push(p);

    Logger::instance().log(Debug, "End button");
    return *this;
}

MenuFactory& MenuFactory::begin_label(mat::Vec2f position, mat::Vec4f color, const std::string& text, Font& font, bool in_grid, Alignement alignement, bool has_grid, Grid grid) {
    Logger::instance().log(Debug, "Begin Label");
    std::shared_ptr<Element> parent = m_element_stack.top();

    Drawable drawable;
    drawable.color = color;
    if (in_grid) {
        drawable.grid_position = mat::Vec2i{(int)position[0], (int)position[1]};
        if     (alignement == Alignement::TL) { drawable.positionning = ElementPositionning::grid_TL; }
        else if(alignement == Alignement::TC) { drawable.positionning = ElementPositionning::grid_TC; }
        else if(alignement == Alignement::TR) { drawable.positionning = ElementPositionning::grid_TR; }
        else if(alignement == Alignement::CL) { drawable.positionning = ElementPositionning::grid_CL; }
        else if(alignement == Alignement::CC) { drawable.positionning = ElementPositionning::grid_CC; }
        else if(alignement == Alignement::CR) { drawable.positionning = ElementPositionning::grid_CR; }
        else if(alignement == Alignement::BL) { drawable.positionning = ElementPositionning::grid_BL; }
        else if(alignement == Alignement::BC) { drawable.positionning = ElementPositionning::grid_BC; }
        else if(alignement == Alignement::BR) { drawable.positionning = ElementPositionning::grid_BR; }
        else { drawable.positionning = ElementPositionning::grid_CC; }
    }else{
        drawable.positionning = ElementPositionning::relative;
    }

    if (has_grid && grid.exist && grid.column > 0 && grid.row > 0) {
        drawable.grid = grid;
    }
    drawable.render_mode = AMB::UI::RenderMode::Text;

    //Logger::instance().log(Debug, "LABEL::Before creation of shared_ptr");
    //std::shared_ptr<Label> p = std::make_shared<Label>(position, drawable, text);
    //Logger::instance().log(Debug, "LABEL::After creation of shared_ptr");
    //m_element_stack.top()->add_child(p);
    //m_element_stack.push(p);

    Logger::instance().log(Debug, "End label");
    return *this;
}

MenuFactory& MenuFactory::end() {
    Logger::instance().log(Debug, "Begin End");
    if (m_element_stack.size() <= 1) {
        AMB::Logger::instance().log(Error, "Menu Factory: End called too many times. Unbalance begin/end statements.");
        return *this;
    }
    m_element_stack.pop();
    Logger::instance().log(Debug, "End End");
    return *this;
}

std::shared_ptr<Menu> MenuFactory::complete() {
    Logger::instance().log(Debug, "Begin completion of menu");
    if (m_element_stack.size() != 1) {
        AMB::Logger::instance().log(Error, "Menu Factory: build process has not been correctly completed. The number of element in the stack are " + std::to_string(m_element_stack.size()) + " and sould be 1.");
        return nullptr;
    }

    m_element_stack.pop(); 
    Logger::instance().log(Debug, "Menu completed");
    return std::move(m_menu);
}

}
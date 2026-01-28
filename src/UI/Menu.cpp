#include "UI/Menu.hpp"

namespace AMB::UI {

UI_Menu::UI_Menu(UI_ElementState state, mat::Vec2f position, mat::Vec2f dimension, UI_Grid grid) 
: m_base(nullptr)
{
    // bool focus, mat::Vec2f position, mat::Vec2f dimension, UI_Grid grid
    m_base = std::make_shared<UI_Container>(state, position, dimension, grid);
}

void UI_Menu::add_element(std::shared_ptr<UI_Element> element) {
    m_base->add_child(element);
}

void UI_Menu::submit(AMB::UI::UI_Renderer& ui_renderer) {
    for (auto c : m_base->get_children()) {
        submit_recursive(c, ui_renderer);
    }
}

void UI_Menu::update(EventManager& event) {
    for (auto c : m_base->get_children()) {
        update_recursive(c, event);
    }
}

std::shared_ptr<UI_Element> UI_Menu::get_container() {
    return m_base;
}

void UI_Menu::submit_recursive(std::shared_ptr<UI_Element> element, AMB::UI::UI_Renderer& ui_renderer) {
    element->submit(ui_renderer);

    for (auto c : element->get_children()) {
        submit_recursive(c, ui_renderer);
    } 
}

void UI_Menu::update_recursive(std::shared_ptr<UI_Element> element, EventManager& event) {
    element->update(event);

    for (auto c : element->get_children()) {
        update_recursive(c, event);
    } 
}

// ==========
// Factory
// ==========

UI_Factory::UI_Factory()
: m_menu(nullptr)
{}

UI_Factory& UI_Factory::create_menu(mat::Vec2f position, mat::Vec2f dimension, UI_Grid grid) {
    m_stack = std::stack<std::shared_ptr<UI_Element>>();
    m_menu = std::make_shared<UI_Menu>(UI_ElementState::Normal, position, dimension, grid);
    m_stack.push(m_menu->get_container());
    return *this;
}

UI_Menu UI_Factory::complete_menu() {
    if (m_stack.size() != 1) {
        Logger::instance().log(Fatal, "UI Factory can not complete Menu. Elements not correctly ended.");
        exit(EXIT_FAILURE);
    }
    return *m_menu;
}

UI_Factory& UI_Factory::begin_panel(UI_ElementState state, mat::Vec2f position, UI_PositionType pos_type, mat::Vec2f dimension, mat::Vec4f color, UI_Grid grid, UI_Anchor anchor) {
    std::shared_ptr<UI_Element> top = get();
    std::shared_ptr<UI_Panel> element 
        = std::make_shared<UI_Panel>(state, UI_Position{pos_type, anchor, position}, dimension, grid, color, mat::Vec2f{0.0f, 0.0f}, mat::Vec2f{0.0f, 0.0f}, UI_DrawMode::Flat);
    top->add_child(element);
    m_stack.push(element);
    return *this;
}

UI_Factory& UI_Factory::begin_image(UI_ElementState state, mat::Vec2f position, UI_PositionType pos_type, mat::Vec2f dimension, mat::Vec2f tex_pos, mat::Vec2f tex_dim, UI_Grid grid, UI_Anchor anchor) {
    std::shared_ptr<UI_Element> top = get();
    std::shared_ptr<UI_Panel> element 
        = std::make_shared<UI_Panel>(state, UI_Position{pos_type, anchor, position}, dimension, grid, mat::Vec4f{0.0f, 0.0f, 0.0f, 1.0f}, tex_pos, tex_dim, UI_DrawMode::Texture);
    top->add_child(element);
    m_stack.push(element);
    return *this;
}

UI_Factory& UI_Factory::begin_button(UI_ElementState state, mat::Vec2f position, UI_PositionType pos_type, mat::Vec2f dimension, std::function<void()> callback, UI_Grid grid, UI_Anchor anchor) {
    std::shared_ptr<UI_Element> top = get();
    std::shared_ptr<UI_Button> element 
        = std::make_shared<UI_Button>(state, UI_Position{pos_type, anchor, position}, dimension, grid, callback);
    top->add_child(element);
    m_stack.push(element);
    return *this;
}

UI_Factory& UI_Factory::begin_text(UI_ElementState state, mat::Vec2f position, UI_PositionType pos_type, mat::Vec4f color, const std::string& text, UI_Grid grid, UI_Anchor anchor) {
    std::shared_ptr<UI_Element> top = get();
    std::shared_ptr<UI_Label> element 
        = std::make_shared<UI_Label>(state, UI_Position{pos_type, anchor, position}, grid, color, text);
    top->add_child(element);
    m_stack.push(element);
    return *this;
}

UI_Factory& UI_Factory::end() {
    end_current();
    return *this;
}

std::shared_ptr<UI_Element> UI_Factory::get() {
    if (m_stack.size() < 1) {
        Logger::instance().log(Fatal, "UI Factory unvalid construction in top. Elements not correctly ended.");
        exit(EXIT_FAILURE);
    }
    return m_stack.top();
}

void UI_Factory::end_current() {
    if (m_stack.size() <= 1) {
        Logger::instance().log(Fatal, "UI Factory unvalid construction in end. Elements not correctly ended.");
        exit(EXIT_FAILURE);
    }
    m_stack.pop();
}

}
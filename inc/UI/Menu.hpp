#pragma once

#include <stack>

#include "UI/Elements.hpp"

namespace AMB::UI {

class UI_Menu {
public:
    UI_Menu(UI_ElementState state, mat::Vec2f position, mat::Vec2f dimension, UI_Grid grid = UI_Grid());

    void add_element(std::shared_ptr<UI_Element> element);

    void submit(AMB::UI::UI_Renderer& ui_renderer);

    void update(EventManager& event);

    std::shared_ptr<UI_Element> get_container();

private:
    void submit_recursive(std::shared_ptr<UI_Element> element, AMB::UI::UI_Renderer& ui_renderer);

    void update_recursive(std::shared_ptr<UI_Element> element, EventManager& event);

    std::shared_ptr<UI_Element> m_base;
};

class UI_Factory {
public:
    UI_Factory();

    UI_Factory& create_menu(mat::Vec2f position, mat::Vec2f dimension, UI_Grid grid = UI_Grid());

    UI_Menu complete_menu();

    UI_Factory& begin_panel(UI_ElementState state, mat::Vec2f position, UI_PositionType pos_type, mat::Vec2f dimension, mat::Vec4f color, UI_Grid grid = UI_Grid(), UI_Anchor anchor = UI_Anchor::CC);

    UI_Factory& begin_image(UI_ElementState state, mat::Vec2f position, UI_PositionType pos_type, mat::Vec2f dimension, mat::Vec2f tex_pos, mat::Vec2f tex_dim, UI_Grid grid = UI_Grid(), UI_Anchor anchor = UI_Anchor::CC);

    UI_Factory& begin_button(UI_ElementState state, mat::Vec2f position, UI_PositionType pos_type, mat::Vec2f dimension, std::function<void()> callback, UI_Grid grid = UI_Grid(), UI_Anchor anchor = UI_Anchor::CC);

    UI_Factory& begin_text(UI_ElementState state, mat::Vec2f position, UI_PositionType pos_type, mat::Vec4f color, const std::string& text, UI_Grid grid = UI_Grid(), UI_Anchor anchor = UI_Anchor::CC);

    UI_Factory& end();

private:
    std::shared_ptr<UI_Element> get();

    void end_current();

    std::stack<std::shared_ptr<UI_Element>> m_stack;
    std::shared_ptr<UI_Menu> m_menu;
};

}
#pragma once

#include "mat/Math.hpp"

#include "UI/Type.hpp"
#include "UI/Element.hpp"

namespace AMB::UI {

class Menu {
public:
    Menu(mat::Vec2f position, mat::Vec2f dimension, const Drawable& drawable);

    std::shared_ptr<Panel> get_root();

    void recursive_submit(std::shared_ptr<Element> element, Renderer& renderer);

    void submit(Renderer& renderer);

    void recursive_update(std::shared_ptr<Element> element, UI_InputTransfert& input);

    void update(EventManager& event_manager);

private:
    std::shared_ptr<Panel> m_root;
    bool m_focus;
    bool m_draw;
};

class MenuFactory {
public:
    MenuFactory(mat::Vec2f position, mat::Vec2f dimension, mat::Vec4f color, bool has_grid = false, Grid grid = Grid());

    MenuFactory(mat::Vec2f position, mat::Vec2f dimension, mat::Vec2f uv_pos, mat::Vec2f uv_dim, bool has_grid = false, Grid grid = Grid());

    MenuFactory& begin_panel(mat::Vec2f position, mat::Vec2f dimension, mat::Vec4f color, bool in_grid = false, Alignement alignement = Alignement::CC, bool has_grid = false, Grid grid = Grid());

    MenuFactory& begin_image(mat::Vec2f position, mat::Vec2f dimension, mat::Vec2f uv_pos, mat::Vec2f uv_dim, bool in_grid = false, Alignement alignement = Alignement::CC, bool has_grid = false, Grid grid = Grid());

    MenuFactory& begin_button(mat::Vec2f position, mat::Vec2f dimension, void (*callback)(), bool in_grid = false, Alignement alignement = Alignement::CC, bool has_grid = false, Grid grid = Grid());

    MenuFactory& begin_label(mat::Vec2f position, mat::Vec4f color, const std::string& text, Font& font, bool in_grid = false, Alignement alignement = Alignement::CC, bool has_grid = false, Grid grid = Grid());

    MenuFactory& end();

    std::shared_ptr<Menu> complete();

private:
    std::shared_ptr<Menu> m_menu;
    std::stack<std::shared_ptr<Element>> m_element_stack;
};

}
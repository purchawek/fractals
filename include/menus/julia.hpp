#ifndef JULIA_MENU_HPP
#define JULIA_MENU_HPP

#include <SFGUI/SFGUI.hpp>
#include <sstream>

#include <SFGUI/Widgets.hpp>

#include "../render_ctx.hpp"

class julia_menu {

    sfg::Window::Ptr window;
    sfg::Box::Ptr box;

    sfg::Entry::Ptr factor, dfactor;

    sfg::Entry::Ptr z0_Im, z0_Re;
    sfg::Entry::Ptr dz0_Im, dz0_Re;

    sfg::Button::Ptr accept_btn, run_btn;

public:
    julia_menu(sfg::Window::Ptr sfg_window, render_ctx& ctx)
    : window{sfg_window} {
        box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);



        z0_Re = sfg::Entry::Create(std::to_string(ctx.get_z0().real()));
        z0_Re->SetRequisition(sf::Vector2f{80.0f, 0.0f});

        auto create_row = [](sfg::Label::Ptr label, sfg::Entry::Ptr en) -> sfg::Box::Ptr {
            auto row = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 3.0f);
            row->Pack(label);
            row->Pack(en);
            return row;
        };

        factor = sfg::Entry::Create(std::to_string(ctx.zoom_factor()));
        factor->SetRequisition(sf::Vector2f{80.0f, 0.0f});

        dfactor = sfg::Entry::Create(std::to_string(ctx.d_zoom()));
        dfactor->SetRequisition(sf::Vector2f{80.0f, 0.0f});

        auto factor_row = create_row(sfg::Label::Create("Factor = "), factor);
        auto dfactor_row = create_row(sfg::Label::Create("dFactor= "), dfactor);

        z0_Im = sfg::Entry::Create(std::to_string(ctx.get_z0().imag()));
        z0_Im->SetRequisition(sf::Vector2f{80.0f, 0.0f});

        auto Im_row = create_row(sfg::Label::Create("Im = "), z0_Im);
        auto Re_row = create_row(sfg::Label::Create("Re = "), z0_Re);

        dz0_Im = sfg::Entry::Create(std::to_string(ctx.dz0.imag()));
        dz0_Im->SetRequisition(sf::Vector2f{80.0f, 0.0f});
        dz0_Re = sfg::Entry::Create(std::to_string(ctx.dz0.real()));
        dz0_Re->SetRequisition(sf::Vector2f{80.0f, 0.0f});

        auto dIm_row = create_row(sfg::Label::Create("dIm= "), dz0_Im);
        auto dRe_row = create_row(sfg::Label::Create("dRe= "), dz0_Re);

        accept_btn = sfg::Button::Create("Accept");
        run_btn = sfg::Button::Create("Stop");

        box->Pack(factor_row);
        box->Pack(dfactor_row);
        box->Pack(Re_row);
        box->Pack(Im_row);
        box->Pack(dRe_row);
        box->Pack(dIm_row);
        box->Pack(accept_btn);
        box->Pack(run_btn);

        sfg_window->Add(box);
        accept_btn->GetSignal(sfg::Widget::OnMouseLeftPress).Connect([&ctx, this] {
            double re = std::stod(std::string{z0_Re->GetText()});
            double im = std::stod(std::string{z0_Im->GetText()});
            double dre = std::stod(std::string{dz0_Re->GetText()});
            double dim = std::stod(std::string{dz0_Im->GetText()});
            double f   = std::stod(std::string{factor->GetText()});
            double df  = std::stod(std::string{dfactor->GetText()});
            ctx.set_z0({re, im});
            ctx.dz0 = {dre, dim};
            ctx.zoom_factor_ = f;
            ctx.factor_ = df;
        });

        run_btn->GetSignal(sfg::Widget::OnMouseLeftPress).Connect([&ctx] {
            ctx.dz0 = {0.0, 0.0};
        });


    }

    void update_dz(render_ctx& ctx) {
        dz0_Re->SetText(std::to_string(ctx.dz0.real()));
        dz0_Im->SetText(std::to_string(ctx.dz0.imag()));
    }

    void update_dzoom(render_ctx& ctx) {
        dfactor->SetText(std::to_string(ctx.d_zoom()));
    }

    void update(render_ctx& ctx) {
        if (std::norm(ctx.dz0) != 0) {
            z0_Im->SetText(std::to_string(ctx.get_z0().imag()));
            z0_Re->SetText(std::to_string(ctx.get_z0().real()));
        }
        if (ctx.d_zoom() != 1.0) {
            factor->SetText(std::to_string(ctx.zoom_factor()));
        }
    }
};



#endif

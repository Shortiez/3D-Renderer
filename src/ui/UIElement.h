//
// Created by gotts on 10/02/2025.
//

#ifndef UIELEMENT_H
#define UIELEMENT_H
#include "../graphics/Renderer.h"


namespace BG3DRenderer::UI{
    class UIElement {
    protected:
         UIElement();
        ~UIElement();

    public:
        virtual void Render();
        virtual void Render(Renderer &renderer);
    };
}

#endif //UIELEMENT_H

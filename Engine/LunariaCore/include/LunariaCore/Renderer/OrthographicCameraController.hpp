#pragma once

#include "LunariaCore/Global/Timestep.hpp"

#include "LunariaCore/Events/Event.hpp"
#include "LunariaCore/Events/ApplicationEvent.hpp"
#include "LunariaCore/Events/MouseEvent.hpp"

#include "LunariaCore/Renderer/OrthographicCamera.hpp"

namespace Lunaria {

    struct OrthographicCameraBounds
    {
        float Left, Right;
        float Bottom, Top;

        float GetWidth() const { return Right - Left; }
        float GetHeight() const { return Top - Bottom; }
    };

    class LUNARIA_API OrthographicCameraController
    {
    public:
        OrthographicCameraController(float aspectRatio, bool rotation = false);

        void OnUpdate(Timestep timestep);
        void OnEvent(Event& event);

        void OnResize(float width, float height);
        
        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }

        float GetZoomLevel() const { return m_ZoomLevel; }
        void SetZoomLevel(float level) { m_ZoomLevel = level; }
    private:
        bool OnMouseScrolled(const MouseScrolledEvent& event);
        bool OnWindowResized(const WindowResizeEvent& event);
        
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation = false;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f; // In degrees, in the anti-clockwise direction
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };


}

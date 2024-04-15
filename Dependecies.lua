-- Lunaria Dependencies

INCLUDES = {}
INCLUDES["stb_image"] = "%{wks.location}/External/stb_image"
INCLUDES["spirv_cross"] = "%{wks.location}/External/spirv_cross"
INCLUDES["spdlog"] = "%{wks.location}/External/spdlog"
INCLUDES["GLFW"] = "%{wks.location}/External/GLFW"
INCLUDES["Glad"] = "%{wks.location}/External/Glad"
INCLUDES["ImGui"] = "%{wks.location}/External/ImGui"
INCLUDES["glm"] = "%{wks.location}/External/glm"
INCLUDES["entt"] = "%{wks.location}/External/entt"
INCLUDES["SDL"] = "%{wks.location}/External/SDL"
INCLUDES["VulkanSDK"] = "%{wks.location}/External/VulkanSDK"
INCLUDES["nlohmann"] = "%{wks.location}/External/nlohmann"

-- Local Dependencies
LOCAL = {}
LOCAL["MATH"] = "%{wks.location}/Engine/LunariaMath/include"
LOCAL["CORE"] = "%{wks.location}/Engine/LunariaCore/include"
LOCAL["WINDOW"] = "%{wks.location}/Engine/LunariaWindowing/include"
LOCAL["ECS"] = "%{wks.location}/Engine/LunariaECS/include"

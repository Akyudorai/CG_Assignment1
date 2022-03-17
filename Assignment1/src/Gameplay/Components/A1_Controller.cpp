#include "Gameplay/Components/A1_Controller.h"
#include <GLFW/glfw3.h>
#define GLM_SWIZZLE
#include <GLM/gtc/quaternion.hpp>

#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"
#include "Application/Application.h"

A1_Controller::A1_Controller()
	: IComponent()
{ }

A1_Controller::~A1_Controller() = default;

void A1_Controller::Awake()
{
	m_Renderer = GetGameObject()->Get<RenderComponent>();
}

void A1_Controller::Update(float deltaTime)
{
	if (InputEngine::GetKeyState(GLFW_KEY_1) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_1) == ButtonState::Pressed)
	{
		// No Lighting
		LOG_INFO("1. No Lighting");
		m_Renderer->GetMaterial()->Set("u_Material.ToggleAmbience", false);
		m_Renderer->GetMaterial()->Set("u_Material.ToggleDiffuse", false);
		
	}

	if (InputEngine::GetKeyState(GLFW_KEY_2) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_2) == ButtonState::Pressed)
	{
		// Ambient Lighting Only
		LOG_INFO("2. Ambient Only");
		m_Renderer->GetMaterial()->Set("u_Material.ToggleAmbience", true);
		m_Renderer->GetMaterial()->Set("u_Material.ToggleDiffuse", false);
	}

	if (InputEngine::GetKeyState(GLFW_KEY_3) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_3) == ButtonState::Pressed)
	{
		// Specular Lighting Only
		LOG_INFO("3. Diffuse Only");
		m_Renderer->GetMaterial()->Set("u_Material.ToggleAmbience", false);
		m_Renderer->GetMaterial()->Set("u_Material.ToggleDiffuse", true);
	}

	if (InputEngine::GetKeyState(GLFW_KEY_4) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_4) == ButtonState::Pressed)
	{
		// Ambient + Specular
		LOG_INFO("4. Ambient + Diffuse");
		m_Renderer->GetMaterial()->Set("u_Material.ToggleAmbience", true);
		m_Renderer->GetMaterial()->Set("u_Material.ToggleDiffuse", true);
	}

	if (InputEngine::GetKeyState(GLFW_KEY_5) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_5) == ButtonState::Pressed)
	{
		// Ambient + SPecular + Custom Shader
		LOG_INFO("5. Ambient + Specular + Custom Shader");
	}

	if (InputEngine::GetKeyState(GLFW_KEY_6) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_6) == ButtonState::Pressed)
	{
		// Toggle Diffuse warp/ramp
		LOG_INFO("6. Toggle Diffuse warp/ramp");
	}

	if (InputEngine::GetKeyState(GLFW_KEY_7) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_7) == ButtonState::Pressed)
	{
		// Toggle Specular warp/ramp
		LOG_INFO("7. Toggle Specular warp/ramp");
	}

	if (InputEngine::GetKeyState(GLFW_KEY_8) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_8) == ButtonState::Pressed)
	{
		// Toggle Color Grading Warm
		LOG_INFO("8. Toggle Color Grading Warm");
	}

	if (InputEngine::GetKeyState(GLFW_KEY_9) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_9) == ButtonState::Pressed)
	{
		// Toggle Color Grading Cool
		LOG_INFO("9. Toggle Color Grading Cool");
	}

	if (InputEngine::GetKeyState(GLFW_KEY_0) == ButtonState::Pressed ||
		InputEngine::GetKeyState(GLFW_KEY_KP_0) == ButtonState::Pressed)
	{
		// Toggle COlor Grading Custom Effect
		LOG_INFO("0. Toggle Color Grading Custom Effect");
	}
}

void A1_Controller::RenderImGui()
{

}

nlohmann::json A1_Controller::ToJson() const
{
	return {
		
	};
}

A1_Controller::Sptr A1_Controller::FromJson(const nlohmann::json & blob)
{
	A1_Controller::Sptr result = std::make_shared<A1_Controller>();
	return result;
}
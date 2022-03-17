#include "Gameplay/Components/FirstPersonCamera.h"
#include <GLFW/glfw3.h>
#define GLM_SWIZZLE
#include <GLM/gtc/quaternion.hpp>

#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/JsonGlmHelpers.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/InputEngine.h"
#include "Application/Application.h"

FirstPersonCamera::FirstPersonCamera()
	: IComponent(),
	m_MoveSpeed(3.0f),
	m_RotateSpeed(0.1f), m_VerticalClamp(glm::vec2(0, 180)), m_CurrentRot(glm::vec2(0))
{ }

FirstPersonCamera::~FirstPersonCamera() = default;

void FirstPersonCamera::Awake()
{
	m_PrevMousePos = InputEngine::GetMousePos();
}

void FirstPersonCamera::Update(float deltaTime)
{
	// Rotation
	if (Application::Get().IsFocused)
	{
		glm::dvec2 currentMousePos = InputEngine::GetMousePos();
		glm::dvec2 delta = currentMousePos - m_PrevMousePos;

		m_CurrentRot.x -= static_cast<float>(delta.x) * m_RotateSpeed;
		m_CurrentRot.y -= static_cast<float>(delta.y) * m_RotateSpeed;

		if (m_CurrentRot.y < m_VerticalClamp.x) {
			m_CurrentRot.y = m_VerticalClamp.x;
		}

		if (m_CurrentRot.y > m_VerticalClamp.y) {
			m_CurrentRot.y = m_VerticalClamp.y;
		}

		glm::quat rotX = glm::angleAxis(glm::radians(m_CurrentRot.x), glm::vec3(0, 0, 1));
		glm::quat rotY = glm::angleAxis(glm::radians(m_CurrentRot.y), glm::vec3(1, 0, 0));
		glm::quat currentRot = rotX * rotY;
		GetGameObject()->SetRotation(currentRot);
		
		m_PrevMousePos = InputEngine::GetMousePos();
	}
	
	// Movement
	glm::vec3 motion = glm::vec3(0.0f);
	if (InputEngine::IsKeyDown(GLFW_KEY_W))
	{
		motion.z -= m_MoveSpeed;
	}

	if (InputEngine::IsKeyDown(GLFW_KEY_S))
	{
		motion.z += m_MoveSpeed;
	}

	if (InputEngine::IsKeyDown(GLFW_KEY_A))
	{
		motion.x -= m_MoveSpeed;
	}

	if (InputEngine::IsKeyDown(GLFW_KEY_D))
	{
		motion.x += m_MoveSpeed;
	}

	motion *= deltaTime;
	glm::vec3 worldMovement = GetGameObject()->GetRotation() * glm::vec4(motion, 1.0f);
	GetGameObject()->SetPostion(GetGameObject()->GetPosition() + worldMovement);





}

void FirstPersonCamera::RenderImGui()
{
	LABEL_LEFT(ImGui::InputFloat, "Movement Speed", &m_MoveSpeed);
	LABEL_LEFT(ImGui::InputFloat, "Rotation Speed", &m_RotateSpeed);
	LABEL_LEFT(ImGui::InputFloat2, "Vertical Clamp", &m_VerticalClamp.x);
}

nlohmann::json FirstPersonCamera::ToJson() const
{
	return {
		{ "movement_speed", m_MoveSpeed },
		{ "rotation_speed", m_RotateSpeed },
		{ "v_clamp", m_VerticalClamp }
	};
}

FirstPersonCamera::Sptr FirstPersonCamera::FromJson(const nlohmann::json& blob)
{
	FirstPersonCamera::Sptr result = std::make_shared<FirstPersonCamera>();
	result->m_MoveSpeed = JsonGet(blob, "movement_speed", result->m_MoveSpeed);
	result->m_RotateSpeed = JsonGet(blob, "rotation_speed", result->m_RotateSpeed);
	result->m_VerticalClamp = JsonGet(blob, "v_clamp", result->m_VerticalClamp);
	return result;
}
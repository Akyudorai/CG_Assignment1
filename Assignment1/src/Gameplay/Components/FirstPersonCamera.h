#pragma once

#include "IComponent.h"
struct GLFWwindow;

class FirstPersonCamera : public Gameplay::IComponent
{
public:
	typedef std::shared_ptr<FirstPersonCamera> Sptr;

	FirstPersonCamera();
	virtual ~FirstPersonCamera();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(FirstPersonCamera);
	virtual nlohmann::json ToJson() const override;
	static FirstPersonCamera::Sptr FromJson(const nlohmann::json& blob);

protected:
	float m_MoveSpeed;
	 
	float m_RotateSpeed;
	glm::vec2 m_VerticalClamp;
	glm::vec2 m_CurrentRot;
	glm::dvec2 m_PrevMousePos;
};
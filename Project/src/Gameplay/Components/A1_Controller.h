#pragma once

#include "IComponent.h"
#include "Gameplay/Components/RenderComponent.h"
#include "Gameplay/Material.h"

class A1_Controller : public Gameplay::IComponent
{
public:
	typedef std::shared_ptr<A1_Controller> Sptr;

	A1_Controller();
	virtual ~A1_Controller();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(A1_Controller);
	virtual nlohmann::json ToJson() const override;
	static A1_Controller::Sptr FromJson(const nlohmann::json& blob);

protected:
	RenderComponent::Sptr m_Renderer;

public:
	Gameplay::Material::Sptr m_Mat1, m_Mat2;

};
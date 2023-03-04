#pragma once
#include "BaseComponent.h"
namespace dae
{
	class UpdateComponent : public BaseComponent
	{
	public:
		UpdateComponent(std::weak_ptr<GameObject> pParent);
		virtual ~UpdateComponent() = default;
		UpdateComponent(const UpdateComponent& other) = delete;
		UpdateComponent(UpdateComponent&& other) = delete;
		UpdateComponent& operator=(const UpdateComponent& other) = delete;
		UpdateComponent& operator=(UpdateComponent&& other) = delete;

		virtual void Update() override = 0;
		virtual void Render() const override {}; // empty body, update components shouldn't render themselves

	protected:

	private:

	};
}



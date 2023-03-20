#pragma once
#include "UpdateComponent.h"
namespace dae
{
	class TrashTheCache_GameObjComponent : public UpdateComponent
	{
	public:
		TrashTheCache_GameObjComponent(std::weak_ptr<GameObject> pOwner);
		virtual ~TrashTheCache_GameObjComponent() = default;
		TrashTheCache_GameObjComponent(const TrashTheCache_GameObjComponent& other) = delete;
		TrashTheCache_GameObjComponent(TrashTheCache_GameObjComponent&& other) = delete;
		TrashTheCache_GameObjComponent& operator=(const TrashTheCache_GameObjComponent& other) = delete;
		TrashTheCache_GameObjComponent& operator=(TrashTheCache_GameObjComponent&& other) = delete;

		virtual void Update() override {};
		virtual void DisplayGui() override;

	protected:

	private:
	};
}



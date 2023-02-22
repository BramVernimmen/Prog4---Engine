#pragma once
#include "BaseComponent.h"
namespace dae
{

    class TextureComponent final : public BaseComponent
    {
    public:
		virtual void Update() override;
		virtual void Render() const override;

		TextureComponent(std::shared_ptr<GameObject>& pParent);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
    private:
		
    };

}

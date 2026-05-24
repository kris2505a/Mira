#pragma once
#include "Mira/Renderer/RHI/Texture.hpp"
#include <string>

#include <d3d11.h>
#include <wrl/client.h>

namespace Mira {

class D3D11Texture : public Texture {
public:
    D3D11Texture(const std::string& path);
    D3D11Texture(uint32_t pixel);
    ~D3D11Texture() override = default;
    void bind(int slot = 0) const final override;

private:
    std::string m_path;
    Microsoft::WRL::ComPtr <ID3D11Texture2D> m_texture = nullptr;
    Microsoft::WRL::ComPtr <ID3D11ShaderResourceView> m_resourceView = nullptr;
};

}
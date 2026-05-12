#include "MiraPch.h"
#include "D3D11Texture.h"
#include "D3DError.h"
#include "Mira/Renderer/RHI/stb_image.h"
#include "D3D11Resource.h"

namespace Mira {

D3D11Texture::D3D11Texture(const std::string& path) {
    m_path		= path;


    int width, height, bpp;
    unsigned char* imgData = stbi_load(m_path.c_str(), &width, &height, &bpp, STBI_rgb_alpha);

    if (!imgData) {
        std::cerr << stbi_failure_reason() << std::endl;
        throw std::runtime_error(stbi_failure_reason());
    }

    D3D11_TEXTURE2D_DESC td = {};
    td.Width				= width;
    td.Height				= height;
    td.MipLevels			= 1;
    td.ArraySize			= 1;
    td.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
    td.SampleDesc.Count		= 1;
    td.Usage				= D3D11_USAGE_IMMUTABLE;
    td.BindFlags			= D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA srd{};
    srd.pSysMem = imgData;
    srd.SysMemPitch = width * 4;

    HRUN(D3D11Resource::getDevice()->CreateTexture2D(&td, &srd, m_texture.GetAddressOf()));
    HRUN(D3D11Resource::getDevice()->CreateShaderResourceView(
        m_texture.Get(),
        nullptr,
        m_resourceView.GetAddressOf()
    ));
    if (imgData) {
        stbi_image_free(imgData);
    }
}

void D3D11Texture::bind(int slot) const {
    RUN(D3D11Resource::getContext()->PSSetShaderResources(slot, 1, m_resourceView.GetAddressOf()), D3D11Resource::getDevice());
}

}
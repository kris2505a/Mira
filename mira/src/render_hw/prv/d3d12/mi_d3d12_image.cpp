#include "mi_d3d12_image.hpp"

namespace mira::rhw {

D3D12Image::D3D12Image(core::ComScope<ID3D12Resource> imgResource)
    : mImage(std::move(imgResource)) {
}


ID3D12Resource* D3D12Image::getImage() const {
    return mImage.Get();
}

}
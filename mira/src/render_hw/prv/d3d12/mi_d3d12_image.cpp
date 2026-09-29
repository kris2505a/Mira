#include "mi_d3d12_image.hpp"

namespace mira::rhw {

D12Image::D12Image(core::ComScope<ID3D12Resource> imgResource)
    : mImage(std::move(imgResource)) {}

}
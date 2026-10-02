#pragma once
#include "pub/mi_image.hpp"

#include <helpers/mi_win_hpr.hpp>
#include <helpers/mi_types.hpp>
#include <d3d12.h>

namespace mira::rhw {

class D3D12Image : public Image {
public:
    D3D12Image(core::ComScope<ID3D12Resource> imgResource);
    ~D3D12Image() override = default;

    ID3D12Resource* getImage() const;

private:
    core::ComScope<ID3D12Resource> mImage;
};

}
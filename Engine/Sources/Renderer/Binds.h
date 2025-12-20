#pragma once
#include <d3d11.h>
#include <wrl/client.h>

namespace Mira {

namespace wrl = Microsoft::WRL;

class Binds {
public:
	Binds()				 = default;
	~Binds()			 = default;
	virtual void		 bind() const = 0;
	ID3D11Device*		 device() const;
	ID3D11DeviceContext* context() const;

};

}
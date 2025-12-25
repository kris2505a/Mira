#include <PreCompHeader.hpp>
#include "Shader.hpp"
#include "Error.hpp"

namespace Mira {

Shader::Shader(const std::wstring& vsPath, const std::wstring& psPath) {
	HRUN(D3DReadFileToBlob(vsPath.c_str(), m_shaderBlobs.vsBlob.GetAddressOf()));
	HRUN(D3DReadFileToBlob(psPath.c_str(), m_shaderBlobs.psBlob.GetAddressOf()));

	HRUN(device()->CreateVertexShader(
		m_shaderBlobs.vsBlob->GetBufferPointer(),
		m_shaderBlobs.vsBlob->GetBufferSize(),
		nullptr,
		m_vertexShader.GetAddressOf()
	));
	HRUN(device()->CreatePixelShader(
		m_shaderBlobs.psBlob->GetBufferPointer(),
		m_shaderBlobs.psBlob->GetBufferSize(),
		nullptr,
		m_pixelShader.GetAddressOf()
	));

}

void Shader::bind() const {
	RUN(context()->VSSetShader(m_vertexShader.Get(), nullptr, 0), device());
	RUN(context()->PSSetShader(m_pixelShader.Get(), nullptr, 0), device());
	

}

const Blobs* Shader::blobs() const {
	return &m_shaderBlobs;
}



}
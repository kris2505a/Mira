#pragma once
#include "Mira/Core/Core.hpp"
#include "Layer.hpp"
#include "Mira/Input/InputCodes.hpp"

namespace Mira {

class MIRA_API ImGuiLayer : public Layer {
public:
	ImGuiLayer();
	~ImGuiLayer() override = default;

	void attach() override;
	void detach() override;
	void update() override;
	void render() override;
	void handleEvent(Event& e) override;

private:
	static int toImGuiKey(Key key);
	static int toImGuiMouseButton(Button button);
    void printLogs();
	bool wireFrame;

};

}
#include <PreCompHeader.h>
#include "WindowAttributes.h" 
#include <nlohmann/json.hpp>

WindowAttributes::WindowAttributes()
	: width(0), height(0), vSync(false), maximized(false) {

}

void WindowAttributes::init() {
	std::ifstream config("Configs/WinConfig.json");
	assert(config.is_open());

	nlohmann::json j;
	config >> j;

	width = j["Window"].value("width", 1280);
	height = j["Window"].value("height", 720);
	vSync = j["Window"].value("vSync", false);
	maximized = j["Window"].value("maximized", false);
	config.close();
}

void WindowAttributes::shutdown() {
	nlohmann::json j;
	j["Window"]["width"] = width;
	j["Window"]["height"] = height;
	j["Window"]["vSync"] = vSync;
	j["Window"]["maximized"] = maximized;

	std::ofstream config("Configs/WinConfig.json");
	config << j.dump(2);
	config.close();
}

WindowAttributes::~WindowAttributes() {
	
}
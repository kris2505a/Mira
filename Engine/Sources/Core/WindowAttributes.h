#pragma once

class WindowAttributes {
public:
	WindowAttributes();
	~WindowAttributes();
	void init();
	void shutdown();

	int  width;
	int  height;
	bool vSync;
	bool maximized;
};
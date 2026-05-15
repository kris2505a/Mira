#pragma once
#include <vector>
#include <string>

namespace Mira {

enum class LayoutDataType {
    Float,
    UnsignedInt
};

struct Layout {
    std::string semanticName;
    LayoutDataType type;
    unsigned int count;
};

class InputLayout {
public:
    InputLayout() = default;
    ~InputLayout() = default;

    inline void addLayout(Layout layout) {
        m_layouts.push_back(layout);
    }

    inline const std::vector<Layout>& getLayouts() const {
        return m_layouts;
    }

private:
    std::vector <Layout> m_layouts;

};

}
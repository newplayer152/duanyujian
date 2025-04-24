#include "configure.h"

ExportConfigure* getClassObj()
{
	return new Configure();
}

Configure::Configure(const std::vector<std::string>& items) : m_vItems(items) {};

int Configure::addItem(std::string str)
{
	auto findIndex = std::find(m_vItems.begin(), m_vItems.end(), str);
	if (findIndex != m_vItems.end()) {
		return findIndex - m_vItems.begin();
	}
	m_vItems.push_back(str);
	return m_vItems.size() - 1;
}

std::string Configure::getItem(int index)
{
	if (m_vItems.empty()||index>= m_vItems.size()|| index<0) {
		return "";
	}
	return m_vItems[index];
}

int Configure::getSize() const
{
	return m_vItems.size();
}

// 释放由 getClassObj 创建的实例
void releaseClassObj(ExportConfigure* obj) {
    delete obj;
}


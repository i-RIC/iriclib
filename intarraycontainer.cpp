#include "intarraycontainer.h"

IntArrayContainer::IntArrayContainer(int size) :
	m_value {new std::vector<int> {}}
{
	m_value->assign(size, 0);
}

IntArrayContainer::~IntArrayContainer()
{
	delete m_value;
}

int IntArrayContainer::size() const
{
	return static_cast<int> (m_value->size());
}

int IntArrayContainer::value(int index) const
{
	if (index < 0) {
		return 0;
	}
	if (index >= static_cast<int>(m_value->size())) {
		return 0;
	}
	return m_value->at(index);
}

void IntArrayContainer::setValue(int index, int v)
{
	if (index < 0) {
		return;
	}
	if (index >= static_cast<int>(m_value->size())) {
		return;
	}
	(*m_value)[index] = v;
}

int* IntArrayContainer::pointer()
{
	return m_value->data();
}

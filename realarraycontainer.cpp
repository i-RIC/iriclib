#include "realarraycontainer.h"

RealArrayContainer::RealArrayContainer(int size) :
	m_value {new std::vector<double> {}}
{
	m_value->assign(size, 0);
}

RealArrayContainer::~RealArrayContainer()
{
	delete m_value;
}

int RealArrayContainer::size() const
{
	return static_cast<int> (m_value->size());
}

double RealArrayContainer::value(int index) const
{
	if (index < 0) {
		return 0;
	}
	if (index >= static_cast<int> (m_value->size())) {
		return 0;
	}
	return m_value->at(index);
}

void RealArrayContainer::setValue(int index, double v)
{
	if (index < 0) {
		return;
	}
	if (index >= static_cast<int> (m_value->size())) {
		return;
	}
	(*m_value)[index] = v;
}

double* RealArrayContainer::pointer()
{
	return m_value->data();
}

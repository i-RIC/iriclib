#include <fstream>
#include "iriclib_polyline.h"
#include "iriclib_bstream.h"

using namespace std;
using namespace iRICLib;

InternalPolyline::InternalPolyline()
{
	x = nullptr;
	y = nullptr;
	pointCount = 0;
}

InternalPolyline::~InternalPolyline()
{
	delete x;
	delete y;
}

InputBStream& operator >> (InputBStream& stream, InternalPolyline& pol)
{
	stream >> pol.pointCount;
	pol.x = new double[pol.pointCount];
	pol.y = new double[pol.pointCount];

	for (int i = 0; i < pol.pointCount; ++i){
		stream >> *(pol.x + i);
	}
	for (int i = 0; i < pol.pointCount; ++i){
		stream >> *(pol.y + i);
	}
	return stream;
}

OutputBStream& operator << (OutputBStream& stream, const InternalPolyline& pol)
{
	stream << pol.pointCount;
	for (int i = 0; i < pol.pointCount; ++i){
		stream << *(pol.x + i);
	}
	for (int i = 0; i < pol.pointCount; ++i){
		stream << *(pol.y + i);
	}
	return stream;
}


Polyline::Polyline()
{
	polyline = nullptr;
}

Polyline::~Polyline()
{
	clear();
}

int Polyline::load(const char* filename, bool noDimensions)
{
	ifstream istream(filename, ios::in | ios::binary);
	if (! istream){
		// open error
		return -1;
	}
	clear();

	InputBStream str(istream);
	values.clear();
	double val;
	if (noDimensions){
		str >> val;
		values.push_back(val);
	} else {
		int count;
		str >> count;
		for (int i = 0; i < count; ++i){
			str >> val;
			values.push_back(val);
		}
	}
	polyline = new iRICLib::InternalPolyline();
	str >> *polyline;

	istream.close();
	return 0;
}

int Polyline::save(const char *filename, bool noDimensions)
{
	ofstream ostream(filename, ios::out | ios::binary);
	if (! ostream){
		// open error
		return -1;
	}
	OutputBStream str(ostream);
	if (noDimensions){
		str << values[0];
	} else {
		int count = static_cast<int>(values.size());
		str << count;
		for (int i = 0; i < count; ++i){
			str << values[i];
		}
	}
	str << *polyline;
	ostream.close();
	return 0;
}

void Polyline::clear()
{
	delete polyline;
	polyline = nullptr;
}

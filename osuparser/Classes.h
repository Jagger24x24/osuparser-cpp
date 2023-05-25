#include "Structs.h"
#include <vector>

enum class ObjectType : int
{
	HitCircle = 1,
	Slider = 2,
	HitCircleNC = 5,
	SliderNC = 6,
	Spinner = 12
	
};

enum class CurveType : char
{
	Bezier = 'B',
	Centripetal_Catmull_Rom = 'C', // who came up with this name
	Linear = 'L',
	PerfectCircle = 'P'

};

class Object	
{
public:
	struct Vector Position;
	int Time;
	ObjectType ObjectType; // not sure about this
	int HitSound;
	HitSample HitSample;

};

class HitCirlce : public Object 
{
public:
	std::string to_string() {
		std::string c = ",";
		auto ObjectType = static_cast<int>(this->ObjectType);
		return this->Position.to_string() + c + std::to_string(this->Time) + c + std::to_string(ObjectType) + c + std::to_string(this->HitSound) + c + this->HitSample.to_string();
	}
// wow so much stuff
};

class Slider : public Object 
{
public:
	CurveType curveType;
	std::vector<Vector> curvePoint;
	int slides;
	float length;
	std::vector<int> edgeSounds;
	std::vector<int> edgeSets;

};

class Spinner : public Object 
{
public:
	int endTime;
};
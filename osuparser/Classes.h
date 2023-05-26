#include "Structs.h"

class HitObject
{
public:
	struct Vector Position;
	int Time;
	ObjectType ObjectType; // not sure about this
	int HitSound;
	HitSample HitSample;

};

class HitCirlce : public HitObject
{
public:
	std::string to_string() {
		std::string c = ",";
		auto ObjectType = static_cast<int>(this->ObjectType);
		return this->Position.to_string() + c + std::to_string(this->Time) + c + std::to_string(ObjectType) + c + std::to_string(this->HitSound) + c + this->HitSample.to_string();
	}
// wow so much stuff
};

class Slider : public HitObject
{
public:
	CurveType curveType;
	std::vector<Vector> curvePoint;
	int slides;
	float length;
	std::vector<int> edgeSounds;
	std::vector<int> edgeSets;
};

class Spinner : public HitObject
{
public:
	int endTime;
};

class TimingPoint {
public:
	int Time;
	float beatLength;
	int meter;
	int sampleSet;
	int sampleIndex;
	int volume;
	IntBool uninherited;
	int effects;

	float GetSV() {
		if (this->uninherited == IntBool::True) {
			return 1.0;
		}
		else {
			return (-1 / this->beatLength) * 100;
		}
	}
};

class OsuMap {
public:
	int Version;
	struct General General;
	struct Metadata Metadata;
	// std::vector<TimingPoint> TimingPoints;
	std::vector<HitObject> HitObjects;
};
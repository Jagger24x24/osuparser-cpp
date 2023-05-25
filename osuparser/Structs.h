#include <iostream>
#include <string>

struct Vector3D {
	float X;
	float Y;
	float Z;

	std::string to_string() {
		return std::to_string(this->X) + "," + std::to_string(this->Y) + "," + std::to_string(this->Z);
	}
};

struct Rotator3D {
	float W;
	float P;
	float R;

	std::string to_string() {
		return std::to_string(this->W) + "," + std::to_string(this->P) + "," + std::to_string(this->R);
	}
};

struct Vector {
	int X;
	int Y;

	std::string to_string() {
		return std::to_string(this->X) + "," + std::to_string(this->Y);
	}
};

struct HitSample {
	int normalSet;
	int additionSet;
	int index;
	int volume;
	std::string filename;
};
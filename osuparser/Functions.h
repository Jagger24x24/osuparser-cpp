#include "Classes.h"
#include <fstream>
#include <string>

void stripPrefix(std::string& str, const std::string& prefix) {
	if (str.substr(0, prefix.size()) == prefix) {
		str.erase(0, prefix.size());
	}
}

namespace OsuFunctions {
	float SliderTimeMS(Slider Slider, Difficulty Difficulty, TimingPoint TimingPoint) {
		return Slider.length / (Difficulty.SliderMultiplier * 100 * TimingPoint.GetSV()) * TimingPoint.beatLength;
	}

	TimingPoint GetTPForObject(HitObject Object, std::vector<TimingPoint> TimingPoints) {
		int i = 0;
		TimingPoint TP;

		while (i >= TimingPoints.size()) {
			if (Object.Time > TimingPoints[i].Time && Object.Time < TimingPoints[i + 1].Time)
			{
				TimingPoint TP = TimingPoints[i];
			}
		}

		return TP;
	}

	Vector ConvertObjectPosToScreenPos(Vector Resolution, HitObject Object) { // i hate geometry
		Vector PlayfieldSize = { 512, 384 };
		Vector OsuResolution = { std::round(Resolution.X * 0.4541666666666667), std::round(Resolution.Y * 0.4537037037037037) };
		int GapY = (OsuResolution.Y - PlayfieldSize.Y) * 0.5; // pov arm computer
		Vector Offset = { (OsuResolution.X - PlayfieldSize.X) * 0.5, std::round(GapY * 0.7735849056603774) };
		Vector OsuPos = OsuResolution + Offset;
		int ReturnX = std::round(OsuPos.X * 2.201834862385321); // something like that
		int ReturnY = std::round(OsuPos.Y * 2.204081632653061);
		return Vector { ReturnX, ReturnY };
	}

	General GetGeneral(std::vector<std::string> lines) {
		General general;
		int i = 0;
		while (i < lines.size()) {
			std::string line = lines[i];
			if (line.contains("AudioFilename: ")) {
				stripPrefix(line, "AudioFilename: ");
				general.AudioFilename = line;
			}
			if (line.contains("AudioLeadIn: ")) {
				stripPrefix(line, "AudioLeadIn: ");
				general.AudioLeadIn = std::stoi(line);
			}
			i++;
		}
		return general;
	}

	Metadata GetMetadata(std::vector<std::string> lines) {

	}

	OsuMap ReadFile(std::string filepath) {
		OsuMap map;
		std::ifstream file(filepath);
		std::string line;
		std::vector<std::string> lines;
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		map.General = GetGeneral(lines);
		map.Metadata.Creator = "jagger";
		return map;
	}
}
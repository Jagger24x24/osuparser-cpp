#include "Classes.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

void stripPrefix(std::string& str, const std::string& prefix) {
	if (str.substr(0, prefix.size()) == prefix) {
		str.erase(0, prefix.size());
	}
}

std::vector<std::string> split(std::string input, char split) {
	std::vector<std::string> elements;

	std::stringstream ss(input);
	std::string item;

	while (std::getline(ss, item, split)) {
		elements.push_back(item);
	}

	return elements;
}

namespace OsuFunctions {
	float GetSliderTimeMS(Slider Slider, Difficulty Difficulty, TimingPoint TimingPoint) {
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

	std::vector<Vector> getSliderPoints(const std::string& value) { // i feel very attacked
		size_t pos = value.find('|');

		std::string substring = value.substr(pos + 1);

		std::vector<std::string> slider_pointsstr;
		std::vector<Vector> slider_points;
		size_t start = 0;
		while (start < substring.length()) {
			size_t end = substring.find('|', start); // chat gpt saved me
			if (end == std::string::npos) {
				end = substring.length();
			}
			std::string point = substring.substr(start, end - start);
			slider_pointsstr.push_back(point);
			auto points = split(point, ':');
			slider_points.push_back({ std::stoi(points[0]), std::stoi(points[1]) }); // what the skunky bozo is this chatgpt skidded slow ass code
			start = end + 1;
		}


		return slider_points;
	}

	HitSample StringToHitSample(std::string hitsample) {
		HitSample HitS;
		auto HitSampleSTR = split(hitsample, ':'); // funny hitsamples
		HitS.normalSet = std::stoi(HitSampleSTR[0]);
		HitS.additionSet = std::stoi(HitSampleSTR[1]);
		HitS.index = std::stoi(HitSampleSTR[2]);
		HitS.volume = std::stoi(HitSampleSTR[3]);
		HitS.filename = HitSampleSTR[4];
		return HitS;
	}

	Vector ConvertObjectPosToScreenPos(Vector Resolution, HitObject Object) { // i hate geometry
		Vector PlayfieldSize = { 512, 384 };

		Vector OsuResolution = { std::round(Resolution.X * 0.4541666666666667), std::round(Resolution.Y * 0.4537037037037037) }; // warning but it's fine
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
		while (i <= (lines.size() -1)) {
			std::string line = lines[i];
			if (line.find("AudioFilename: ")) {
				stripPrefix(line, "AudioFilename: ");
				general.AudioFilename = line;
			}
			else if (line.find("AudioLeadIn: ")) {
				stripPrefix(line, "AudioLeadIn: ");
				general.AudioLeadIn = std::stoi(line);
			}
			else if (line.find("AudioHash: ")) {
				stripPrefix(line, "AudioHash: ");
				general.AudioHash = line;
			}
			else if (line.find("PreviewTime: ")) {
				stripPrefix(line, "PreviewTime: ");
				general.PreviewTime = std::stoi(line);
			}
			else if (line.find("Countdown: ")) {
				stripPrefix(line, "Countdown: ");
				general.cd = static_cast<Countdown>(std::stoi(line));
			}
			else if (line.find("SampleSet: ")){
				stripPrefix(line, "SampleSet: ");
				general.SampleSet = line;
			}
			else if (line.find("StackLeniency: ")) {
				stripPrefix(line, "StackLeniency: ");
				general.StackLeniency = std::stof(line);
			}
			else if (line.find("Mode: ")) {
				stripPrefix(line, "Mode: ");
				general.Mode = static_cast<GameMode>(std::stoi(line));
			}
			else if (line.find("LetterboxInBreaks: ")) {
				stripPrefix(line, "LetterboxInBreaks: ");
				general.LetterboxInBreaks = static_cast<IntBool>(std::stoi(line));
			}
			else if (line.find("UseSkinSprites: ")) {
				stripPrefix(line, "UseSkinSprites: ");
				general.UseSkinSprites = static_cast<IntBool>(std::stoi(line));
			}
			else if (line.find("OverlayPosition: ")) {
				stripPrefix(line, "OverlayPosition: ");
				general.OverlayPosition = line;
			}
			else if (line.find("SkinPreference: ")) {
				stripPrefix(line, "SkinPreference: ");
				general.SkinPreference = line;
			}
			else if (line.find("EpilepsyWarning: ")) {
				stripPrefix(line, "EpilepsyWarning: ");
				general.EpilepsyWarning = static_cast<IntBool>(std::stoi(line));
			}
			else if (line.find("CountdownOffset: ")) {
				stripPrefix(line, "CountdownOffset: ");
				general.CountdownOffset = std::stoi(line);
			}
			else if (line.find("SpecialStyle: ")) {
				stripPrefix(line, "SpecialStyle: ");
				general.SpecialStyle = static_cast<IntBool>(std::stoi(line));
			}
			else if (line.find("WidescreenStoryboard: ")) {
				stripPrefix(line, "WidescreenStoryboard: ");
				general.WidescreenStoryboard = static_cast<IntBool>(std::stoi(line));
			}
			else if (line.find("SamplesMatchPlaybackRate: ")) {
				stripPrefix(line, "SamplesMatchPlaybackRate: ");
				general.SamplesMatchPlaybackRate = static_cast<IntBool>(std::stoi(line));
			}
			i++;
		}
		std::cout << "????\n";
		return general;
	}

	Difficulty GetDifficulty(std::vector<std::string> lines) {
		Difficulty difficulty;
		int i = 0;
		while (i <= (lines.size() - 1)) {
			std::string line = lines[i];
			if (line.find("HPDrainRate:")) {
				stripPrefix(line, "HPDrainRate:");
				difficulty.HPDrainRate = std::stoi(line);
			}
			else if (line.find("CircleSize:")) {
				stripPrefix(line, "CircleSize:");
				difficulty.CircleSize = std::stoi(line);
			}
			else if (line.find("OverallDifficulty:")) {
				stripPrefix(line, "OverallDifficulty:");
				difficulty.OverallDifficulty = std::stoi(line);
			}
			else if (line.find("ApproachRate:")) {
				stripPrefix(line, "ApproachRate:");
				difficulty.ApproachRate = std::stoi(line);
			}
			else if (line.find("SliderMultiplier:")) {
				stripPrefix(line, "SliderMultiplier:");
				difficulty.SliderMultiplier = std::stof(line);
			}
			else if (line.find("SliderTickRate:")) {
				stripPrefix(line, "SliderTickRate:");
				difficulty.SliderTickRate = std::stoi(line);
			}
			i++;
		}
		return difficulty;
	}

	std::vector<TimingPoint> GetTimingPoints(std::vector<std::string> lines) {
		std::vector<TimingPoint> TimingPoints;
		int i = 0;
		bool InTimingPoints = false;
		while (i <= (lines.size() - 1)) {
			std::string line = lines[i];
			if (line == "[TimingPoints]") {
				InTimingPoints = true;
			}

			if (InTimingPoints) {
				auto TPStrs = split(line, ',');
				TimingPoint TP;
				TP.Time = std::stoi(TPStrs[0]);
				TP.beatLength = std::stof(TPStrs[1]);
				TP.meter = std::stoi(TPStrs[2]);
				TP.sampleSet = std::stoi(TPStrs[3]);
				TP.sampleIndex = std::stoi(TPStrs[4]);
				TP.volume = std::stoi(TPStrs[5]);
				TP.uninherited = static_cast<IntBool>(std::stoi(TPStrs[6]));
				TP.effects = std::stoi(TPStrs[7]);
				TimingPoints.push_back(TP);
			}

			i++;
			if (line == "") {
				InTimingPoints = false;
			}
		}
		return TimingPoints;
	}

	std::vector<HitObject> GetHitObjects(std::vector<std::string> lines) {
		std::vector<HitObject> HitObjects;
		int i = 0;
		bool InHitObjects = false;
		std::cout << i << " ? " << lines.size() << std::endl;
		while (i <= (lines.size() - 1)) {
			std::string line = lines[i];
			std::cout << line << "\n";
			if (line == "[HitObjects]") {
				std::cout << "in hos\n";
				InHitObjects = true;
			}

			if (InHitObjects) {
				auto HOStrs = split(line, ',');
				auto type = static_cast<ObjectType>(std::stoi(HOStrs[3]));
				if (type == ObjectType::HitCircle || type == ObjectType::HitCircleNC) {
					HitObject HO;
				}
				else if (type == ObjectType::Slider || type == ObjectType::HitCircleNC) {
					Slider SO;
					SO.Position = { std::stoi(HOStrs[0]), std::stoi(HOStrs[1]) };
					SO.Time = std::stoi(HOStrs[2]);
					SO.HitSound = std::stoi(HOStrs[4]);

					size_t pos = HOStrs[5].find('|');
					std::string substring = HOStrs[5].substr(0, pos); // i feel attacked
					SO.curveType = static_cast<CurveType>(substring[0]);

					SO.curvePoints = getSliderPoints(HOStrs[5]);
					SO.slides = std::stoi(HOStrs[6]);
					SO.length = std::stoi(HOStrs[7]);
					auto edgeSounds = split(HOStrs[8], ':');
					i = 0;
					while (i <= edgeSounds.size()) SO.edgeSounds.push_back(std::stoi(edgeSounds[i]));

					auto edgeSets = split(HOStrs[8], ':');
					i = 0;
					while (i <= edgeSets.size()) SO.edgeSets.push_back(std::stoi(edgeSets[i]));

					SO.HitSample = StringToHitSample(HOStrs[9]);

				}
				else if (type == ObjectType::Spinner) {
					Spinner SO;
					SO.Position = { std::stoi(HOStrs[0]), std::stoi(HOStrs[1]) };
					SO.Time = std::stoi(HOStrs[2]);
					SO.HitSound = std::stoi(HOStrs[4]);
					SO.endTime = std::stoi(HOStrs[5]);
					SO.HitSample = StringToHitSample(HOStrs[6]);
					
				}
			}
			std::cout << line << std::endl;
			i++;
			if (line == "") {
				std::cout << "out hos\n";
				InHitObjects = false;
			}
		}
		return HitObjects;
	}

	Metadata GetMetadata(std::vector<std::string> lines) {
		Metadata metadata;
		int i = 0;
		while (i <= (lines.size() - 1)) {
			std::string line = lines[i];
			if (line.find("Title:")) {
				stripPrefix(line, "Title:");
				metadata.Title = line;
			}
			else if (line.find("TitleUnicode:")) {
				stripPrefix(line, "TitleUnicode:");
				metadata.TitleUnicode = line;
			}
			else if (line.find("Artist:")) {
				stripPrefix(line, "Artist:");
				metadata.Artist = line;
			}
			else if (line.find("ArtistUnicode:")) {
				stripPrefix(line, "ArtistUnicode:");
				metadata.ArtistUnicode = line;
			}
			else if (line.find("Creator:")) {
				stripPrefix(line, "Creator:");
				metadata.Creator = line;
			}
			else if (line.find("Version:")) {
				stripPrefix(line, "Version:");
				metadata.Version = line;
			}
			else if (line.find("Source:")) {
				stripPrefix(line, "Source:");
				metadata.Source = line;
			}
			else if (line.find("Tags:")) {
				stripPrefix(line, "Tags:");
				metadata.Tags = split(line, ' ');
			}
			else if (line.find("BeatmapID:")) {
				stripPrefix(line, "BeatmapID:");
				metadata.BeatmapID = std::stoi(line);
			}
			else if (line.find("BeatmapSetID:")) {
				stripPrefix(line, "BeatmapSetID:");
				metadata.BeatmapSetID = std::stoi(line);
			}
			i++;
		}
		return metadata;
	}

	OsuMap ReadFile(std::string filepath) {
		std::cout << "Hello world" << std::endl;
		OsuMap map;
		std::ifstream file(filepath);
		std::string line;
		std::vector<std::string> lines;
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		std::cout << lines.size() << std::endl;
		map.General = GetGeneral(lines);
		map.Metadata = GetMetadata(lines); // there is probably a better way to do all of this
		map.Difficulty = GetDifficulty(lines);
		map.TimingPoints = GetTimingPoints(lines);
		map.HitObjects = GetHitObjects(lines);
		std::cout << "????" << std::endl;

		return map;
	}
}
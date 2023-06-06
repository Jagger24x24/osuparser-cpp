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
		while (i < lines.size()) {
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
		return general;
	}

	Difficulty GetDifficulty(std::vector<std::string> lines) {
		Difficulty difficulty;
		int i = 0;
		while (i < lines.size()) {
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
		bool InTimingPoints;
		while (i < lines.size()) {
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
				TP.sampleIndex = std::stoi(TPStrs[4]); // im not sure about this because some timing points end with something like 0:0:0:0
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
		bool InHitObjects;
		while (i < lines.size()) {
			std::string line = lines[i];
			if (line == "[HitObjects]") {
				InHitObjects = true;
			}

			if (InHitObjects) {
				auto HOStrs = split(line, ',');
				HitObject HO; // i will skid my python

				HitObjects.push_back(HO);
			}

			i++;
			if (line == "") {
				InHitObjects = false;
			}
		}
		return HitObjects;
	}

	Metadata GetMetadata(std::vector<std::string> lines) {
		Metadata metadata;
		int i = 0;
		while (i < lines.size()) {
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
		OsuMap map;
		std::ifstream file(filepath);
		std::string line;
		std::vector<std::string> lines;
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
		map.General = GetGeneral(lines);
		map.Metadata = GetMetadata(lines); // there is probably a better way to do this
		map.Difficulty = GetDifficulty(lines);
		map.TimingPoints = GetTimingPoints(lines);
		map.HitObjects = GetHitObjects(lines);

		return map;
	}
}
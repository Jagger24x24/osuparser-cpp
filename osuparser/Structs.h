#include <iostream>
#include <string>
#include <vector>
#include <cmath>

enum class IntBool : int
{
	False = 0,
	True = 1
};

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

enum class Countdown : int //  (0 = no countdown, 1 = normal, 2 = half, 3 = double)
{ 
	None = 0,
	Normal = 1,
	Half = 2,
	Double = 3
};

enum class GameMode : int // (0 = osu!, 1 = osu!taiko, 2 = osu!catch, 3 = osu!mania)
{
	Standard = 0,
	Taiko = 1,
	CTB = 2,
	Mania = 3
};

struct Vector {
	int X;
	int Y;

	std::string to_string() {
		return std::to_string(this->X) + "," + std::to_string(this->Y);
	}

	Vector operator+(const Vector& vect) const 
	{
		return Vector { this->X + vect.X, this->Y + vect.Y };
	}

	Vector operator-(const Vector& vect) const
	{
		return Vector{ this->X - vect.X, this->Y - vect.Y };
	}

	Vector operator*(const Vector& vect) const
	{
		return Vector{ this->X * vect.X, this->Y * vect.Y };
	}

	Vector operator/(const Vector& vect) const
	{
		return Vector{ this->X / vect.X, this->Y / vect.Y };
	}
};

struct HitSample {
	int normalSet;
	int additionSet;
	int index;
	int volume;
	std::string filename;

	std::string to_string() {
		std::string c = ":";
		return std::to_string(this->normalSet) + c + std::to_string(this->additionSet) + c + std::to_string(this->index) + c + std::to_string(this->volume) + c + filename;
	}
};

struct Difficulty {
	float HPDrainRate;
	float CircleSize;
	float OverallDifficulty;
	float ApproachRate;
	float SliderMultiplier;
	float SliderTickRate;
};

struct General {
	std::string AudioFilename; // Location of the audio file relative to the current folder
	int AudioLeadIn; // Milliseconds of silence before the audio starts playing
	std::string AudioHash; // Deprecated
	int PreviewTime; // Time in milliseconds when the audio preview should start
	Countdown Countdown; // Speed of the countdown before the first hit object.
	std::string SampleSet; // Sample set that will be used if timing points do not override it (Normal, Soft, Drum)
	float StackLeniency; // Multiplier for the threshold in time where hit objects placed close together stack (0–1)
	GameMode Mode; // Game mode.
	IntBool LetterboxInBreaks; // Whether or not breaks have a letterboxing effect (0 or 1)
	int StoryFireInFront; // Deprecated
	IntBool UseSkinSprites; // Whether or not the storyboard can use the user's skin images (0 or 1)
	int AlwaysShowPlayfield; // Deprecated
	std::string OverlayPosition; // Draw order of hit circle overlays compared to hit numbers (NoChange = use skin setting, Below = draw overlays under numbers, Above = draw overlays on top of numbers)
	std::string SkinPreference; // Preferred skin to use during gameplay
	IntBool EpilepsyWarning; // Whether or not a warning about flashing colours should be shown at the beginning of the map (0 or 1)
	int CountdownOffset; // Time in beats that the countdown starts before the first hit object
	IntBool SpecialStyle; // Whether or not the "N+1" style key layout is used for osu!mania (0 or 1)
	IntBool WidescreenStoryboard; // Whether or not the storyboard allows widescreen viewing (0 or 1)
	IntBool SamplesMatchPlaybackRate; // Whether or not sound samples will change rate when playing with speed-changing mods (0 or 1)
};

struct Metadata {
	std::string Title; // Romanised song title
	std::string TitleUnicode; // Song title
	std::string Artist; // Romanised song artist
	std::string ArtistUnicode; // Song artist
	std::string Creator; // Beatmap creator
	std::string Version; // Difficulty name
	std::string Source; // Original media the song was produced for
	std::vector<std::string> Tags; // Space-separated list of strings, search terms
	int BeatmapID; // Difficulty ID
	int BeatmapSetID; // Beatmap ID
};
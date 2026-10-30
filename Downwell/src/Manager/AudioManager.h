#pragma once
#include <unordered_map>
#include <string>

class AudioManager
{
private:
	static constexpr int MAX_VOLUME = 255;

	std::unordered_map<std::string, int> m_BGMs;
	std::unordered_map<std::string, int> m_SEs;

	int m_CurrentBGM = 0;

	int m_VolumeMaster = MAX_VOLUME;	// 0 - 255
	int m_VolumeBGM = 100;				// 0 - 255
	int m_VolumeSE = 110;				// 0 - 255

private:
	AudioManager() {}
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	bool LoadBGM(std::string name, std::string fileName);
	bool LoadSE(std::string name, std::string fileName);

public:
	static AudioManager& GetInstance()
	{
		static AudioManager audioManager;
		return audioManager;
	}

	void Initialize();
	void Finalize();

	bool PlayBGM(const std::string& name);
	bool PlaySE(const std::string& name);

	bool StopBGM(const std::string& name);

	void SetVolumeMaster(int volume);	// 0 - 255
	void SetVolumeBGM(int volume);		// 0 - 255
	void SetVolumeSE(int volume);		// 0 - 255

	void ApplyVolumeBGM();
	void ApplyVolumeSE();

};
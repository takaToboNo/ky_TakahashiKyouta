#include "AudioManager.h"
#include "DxLib.h"
#include "MathHelper.h"

bool AudioManager::LoadBGM(std::string name, std::string fileName)
{
	std::string filePath = "Data/Sound/" + fileName;
	m_BGMs[name] = LoadSoundMem(filePath.c_str());

	return (m_BGMs[name] != -1) ? true : false;
}

bool AudioManager::LoadSE(std::string name, std::string fileName)
{
	std::string filePath = "Data/Sound/" + fileName;
	m_SEs[name] = LoadSoundMem(filePath.c_str());

	return (m_SEs[name] != -1) ? true : false;
}

void AudioManager::Initialize()
{
	LoadBGM("Game", "未定.mp3");


	//プレイヤー
	LoadSE("Jump", "未定.mp3");
	LoadSE("Shot", "未定.mp3");
	LoadSE("ShotEmpty", "未定.mp3");
	LoadSE("Reload", "未定.mp3");
	LoadSE("Land", "未定.mp3");
	LoadSE("Damage", "未定.mp3");
	LoadSE("Stomp", "未定.mp3");//敵踏みつけ
	LoadSE("Dead", "未定.mp3");
	//ブロック
	LoadSE("BlockHit", "未定.mp3");
	LoadSE("BlockBreak", "未定.mp3");
	//エネミー
	LoadSE("EnemyHit", "未定.mp3");
	LoadSE("EnemyDead", "未定.mp3");
	//操作
	LoadSE("Decide", "未定.mp3");
}

void AudioManager::Finalize()
{
	for (const std::pair<const std::string, int>& pair : m_BGMs)
	{
		DeleteSoundMem(pair.second);
	}
	for (const std::pair<const std::string, int>& pair : m_SEs)
	{
		DeleteSoundMem(pair.second);
	}
	m_BGMs.clear();
	m_SEs.clear();
}

bool AudioManager::PlayBGM(const std::string& name)
{
	if (m_CurrentBGM != 0 && m_CurrentBGM != -1)
	{	//再生中
		m_CurrentBGM = StopSoundMem(m_CurrentBGM);

		if (m_CurrentBGM == -1) return false;
	}
	
	// 0:成功/ -1:エラー発生
	m_CurrentBGM = PlaySoundMem(m_BGMs[name], DX_PLAYTYPE_LOOP);

	if (m_CurrentBGM == -1) return false;

	m_CurrentBGM = m_BGMs[name];
	return true;
}

bool AudioManager::PlaySE(const std::string& name)
{
	// 0:成功/ -1:エラー発生
	int result = PlaySoundMem(m_SEs[name], DX_PLAYTYPE_BACK);

	return (result != -1) ? true : false;
}

bool AudioManager::StopBGM(const std::string& name)
{
	// 0:成功/ -1:エラー発生
	m_CurrentBGM = StopSoundMem(m_BGMs[name]);

	return (m_CurrentBGM != -1) ? true : false;
}

void AudioManager::SetVolumeMaster(int volume)
{
	m_VolumeMaster = volume;
	m_VolumeMaster = math_helper::clamp(m_VolumeMaster, 0, MAX_VOLUME);

	SetVolumeBGM(m_VolumeMaster);
	SetVolumeSE(m_VolumeMaster);
}

void AudioManager::SetVolumeBGM(int volume)
{
	m_VolumeBGM = m_VolumeMaster * (volume / MAX_VOLUME);
	m_VolumeBGM = math_helper::clamp(m_VolumeBGM, 0, MAX_VOLUME);

	for (const std::pair<const std::string, int>& pair : m_BGMs)
	{
		ChangeVolumeSoundMem(m_VolumeBGM, pair.second);
	}
}

void AudioManager::SetVolumeSE(int volume)
{
	m_VolumeSE = m_VolumeMaster * (volume / MAX_VOLUME);
	m_VolumeSE = math_helper::clamp(m_VolumeSE, 0, MAX_VOLUME);

	for (const std::pair<const std::string, int>& pair : m_BGMs)
	{
		ChangeVolumeSoundMem(m_VolumeSE, pair.second);
	}
}

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
	LoadBGM("Game", "Zero_Defects.mp3");

	//プレイヤー
	LoadSE("Jump", "Jump.mp3");
 	LoadSE("Shot", "Shot.mp3");
	LoadSE("ShotEmpty", "ShotEmpty.mp3");
	LoadSE("Reload", "Reload.mp3");
	LoadSE("Land", "Land.mp3");
	LoadSE("Damage", "Damage.mp3");
	LoadSE("Stomp", "Stomp.mp3");//敵踏みつけ
	LoadSE("Dead", "Dead.mp3");
	//ブロック
	LoadSE("BlockHit", "BlockHit.mp3");
	LoadSE("BlockBreak", "BlockBreak.mp3");
	//エネミー
	LoadSE("EnemyHit", "EnemyHit.mp3");
	LoadSE("EnemyDead", "EnemyDead.mp3");
	//操作
	LoadSE("Decide", "Decide.mp3");

	SetVolumeMaster(m_VolumeMaster);
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

	ApplyVolumeBGM();
	ApplyVolumeSE();
}

void AudioManager::SetVolumeBGM(int volume)
{
	m_VolumeBGM = math_helper::clamp(volume, 0, MAX_VOLUME);
	ApplyVolumeBGM();
}

void AudioManager::SetVolumeSE(int volume)
{
	m_VolumeSE = math_helper::clamp(volume, 0, MAX_VOLUME);
	ApplyVolumeSE();
}

void AudioManager::ApplyVolumeBGM()
{
	int volume = m_VolumeMaster * m_VolumeBGM / MAX_VOLUME;

	for (const std::pair<const std::string, int>& pair : m_BGMs)
	{
		ChangeVolumeSoundMem(volume, pair.second);
	}
}

void AudioManager::ApplyVolumeSE()
{
	int volume = m_VolumeMaster * m_VolumeSE / MAX_VOLUME;

	for (const std::pair<const std::string, int>& pair : m_SEs)
	{
		ChangeVolumeSoundMem(volume, pair.second);
	}
}

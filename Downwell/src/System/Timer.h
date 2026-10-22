#pragma once

class Timer
{
private:
	static constexpr float FRAME_PER_SECOND = 60.0f;
	static constexpr float FIXED_DELTA_TIME = 1.0f / FRAME_PER_SECOND;
	static constexpr float MAX_DELTA_TIME = 0.1f;
	static constexpr float MICRO_TO_SECOND = 1.0e-6f;

	long long m_LastCount = 0;
	float m_DeltaTime = 0.0f;
	float m_Accumulator = 0.0f;

	//デバッグ表示用
	float m_UPS = 0.0f;
	float m_FPS = 0.0f;
	float m_FpsTimer = 0.0f;
	int m_FrameCount = 0;

public:
	Timer() = default;
	~Timer() = default;

	void Initialize();
	void Finalize();
	void Tick();

	void Update();
	void Draw();

	bool ConsumeFixedStep();
	float GetFixedDeltaTime() const { return FIXED_DELTA_TIME; }

	bool HasRemainingStep();
	void DiscardRemainingSteps();

};
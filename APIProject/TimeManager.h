#pragma once

class TimeManager
{
private:
	TimeManager();
	~TimeManager();
public:
	TimeManager(const TimeManager&) = delete;
	TimeManager(TimeManager&&) = delete;
	TimeManager& operator=(const TimeManager&) = delete;
	TimeManager& operator=(TimeManager&&) = delete;

	static TimeManager& GetInstance() { static TimeManager sMgr; return sMgr; }

public:
	void 	Init();
	void 	Update();
	void	FrameLimit();

	float 	GetDeltaTime() const { return mDeltaTime; }
	float 	GetUnscaledDeltaTime() const { return mUnscaledDeltaTime; }
	float 	GetTimeScale() const { return mTimeScale; }
	void 	SetTimeScale(float scale) { mTimeScale = scale; }
	float 	GetUnscaledTime() const { return mUnscaledTime; }
	void 	SetTargetFrameRate(float fps) { mTargetFrameTime = 1.0f / fps; }

private:
	LARGE_INTEGER 	mFrequency;
	LARGE_INTEGER 	mLastFrameTime;
	LARGE_INTEGER 	mCurrentFrameTime;
	float 			mDeltaTime;
	float 			mUnscaledDeltaTime;
	float 			mTimeScale;
	float 			mUnscaledTime;
	float 			mTargetFrameTime;

	double			mAccTime;
	int				mFPS;
	TCHAR			m_szFPS[16];
};


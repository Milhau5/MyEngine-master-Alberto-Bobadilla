/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/05
*/
#ifndef __SystemSingleton_H_
#define __SystemSingleton_H_

#include "ME\System\FolderSingleton.h"

namespace MyEngine
{

//System Class
class MyEngineDLL SystemSingleton
{
	bool m_bWindowFullscreen; // Window Fullscreen
	bool m_bWindowBorderless; // Window Borderless

	int m_nWindowWidth; // Window width
	int m_nWindowHeight; // Window height
	int m_nWindowX; // Window Position X
	int m_nWindowY; // Window Position Y

	int m_nFPS; //Frames per Second
	int m_nFrames; //Frames Passed

	static SystemSingleton* m_pInstance; // Singleton

	String m_sWindowName; // Window Name
	String m_sAppName;

	DWORD m_dTimerStart; //Start time of the program
	DWORD m_dStartingTime; //Start time of the program
	DWORD m_dLastFPS; //Last time the time was called

	std::vector<DWORD> lClock;//clockls list
	
public:
	static SystemSingleton* GetInstance(); // Singleton accessor
	static void ReleaseInstance(void); //Singleton Release

	// Application Name Property
	String GetAppName(void);
	__declspec(property(get = GetAppName)) String ApplicationName;

	// Window Borderless Property
	__declspec(property(get = IsWindowBorderless, put = SetWindowBorderless)) bool WindowBorderless;
	void SetWindowBorderless(bool a_bBorderless = true);
	bool IsWindowBorderless(void);

	// Window Fullscreen Property
	__declspec(property(get = IsWindowFullscreen, put = SetWindowFullscreen)) bool WindowFullscreen;
	void SetWindowFullscreen(bool a_bFullscreen = true);
	bool IsWindowFullscreen(void);
	
	// Window Width Property
	__declspec(property(get = GetWindowWidth, put = SetWindowWidth)) int WindowWidth;
	void SetWindowWidth(int a_nWidth);
	int GetWindowWidth(void);

	// Window Height Property
	__declspec(property(get = GetWindowHeight, put = SetWindowHeight)) int WindowHeight;
	void SetWindowHeight(int a_nHeight);
	int GetWindowHeight(void);

	// WindowX Property
	__declspec(property(get = GetWindowX, put = SetWindowX)) int WindowX;
	void SetWindowX(int a_nX);
	int GetWindowX(void);

	// WindowY Property
	__declspec(property(get = GetWindowY, put = SetWindowY)) int WindowY;
	void SetWindowY(int a_nY);
	int GetWindowY(void);
	
	// Window Name Property
	__declspec(property(get = GetWindowName, put = SetWindowName)) String WindowName;
	void SetWindowName(String a_sWindowName);
	String GetWindowName(void);

	/*
	float GetWindowRatio(void);
		This will return the proportions of the window size in the system, from bottom to top of the window the value is 1,
		from left to right the value is the output of this function.
	*/
	float GetWindowRatio(void);

	// WindowX Property
	__declspec(property(get = GetFPS)) int FPS;
	int GetFPS(void);

	void UpdateTime(void);//Updates the current time
	//float LapClock(void);//Checks the time difference between startclock and current call
	void StartClock(unsigned int a_nClock = 1);//Starts a time count for the specified clock
	float LapClock(unsigned int a_nClock = 1);//Gets the time difference between the last time this method was called for this particular clock
	bool CountDown(float a_fTime, bool a_bRepeat = false);//counts down on the specified clock, returns true when the count is up

	FolderSingleton* m_pFolder;
	MEOptions m_RenderingContext;

private:
	SystemSingleton(void); // Constructor
	SystemSingleton(SystemSingleton const& other); //Copy Constructor
	SystemSingleton& operator=(SystemSingleton const& other); // Copy Assignment Operator
	~SystemSingleton(void); // Destructor

	void Release(void); // Release Memory
	void Init(void); // Initialize variables
};

}
#include "ME\system\WindowClass.h"
#include "ME\System\GLSystemSingleton.h"

#endif //__SystemSingleton_H__
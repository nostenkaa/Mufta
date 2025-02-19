
// CourseProject.h: основной файл заголовка для приложения CourseProject
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CCourseProjectApp:
// Сведения о реализации этого класса: CourseProject.cpp
//

class CCourseProjectApp : public CWinApp
{
public:
	CCourseProjectApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCourseProjectApp theApp;

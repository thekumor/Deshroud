/* ================================================================
*
*	Contains all controls used in this app.
*
*	#Authors: The Kumor
*
* ================================================================ */

#pragma once

// STL
#include <string>
#include <vector>

// WinAPI
#include <windows.h>

// Deshroud
#include <ds/vector.h>

namespace ds {

	Pos GetScreenCenter();

	class Control
	{
	public:
		Control(Pos pos, Size size, const std::wstring& title, Control* parent = nullptr);
		Control() = default;

		static LRESULT s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

		friend class Window;
		friend class Button;
		friend class Label;
		friend class ComboBox;
		friend class Numeric;

	protected:
		HWND m_Handle;
		Pos m_Pos;
		Size m_Size;
		std::wstring m_Title;
		Control* m_Parent;
	};

	class Window : public Control
	{
	public:
		Window(Pos pos, Size size, const std::wstring& title, Control* parent = nullptr);
		Window() = default;

		static LRESULT s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

	private:

	};

	class Button : public Control
	{
	public:
		Button(Pos pos, Size size, const std::wstring& title, Control* parent = nullptr);
		Button() = default;
	};

	class Label : public Control
	{
	public:
		Label(Pos pos, Size size, const std::wstring& title, Control* parent = nullptr);
		Label() = default;
	};

	class ComboBox : public Control
	{
	public:
		ComboBox(Pos pos, Size size, const std::wstring& title, Control* parent = nullptr);
		ComboBox() = default;

		void AddEntry(const std::wstring& entry);
		void AddEntries(const std::vector<std::wstring>& entries);
	};

	class Numeric : public Control
	{
	public:
		Numeric(Pos pos, Size size, const std::wstring& title, Control* parent = nullptr);
		Numeric() = default;
	};

}
/* ================================================================
*
*	Console for logging, debugging.
*
*	#Authors: The Kumor
*
* ================================================================ */

// STL
#include <iostream>
#include <sstream>
#include <cstdint>
#include <array>
#include <vector>
#include <chrono>

// Deshroud
#include <ds/controls.h>
#include <ds/vector.h>

namespace ds {

	enum class BufferType : std::int16_t
	{
		Invalid = 0,
		Out,
		Error,
		Log
	};

	struct BufferInfo
	{
		BufferInfo(std::streambuf* old, BufferType type);
		BufferInfo() = default;

		std::streambuf* OldBuffer = nullptr;
		std::ostringstream Stream = std::ostringstream();
		BufferType Type = BufferType::Invalid;
	};

	struct Timestamp
	{
		Timestamp();

		std::time_t m_Epoch;

		[[nodiscard]] std::string ToString() const;
	};

	enum class MessageType : std::int32_t
	{
		Invalid = 0,
		Info,
		Warning,
		Error
	};

	struct Message
	{
		Message(const std::string& string, MessageType type);
		Message() = default;

		std::string Content;
		Timestamp Time;
		MessageType Type;
	};

	class Console : public Control
	{
	public:
		Console(Pos pos, Size size, const std::wstring& title, Control* parent = nullptr);
		Console() = default;

		static LRESULT s_Procedure(HWND handle, UINT msg, WPARAM wp, LPARAM lp);

		BufferInfo* GetBuffer(BufferType type);
		void AddMessage(const Message& msg);

	private:
		std::array<BufferInfo, 3> m_Buffers;
		std::vector<Message> m_Messages;
	};

}
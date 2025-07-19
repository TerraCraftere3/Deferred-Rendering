#ifndef LOG_H
#define LOG_H

#include <mutex>
#include <vector>
#include <string>

#ifdef USE_IMGUI
#define GLIB_USE_IMGUI
#endif

#ifdef USE_LOG
#define GLIB_USE_LOG
#define GLIB_USE_SPDLOG
#endif

#ifdef USE_LOG
#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#ifdef USE_IMGUI
#include <imgui.h>
class ImGuiSink : public spdlog::sinks::base_sink<std::mutex>
{
  public:
	const std::vector<std::pair<spdlog::level::level_enum, std::string>>&
	GetLogBuffer() const
	{
		return m_LogBuffer;
	}
	void Clear() { m_LogBuffer.clear(); }

  protected:
	void sink_it_(const spdlog::details::log_msg& msg) override
	{
		spdlog::memory_buf_t formatted;
		formatter_->format(msg, formatted);
		m_LogBuffer.emplace_back(msg.level, fmt::to_string(formatted));
	}

	void flush_() override {}

  private:
	std::vector<std::pair<spdlog::level::level_enum, std::string>> m_LogBuffer;
};
#endif

class Log
{
  public:
	static void Init()
	{
#ifdef USE_IMGUI
		if (!s_ImguiSink)
			s_ImguiSink = std::make_shared<ImGuiSink>();
#endif

		if (!s_ConsoleSink)
			s_ConsoleSink =
			    std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

		if (!s_Logger)
		{
#ifdef USE_IMGUI
			std::vector<spdlog::sink_ptr> sinks{s_ImguiSink, s_ConsoleSink};
			s_Logger = std::make_shared<spdlog::logger>("Core", sinks.begin(),
			                                            sinks.end());
#else
			std::vector<spdlog::sink_ptr> sinks{s_ConsoleSink};
			s_Logger = std::make_shared<spdlog::logger>("Core", sinks.begin(),
			                                            sinks.end());
#endif
			spdlog::register_logger(s_Logger);
			spdlog::set_default_logger(s_Logger);
			spdlog::set_level(spdlog::level::trace);
			spdlog::flush_on(spdlog::level::info);
		}
	}

#ifdef USE_IMGUI
	static void DrawLogs()
	{
		if (ImGui::Button("Clear"))
			::Log::GetSink()->Clear();

		ImGui::BeginChild("LogScrollRegion", ImVec2(0, 0), false,
		                  ImGuiWindowFlags_HorizontalScrollbar);

		const auto& buffer = ::Log::GetSink()->GetLogBuffer();
		static size_t lastLogSize = 0;
		bool shouldScroll = false;

		if (lastLogSize != buffer.size())
		{
			shouldScroll = true;
			lastLogSize = buffer.size();
		}

		for (const auto& entry : buffer)
		{
			auto level = entry.first;
			const auto& line = entry.second;

			ImVec4 color;
			switch (level)
			{
			case spdlog::level::trace:
				color = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
				break;
			case spdlog::level::debug:
				color = ImVec4(0.0f, 0.5f, 1.0f, 1.0f);
				break;
			case spdlog::level::info:
				color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case spdlog::level::warn:
				color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
				break;
			case spdlog::level::err:
				color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			case spdlog::level::critical:
				color = ImVec4(1.0f, 0.0f, 1.0f, 1.0f);
				break;
			default:
				color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			}

			ImGui::PushStyleColor(ImGuiCol_Text, color);
			ImGui::TextUnformatted(line.c_str());
			ImGui::PopStyleColor();
		}

		if (shouldScroll)
			ImGui::SetScrollHereY(1.0f); // scroll to bottom

		ImGui::EndChild();
	}
#endif

	static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
#ifdef USE_IMGUI
	static std::shared_ptr<ImGuiSink>& GetSink() { return s_ImguiSink; }
#endif

  private:
	static std::shared_ptr<spdlog::logger> s_Logger;
#ifdef USE_IMGUI
	static std::shared_ptr<ImGuiSink> s_ImguiSink;
#endif
	static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> s_ConsoleSink;
};

// Static definitions
inline std::shared_ptr<spdlog::logger> Log::s_Logger = nullptr;
#ifdef USE_IMGUI
inline std::shared_ptr<ImGuiSink> Log::s_ImguiSink = nullptr;
#endif
inline std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> Log::s_ConsoleSink =
    nullptr;

// Logging macros
#define LOG_TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) ::Log::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...) ::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Log::GetLogger()->critical(__VA_ARGS__)

#else // USE_LOG

namespace Log
{
static void Init() {}
#ifdef USE_IMGUI
static void DrawLogs() {};
#endif
} // namespace Log

#define LOG_TRACE(...) (void)0
#define LOG_DEBUG(...) (void)0
#define LOG_INFO(...) (void)0
#define LOG_WARN(...) (void)0
#define LOG_ERROR(...) (void)0
#define LOG_CRITICAL(...) (void)0

#endif // USE_LOG

#endif // LOG_H

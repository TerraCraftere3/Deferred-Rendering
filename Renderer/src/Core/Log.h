// FROM 3D RENDERER https://github.com/TerraCraftere3/3D-Renderer/blob/main/Renderer/src/Core/Log.h
#ifndef LOG_H
#define LOG_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/base_sink.h>
#include <mutex>
#include <vector>
#include <string>

class ImGuiSink : public spdlog::sinks::base_sink<std::mutex>
{
public:
    const std::vector<std::pair<spdlog::level::level_enum, std::string>> &GetLogBuffer() const { return m_LogBuffer; }
    void Clear() { m_LogBuffer.clear(); }

protected:
    void sink_it_(const spdlog::details::log_msg &msg) override
    {
        spdlog::memory_buf_t formatted;
        formatter_->format(msg, formatted);
        m_LogBuffer.emplace_back(msg.level, fmt::to_string(formatted));
    }
    void flush_() override {}

private:
    std::vector<std::pair<spdlog::level::level_enum, std::string>> m_LogBuffer;
};

class Log
{
public:
    static void Init()
    {
        if (!s_ImguiSink)
            s_ImguiSink = std::make_shared<ImGuiSink>();

        if (!s_Logger)
        {
            s_Logger = std::make_shared<spdlog::logger>("Core", s_ImguiSink);
            spdlog::register_logger(s_Logger);
            spdlog::set_default_logger(s_Logger);
            spdlog::set_level(spdlog::level::trace);
            spdlog::flush_on(spdlog::level::info);
        }
    }

    static void DrawLogs()
    {
        if (ImGui::Button("Clear"))
            ::Log::GetSink()->Clear();

        ImGui::BeginChild("LogScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        const auto &buffer = ::Log::GetSink()->GetLogBuffer();
        static size_t lastLogSize = 0;
        bool shouldScroll = false;

        if (lastLogSize != buffer.size())
        {
            shouldScroll = true;
            lastLogSize = buffer.size();
        }

        for (const auto &entry : buffer)
        {
            auto level = entry.first;
            const auto &line = entry.second;

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

    static std::shared_ptr<spdlog::logger> &GetLogger() { return s_Logger; }
    static std::shared_ptr<ImGuiSink> &GetSink() { return s_ImguiSink; }

private:
    static std::shared_ptr<spdlog::logger> s_Logger;
    static std::shared_ptr<ImGuiSink> s_ImguiSink;
};

inline std::shared_ptr<spdlog::logger> Log::s_Logger = nullptr;
inline std::shared_ptr<ImGuiSink> Log::s_ImguiSink = nullptr;

#define LOG_TRACE(...) ::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) ::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Log::GetLogger()->critical(__VA_ARGS__)

#endif // LOG_H
#pragma once

#include <stdint.h>
#include <string>
#include <fstream>

namespace MyTools {

    // Палитра цветов от 0 до 15
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

	void ClrScr();

	void __fastcall GotoXY(double x, double y);

	uint16_t GetMaxX();

	uint16_t GetMaxY();

    void SetColor(ConsoleColor color);

	//=============================================================================================

    class ILogger {
    public:
        virtual ~ILogger() = default;
        virtual void OpenLogFile(const std::string& filename) = 0;
        virtual void CloseLogFile() = 0;
        virtual void WriteToLog(const std::string& str) = 0;
        virtual void WriteToLog(const std::string& str, int n) = 0;
        virtual void WriteToLog(const std::string& str, double d) = 0;
    };

    class FileLoggerSingleton : public ILogger {
    public:
        static FileLoggerSingleton& getInstance() {
            static FileLoggerSingleton instance;
            return instance;
        }

        void OpenLogFile(const std::string& filename) override;
        void CloseLogFile() override;
        void WriteToLog(const std::string& str) override;
        void WriteToLog(const std::string& str, int n) override;
        void WriteToLog(const std::string& str, double d) override;

    private:
        FileLoggerSingleton() = default;
        FileLoggerSingleton(const FileLoggerSingleton&) = delete;
        FileLoggerSingleton& operator=(const FileLoggerSingleton&) = delete;
        FileLoggerSingleton(FileLoggerSingleton&&) = delete;
        FileLoggerSingleton& operator=(FileLoggerSingleton&&) = delete;

        static std::string GetCurDateTime();

        std::ofstream logOut;
    };

    class ProxyLogger : public ILogger {
    public:
        ProxyLogger(ILogger& logger) : logger{logger} {}
        ~ProxyLogger() override;

        void OpenLogFile(const std::string& filename) override;
        void CloseLogFile() override;
        void WriteToLog(const std::string& str) override;
        void WriteToLog(const std::string& str, int n) override;
        void WriteToLog(const std::string& str, double d) override;

    private:
        ILogger& logger;
        uint32_t counter{0u};
    };

	//=============================================================================================

};
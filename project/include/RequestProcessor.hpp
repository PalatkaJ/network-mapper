#ifndef REQUEST_PROCESSOR_HPP
#define REQUEST_PROCESSOR_HPP
#include "cxxopts.hpp"
#include "Logger.hpp"

namespace netmap {
    class RequestProcessor {
    protected:
        Logger& logger_;
    public:
        explicit RequestProcessor(Logger& logger);
        virtual ~RequestProcessor() = default;

        virtual void Process() = 0;
    };

    class HelpProcessor final : public RequestProcessor {
        std::string_view help_;

    public:
        explicit HelpProcessor(std::string_view help, Logger& logger);

        void Process() override;
    };
}

#endif //REQUEST_PROCESSOR_HPP

#ifndef OPTION_HANDLER_HPP
#define OPTION_HANDLER_HPP
#include "cxxopts.hpp"
#include "Logger.hpp"


namespace netmap {
    class RequestProcessor {
    public:
        virtual ~RequestProcessor() = default;

        virtual void Process() = 0;
    };

    class HelpProcessor final : public RequestProcessor {
        std::string help_;

    public:
        explicit HelpProcessor(std::string help);

        void Process() override;
    };
}

#endif //OPTION_HANDLER_HPP

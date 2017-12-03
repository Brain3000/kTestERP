#pragma once

#include <string>
#include <set>
#include <memory>

class MainUtil;

const std::string kEmptyString;

class MenuBase {
protected:
    enum class OptionAction {
        eExit,
        eRunItem,
        eRunItemAndExit,
//        eInputString,
    };

    struct Option {
        Option(const std::string& cap, int keyCode,
               OptionAction action, const std::string& addParam = kEmptyString);
        void show();

        const std::string m_caption;
        const int m_keyCode;
        const OptionAction m_action;
        const std::string m_additionalParam;

    private:
        std::string printableKey() const;

    };

    struct OptionLess : std::binary_function<Option, Option, bool>  {
        bool operator()(const Option& op1, const Option& op2) const {
            return op1.m_keyCode < op2.m_keyCode;
        }
    };
    using Options = std::set<Option, OptionLess>;
public:
    virtual ~MenuBase(){}
    void run();
    const MainUtil* mainUtil() const noexcept {
        return m_mainUtil;
    }
    const std::string& resultString() const noexcept {
        return m_resultString;
    }

protected:
    MenuBase(MainUtil* mainUtil, const std::string& caption);
    virtual void runOption(const Option& opt) = 0;
    virtual Options options() const {
        return m_options;
    }
//    void inputString(const Option& opt);

protected:
    MainUtil* m_mainUtil;
    const std::string m_caption;
    Options m_options;
    std::string m_resultString;
};


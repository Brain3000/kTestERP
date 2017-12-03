/**
\file
\brief ������� ���� ��� ���� ����
\author Leontyev George
\version 1.0
\date ������ 2017
*/
#pragma once

#include <string>
#include <set>
#include <memory>

class MainUtil;

/// ��������� ��� ������ ������.
const std::string kEmptyString;

/**
    \brief ������� ����� ��� ���� ����.

    �������� ��������� ��� ���� ���� ����� � ��� ����� - �������� �����
*/
class CustomMenu {
protected:
    /// ���� ����� ����.
    enum class OptionAction {
        eExit,          ///< ������ �� ������, ����� �� ����.
        eRunItem,       ///< ��������� ������� runOption � ������������ ����.
        eRunItemAndExit,///< ��������� ������� runOption � ����� �� ����.
    };

    /// ���������, ����������� ������� ����
    struct Option {
        Option(const std::string& cap,                      ///< ����� ������ ����.
               int keyCode,                                 ///< ��� ������ ���� (�������, �� ������� ����� ������)
               OptionAction action,                         ///< �������� ��� ������ ������ ����
               const std::string& addParam = kEmptyString); ///< ��������, ������� ����� ���� ����������� ��� ������������ ����� ������ ����.
        /// ���������� ������������� ������ ���� � �������. ��� ������� ����� ��������� � ���������� �������.
        void show();                                        

        const std::string m_caption;        ///< ��������� ������ ����.
        const int m_keyCode;                ///< ��� (������), ������� ������������ ������ ������, ����� ����� ���� ��������.
        const OptionAction m_action;        ///< �������� ��� ������ ������ ����.
        const std::string m_additionalParam;///< �������������� ��������, ����� ���� ��� ������, ������������ ��� boost::variant

    private:
        /// ���������� �������� �������� ��� �����, �������� ��� ' ' ������������ ����� ������.
        std::string printableKey() const;

    };

    /// ������� ��� ��������� ������ ���� (������������ �� ���� ������)
    struct OptionLess : std::binary_function<Option, Option, bool>  {
        bool operator()(const Option& op1, const Option& op2) const {
            return op1.m_keyCode < op2.m_keyCode;
        }
    };
    using Options = std::set<Option, OptionLess>;
public:
    virtual ~CustomMenu(){}
    /// ���������� ����, ����� ������� �� ������� � ������������ ������ ��,
    /// ������� ������ ��� ����� ������� ����.
    void run();

    /// ���������� m_additionalParam ���������� ����� ����. ����� ���� ������ �������.
    const std::string& resultString() const noexcept {
        return m_resultString;
    }

protected:
    /**
        \brief ����������� � ����������� - ���������� ������ �� �������
        ������� � ��������� ����� ���� (��� ����� ���������, � ��� ������
        ���� ����� ����� ��������� ������ � ����������� ������)
    */    
    CustomMenu(MainUtil* mainUtil, const std::string& caption);

    /**
        \brief     ���������� ��� ������ ������ ����. ������ ���� �������������� 
        � ����������� �������, ��� ���������� ������� �� ������ ����.
        \param[int] ����������� ����� ����.
    */
    virtual void runOption(const Option& opt) = 0;

    /// ���������� ������ ���� �����.
    virtual Options options() const {
        return m_options;
    }

protected:
    MainUtil* m_mainUtil;
    const std::string m_caption;
    Options m_options;
    std::string m_resultString;
};


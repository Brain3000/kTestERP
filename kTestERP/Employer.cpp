#include "stdafx.h"

#include  <iterator>
#include  <algorithm>

#include "Employer.h"
#include "EnumImpl.h"

using PosStrMap = std::unordered_map<EmployerPosition, std::string>;
using StrPosMap = std::unordered_map<std::string, EmployerPosition>;

const PosStrMap& getPosStrMap() {
    static const PosStrMap s_posStrMap = {
        { EmployerPosition::eProgrammer, "Разработчик" },
        { EmployerPosition::eWriter, "Писатель", },
        { EmployerPosition::eTester, "Тестер" },
        { EmployerPosition::eAccountant, "Бухгалтер" },
    };
#ifdef _DEBUG
    for (auto e : EnumImpl<EmployerPosition>()) {
        assert(s_posStrMap.find(e) != s_posStrMap.end());
    }
#endif // _DEBUG

    return s_posStrMap;
}

const std::string& pos_to_str(EmployerPosition pos) {
    return getPosStrMap().at(pos);
}


EmployerPosition str_to_pos(const std::string& posAsStr) {
    static StrPosMap s_strPosMap;
    if (s_strPosMap.empty()) {
        const PosStrMap& posStrMap(getPosStrMap());
        std::transform(posStrMap.begin(),
                       posStrMap.end(),
                       std::inserter(s_strPosMap, s_strPosMap.begin()),
                       [](auto pair) { return std::make_pair(pair.second, pair.first);  });
    }
    return s_strPosMap.at(posAsStr);
}


bool Employer::doJob(Job job, StringList& report) const {
    using ReverseEmplPosMap = std::unordered_map<EmployerPosition, std::string>;

    bool jobResult = m_jobs.find(job) != m_jobs.end();
    std::string msg = "Сотрудник '";
    msg.append(m_name);
    msg.append("' в должности '");
    msg.append(pos_to_str(m_position));
    msg.append("' работу '");
    msg.append(job_to_str(job));
    msg.append("' ");
    msg.append(jobResult ? "выполнил(а)" : "не может выполнить");
    report.emplace_back(msg);
    return jobResult;
}

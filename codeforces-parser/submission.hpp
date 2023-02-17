#pragma once

const std::string delimiter = "my_stupid_delimiter";

struct Submission {
    int subId{};  // id of submission
    std::string when; // time of submission
    int partId{}; // participant who made submission
    std::string hrefUser;
    std::string nickname;
    int problemId{};
    std::string hrefProblem;
    std::string problemName;
    std::string runtime;
    std::string lang;
    std::string verdict;
    std::string memory;
    
    bool readFromPage(std::string &fs, bool &lastRowDetected)
    {
        // read full submission info from input stream
        // submission id on codeforces:
        std::string subIdS;
        bool subIdOK = extractBetween(fs,"<tr data-submission-id=\"","\"", subIdS);
        if (!subIdOK) {
            subIdOK = extractBetween(fs,"<tr class=\"last-row\" data-submission-id=\"","\"", subIdS);
            lastRowDetected = true;
        }
        if (!subIdOK)
            return false;
        assert(subIdOK);
        trimRef(subIdS);
        subId = std::stoi(subIdS);
        watch(subId);
        // when submission is done:
        bool whenOK = removeBefore(fs,"format-time");
        whenOK = whenOK && extractBetween(fs,">", "<",when);
        assert(whenOK);
        trimRef(when);
        watch(when);
        // user id on codeforces:
        std::string partIdS;
        bool partIdOK = extractBetween(fs,"data-participantId=\"","\"",partIdS);
        assert(partIdOK);
        partId = std::stoi(partIdS);
        watch(partId);
        // href to user profile:
        bool hrefUserOK = extractBetween(fs,"href=\"", "\"",hrefUser);
        assert(hrefUserOK);
        watch(hrefUser);
        // nickname of user:
        bool nicknameOK = extractBetween(fs,">", "<",nickname);
        assert(nicknameOK);
        watch(nickname);
        // id of problem:
        std::string problemIdS;
        bool problemIdOK = extractBetween(fs,"data-problemId=\"","\"", problemIdS);
        assert(problemIdOK);
        problemId = std::stoi(problemIdS);
        watch(problemId);
        // href to problem:
        bool hrefProblemOK = extractBetween(fs,"href=\"", "\"",hrefProblem);
        assert(hrefProblemOK);
        watch(hrefProblem);
        // the title of problem
        bool problemNameOK = extractBetween(fs,">", "<",problemName);
        assert(problemNameOK);
        trimRef(problemName);
        replaceSubstrRef(problemName, "&rsquo;", "'");
        watch(problemName);
        // language of submission (C++, Java, etc)
        bool langOK = extractBetween(fs,"<td>", "<",lang);
        assert(langOK);
        trimRef(lang);
        watch(lang);
        // submission href
        /*bool hrefOK = extractBetween(fs,"href=\"", "\"",href);
        assert(hrefOK);
        watch(href);*/
        // submission verdict
        bool verdictOK = extractBetween(fs,"submissionVerdict=\"","\"",verdict);
        assert(verdictOK);
        watch(verdict);
        // runtime of submission
        bool runtimeOK = removeBefore(fs,"time-consumed-cell");
        runtimeOK = runtimeOK && extractBetween(fs,">", "<",runtime);
        assert(runtimeOK);
        trimRef(runtime);
        replaceSubstrRef(runtime, "&nbsp;", " ");
        watch(runtime);
        // used memory in submission
        bool memoryOK = removeBefore(fs,"memory-consumed-cell");
        memoryOK = memoryOK && extractBetween(fs,">", "<",memory);
        assert(memoryOK);
        trimRef(memory);
        replaceSubstrRef(memory, "&nbsp;", " ");
        watch(memory);
        return true;
    }
    Submission &from_string(const std::string& s)
    {
        auto vec = split(s, delimiter);
        if(vec.size() != 12u) {
            std::cerr << "s = '" << s << "'" << std::endl;
            for (auto &it : vec) {
                std::cerr << "vec_item = '" << it << "'" << std::endl;
            }
        }
        assert(vec.size() == 12);
        subId = std::stoi(vec[0]);
        when = vec[1];
        partId = std::stoi(vec[2]);
        hrefUser = vec[3];
        nickname = vec[4];
        problemId = std::stoi(vec[5]);
        hrefProblem = vec[6];
        problemName = vec[7];
        runtime = vec[8];
        lang = vec[9];
        verdict = vec[10];
        memory = vec[11];
        return *this;
    }
    std::string to_string() const
    {
        std::string s;
        (s += std::to_string(subId))+=delimiter;
        (s += when)+=delimiter;
        (s += std::to_string(partId))+=delimiter;
        (s += hrefUser)+=delimiter;
        (s += nickname)+=delimiter;
        (s += std::to_string(problemId))+=delimiter;
        (s += hrefProblem)+=delimiter;
        (s += problemName)+=delimiter;
        (s += runtime)+=delimiter;
        (s += lang)+=delimiter;
        (s += verdict)+=delimiter;
        (s += memory)+=delimiter;
        return s;
    }
};

bool operator<(const Submission &a, const Submission &b) {
    return a.subId < b.subId;
}

bool operator>(const Submission &a, const Submission &b) {
    return b < a;
}

std::string link2filename(std::string link) {
    // сначала проверим, что это группа
{
    std::string group;
    bool groupOK = extractBetween(link, "group/", "/", group);
    if (groupOK) {
        std::string contest;
        bool contestOK = extractBetween(link, "contest/", "/", contest);
        assert(contestOK);
        std::string filename = "group_";
        filename += group;
        filename += "_contest_";
        filename += contest;
        filename += ".txt";
        return filename;
    }
}
{
    // теперь то, что это посылки участника
    std::string nickname;
    bool submissionsOK = extractBetween(link, "submissions/", "/", nickname);
    assert(submissionsOK);
    std::string filename = "submissions_";
    filename += nickname;
    filename += ".txt";
    return filename;
}
}

struct Cache {
    std::string filename;
    std::vector<Submission> cache;
    Cache(std::string link)
    {
        filename = link2filename(link);
        std::ifstream fin(filename);
        std::string s;
        while (std::getline(fin, s))
            cache.push_back(Submission().from_string(s));
        }
    ~Cache() {
        std::ofstream fout(filename);
        for (const auto &s : cache) {
            fout << s.to_string() << '\n';
        }
    }
};
#!/bin/sh
LC_ALL="tt_RU";
domain="https://codeforces.com"
downloadLink() {
    link="$1"
    if [ -e "temp.txt" ]
    then
        rm -rf contests
    fi
    echo -e "\n~~~~~~~~~~~~~~ Codeforces Page Downloader ~~~~~~~~~~~~~~~"
    echo "Start downloading of page $link"
    curl "$link" -o "temp.txt"
    if [ -e "temp.txt" ]
    then
        echo "The content of $link has been downloaded";
    else
        echo "Can't download $link";
        return 0;
    fi
    echo -e "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
}

parseGroup() {
    groupId="$1"
    echo -e "\nStart parsing the group $groupId"
    if ! downloadLink "$domain/group/$groupId/contests"
    then
        return 1;
    fi
    echo "" > out.txt;
    for i in $(./group-contests.exe temp.txt h 2>/dev/null);
    do
        var="1"
        while [ $var != "done" ]
        do
            link="$domain$i/status/page/$var";
            echo $link;
            if ! downloadLink "$link"
            then
                return 1;
            fi
            var="$(./contest-status temp.txt $link)"
            echo "var = $var"
        done
    done
    echo -e "Parsing of group $groupId is done"
}

parseUser() {
    userName="$1"
    echo -e "\nStart parsing the user $userName"
    echo "" > out.txt;
    # https://codeforces.com/submissions/Harek/page/1
    var="1"
    i="/submissions/$userName"
    while [ $var != "done" ]
    do
        link="$domain$i/page/$var";
        echo $link;
        if ! downloadLink "$link"
        then
            return 1;
        fi
        var="$(./user-status temp.txt $link)"
        echo "var = $var"
    done
    echo -e "Parsing of user $userName is done"
}

# может парсить только те группы, где в администрировании в параметрах
# политика регистрации зрителей выставлена в режи "автоматически"

#parseGroup "PZJYXH0KrS" # Курс начинающего олимпиадника
#parseGroup "uQw4LhzOcG" # Новое олимпиадное программирование в МИРЭА
#parseGroup "bcNLtajskz" # Курс по олимпиадному программированию
#parseGroup "LB1sSRhotq" # Олимпиадное программирование в МИРЭА
#cat group_* > temp.txt
#./process-rating.exe temp.txt 100 "only_users" > users.txt
for i in $(cat users.txt); do
    parseUser "$i";
done
#./process-rating.exe temp.txt
#cat group_* submissions_* > temp.txt
#./process-rating.exe temp.txt 100 "all_info" > rating.txt
#parseUser "Richard_Try";
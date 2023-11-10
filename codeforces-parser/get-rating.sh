#!/bin/sh
LC_ALL="tt_RU";
domain="https://codeforces.com"
downloadLink() {
    while true
    do
        #sleep 5;
        link="$1"
        echo "link='$link'";
        if [ -e "temp.txt" ]
        then
            rm -rf "temp.txt"
        fi
        echo -e "\n~~~~~~~~~~~~~~ Codeforces Page Downloader ~~~~~~~~~~~~~~~"
        echo "Start downloading of page $link"
        curl "$link" -o "temp.txt"
        if [ -e "temp.txt" ]
        then
            echo "The content of $link has been downloaded";
            var=$(./search-in-file.exe "<h1>403 Forbidden</h1>" "temp.txt");
            if [ $var == "1" ]
            then
                echo -e "\n403 Forbidden. Will try in 60 seconds...\n";
                sleep 60;
            else
                var=$(./search-in-file.exe "Oops! Probably Codeforces can't be reached right now or your Internet connection is broken. You can try:" "temp.txt");
                if [ $var == "1" ]
                then
                    echo -e "\nOops! Probably Codeforces can't be reached right now or your Internet connection is broken.. Will try in 60 seconds...\n";
                    sleep 60;
                else
                    var=$(./search-in-file.exe "<head><title>Just a moment...</title>" "temp.txt");
                    if [ $var == "1" ]
                    then
                        echo -e "\nAnti-robot check... Will try in 60 seconds...\n";
                        sleep 60;
                    else
                        echo -e "\nSeems that the page is really downloaded...\n";
                        break;
                    fi
                fi
            fi
        else
            echo "Can't download $link";
            echo -e "Will try in 60 seconds...\n";
            sleep 60;
        fi
        echo -e "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    done
}

parseGroup() {
    groupId="$1"
    echo -e "\nStart parsing the group $groupId"
    if ! downloadLink "$domain/group/$groupId/contests?locale=ru"
    then
        return 1;
    fi
    echo "" > out.txt;
    for i in $(./group-contests.exe temp.txt h);
    do
        i=$(./get-link.exe "$i");
        var="1";
        while [ $var != "0" ]
        do
            link=$(./get-link.exe "$domain" "$i" "/status/page/" "$var" "?locale=ru");            
            ##echo "link='$link'";
            if ! downloadLink "$link"
            then
                return 1;
            fi
            var="$(./contest-status temp.txt $link)"
            var=$(./get-link.exe "$var")
            echo "var = '$var'"
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
    i=$(./get-link.exe "/submissions/" "$userName");
    link=$(./get-link.exe "$domain" "$i" "/page/" "$var" "?locale=ru");
    if ! downloadLink "$link"
    then
        return 1;
    fi
    temp="$(./user-status temp.txt $link save)"
    var=$(echo $temp | cut -d " " -f 1);
    maxPage=$(echo $temp | cut -d " " -f 2);
    addedFirst=$(echo $temp | cut -d " " -f 3);
    ignoredFirst=$(echo $temp | cut -d " " -f 4);
    
    var=$maxPage;
    i=$(./get-link.exe "/submissions/" "$userName");
    link=$(./get-link.exe "$domain" "$i" "/page/" "$var" "?locale=ru");
    if ! downloadLink "$link"
    then
        return 1;
    fi
    temp="$(./user-status temp.txt $link)"
    var=$(echo $temp | cut -d " " -f 1);
    maxPage=$(echo $temp | cut -d " " -f 2);
    addedLast=$(echo $temp | cut -d " " -f 3);
    ignoredLast=$(echo $temp | cut -d " " -f 4);
    notConsistent=0;
    if [ $addedLast != "0" ]
    then
        echo "not consistent";
        echo "addedLast=$addedLast";
        echo "ignoredLast=$ignoredLast";
        notConsistent=1;
    fi
    var="1";
    while [ $var != "done" ]
    do
        link=$(./get-link.exe "$domain" "$i" "/page/" "$var" "?locale=ru");
        if ! downloadLink "$link"
        then
            return 1;
        fi
        temp="$(./user-status temp.txt $link save)"
        var=$(echo $temp | cut -d " " -f 1);
        #var2=$(echo $temp | cut -d " " -f 2);
        added=$(echo $temp | cut -d " " -f 3);
        #ignored=$(echo $temp | cut -d " " -f 4);
        echo "added=$added"
        echo "notConsistent=$notConsistent"
        if [ $added == "0" ]
        then
            if [ $notConsistent == "0" ]
            then
                echo -e "Break, because file is consistent and there is no any update";
                break;
            fi
        fi
    done
    echo -e "Parsing of user $userName is done"
}

# может парсить только те группы, где в администрировании в параметрах
# политика регистрации зрителей выставлена в режи "автоматически"

#parseGroup "PZJYXH0KrS" # Курс начинающего олимпиадника
#parseGroup "dnpUeCC2dg" # Олимпиадное программирование by Слава Муравьёв
#parseGroup "uQw4LhzOcG" # Новое олимпиадное программирование в МИРЭА
#parseGroup "bcNLtajskz" # Курс по олимпиадному программированию
parseGroup "LB1sSRhotq" # Олимпиадное программирование в МИРЭА
parseGroup "XWOeQO4RLM" # Тренировки Самарских лицеев и школ
parseGroup "YnP1G037Yb" # Тренировки АСМ в Самаре
#cat group_* > temp.txt
#./process-rating.exe temp.txt 1000 "only_users" > users.txt
##./process-rating.exe temp.txt 1000 "all_info" > rating.txt
#echo dmkozyrev_thinks_slowly > users.txt
#for i in $(cat users.txt); do
#    parseUser "$i";
#done
##./process-rating.exe temp.txt
#cat group_* submissions_* > temp.txt
#./process-rating.exe temp.txt 100 "all_info" > rating.txt
#parseUser "Richard_Try";
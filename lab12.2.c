#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <locale.h>

//подсчет количества символов в строке с учетом UTF-8
int slen(char* str) {
    int len = 0;
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] < 0)
            i++;
        len++;
    }
    return len;
}

//печать строки по центру в рамке из 80 символов
void p_c(char* t) {
    int dl = 80;
    int len = slen(t);
    int i;

    if (len == 0) {
        for (i = 0; i < dl; i++)
            printf("*");
        printf("\n");
        return;
    }

    int total = dl - len;
    int left = total / 2;
    int right = total - left;

    for (i = 0; i < left; i++)
        printf("*");

    printf("%s", t);

    for (i = 0; i < right; i++)
        printf("*");

    printf("\n");
}

int main() {

    setlocale(LC_ALL, ".UTF8");

    struct tm* mytime;
    time_t t;

    t = time(NULL);
    mytime = localtime(&t);

    int total_min = mytime->tm_hour * 60 + mytime->tm_min;
    int dif_min = total_min - (8 * 60 + 30);

    if (dif_min < 0)
        dif_min = 0;

    //массивы для вывода дней недели и месяцев
    char* days[] = { "Воскресенье", "Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота" };
    char* months[] = { "января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря" };
    int months_day[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    char* r_months[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "XI", "XII" };

    //проверка на високосный год
    int year = mytime->tm_year + 1900;
    int is_vis = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_vis)
        months_day[1] = 29;

    char* season;
    char b[256];

    //определение времени года
    if (mytime->tm_mon == 11 || mytime->tm_mon == 0 || mytime->tm_mon == 1)
        season = "зима";
    else if (mytime->tm_mon >= 2 && mytime->tm_mon <= 4)
        season = "весна";
    else if (mytime->tm_mon >= 5 && mytime->tm_mon <= 7)
        season = "лето";
    else
        season = "осень";

    p_c("");

    sprintf(b, "Московское время %02d:%02d:%02d", mytime->tm_hour, mytime->tm_min, mytime->tm_sec);
    p_c(b);

    sprintf(b, "День недели - %s", days[mytime->tm_wday]);
    p_c(b);

    sprintf(b, "%02d.%02d.%d", mytime->tm_mday, mytime->tm_mon + 1, year);
    p_c(b);

    sprintf(b, "%d %s", mytime->tm_mday, months[mytime->tm_mon]);
    p_c(b);

    sprintf(b, "Сегодня %d-й день %d года", mytime->tm_yday + 1, year);
    p_c(b);

    if (mytime->tm_wday == 0) {
        sprintf(b, "Сегодня воскресенье");
        p_c(b);
    }
    else {
        int do_min = (6 - mytime->tm_wday) * 24 * 60 + (24 * 60 - total_min);
        sprintf(b, "До воскресенья осталось %d дней и %d часов", do_min / (24 * 60), do_min / 60 % 24);
        p_c(b);
    }

    sprintf(b, "С первой пары прошло %d часов %d минут", dif_min / 60, dif_min % 60);
    p_c(b);

    sprintf(b, "До Нового года осталось %d месяцев и %d дней", 11 - mytime->tm_mon, months_day[mytime->tm_mon] - mytime->tm_mday);
    p_c(b);

    //определение времени окончания текущей пары
    int end_sec = 0;

    if (total_min >= 510 && total_min < 605)
        end_sec = (10 * 60 + 5) * 60;
    else if (total_min >= 615 && total_min < 710)
        end_sec = (11 * 60 + 50) * 60;
    else if (total_min >= 720 && total_min < 815)
        end_sec = (13 * 60 + 35) * 60;
    else if (total_min >= 860 && total_min < 955)
        end_sec = (15 * 60 + 55) * 60;
    else if (total_min >= 965 && total_min < 1060)
        end_sec = (17 * 60 + 40) * 60;

    if (end_sec == 0) {
        sprintf(b, "Пары закончились или не начались");
        p_c(b);
    }
    else {
        int tek_sec = total_min * 60 + mytime->tm_sec;
        sprintf(b, "До конца пары осталось %d минут и %d секунд", (end_sec - tek_sec) / 60, (end_sec - tek_sec) % 60);
        p_c(b);
    }

    sprintf(b, "До конца месяца осталось %d дней, до конца года - %d месяцев", months_day[mytime->tm_mon] - mytime->tm_mday, 11 - mytime->tm_mon);
    p_c(b);

    sprintf(b, "Месяц %s и год %d", r_months[mytime->tm_mon], year);
    p_c(b);

    sprintf(b, "Время года - %s, последние 2 цифры года - %02d", season, year % 100);
    p_c(b);

    //расчет текущего дня зимы или осени
    if (mytime->tm_mon == 11 || mytime->tm_mon == 0 || mytime->tm_mon == 1) {
        int z_day;
        if (mytime->tm_mon == 11)
            z_day = mytime->tm_mday;
        else
            z_day = 31 + mytime->tm_yday + 1;

        sprintf(b, "Идет %d день зимы", z_day);
        p_c(b);
    }
    else if (mytime->tm_mon >= 8 && mytime->tm_mon <= 10) {
        int o_day = mytime->tm_yday - (243 + is_vis) + 1;
        sprintf(b, "Идет %d день осени", o_day);
        p_c(b);
    }

    p_c("");

    return 0;
}

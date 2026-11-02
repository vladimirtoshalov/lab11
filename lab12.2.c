#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <locale.h>

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

   

    printf("Московское время %02d:%02d:%02d\n", mytime->tm_hour, mytime->tm_min, mytime->tm_sec);
    

    printf("День недели - %s\n", days[mytime->tm_wday]);
    

    printf("%02d.%02d.%d\n", mytime->tm_mday, mytime->tm_mon + 1, year);
    

    printf("%d %s\n", mytime->tm_mday, months[mytime->tm_mon]);
    

    printf("Сегодня %d-й день %d года\n", mytime->tm_yday + 1, year);
    

    if (mytime->tm_wday == 0) {
        printf("Сегодня воскресенье\n");
        
    }
    else {
        int do_min = (6 - mytime->tm_wday) * 24 * 60 + (24 * 60 - total_min);
        printf("До воскресенья осталось %d дней и %d часов\n", do_min / (24 * 60), do_min / 60 % 24);
        
    }

    printf("С первой пары прошло %d часов %d минут\n", dif_min / 60, dif_min % 60);
   

    printf("До Нового года осталось %d месяцев и %d дней\n", 11 - mytime->tm_mon, months_day[mytime->tm_mon] - mytime->tm_mday);
    

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
        printf("Пары закончились или не начались\n");
        
    }
    else {
        int tek_sec = total_min * 60 + mytime->tm_sec;
        printf("До конца пары осталось %d минут и %d секунд\n", (end_sec - tek_sec) / 60, (end_sec - tek_sec) % 60);
        
    }

    printf("До конца месяца осталось %d дней, до конца года - %d месяцев\n", months_day[mytime->tm_mon] - mytime->tm_mday, 11 - mytime->tm_mon);
    

    printf("Месяц %s и год %d\n", r_months[mytime->tm_mon], year);
    

    printf("Время года - %s, последние 2 цифры года - %02d\n", season, year % 100);
    

    //расчет текущего дня зимы или осени
    if (mytime->tm_mon == 11 || mytime->tm_mon == 0 || mytime->tm_mon == 1) {
        int z_day;
        if (mytime->tm_mon == 11)
            z_day = mytime->tm_mday;
        else
            z_day = 31 + mytime->tm_yday + 1;

        printf(b, "Идет %d день зимы\n", z_day);
        
    }
    else if (mytime->tm_mon >= 8 && mytime->tm_mon <= 10) {
        int o_day = mytime->tm_yday - (243 + is_vis) + 1;
        printf(b, "Идет %d день осени\n", o_day);
        
    }



    return 0;
}

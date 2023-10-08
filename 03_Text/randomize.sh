#!/bin/dash

DELAY=${1:-0.05}

# Чтение ASCII-арт из стандартного ввода и сохранение его во временный файл
TMPFILE=$(mktemp)
cat > "$TMPFILE"

# Создание временного файла для хранения координат и символов
TMP_COORDS=$(mktemp)

# Разбор ASCII-арт на символы и их координаты
LINE_NUM=0
while IFS= read -r LINE; do
    COL_NUM=0
    echo "$LINE" | sed -e 's/\(.\)/\1\n/g' | while IFS= read -r CHAR; do
        echo "$LINE_NUM $COL_NUM $CHAR" >> "$TMP_COORDS"
        COL_NUM=$((COL_NUM + 1))
    done
    LINE_NUM=$((LINE_NUM + 1))
done < "$TMPFILE"

# Перемешивание строк в файле с координатами
shuf "$TMP_COORDS" -o "$TMP_COORDS"

# Очистка экрана
tput clear

# Вывод символов в случайном порядке
while IFS=' ' read -r ROW COL CHAR; do
    tput cup $ROW $COL
    echo -n "$CHAR"
    sleep "$DELAY"
done < "$TMP_COORDS"

# Удаление временных файлов и очистка экрана
rm "$TMPFILE" "$TMP_COORDS"
tput clear

# Последовательность команд запуска проекта

```bash
git clean -fd
autoreconf -fisv
./configure --prefix /tmp/qq
make all install
/tmp/qq/bin/number_guesser - для запуска на русской локали (локаль по умолчанию)
LC_ALL=C /tmp/qq/bin/number_guesser - для запуска на английской локали
```

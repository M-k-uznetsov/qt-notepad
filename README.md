# Текстовый редактор средствами Qt.

Используя функционал Qt, разработан текстовый редактор с поддержкой расцветки синтаксиса.

## Часть 1

1.	Предоставлена возможность открытия нескольких файлов посредством использования виджета вкладок (`QTabWidget`).
2.	Редактор производит анализ расширения файлов при открытии. 
    Если файл имеет расширение файлов исходных кодов программ (например, .h, .cpp или .hpp – расширения файлов исходных кодов программ на C++),
    то при открытии выполняется расцветка синтаксиса с использованием класса `QSyntaxHighlighter`.
3.	Все расцветки зарегистрированы в xml-файле настроек приложения. 
    В данном файле регистрируются расширения файлов для данного языка программирования и
    соответствующие ключевые слова и регулярные выражения. В программе предоставлена расцветка синтаксиса C++.
    Пример xml-файла настроек редактора:

```xml
<?xml version="1.0" encoding="utf-8"?>

<settings>
    <syntaxes>

        <syntax id = "python"
                name = "Язык программирования Python"
                ext_list="py">

            <!-- Ключевые слова -->

            <rule>
                <pattern value = "\bclass\b"/>
                <format foreground="#00008B" font_weight="75"/>
            </rule>

            <!-- Однострочный комментарий -->

            <rule>
                <pattern value = "#[^\n]*"/>
                <format foreground="#008000" font_weight="75"/>
           </rule>

        </syntax>

    </syntaxes >
</settings>
```

## Часть 2

4.	Реализовано меню (`QMenu`), содержащее следующие пункты:
    * Файл: 
        + Новый (Создание нового документа)
        + Открыть (Открытие существующего документа на основе `QFileDialog`)
        + Сохранить (Сохранение документа из активной вкладки)
        + Сохранить как… (Сохранение в заданном формате на основе `QFileDialog`)
        + Сохранить все (Сохранить все открытые документы)
        + Закрыть (Закрыть текущий документ)
        + Закрыть все (Закрытие всех открытых документов)
        + Выход (Закрыть редактор с диалогом сохранения несохраненных документов)
    * Правка:
        + Вырезать
        + Копировать
        + Вставить
        + Удалить
        + Выделить все
    * Вид:
        + Показать проводник (Создание обозревателя каталогов с использованием `QDockWidget` и `QFileSystemModel`.
          При выборе документа в обозревателе открывать документ в новой вкладке.)
        + Показать обозреватель открытых документов (Создание обозревателя открытых документов на основе `QDockWidget` и
          `QStringListModel`. При щелчке по имени документа должна становиться активной его вкладка.)
5.	Перед закрытием приложения выводится сообщение с предложением сохранить измененные документ(-ы).
    Окно сообщения разработано на основе классов `QDialog` и `QTableWidget`.
    В первом столбце таблицы выводится имя файла, во втором - его расположение.
    При закрытии отдельной вкладки предлагается сохранение изменённого файла с использованием диалогового окна сообщений (`QMessageBox`).
6.	Возможные ошибки обрабатываются выводом окна критических сообщений.
7.	Для открытия и сохранения файлов используется стандартное диалоговое окно выбора файлов (`QFileDialog`).
 



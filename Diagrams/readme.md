# Что находится в данной директории?
Тут находятся диаграммы и их исходный код (PlantUML), которые описывают основное поведение системы, объектов системы между собой и возможные действия пользователей.
* Файл `case.wsd`, содержит исходный код диаграммы прецедентов, эта диаграмма указана ниже. Из нее мы выделим следующие основные прецеденты:
    * Авторизация
    * Заказ ремонтной работы
    * Посмотреть описание заказа (со стороны рабочего)
    * Заверишть заказ
    * Добавить пользователя
* Файл `ER.wsd`, содержит исходный код ER-диаграммы, в которой описывается структура хранения сущностей в базе данных, их связи и ограничения
* Папка `suitability` содержит диаграммы пригодности для основных прецедентов 
* Папка `sequences` содержит диаграммы последовательности для основных прецедентов
* Папка `classes` содержит диаграммы классов, разделенных на три категории, в зависимости от роли пользователя:
    * Диаграммы классов **Клиента**
    * Диаграммы классов **Рабочего**
    * Диаграммы классов **Администратора**

Описание диаграмм находится в соответствующих папках
## Диаграмма прецедентов
![case diagram](https://www.plantuml.com/plantuml/svg/1C6z4O0W30RGFbDa1JjBAnTmWXm4pF435puQf_UzQq4SkrKEifIeQW9Zi5j-mT5S0snqebMiJt5f73N9hhX7nsEVyd4IJGb5ilBVIXMifWu5qNs-ukBgkV0N7lqLKHVILi4ANPH2Z4WB2hee5BgffJzm6n9oJKpw2sV-g3CEGHig8QLW5C-SS-RScQjuGq41-JH7X1mEAPovyupfzgRZYMbX2uiFvZnmRTSotHjpEvvS3YOdb0rBzt0YfvcOmLB04lz0x_QlXoFltlDQU476j1Wv1OTIxseu64qz_J2Tpd_p3wyid66lgH3p-yemy2dUA90QGQKkBlmiQI6GXWmC7By4Mi0AZ9HPCVaQJS_N_jxnMLZy9B3QhT80yKa3MbRKJoYuOX72gLhQMEIIjTtqQ3EsAJH_QPCo45QCDWXrm718fAx9MRDkUxgUigLmaDDQwWP9UTGAhJOP8c4mFcTGXrwQQOB6XhePX_2tTcnM8EAlClzSuy4PDapak7zhMfmknDAYOYLNA9HhHezmvqTTkxl3R-NdYwNHCbeTLOYHLLNlY5YJDT9i6OpAXP2lr0RwkcMViU5dTpIgdOrtCHZr-N_l2m00)
## ER-Диаграмма
![ER diagram](https://www.plantuml.com/plantuml/svg/jLLRJzim57xthpYFCANInDiYJQA2eA6nZcMj44-L6n-eLLyYNu2ktNyVSPrYDQHTfUtDzNVfvtFiatFhg75U2YXAGko2gveQAe7X0_N2NMdbVl9V26SV2K7bk5k2jsWih0W0PpbOD9mAk2sllmtBU_XQtCFe-nX6aviR0Z0O40159URWyCMbaD2FNCNjoUZwnwH8qPfQ-wmDw-gC5fY74DDc-GRzRWDAMisvmgbRrdXqq6wYQBxhFZDKiVzdBwbP7ENUd3O7hXm-eadH4BIBH5sCSjB8imttj1ld7_HRFoiqxyPeZdemNv1dmJlDPz4yyMfllhyeFm3pXZgkrLHgvURsrKTI8RXoxv8ONHwYpBKtXpYIA--mXrKRNc4E32l-Yfvyok3iz0tlLc1pOuveKnGUrPB-ElMNPqzLzXQZfmOxzoAU8WkHqvkX3JjoJZ7gS1hcOHxMMm9S5bV3oSqOBYPbMOp6qylXk6W5g5YaHrRhMMbP2tIOmqnhWLHr_HweiDWOeQqChntNSI9slBnrMlQy7tp1oZkTW3lg-8YxuWEt8Arpco1htR9MUWftNugoI4uCd-F9GZUyJARrAaxmu7whhUKpWV14XKSR_ku3N0YEoeNbdJOBD64vP9Ahnf0qPdQz7WpqQkkRRcuQJxQJQxCBwM3jea5FWZJiwTNsOP5K6S7q6tE04KPgXw87wzNEqoNnPmzApb4nByKV)
Примечания:
* Все сущности связаны между собой ключом Foreign Key
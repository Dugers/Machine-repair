# Что находится в данной директории?
Тут находятся файлы с исходным кодом приложения
## Файлы
* `authwindow.*` представляет основное окно, в котором выполняется авторизация, а также можно загрузить/сохранить/сбросить данные приложения
* `config.h` импортируется для получения настроек из `config.ini` (переименуйте `config_example.ini`->`config.ini` и введите свои настройки)
* `confirmationdialog.*` представляет диалоговое окно для подтверждения
* `permissioncontroller.*` представляет из себя шаблонный класс, который выполняет авторизацию пользователя (проверяет права пользователя на совершение действия) и хранит id пользователя
* `main.cpp` содержит в себе точку входа
## Папки
* В папке `admin` находятся классы и ui окон, с которыми взаимодействует пользователь с ролью **администратор**
* В папке `worker` находятся классы и ui окон, с которыми взаимодействует пользователь с ролью **работник**
* В папке `client` находятся классы и ui окон, с которыми взаимодействует пользователь с ролью **клиент**
* В папке `entities` находятся классы, которые представляют сущности, хранящиеся вне приложения
* В папке `models` находятся функции, которые предоставляют API к базе данных. Также там находится `base_dump.sql`, который можно использовать для загрузки начальных данных
* В папке `tools` находятся вспомогательные функции и макросы
## Подробнее о некоторых файлах
### `permissioncontroller.*`
Данный шаблонный класс принимает в качестве шаблонного параметра роль, которой должен соответствовать пользователь

Чтобы его использовать, просто унаследуйтесь от этого класса с указанием соответствующей роли и передайте **id пользователя** в конструктор `PermissionController` класса
```c++
class SomeClass :
    PermissionController<UserRole::Admin>
{
    SomeClass(int user_id) :
        PermissionController<UserRole::Admin>{user_id}
    {}
    // some code
};
```

Для выолнения авторизации вызовете метод `confirm()`
```c++
class DeleteUser :
    PermissionController<UserRole::Admin>
{
    DeleteUser(int user_id, int deleted_user_id) :
        PermissionController<UserRole::Admin>{user_id}
    {/*some code*/}
    void delete_user(int deleted_user_id) const {
        confirm();
        db::delete_user(deleted_user_id);
    }
    // some code
};
```
Вы также можете переопределить метод `confirm()` полностью или добавить дополнительные проверки
```c++
class DeleteUser
    PermissionController<UserRole::Admin>
{
    //some code
    void confirm() override {
        if (user_id() % 7 != 0)
            throw permission_error{"the user hasn't a beautiful id"};
        return PermissionController<UserRole::Admin>::confirm();
    }
}
```
Класс `PermissionController` также предоставляет метод для получения id пользователя `user_id()`

При неудачной авторизации будет выброшено исключение `permission_error` (унаследованное от `std::runtime_error`)